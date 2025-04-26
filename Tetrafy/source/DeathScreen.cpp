#include "DeathScreen.h"

DeathScreen::DeathScreen(uint32_t currentScore, uint32_t highScore, uint32_t level)
	: m_CurrentScore(currentScore), m_HighScore(highScore)
{
	m_GameOverText = Text("Game Over!", { GetRenderWidth() / 2, static_cast<int>(75 * Globals::Options.GUIScale) }, {.5f, .5f}, Globals::TetrisFont, 28.f * Globals::Options.GUIScale);

	if (currentScore > highScore) {
		m_TitleText = Text("High Score!", { GetRenderWidth() / 2, static_cast<int>(125 * Globals::Options.GUIScale) }, { .5f, .5f }, Globals::TetrisFontBig, 72.f * Globals::Options.GUIScale);
	}
	else {
		std::vector<std::string> choices = { "Good Job!", "Congrats!", "Nice!", "You Rock!", "Great Round!", "Keep Going!" };
		std::mt19937 RNG{ static_cast<std::mt19937::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()) };
		std::uniform_int_distribution<> choiceDistribution{ 0, (int32_t)choices.size() - 1 };

		m_TitleText = Text(choices[choiceDistribution(RNG)], { GetRenderWidth() / 2, static_cast<int>(125 * Globals::Options.GUIScale) }, { .5f, .5f }, Globals::TetrisFontBig, 72.f * Globals::Options.GUIScale);
	}


	int32_t widgetWidth = 300 * Globals::Options.GUIScale;

	m_ScoreText = Text("Score", { GetRenderWidth() / 2 - widgetWidth / 2, static_cast<int>(300 * Globals::Options.GUIScale) }, { 0.f, 0.f }, Globals::TetrisFont, 28.f * Globals::Options.GUIScale);
	m_ScoreValueText = Text(std::to_string(currentScore),
	                        { GetRenderWidth() / 2 + widgetWidth / 2, static_cast<int>(300 * Globals::Options.GUIScale) }, { 1.f, 0.f },
	                        Globals::TetrisFont, 28.f * Globals::Options.GUIScale);
	m_BestText = Text("Best", { GetRenderWidth() / 2 - widgetWidth / 2, static_cast<int>(350 * Globals::Options.GUIScale) }, { 0.f, 0.f }, Globals::TetrisFont, 28.f * Globals::Options.GUIScale);
	m_BestValueText = Text(std::to_string(highScore), { GetRenderWidth() / 2 + widgetWidth / 2, static_cast<int>(350 * Globals::Options.GUIScale) }, { 1.f, 0.f }, Globals::TetrisFont, 28.f * Globals::Options.GUIScale);
	m_LevelText = Text("Level", { GetRenderWidth() / 2 - widgetWidth / 2, static_cast<int>(400 * Globals::Options.GUIScale) }, { 0.f, 0.f }, Globals::TetrisFont, 28.f * Globals::Options.GUIScale);
	m_LevelValueText = Text(std::to_string(level), {GetRenderWidth() / 2 + widgetWidth / 2, static_cast<int>(400 * Globals::Options.GUIScale) }, {1.f, 0.f}, Globals::TetrisFont, 28.f * Globals::Options.GUIScale);

	ButtonProperties buttonProperties = {
		.TextAlignment = ButtonTextAlignment::Center,
		.Font = &Globals::TetrisFont,
		.FontSize = 28.f * Globals::Options.GUIScale,
		.FontSpacing = 1.f
	};
	m_RetryButton = std::make_unique<Button>(Vec2{ static_cast<int>(GetRenderWidth() / 2 - 100 * Globals::Options.GUIScale), static_cast<int>(530 * Globals::Options.GUIScale)}, Vec2{static_cast<int>(200 * Globals::Options.GUIScale),static_cast<int>(50 * Globals::Options.GUIScale)}, "Retry", buttonProperties );
	m_RetryButton->OnClick = []() {
		States::Flags::ForceResetBoard = true;
		Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::ClickSound);
	};

	m_RetryButton->OnHover = []() {
		Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound);
	};

	m_MainMenuButton = std::make_unique<Button>(Vec2{static_cast<int>(GetRenderWidth() / 2 - 100 * Globals::Options.GUIScale), static_cast<int>(610 * Globals::Options.GUIScale)}, Vec2{static_cast<int>(200 * Globals::Options.GUIScale),static_cast<int>(50 * Globals::Options.GUIScale)}, "Main Menu", buttonProperties );
	m_MainMenuButton->OnClick = []() {
		States::ChangeScreen(ScreensE::Main);
		Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::ClickSound);
		};

	m_MainMenuButton->OnHover = []() {
		Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound);
		};

	m_ExitButton = std::make_unique<Button>(Vec2{static_cast<int>(GetRenderWidth() / 2 - 100 * Globals::Options.GUIScale), static_cast<int>(690 * Globals::Options.GUIScale)}, Vec2{static_cast<int>(200 * Globals::Options.GUIScale),static_cast<int>(50 * Globals::Options.GUIScale)}, "Exit", buttonProperties );
	m_ExitButton->OnClick = []() {
		States::ForceClose = true;
		Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::ClickSound);
	};

	m_ExitButton->OnHover = []() {
		Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound);
	};
}

void DeathScreen::Update() {
	//if (m_TitleText == "") {
	//	if (m_CurrentScore > m_HighScore) {
	//		m_TitleText = "High Score!";
	//	}
	//	else {
	//		std::vector<std::string> choices = { "Good Job!", "Congrats!", "Nice!", "You Rock!", "Great Round!", "Keep Going!" };
	//		std::mt19937 RNG{ static_cast<std::mt19937::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()) };
	//		std::uniform_int_distribution<> m_ChoiceDistribution{ 0, (int32_t)choices.size() - 1 };
	//		
	//		m_TitleText = choices[m_ChoiceDistribution(RNG)];
	//	}
	//}

	//if (m_TitleTextPos == Vec2{ 0,0 }) {
	//	Vector2 textsize = MeasureTextEx(Globals::TetrisFontBig, m_TitleText.c_str(), 72.f, 1.f);
	//	m_TitleTextPos = { (GetRenderWidth() - (int32_t)textsize.x) / 2, 50 };
	//}

	m_RetryButton->Update();
	m_MainMenuButton->Update();
	m_ExitButton->Update();
}

void DeathScreen::Draw() {
	//DrawTextEx(Globals::TetrisFontBig, m_TitleText.c_str(), m_TitleTextPos, 72.f, 1.f, WHITE);
	m_GameOverText.Draw();
	m_TitleText.Draw();
	m_ScoreText.Draw();
	m_ScoreValueText.Draw();
	m_BestText.Draw();
	m_BestValueText.Draw();
	m_LevelText.Draw();
	m_LevelValueText.Draw();

	m_RetryButton->Draw();
	m_MainMenuButton->Draw();
	m_ExitButton->Draw();
}