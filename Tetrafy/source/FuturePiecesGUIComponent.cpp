#include "FuturePiecesGUIComponent.h"

FuturePiecesGUIComponent::FuturePiecesGUIComponent(Vec2<int32_t> pos, std::deque<Tetromino>& tetrominos)
	: m_Pos(pos), m_Tetrominos(tetrominos)
{}

//FuturePiecesGUIComponent& FuturePiecesGUIComponent::operator=(const FuturePiecesGUIComponent& other)
//{
//	if (this != &other) {
//		m_Pos = other.m_Pos;
//		m_Size = other.m_Size;
//		m_TextSize = other.m_TextSize;
//		m_SpritesPosY = other.m_SpritesPosY;
//		// Copy the elements from other's m_Tetrominos to this object's m_Tetrominos
//		m_Tetrominos = other.m_Tetrominos;
//	}
//	return *this;
//}

FuturePiecesGUIComponent::~FuturePiecesGUIComponent()
{
}

void FuturePiecesGUIComponent::Update() {
	Vector2 textSize = MeasureTextEx(Globals::TetrisFont, "Following", 28.f, 1.f);
	m_TextSize = { (int32_t)textSize.x, (int32_t)textSize.y };

	int32_t allSpriteSizesY = ((int32_t)m_Tetrominos.size() - 1) * CTetrominoYPadding;
	for (auto& tetromino : this->m_Tetrominos) {
		allSpriteSizesY += tetromino.GetSpriteSize().GetY();
	}
	m_SpritesPosY = this->m_Pos.GetY() + 5 + m_TextSize.GetY() + CTetrominoYPadding + (this->m_Size.GetY() - CTetrominoYPadding - m_TextSize.GetY() - 5 - allSpriteSizesY) / 2;
}

void FuturePiecesGUIComponent::Draw()
{
	DrawRectangleLines(this->m_Pos.GetX() - 5, this->m_Pos.GetY() - 5, this->m_Size.GetX() + 5, this->m_Size.GetY() + 5, RAYWHITE);
	
	DrawTextEx(Globals::TetrisFont, "Following", Vector2((float)this->m_Pos.GetX() + (float)(this->m_Size.GetX() - m_TextSize.GetX()) / 2, (float)this->m_Pos.GetY() + 5), 28.f, 1.f, RAYWHITE);
	int32_t yPos = m_SpritesPosY;
	for (int32_t i = 1; i < this->m_Tetrominos.size(); ++i) {
		this->m_Tetrominos[i].DrawAsSprite({ this->m_Pos.GetX() + this->m_Size.GetX() / 2 , yPos });
		yPos += this->m_Tetrominos[i].GetSpriteSize().GetY() + 10;
	}
}
