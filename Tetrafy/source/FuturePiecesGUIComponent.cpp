#include "FuturePiecesGUIComponent.h"

FuturePiecesGUIComponent::FuturePiecesGUIComponent(Vec2<int32_t> pos, std::deque<Tetromino>& tetrominos)
	: m_Pos(pos), m_Tetrominos(tetrominos)
{
	m_Size.SetX(m_Size.GetX() * Globals::Options.GUIScale);
	m_Size.SetY(m_Size.GetY() * Globals::Options.GUIScale);
	m_TitleText = Text("Next", { pos.GetX() + m_Size.GetX() / 2, static_cast<int>(pos.GetY() + CPadding * Globals::Options.GUIScale) }, {.5f, 0.f}, Globals::TetrisFont, 28.f * Globals::Options.GUIScale);
}

FuturePiecesGUIComponent::~FuturePiecesGUIComponent()
{
}

void FuturePiecesGUIComponent::Update() {
	int32_t textSzY = m_TitleText.GetSize().GetY();

	int32_t allSpriteSizesY = 0;
	for (int32_t i = 1; i < m_Tetrominos.size() and i <= 3; ++i) {
		allSpriteSizesY += m_Tetrominos[i].GetSpriteSize().GetY();
	}
	allSpriteSizesY += ((int32_t)m_Tetrominos.size() - 2) * CPadding * Globals::Options.GUIScale;

	int32_t spaceAvailable = m_Size.GetY() - textSzY - 3 * CPadding * Globals::Options.GUIScale;
	m_SpritesPosY = m_Pos.GetY() + 2 * CPadding * Globals::Options.GUIScale + textSzY + (spaceAvailable - allSpriteSizesY) / 2;
}

void FuturePiecesGUIComponent::Draw()
{
	DrawRectangleLines(m_Pos.GetX() - 5, m_Pos.GetY() - 5, m_Size.GetX() + 5, m_Size.GetY() + 5, RAYWHITE);
	
	m_TitleText.Draw();

	int32_t yPos = m_SpritesPosY;
	for (int32_t i = 1; i < m_Tetrominos.size() and i <= 3; ++i) {
		m_Tetrominos[i].DrawAsSprite({ m_Pos.GetX() + m_Size.GetX() / 2 , yPos });
		yPos += m_Tetrominos[i].GetSpriteSize().GetY() + CPadding * Globals::Options.GUIScale;
	}
}
