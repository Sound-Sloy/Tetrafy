#include "MainScreen.h"

MainScreen::MainScreen() {
	ButtonProperties buttonProperties = {
		.TextAlignment = ButtonTextAlignment::Center,
		.Font = &Globals::TetrisFont,
		.FontSize = 28.f * Globals::Options.GUIScale ,
		.FontSpacing = 1.f
	};
	m_PlayButton = new Button({ static_cast<int>((GetRenderWidth() - 200 * Globals::Options.GUIScale) / 2), int32_t(300 * Globals::Options.GUIScale) }, { int32_t(200 * Globals::Options.GUIScale) ,int32_t(50 * Globals::Options.GUIScale) }, "Play", buttonProperties);
	m_OptionsButton = new Button({ static_cast<int>((GetRenderWidth() - 200 * Globals::Options.GUIScale) / 2), int32_t(380 * Globals::Options.GUIScale) }, { int32_t(200 * Globals::Options.GUIScale) ,int32_t(50 * Globals::Options.GUIScale) }, "Options", buttonProperties);
	m_ExitButton = new Button({ static_cast<int>((GetRenderWidth() - 200 * Globals::Options.GUIScale) / 2), int32_t(460 * Globals::Options.GUIScale) }, { int32_t(200 * Globals::Options.GUIScale) ,int32_t(50 * Globals::Options.GUIScale) }, "Exit", buttonProperties);

	m_PlayButton->OnClick = []() {
		States::Flags::ForceResetBoard = true; // INFO fix for until  the screen manager will be replaced by the new one
		States::ChangeScreen(ScreensE::Board);
		Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::ClickSound);
	};
	m_OptionsButton->OnClick = []() {
		States::ChangeScreen(ScreensE::Options); 
		Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::ClickSound);
	};
	m_ExitButton->OnClick = []() {
		States::ForceClose = true; 
		Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::ClickSound);
	};

	m_PlayButton->OnHover = []() { Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };
	m_OptionsButton->OnHover = []() { Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };
	m_ExitButton->OnHover = []() { Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };

	m_TitleTextMeasurements = MeasureTextEx(Globals::TetrisFontBig, "Tetrafy", 72.f * Globals::Options.GUIScale, 1.f);
}

void MainScreen::Update() {
	m_PlayButton->Update();
	m_OptionsButton->Update();
	m_ExitButton->Update();
}

void MainScreen::Draw() {
	DrawTextEx(Globals::TetrisFontBig, "Tetrafy", { ((float)GetRenderWidth() - m_TitleTextMeasurements.x) / 2.f, 50.f * Globals::Options.GUIScale }, 72.f * Globals::Options.GUIScale, 1.f, WHITE);
	m_PlayButton->Draw();
	m_OptionsButton->Draw();
	m_ExitButton->Draw();
}