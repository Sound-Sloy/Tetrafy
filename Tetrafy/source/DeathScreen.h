#pragma once
#include <iostream>
#include <raylib.h>
#include <string>
#include <random>
#include <algorithm>

#include "Vec2.h"
#include "Button.h"
#include "Globals.h"
#include "States.h"
#include "Text.h"

class DeathScreen {
public:
	DeathScreen(uint32_t currentScore = 0, uint32_t level = 0);
	~DeathScreen() = default;

	void Update();
	void Draw();

private:
	const uint64_t c_CurrentScore = 0;
	static constexpr int32_t C_TABLE_COL_SPACING = 30;
	static constexpr int32_t C_TABLE_ROW_SPACING = 5;

	std::unique_ptr<Button> m_RetryButton;
	std::unique_ptr<Button> m_ExitButton;
	std::unique_ptr<Button> m_MainMenuButton;
	std::vector<Text> m_Texts;
	Text m_TitleText;
	Text m_GameOverText;


	static std::string FormatTimeSpent(uint32_t timeSpentSeconds);
	static std::string FormatTimestamp(std::time_t timestamp);
};