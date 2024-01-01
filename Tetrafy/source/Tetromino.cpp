#include "Tetromino.h"

void TetrominoSprite::DrawSprite(TetrominosE shape, Vec2<int32_t> pos, int32_t cellSize, int32_t padding) {
	const Vec2<int32_t> matSize = TetrominoSprite::GetSpriteMatSize(shape);
	const Vec2<int32_t> spriteSize = TetrominoSprite::GetSpriteSize(shape, cellSize, padding);
	const int32_t initialPosX = pos.GetX() - spriteSize.GetX() / 2;
	const int32_t initialPosY = pos.GetY();

	for (int32_t i = 0; i < matSize.GetX() * matSize.GetY(); ++i) {
		if (!spriteMatrices[shape][i]) {
			continue;
		}
		int32_t cX = i % matSize.GetX();
		int32_t cY = i / matSize.GetX();

		DrawRectangle(initialPosX + cX * (cellSize + padding),
			initialPosY + cY * (cellSize + padding),
			cellSize, cellSize, 
			TetrominoSprite::GetTetrominoColor(shape));
	}
}


Tetromino::Tetromino(TetrominosE shape, Vec2<int32_t> gridSize, int32_t cellSize, std::vector<Cell>& cells)
	:
	m_Shape(shape),
	m_GridSize(gridSize),
	m_CellSize(cellSize),
	m_Cells(cells)
{
	this->m_Shape = shape;

	this->m_Padding = cells.front().GetPadding();

	this->m_Color = TetrominoSprite::GetTetrominoColor(shape);
	this->m_Matrix = TetrominoSprite::GetShapeMatrix(shape);
	this->m_SpriteSize = TetrominoSprite::GetSpriteSize(shape, cellSize, this->m_Padding);
	this->m_SpriteMatSize = TetrominoSprite::GetSpriteMatSize(shape);

	this->m_Pos = Vec2<int32_t>((gridSize.GetX() - GetMatrixSizeXAxes()) / 2, 0);
}

Tetromino::~Tetromino() {}

int32_t Tetromino::GetMatrixSizeXAxes() const
{
	if (this->m_Matrix.size() == 16) return 4;
	if (this->m_Matrix.size() == 9) return 3;
	if (this->m_Matrix.size() == 4) return 2;
	return 0;
}

int32_t Tetromino::_LiniarPosFrom2D(int32_t row, int32_t column) const {
	return row * this->m_GridSize.GetX() + column;
}

void Tetromino::PlaceTetrominoInsideBounds() {
	for (int32_t i = 0; i < this->m_Matrix.size(); ++i) {
		int32_t xComponent = i % GetMatrixSizeXAxes();

		//If the piece has at least one cell outside of the board, move it in the corresponding direction
		if (this->m_Pos.GetX() + xComponent < 0) {
			MoveRight();
		}
		else if (this->m_Pos.GetX() + xComponent >= this->m_GridSize.GetX()) {
			MoveLeft();
		}
	}
}


void Tetromino::Rotate(TetrominoRotation direction)
{
	if (this->m_Shape == TetrominosE::Square) {
		return;
	}

	int32_t matSizeX = this->GetMatrixSizeXAxes();
	std::vector<bool> result(this->m_Matrix.size());

	switch (direction) {
	case TetrominoRotation::Clockwise: {
		for (int32_t iY = 0; iY < matSizeX; iY++) {
			for (int32_t iX = 0; iX < matSizeX; iX++) {
				result[iY * matSizeX + iX] = this->m_Matrix[(matSizeX - iX - 1) * matSizeX + iY];
			}
		}
		break;
	}
	case TetrominoRotation::Counterclockwise: {
		for (int32_t iY = 0; iY < matSizeX; iY++) {
			for (int32_t iX = 0; iX < matSizeX; iX++) {
				result[iY * matSizeX + iX] = this->m_Matrix[iX * matSizeX + (matSizeX - iY - 1)];
			}
		}
		break;
	}
	}

	bool collided = false;
	for (int32_t i = 0; i < result.size(); ++i) {
		if (!result[i]) {
			continue;
		}
		int32_t eX = this->m_Pos.GetX() + i % GetMatrixSizeXAxes();
		int32_t eY = this->m_Pos.GetY() + i / GetMatrixSizeXAxes();

		int32_t cellID = _LiniarPosFrom2D(eY, eX);
		if (cellID < 0 or cellID >= m_Cells.size()) {
			//TraceLog(LOG_FATAL, "CellID out of bounds (Tetromino::Rotate)");
			continue;
		}

		if (m_Cells[cellID].IsShown()) {
			collided = true;
			break;
		}
	}

	if (!collided) {
		this->m_Matrix = result;
	}
	PlaceTetrominoInsideBounds();
}

