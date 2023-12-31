#pragma once
#include "Vec2.h"
#include "Tetromino.h"
#include <deque>
#include "Globals.h"

class FuturePiecesGUIComponent
{
public:
	FuturePiecesGUIComponent() = default;
	FuturePiecesGUIComponent(Vec2<int32_t> pos, std::deque<Tetromino>& tetrominos);
	~FuturePiecesGUIComponent();
	void Update();
	void Draw();
private:
	Vec2<int32_t> m_Pos{0,0};
	Vec2<int32_t> m_Size{196, 320};
	Vec2<int32_t> m_TextSize{0,0};
	int32_t m_SpritesPosY = 0;
	const int32_t CTetrominoYPadding = 10;
	std::deque<Tetromino>& m_Tetrominos;

};

