#include "PauseScreen.h"

PauseScreen::PauseScreen() {
	m_TitleText = Text("Paused", { GetRenderWidth() / 2, 125 }, { .5f, .5f }, Globals::TetrisFontBig, 72.f);
	
	ButtonProperties buttonProperties {
		.Font = &Globals::TetrisFont,
		.FontSize = 28.f
	};

	int32_t buttonFirstY = 300;

	m_ResumeButton = Button({ (GetRenderWidth() - 200) / 2, buttonFirstY }, {200, 50}, "Resume", buttonProperties);
	m_ResumeButton.OnClick = [this]() { SetActive(false); States::ChangeScreen(ScreensE::Board); Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::ClickSound); };
	m_ResumeButton.OnHover = []() { Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };

	m_RestartButton = Button({ (GetRenderWidth() - 200) / 2, buttonFirstY + 80 }, { 200, 50 }, "Restart", buttonProperties);
	m_RestartButton.OnClick = [this]() {SetActive(false); States::ChangeScreen(ScreensE::Board); FlagShouldRestartBoard = true; Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::ClickSound); };
	m_RestartButton.OnHover = []() { Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };

	m_ExitButton = Button({ (GetRenderWidth() - 200) / 2, buttonFirstY + 2 * 80 }, { 200, 50 }, "Exit", buttonProperties);
	m_ExitButton.OnClick = []() {States::ForceClose = true; Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::ClickSound); };
	m_ExitButton.OnHover = []() { Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };

	m_OptionsButton = Button({ (GetRenderWidth() - 200) / 2, buttonFirstY + 3 * 80 }, {200, 50}, "Options", buttonProperties);
	m_OptionsButton.OnClick = [this]() { SetActive(false); States::ChangeScreen(ScreensE::Options); Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::ClickSound); };
	m_OptionsButton.OnHover = []() { Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };
}


void PauseScreen::Update() {
	m_ResumeButton.Update();
	m_RestartButton.Update();
	m_ExitButton.Update();
	m_OptionsButton.Update();
}

void PauseScreen::Draw() {
	m_TitleText.Draw();
	m_ResumeButton.Draw();
	m_RestartButton.Draw();
	m_ExitButton.Draw();
	m_OptionsButton.Draw();
}

void PauseScreen::SetActive(bool active) {
	m_Active = active;
}

bool PauseScreen::IsActive() const {
	return m_Active;
}
