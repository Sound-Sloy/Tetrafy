#include "Score.h"

ScoreGUIComponent::ScoreGUIComponent(Vec2<int32_t> pos, Vec2<int32_t> size)
	: m_Pos(pos),
	m_Size(size)
{}

void ScoreGUIComponent::AddScore(int32_t score)
{
	this->m_Score += score;
}

void ScoreGUIComponent::SetScore(int32_t score)
{
	this->m_Score = score;
}

int32_t ScoreGUIComponent::GetScore() const
{
	return this->m_Score;
}

void ScoreGUIComponent::Draw()
{
	Vector2 textSize = MeasureTextEx(Globals::TetrisFont, "Score", 28.f, 1.f);
	std::string scoreStr = std::to_string(m_Score);
	Vector2 scoreTextSize = MeasureTextEx(Globals::TetrisFontMedium, scoreStr.c_str(), 20.f, 1.f);

	DrawRectangleLines(m_Pos.GetX() - 5, m_Pos.GetY() - 5, m_Size.GetX() + 5, m_Size.GetY() + 5, RAYWHITE);
	DrawTextEx(Globals::TetrisFont, "Score", Vector2((float)m_Pos.GetX() + ((float)m_Size.GetX() - textSize.x) / 2, (float)m_Pos.GetY() + 5), 28.f, 1.f, RAYWHITE);
	DrawTextEx(Globals::TetrisFontMedium, scoreStr.c_str(), Vector2((float)m_Pos.GetX() + ((float)m_Size.GetX() - scoreTextSize.x) / 2, (float)m_Pos.GetY() + 5 + textSize.y + 10), 20.f, 1.f, m_ScoreColor);

}

void SplashTextController::SpawnSplash(std::string splashText, Font& font, float fontSize, Color color, Vec2<int32_t> pos, float lifeTime)
{
	this->m_Splashes.push_back(SplashText(splashText, font, fontSize, color, pos, lifeTime));
}

void SplashTextController::Update(float deltaTime)
{
	for (SplashText& splash : this->m_Splashes) {
		splash.Update(deltaTime);
	}
	for (int32_t i = 0; i < this->m_Splashes.size(); ++i) {
		if (!m_Splashes[i].IsEnabled()) {
			m_Splashes.erase(m_Splashes.begin() + i);
			i--;
		}
	}
}

void SplashTextController::Draw()
{
	for (SplashText& splash : this->m_Splashes) {
		splash.Draw();
	}
}

SplashText::SplashText(std::string splashText, Font& font, float fontSize, Color color, Vec2<int32_t> pos, float lifeTime)
	: m_Text(splashText),
	m_Font(font),
	m_FontSize(fontSize),
	m_Color(color),
	m_Pos(pos),
	m_LifeTime(lifeTime)
{}

void SplashText::Update(float deltaTime)
{
	if (!m_bEnabled) {
		return;
	}
	if (m_TimeSinceSpawn > m_LifeTime) {
		return;
	}
	m_TimeSinceSpawn += deltaTime;
	//this->m_Color.a *= (this->m_LifeTime - this->m_TimeSinceSpawn) / this->m_LifeTime;
	if (m_TimeSinceSpawn == m_LifeTime) {
		m_bEnabled = false;
	}
}

void SplashText::Draw()
{
	Color col = m_Color;
	col.a *= -(1 / m_LifeTime * m_TimeSinceSpawn) * (1 / m_LifeTime * m_TimeSinceSpawn) * (1 / m_LifeTime * m_TimeSinceSpawn) + 1;
	DrawTextEx(this->m_Font, m_Text.c_str(), m_Pos, m_FontSize, 1.f, col);
}

bool SplashText::IsEnabled() const
{
	return this->m_bEnabled;
}
