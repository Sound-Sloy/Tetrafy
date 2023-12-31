#pragma once
#include <iostream>
#include <raylib.h>
#include <string>
#include <random>

#include "Vec2.h"
#include "Button.h"
#include "Globals.h"
#include "States.h"
#include "Text.h"

class DeathScreen {
public:
	DeathScreen(uint32_t currentScore = 0, uint32_t highScore = -1, uint32_t level = 0);
	~DeathScreen() = default;

	void Update();
	void Draw();

private:
	const uint32_t m_CurrentScore = 0;
	const uint32_t m_HighScore = -1;
	
	Button* m_RetryButton;
	Button* m_ExitButton;
	Text m_TitleText;
	Text m_GameOverText;
	Text m_ScoreText;
	Text m_ScoreValueText;
	Text m_BestText;
	Text m_BestValueText;
	Text m_LevelText;
	Text m_LevelValueText;
};