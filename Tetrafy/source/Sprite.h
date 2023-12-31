#pragma once
#include <iostream>
#include <raylib.h>
#include "Vec2.h"

class Sprite {
public:
	Sprite() = default;
	Sprite(Texture2D& sprite, float scale = 1.f);
	void Draw(Vec2<int32_t> pos, float scale = 1.f);
	void Draw(int32_t posX, int32_t posY, float scale = 1.f);
	void RotateAt(float radians);
	void RotateBy(float radians);
private:
	Texture2D& m_Texture;
	float m_Radians = 0.f;
	float m_Scale = 1.f;
};