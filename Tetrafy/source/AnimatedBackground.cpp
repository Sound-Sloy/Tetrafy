#include "AnimatedBackground.h"

AnimatedBackground::AnimatedBackground(float guiScale)
{
	std::vector<TetrominosE_Shadow> tetrominos = { TetrominosE_Shadow::Straight,
		TetrominosE_Shadow::Tee,
		TetrominosE_Shadow::El,
		TetrominosE_Shadow::Jay,
		TetrominosE_Shadow::LeftZigZag,
		TetrominosE_Shadow::RightZigZag,
		TetrominosE_Shadow::Square
	};

	int32_t cellSize = static_cast<int32_t>(floor(32 * guiScale));

	for(auto tet : tetrominos) {
		const Vec2<int32_t> spriteSize = TetrominoSprite_Shadow::GetSpriteSize(tet, cellSize, C_SPACING);

		RenderTexture2D tex = LoadRenderTexture(spriteSize.GetX(), spriteSize.GetY());

		BeginTextureMode(tex);

		TetrominoSprite_Shadow::DrawSprite(tet, cellSize, C_SPACING);

		EndTextureMode();

		m_Textures.push_back(std::make_shared<Texture2D>(tex.texture));

	}

	std::uniform_int_distribution<int32_t> distribution(10, 18);
	int32_t elementCount = distribution(m_RNG);

	std::uniform_int_distribution<int32_t> texDistribution(0, m_Textures.size() - 1);
	std::uniform_real_distribution<float> angDistribution(0.f, 2 * PI);
	std::uniform_int_distribution<int32_t> posDistributionX(0, GetRenderWidth());
	std::uniform_int_distribution<int32_t> posDistributionY(0, GetRenderHeight());

	for(int32_t i = 0; i < elementCount; ++i) {
		m_Elements.emplace_back(m_Textures.at(texDistribution(m_RNG)), angDistribution(m_RNG), Vec2(posDistributionX(m_RNG), posDistributionY(m_RNG)));
	}

}

AnimatedBackground::~AnimatedBackground()
{
	for(auto& texture : m_Textures) {
		UnloadTexture(*texture.get());
	}
}

void AnimatedBackground::Update(float deltaTime)
{
	for (auto& element : m_Elements) {
		element.Update(deltaTime);
	}
}

void AnimatedBackground::Draw()
{
	for (auto& element : m_Elements) {
		element.Draw(C_COLOR);
	}
}

AnimatedBackground::Element::Element(std::weak_ptr<Texture2D> texture, float rotationRad, Vec2<int32_t> pos) :
	m_Texture(texture), m_Rotation(rotationRad), m_Pos(Vec2{(float)pos.GetX(), (float)pos.GetY()})
{
	m_bInitialized = true;
	if (!m_Texture.lock()) {
		m_bInitialized = false;
		return;
	}

	if(!IsTextureValid(*m_Texture.lock())) {
		m_bInitialized = false;
		return;
	}

	m_PosLastFrame = m_Pos;
	m_RotationLastFrame = m_Rotation;
	this->GenerateGoal();
}

void AnimatedBackground::Element::Update(float deltaTime)
{
	if(!m_bInitialized or !m_Texture.lock()) {
		return;
	}

	if(m_bAchievedGoal) {
		GenerateGoal();
		m_bAchievedGoal = false;
	}
	else {
		if(CheckGoalCompletion()) {
			m_bAchievedGoal = true;
			return;
		}
	}

	m_TimeSinceGoalGen += deltaTime;

	m_PosLastFrame = m_Pos;

	Vec2<float> moveVecDT = Vec2<float>(m_GoalMoveVector.GetX() * C_MOVE_SPEED * deltaTime, m_GoalMoveVector.GetY() * C_MOVE_SPEED * deltaTime); // Vec2 * float will cast to Vec2 * int ...

	m_Pos = m_Pos + moveVecDT;
	m_RotationLastFrame = m_Rotation;
	m_Rotation = m_Rotation + m_RotationSpeed * deltaTime;
}

void AnimatedBackground::Element::Draw(Color col) const
{
	if (!m_bInitialized or !m_Texture.lock()) {
		return;
	}

	DrawTextureEx(*m_Texture.lock(), m_Pos, m_Rotation, 1.f, col);
}

void AnimatedBackground::Element::GenerateGoal()
{
	std::uniform_real_distribution<float> distRotation(-PI / 4, PI / 4);
	float angle = distRotation(m_RNG);
	m_GoalRotation = m_Rotation + angle;
	m_GoalRotationSign = angle > 0 ? 1.f : -1.f;

	std::uniform_int_distribution<int32_t> distDistance(30, 150);
	std::uniform_real_distribution<float> distVectorXY(-1, 1);


	int32_t distance = distDistance(m_RNG);

	m_GoalMoveVector = Vec2(distVectorXY(m_RNG), distVectorXY(m_RNG)).Normalize();
	m_GoalPos = m_GoalPos + m_GoalMoveVector * distance;

	// compute speeds
	float moveTime = static_cast<float>(distance) / C_MOVE_SPEED;
	m_NeededTime = moveTime;
	m_RotationSpeed = angle / moveTime;
	printf("moveTime: %f\n", moveTime);


	m_PosLastFrame = m_Pos;
	m_RotationLastFrame = m_Rotation;

	m_TimeSinceGoalGen = 0.f;

	m_bAchievedGoal = false;
}

bool AnimatedBackground::Element::CheckGoalCompletion() const
{

	return m_TimeSinceGoalGen >= m_NeededTime;


	// TODO Make this work with positions and rotations

	float angMin = std::min(m_Rotation, m_RotationLastFrame);
	float angMax = std::max(m_Rotation, m_RotationLastFrame);
	if(!(m_GoalRotation >= angMin and m_GoalRotation <= angMax)) {
		return false;
	}

	Vector2 posMin = { std::min(m_Pos.GetX(), m_PosLastFrame.GetX()), std::min(m_Pos.GetY(), m_PosLastFrame.GetY()) };
	Vector2 posMax = { std::max(m_Pos.GetX(), m_PosLastFrame.GetX()), std::max(m_Pos.GetY(), m_PosLastFrame.GetY()) };
	if(!CheckCollisionPointLine(m_GoalPos, posMin, posMax, 30)) {
		return false;
	}

	return true;
}

void AnimatedBackground::TetrominoSprite_Shadow::DrawSprite(TetrominosE_Shadow shape, int32_t cellSize, int32_t padding)
{
	const Vec2<int32_t> matSize = TetrominoSprite_Shadow::GetSpriteMatSize(shape);
	const Vec2<int32_t> spriteSize = TetrominoSprite_Shadow::GetSpriteSize(shape, cellSize, C_SPACING);

	for (int32_t i = 0; i < matSize.GetX() * matSize.GetY(); ++i) {
		if (!spriteMatrices[shape][i]) {
			continue;
		}
		int32_t cX = i % matSize.GetX();
		int32_t cY = i / matSize.GetX();

		DrawRectangleLinesEx(Rectangle{ (float)(cX * (cellSize + C_SPACING)),
			(float)(cY * (cellSize + C_SPACING)),
			(float)cellSize, (float)cellSize, }, 2,
			WHITE);
	}
}