void Tetromino::MoveLeft() {
	int32_t leftmostPos = m_GridSize.GetX();
	for (int32_t i = 0; i < m_Matrix.size(); ++i) {
		if (!m_Matrix[i]) {
			continue;
		}
		
		int32_t eX = m_Pos.GetX() + i % GetMatrixSizeXAxes();
		int32_t eY = m_Pos.GetY() + i / GetMatrixSizeXAxes();
		
		leftmostPos = std::min(leftmostPos, eX);
		if (leftmostPos <= 0) {
			return;
		}
	
		int32_t cellID = _LiniarPosFrom2D(eY, eX - 1);
		if (cellID < 0 or cellID >= m_Cells.size()) {
			continue;
		}

		if (m_Cells[cellID].IsShown()) {
			return;
		}
	}

	this->m_Pos += Vec2(-1, 0);
}

void Tetromino::MoveRight() {
	int32_t rightmostPos = 0;
	for (int32_t i = 0; i < m_Matrix.size(); ++i) {
		if (!m_Matrix[i]) {
			continue;
		}

		int32_t eX = m_Pos.GetX() + i % GetMatrixSizeXAxes();
		int32_t eY = m_Pos.GetY() + i / GetMatrixSizeXAxes();
		
		rightmostPos = std::max(rightmostPos, eX);
		if (rightmostPos >= this->m_GridSize.GetX() - 1) {
			return;
		}

		int32_t cellID = _LiniarPosFrom2D(eY, eX + 1);
		if (cellID < 0 or cellID >= m_Cells.size()) {
			continue;
		}

		if (m_Cells[cellID].IsShown()) {
			return;
		}
	}

	this->m_Pos += Vec2(1, 0);
}

void Tetromino::Update(float deltaTime, int32_t level) {
	if (this->m_bSolid) {
		return;
	}

	if (CanBeSolidified()) {
		Solidify();
		//return;
	}
	else {
		m_bInSolidification = false;
		m_SolidificationTimer = 2.f;
	}


	if (IsKeyPressed(Globals::Options.KeyRotateCW)) {
		this->Rotate(TetrominoRotation::Clockwise);
	}
	if (IsKeyPressed(Globals::Options.KeyRotateCCW)) {
		this->Rotate(TetrominoRotation::Counterclockwise);
	}

	if (Globals::KeyboardManager.IsKeyPressedRepeated(Globals::Options.KeyLeft)) {
		this->MoveLeft();
	}
	else if (Globals::KeyboardManager.IsKeyPressedRepeated(Globals::Options.KeyRight)) {
		this->MoveRight();
	}
	
	// Soft drop
	float speed = this->m_DownSpeed + this->m_DownSpeed * 0.3 * (level - 1);
	bool softdropping = false;
	if (Globals::Options.SoftDropToggle and IsKeyDown(Globals::Options.KeySoftDrop)) {
		speed = speed * m_SoftDropMultiplier;
		softdropping = true;
	}
	// ---

	// Hard drop
	if (Globals::Options.HardDropToggle and IsKeyPressed(Globals::Options.KeyHardDrop) and !m_bInSolidification) {
		Vec2<int32_t> landingPos = GetLandingPos();
		this->m_ScoreAccumulated += 2 * (landingPos.GetY() - this->m_Pos.GetY());
		this->m_Pos = landingPos;
		m_SolidificationTimer = 0.f;
		return;
	}
	// ---

	this->m_RealDistanceToGoDown += deltaTime * speed;

	if (this->m_RealDistanceToGoDown < this->m_CellSize) {
		this->m_GhostPos = GetLandingPos();
		return;
	}

	this->m_RealDistanceToGoDown = 0;

	if (!m_bInSolidification) {
		this->m_Pos += Vec2(0, 1);
		this->m_SolidificationTimer = 2.f;
	}

	// If tetromino is soft dropping
	if (softdropping) {
		this->m_ScoreAccumulated++;
	}
	this->m_GhostPos = GetLandingPos();

}


