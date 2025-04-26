#include "DeathScreen.h"

DeathScreen::DeathScreen(uint32_t currentScore, uint32_t level)
	: c_CurrentScore(currentScore)
{
	m_GameOverText = Text("Game Over!", { GetRenderWidth() / 2, static_cast<int>(75 * Globals::Options.GUIScale) }, {.5f, .5f}, Globals::TetrisFont, 28.f * Globals::Options.GUIScale);

	std::vector<ScoreFileHandler::PlayerScore> scores = Globals::GScoreFileHandlerInstance->GetScores();
	ScoreFileHandler::PlayerScore latestAddedScore;
	if(!scores.empty()) {
		latestAddedScore = scores.back();
	}
	std::ranges::sort(scores, [](const ScoreFileHandler::PlayerScore& ps1, const ScoreFileHandler::PlayerScore& ps2) {if (ps1.Score > ps2.Score)return true; else if (ps1.Score == ps2.Score) return ps1.TimeSpent < ps2.TimeSpent; return false; });

	uint64_t highScore = 0;
	if(!scores.empty()) {
		highScore = scores.at(0).Score;
	}

	if (currentScore > highScore) {
		m_TitleText = Text("High Score!", { GetRenderWidth() / 2, static_cast<int>(125 * Globals::Options.GUIScale) }, { .5f, .5f }, Globals::TetrisFontBig, 72.f * Globals::Options.GUIScale);
	}
	else {
		std::vector<std::string> choices = { "Good Job!", "Congrats!", "Nice!", "You Rock!", "Great Round!", "Keep Going!" };
		std::mt19937 RNG{ static_cast<std::mt19937::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()) };
		std::uniform_int_distribution<> choiceDistribution{ 0, (int32_t)choices.size() - 1 };

		m_TitleText = Text(choices[choiceDistribution(RNG)], { GetRenderWidth() / 2, static_cast<int>(125 * Globals::Options.GUIScale) }, { .5f, .5f }, Globals::TetrisFontBig, 72.f * Globals::Options.GUIScale);
	}


	if(!scores.empty()) {
		int32_t tableY = 300 * Globals::Options.GUIScale;
		int32_t stopInd = std::min<int32_t>(5, scores.size());

		int32_t timeTextPosX = 0;
		int32_t scoreTextPosX = 0;
		int32_t spentTextPosX = 0;

		int32_t timeTextMaxWidth = 0;
		int32_t scoreTextMaxWidth = 0;
		int32_t spentTextMaxWidth = 0;


		for (int32_t i = 0; i < stopInd; ++i) {
			timeTextMaxWidth = std::max<int32_t>(timeTextMaxWidth,
				static_cast<int32_t>(MeasureTextEx(Globals::TetrisFont, FormatTimestamp(scores.at(i).Timestamp).c_str(),
					28.f * Globals::Options.GUIScale, 1.f).x));
			scoreTextMaxWidth = std::max<int32_t>(scoreTextMaxWidth,
				static_cast<int32_t>(MeasureTextEx(Globals::TetrisFont, std::to_string(scores.at(i).Score).c_str(),
					28.f * Globals::Options.GUIScale, 1.f).x));
			spentTextMaxWidth = std::max<int32_t>(spentTextMaxWidth,
				static_cast<int32_t>(MeasureTextEx(Globals::TetrisFont, FormatTimeSpent(scores.at(i).TimeSpent).c_str(),
					28.f * Globals::Options.GUIScale, 1.f).x));
		}

		int32_t lineHeight = MeasureTextEx(Globals::TetrisFont, FormatTimestamp(scores.at(0).Timestamp).c_str(),
			28.f * Globals::Options.GUIScale, 1.f).y;

		int32_t widgetWidth = timeTextMaxWidth + scoreTextMaxWidth + spentTextMaxWidth + 2 * C_TABLE_COL_SPACING;
		int32_t widgetPosX = (GetRenderWidth() - widgetWidth) / 2;
		timeTextPosX = widgetPosX;
		scoreTextPosX = timeTextPosX + timeTextMaxWidth + C_TABLE_COL_SPACING;
		spentTextPosX = scoreTextPosX + scoreTextMaxWidth + C_TABLE_COL_SPACING;

		for (int32_t i = 0; i < stopInd; ++i) {
			Color col = WHITE;
			if(scores.at(i) == latestAddedScore) {
				col = GREEN;
			}
			m_Texts.emplace_back(FormatTimestamp(scores.at(i).Timestamp), Vec2{ timeTextPosX, tableY + i * (lineHeight + C_TABLE_ROW_SPACING) }, Vec2{ 0.f, 0.f }, Globals::TetrisFont, 28.f * Globals::Options.GUIScale, 1.f, 0.f, col);
			m_Texts.emplace_back(std::to_string(scores.at(i).Score), Vec2{ scoreTextPosX, tableY + i * (lineHeight + C_TABLE_ROW_SPACING) }, Vec2{ 0.f, 0.f }, Globals::TetrisFont, 28.f * Globals::Options.GUIScale, 1.f, 0.f, col);
			m_Texts.emplace_back(FormatTimeSpent(scores.at(i).TimeSpent), Vec2{ spentTextPosX, tableY + i * (lineHeight + C_TABLE_ROW_SPACING) }, Vec2{ 0.f, 0.f }, Globals::TetrisFont, 28.f * Globals::Options.GUIScale, 1.f, 0.f, col);
		}
	}

	


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
	m_GameOverText.Draw();
	m_TitleText.Draw();

	for (auto& text : m_Texts) {
		text.Draw();
	}

	m_RetryButton->Draw();
	m_MainMenuButton->Draw();
	m_ExitButton->Draw();
}

std::string DeathScreen::FormatTimeSpent(uint32_t timeSpentSeconds)
{
	using namespace std::chrono;
	auto duration = seconds(timeSpentSeconds);

	return std::format("{:02}:{:02}:{:02}",
		duration_cast<hours>(duration).count(),
		duration_cast<minutes>(duration % hours(1)).count(),
		duration_cast<seconds>(duration % minutes(1)).count());
}

std::string DeathScreen::FormatTimestamp(std::time_t timestamp)
{
	std::tm tm;
#ifdef _WIN32
	localtime_s(&tm, &timestamp);
#else
	localtime_r(&timestamp, &tm);
#endif

	std::ostringstream oss;
	oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
	return oss.str();
}
