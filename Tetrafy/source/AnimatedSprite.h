#pragma once
#include <iostream>
#include <raylib.h>
#include "Vec2.h"
#include <vector>

struct Animation {
	Texture2D Atlas;
	int32_t FPS = 30;
	std::vector<Rectangle> Rectangles;
	Vec2<int32_t> Origin = { 0,0 };
};

class AnimatedSprite {
public:
	AnimatedSprite() = default;
	AnimatedSprite(Animation& animation, float scale = 1.f);
	void Draw(Vec2<int32_t> pos, Color color = WHITE, float scale = 1.f);
	void Draw(int32_t posX, int32_t posY, Color color = WHITE, float scale = 1.f);
	void RotateAt(float radians);
	void RotateBy(float radians);
	void Restart();
	void Pause();
	void Unpause();

	float GetRotation() const;
	int32_t GetFrame() const;
	bool IsPaused() const;
	int32_t GetRepeatCounter() const;
private:
	Animation& m_Animation;
	int32_t m_CurrentFrame = 0;
	float m_Radians = 0;
	float m_Scale = 1.f;
	float m_SpawnTime = 0.f;
	bool m_bPaused = false;
	int32_t m_RepeatCounter = 0;
};