void Tetromino::Draw() {
	if (this->m_bSolid) {
		return;
	}
	for (int32_t i = 0; i < this->m_Matrix.size(); ++i) {
		if (!this->m_Matrix[i]) {
			continue;
		}
		int32_t eX = this->m_Pos.GetX() + (i % this->GetMatrixSizeXAxes());
		int32_t eY = this->m_Pos.GetY() + (i / this->GetMatrixSizeXAxes());

		int32_t cellID = _LiniarPosFrom2D(eY, eX);
		if (cellID >= m_Cells.size()) {
			std::cout << "Uhh? Tetromino::Draw(void) >>> cellID out of bounds\n";
			return;
		}
		m_Cells[cellID].SetVirtual(true);
		m_Cells[cellID].SetVirtualColor(this->m_Color);
	}
	DrawGhost();
}


Vec2<int32_t> Tetromino::GetLandingPos() const
{
	int32_t collidedY = -1;
	int32_t lastRowY = -1;
	for (int32_t iY = this->m_Pos.GetY(); iY < this->m_GridSize.GetY(); ++iY) {
		for (int32_t i = 0; i < this->m_Matrix.size(); ++i) {
			if (!this->m_Matrix[i]) {
				continue;
			}
			const int32_t eX = this->m_Pos.GetX() + (i % GetMatrixSizeXAxes());
			const int32_t eY = iY + (i / GetMatrixSizeXAxes());

			const int32_t cellID = _LiniarPosFrom2D(eY, eX);

			if (cellID >= m_Cells.size()) {
				continue;
			}

			if (m_Cells[cellID].IsShown() and collidedY == -1) {
				collidedY = iY - 1;
				continue;
			}

			if (eY == this->m_GridSize.GetY() - 1 and lastRowY == -1) {
				lastRowY = iY;
			}
		}
	}

	if (collidedY == -1 or collidedY >= lastRowY) {
		return { this->m_Pos.GetX(), lastRowY };
	}
	return { this->m_Pos.GetX(), collidedY };
}

void Tetromino::DrawGhost()
{
	if (this->m_bSolid or !Globals::Options.LandingPreviewToggle) {
		return;
	}

	for (int32_t i = 0; i < this->m_Matrix.size(); ++i) {
		if (!this->m_Matrix[i]) {
			continue;
		}
		int32_t eX = this->m_GhostPos.GetX() + (i % this->GetMatrixSizeXAxes());
		int32_t eY = this->m_GhostPos.GetY() + (i / this->GetMatrixSizeXAxes());

		int32_t cellID = _LiniarPosFrom2D(eY, eX);
		if (cellID >= m_Cells.size()) {
			//std::cout << "Uhh? Tetromino::DrawGhost(void) >>> cellID out of bounds\n";
			return;  
		}
		
		m_Cells[cellID].SetGhost(true);
		m_Cells[cellID].SetGhostColor(this->m_Color);
	}
}

bool Tetromino::CanBeSolidified()
{
	int32_t lowermostPos = 0;
	for (int32_t i = 0; i < m_Matrix.size(); ++i) {
		if (!m_Matrix[i]) {
			continue;
		}

		int32_t eX = m_Pos.GetX() + i % GetMatrixSizeXAxes();
		int32_t eY = m_Pos.GetY() + i / GetMatrixSizeXAxes();

		lowermostPos = std::max(lowermostPos, eY);
		if (lowermostPos >= m_GridSize.GetY() - 1) {
			return true;
		}

		int32_t cellID = _LiniarPosFrom2D(eY + 1, eX); // The cell under the current cell from the matrix
		if (cellID < 0 or cellID >= m_Cells.size()) {
			TraceLog(LOG_FATAL, "Tetromino::CanBeSolidified(void) >>> cellID out of bounds");
			return false;
		}
		
		if (m_Cells[cellID].IsShown()) {
			return true;
		}
	}
	return false;
}

