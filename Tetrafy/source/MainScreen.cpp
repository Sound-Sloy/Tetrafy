#include "MainScreen.h"

MainScreen::MainScreen() {
	ButtonProperties buttonProperties = {
		.TextAlignment = ButtonTextAlignment::Center,
		.Font = &Globals::TetrisFont,
		.FontSize = 28.f,
		.FontSpacing = 1.f
	};
	m_PlayButton = new Button({ (GetRenderWidth() - 200) / 2, 300 }, { 200,50 }, "Play", buttonProperties);
	m_OptionsButton = new Button({ (GetRenderWidth() - 200) / 2, 380 }, { 200,50 }, "Options", buttonProperties);
	m_ExitButton = new Button({ (GetRenderWidth() - 200) / 2, 460 }, { 200,50 }, "Exit", buttonProperties);

	m_PlayButton->OnClick = []() { 
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

	m_TitleTextMeasurements = MeasureTextEx(Globals::TetrisFontBig, "Tetrafy", 72.f, 1.f);
}

void MainScreen::Update() {
	m_PlayButton->Update();
	m_OptionsButton->Update();
	m_ExitButton->Update();
}

void MainScreen::Draw() {
	DrawTextEx(Globals::TetrisFontBig, "Tetrafy", { ((float)GetRenderWidth() - m_TitleTextMeasurements.x) / 2.f, 50.f }, 72.f, 1.f, WHITE);
	m_PlayButton->Draw();
	m_OptionsButton->Draw();
	m_ExitButton->Draw();
}