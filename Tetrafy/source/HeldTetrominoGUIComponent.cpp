#include "HeldTetrominoGUIComponent.h"

HeldTetrominoGUIComponent::HeldTetrominoGUIComponent(Vec2<int32_t> pos, Vec2<int32_t> size, const HeldTetromino& heldTetromino)
	: m_Pos(pos), m_Size(size), m_HeldTetromino(heldTetromino)
{}

void HeldTetrominoGUIComponent::Draw()
{
	Vector2 textSize = MeasureTextEx(Globals::TetrisFont, "Hold", 28.f, 1.f);

	DrawRectangleLines(this->m_Pos.GetX() - 5, this->m_Pos.GetY() - 5, this->m_Size.GetX() + 5, this->m_Size.GetY() + 5, RAYWHITE);
	DrawTextEx(Globals::TetrisFont, "Hold", Vector2((float)this->m_Pos.GetX() + (this->m_Size.GetX() - textSize.x) / 2, (float)this->m_Pos.GetY() + 5), 28.f, 1.f, RAYWHITE);
	this->m_HeldTetromino.Draw({ this->m_Pos.GetX() + this->m_Size.GetX() / 2, this->m_Pos.GetY() + (int32_t)textSize.y + 10 + 5 });
}
