#pragma once
#include <iostream>
#include <raylib.h>
#include "Vec2.h"
#include "Tetromino.h"
#include "Globals.h"
#include <string>

class HeldTetrominoGUIComponent
{
public:
	HeldTetrominoGUIComponent() = default;
	HeldTetrominoGUIComponent(Vec2<int32_t> pos, Vec2<int32_t> size, const HeldTetromino& heldTetromino);
	
	void Draw();
private:
	Vec2<int32_t> m_Pos;
	Vec2<int32_t> m_Size;
	const HeldTetromino& m_HeldTetromino;
};