void Tetromino::Solidify() {
	if (this->m_bSolid) {
		return;
	}

	m_bInSolidification = true;
	m_SolidificationTimer -= GetFrameTime();

	for (int32_t i = 0; i < m_Matrix.size(); ++i) {
		if (!m_Matrix[i]) {
			continue;
		}
		int32_t eX = m_Pos.GetX() + i % GetMatrixSizeXAxes();
		int32_t eY = m_Pos.GetY() + i / GetMatrixSizeXAxes();
		
		int32_t cellID = _LiniarPosFrom2D(eY, eX);
		if (cellID >= m_Cells.size()) {
			TraceLog(LOG_FATAL, "Tetromino::Solidify(???) >>> cellID out of bounds");
			return;
		}
		
		m_Cells[cellID].SetColor(m_Color);
		
		if (m_SolidificationTimer <= 0.f) {
			m_Cells[cellID].SetShown(true);
		}
		else {
			m_Cells[cellID].SetBlinking(true);
		}
	}

	if (m_SolidificationTimer <= 0.f) {
		this->m_bSolid = true;

		Globals::SoundManagerInstance->PlaySoundNow(Globals::Sounds::SolidifySound);

		for (int32_t i = 0; i < m_Matrix.size(); ++i) {
			if (!m_Matrix[i]) {
				continue;
			}
			int32_t eX = m_Pos.GetX() + i % GetMatrixSizeXAxes();
			int32_t eY = m_Pos.GetY() + i / GetMatrixSizeXAxes();

			int32_t cellID = _LiniarPosFrom2D(eY, eX);
			if (cellID >= m_Cells.size()) {
				TraceLog(LOG_FATAL, "Tetromino::Solidify(???) >>> cellID out of bounds");
				return;
			}

			m_Cells[cellID].SetShown(true);
			m_Cells[cellID].SetBlinking(false);
		}
	}
}

bool Tetromino::IsSolid() const
{
	return this->m_bSolid;
}

bool Tetromino::IsInSolidification() const
{
	return m_SolidificationTimer <= 0.f and m_bInSolidification;
}

Vec2<int32_t> Tetromino::GetSpriteSize() const {
	return this->m_SpriteSize;
}

void Tetromino::DrawAsSprite(Vec2<int32_t> pos) const {
	TetrominoSprite::DrawSprite(this->m_Shape, pos, this->m_CellSize, this->m_Padding);
}

int32_t Tetromino::GetAccumulatedScore() const
{
	return this->m_ScoreAccumulated;
}

TetrominosE Tetromino::GetShape() const
{
	return this->m_Shape;
}

int32_t Tetromino::GetCellSize() const
{
	return this->m_CellSize;
}

int32_t Tetromino::GetPadding() const
{
	return m_Padding;
}

HeldTetromino::HeldTetromino(Tetromino tetromino)
{
	m_bExists = true;
	m_Shape = tetromino.GetShape();
	m_CellSize = tetromino.GetCellSize();
	m_Padding = tetromino.GetPadding();
}

HeldTetromino::HeldTetromino(TetrominosE shape, int32_t cellSize, int32_t padding)
	: m_Shape(shape), m_CellSize(cellSize), m_Padding(padding), m_bExists(true)
{}

void HeldTetromino::Draw(Vec2<int32_t> pos) const {
	if (!m_bExists) {
		return;
	}
	TetrominoSprite::DrawSprite(this->m_Shape, pos, this->m_CellSize, this->m_Padding);
}

void HeldTetromino::Clear() {
	m_bExists = false;
}

bool HeldTetromino::Exists() const {
	return this->m_bExists;
}

TetrominosE HeldTetromino::GetShape() const
{
	return this->m_Shape;
}
