#include "LevelGUIComponent.h"

LevelGUIComponent::LevelGUIComponent(Vec2<int32_t> pos, Vec2<int32_t> size)
	: m_Pos(pos), m_Size(size)
{}

void LevelGUIComponent::SetLevel(int32_t level)
{
	this->m_Level = level;
}

int32_t LevelGUIComponent::GetLevel() const
{
	return this->m_Level;
}

void LevelGUIComponent::Draw()
{
	Vector2 textSize = MeasureTextEx(Globals::TetrisFont, "Level", 28.f, 1.f);
	std::string scoreStr = std::to_string(m_Level);
	Vector2 scoreTextSize = MeasureTextEx(Globals::TetrisFontMedium, scoreStr.c_str(), 20.f, 1.f);

	DrawRectangleLines(this->m_Pos.GetX() - 5, this->m_Pos.GetY() - 5, this->m_Size.GetX() + 5, this->m_Size.GetY() + 5, RAYWHITE);
	DrawTextEx(Globals::TetrisFont, "Level", Vector2((float)this->m_Pos.GetX() + (this->m_Size.GetX() - textSize.x) / 2, this->m_Pos.GetY() + 5), 28.f, 1.f, RAYWHITE);
	DrawTextEx(Globals::TetrisFontMedium, scoreStr.c_str(), Vector2(this->m_Pos.GetX() + (this->m_Size.GetX() - scoreTextSize.x) / 2, this->m_Pos.GetY() + 5 + textSize.y + 10), 20.f, 1.f, m_LevelColor);
}
