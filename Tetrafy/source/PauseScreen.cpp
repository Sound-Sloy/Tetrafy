#include "PauseScreen.h"

PauseScreen::PauseScreen() {
	m_TitleText = Text("Paused", { GetRenderWidth() / 2, static_cast<int>(125 * Globals::Options.GUIScale) }, { .5f, .5f }, Globals::TetrisFontBig, 72.f * Globals::Options.GUIScale);
	
	ButtonProperties buttonProperties {
		.Font = &Globals::TetrisFont,
		.FontSize = 28.f * Globals::Options.GUIScale
	};

	int32_t buttonFirstY = 300 * Globals::Options.GUIScale;

	Vec2<int32_t> size = { static_cast<int>(200 * Globals::Options.GUIScale),static_cast<int>(50 * Globals::Options.GUIScale) };
	int32_t spacing = 30 * Globals::Options.GUIScale;

	m_ResumeButton = Button({ (GetRenderWidth() - size.GetX()) / 2, buttonFirstY }, size, "Resume", buttonProperties);
	m_ResumeButton.OnClick = [this]() { SetActive(false); States::ChangeScreen(ScreensE::Board); Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::ClickSound); };
	m_ResumeButton.OnHover = []() { Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };

	m_RestartButton = Button({ (GetRenderWidth() - size.GetX()) / 2, buttonFirstY + size.GetY() + spacing }, size, "Restart", buttonProperties);
	m_RestartButton.OnClick = [this]() {SetActive(false); States::ChangeScreen(ScreensE::Board); FlagShouldRestartBoard = true; Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::ClickSound); };
	m_RestartButton.OnHover = []() { Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };

	m_ExitButton = Button({ (GetRenderWidth() - size.GetX()) / 2, buttonFirstY + 2 * (size.GetY() + spacing)}, size, "Exit", buttonProperties);
	m_ExitButton.OnClick = []() {States::ForceClose = true; Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::ClickSound); };
	m_ExitButton.OnHover = []() { Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };

	m_OptionsButton = Button({ (GetRenderWidth() - size.GetX()) / 2, buttonFirstY + 3 * (size.GetY() + spacing) }, size, "Options", buttonProperties);
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
