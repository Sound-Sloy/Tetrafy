#pragma once
#include <iostream>
#include <raylib.h>
#include "Vec2.h"
#include "Globals.h"
#include <string>
#include <deque>

class ScoreGUIComponent
{
public:
	ScoreGUIComponent() = default;
	ScoreGUIComponent(Vec2<int32_t> pos, Vec2<int32_t> size);
	void AddScore(int32_t score);
	void SetScore(int32_t score);
	int32_t GetScore() const;
	void Draw();
private:
	Vec2<int32_t> m_Pos{0,0};
	Vec2<int32_t> m_Size{0,0};
	int32_t m_Score = 0;
	Color m_ScoreColor = LIGHTGRAY;
};

class SplashText {
public:
	SplashText() = default;
	SplashText(std::string splashText, Font& font, float fontSize, Color color, Vec2<int32_t> pos, float lifeTime);
	void Update(float deltaTime);
	void Draw();
	bool IsEnabled() const;
private:
	std::string m_Text;
	Font m_Font;
	float m_FontSize;
	Color m_Color;
	Vec2<int32_t> m_Pos;
	float m_LifeTime;
	float m_TimeSinceSpawn = 0;
	bool m_bEnabled = true;
};

class SplashTextController {
public:
	SplashTextController() = default;
	void SpawnSplash(std::string splashText, Font& font, float fontSize, Color color, Vec2<int32_t> pos, float lifeTime);
	void Update(float deltaTime);
	void Draw();
private:
	std::deque<SplashText> m_Splashes;

};

