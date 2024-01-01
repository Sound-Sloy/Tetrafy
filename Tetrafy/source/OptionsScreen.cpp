#include "OptionsScreen.h"

OptionsScreen::OptionsScreen()
{
	m_Title = Text("Options", { GetRenderWidth() / 2,125 }, { .5f,.5f }, Globals::TetrisFontBig, 72.f);

	Vector2 musicSwitchTextMeasurements = MeasureTextEx(Globals::TetrisFont, "Music", 28.f, 1.f);
	m_SFXSwitchTextPos = m_MusicSwitchTextPos + Vec2<int32_t>{0, (int32_t)musicSwitchTextMeasurements.y + m_Padding};
	Vector2 SFXSwitchTextMeasurements = MeasureTextEx(Globals::TetrisFont, "SFX", 28.f, 1.f);

	m_SoftDropSwitchTextPos = m_SFXSwitchTextPos + Vec2<int32_t>{0, (int32_t)SFXSwitchTextMeasurements.y + m_Padding};
	Vector2 softDropSwitchTextMeasurements = MeasureTextEx(Globals::TetrisFont, "Soft Drop", 28.f, 1.f);

	m_HardDropSwitchTextPos = m_SoftDropSwitchTextPos + Vec2<int32_t>{0, (int32_t)softDropSwitchTextMeasurements.y + m_Padding};
	Vector2 hardDropSwitchTextMeasurements = MeasureTextEx(Globals::TetrisFont, "Hard Drop", 28.f, 1.f);

	m_LandingPreviewSwitchTextPos = m_HardDropSwitchTextPos + Vec2<int32_t>{0, (int32_t)hardDropSwitchTextMeasurements.y + m_Padding};
	Vector2 landingPrevwSwitchTextMeasurements = MeasureTextEx(Globals::TetrisFont, "Landing Preview", 28.f, 1.f);

	SwitchProperties switchProperties{
		.Size = { 48,24 },
		.OnTexture = Globals::Textures::SwitchOn,
		.OffTexture = Globals::Textures::SwitchOff,
		.InactiveTexture = Globals::Textures::SwitchOff
	};


	int32_t maxX = Utils::max<float>({ musicSwitchTextMeasurements.x, SFXSwitchTextMeasurements.x, softDropSwitchTextMeasurements.x, hardDropSwitchTextMeasurements.x, landingPrevwSwitchTextMeasurements.x });

	int32_t switchXCoord = m_MusicSwitchTextPos.GetX() + maxX + m_Padding;
	Vec2<int32_t> musicSwitchPos		= { switchXCoord, m_MusicSwitchTextPos.GetY() + (int32_t)(musicSwitchTextMeasurements.y - switchProperties.Size.GetY()) / 2};
	Vec2<int32_t> SFXSwitchPos			= { switchXCoord, m_SFXSwitchTextPos.GetY() + (int32_t)(SFXSwitchTextMeasurements.y - switchProperties.Size.GetY()) / 2 };
	Vec2<int32_t> softDropSwitchPos		= { switchXCoord, m_SoftDropSwitchTextPos.GetY() + (int32_t)(softDropSwitchTextMeasurements.y - switchProperties.Size.GetY()) / 2 };
	Vec2<int32_t> hardDropSwitchPos		= { switchXCoord, m_HardDropSwitchTextPos.GetY() + (int32_t)(hardDropSwitchTextMeasurements.y - switchProperties.Size.GetY()) / 2 };
	Vec2<int32_t> landingPrevwSwitchPos = { switchXCoord, m_LandingPreviewSwitchTextPos.GetY() + (int32_t)(landingPrevwSwitchTextMeasurements.y - switchProperties.Size.GetY()) / 2 };

	m_MusicSwitch			= new Switch(musicSwitchPos, switchProperties);
	m_SFXSwitch				= new Switch(SFXSwitchPos, switchProperties);
	m_SoftDropSwitch		= new Switch(softDropSwitchPos, switchProperties);
	m_HardDropSwitch		= new Switch(hardDropSwitchPos, switchProperties);
	m_LandingPreviewSwitch  = new Switch(landingPrevwSwitchPos, switchProperties);

	m_MusicSwitch->SetState((SwitchStatesE)Globals::Options.MusicToggle);
	m_SFXSwitch->SetState((SwitchStatesE)Globals::Options.SFXToggle);
	m_SoftDropSwitch->SetState((SwitchStatesE)Globals::Options.SoftDropToggle);
	m_HardDropSwitch->SetState((SwitchStatesE)Globals::Options.HardDropToggle);
	m_LandingPreviewSwitch->SetState((SwitchStatesE)Globals::Options.LandingPreviewToggle);

	m_MusicSwitch->OnHover = [](Vec2<int32_t>) { Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };
	m_SFXSwitch->OnHover = [](Vec2<int32_t>) { Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };
	m_SoftDropSwitch->OnHover = [](Vec2<int32_t>) { Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };
	m_HardDropSwitch->OnHover = [](Vec2<int32_t>) { Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };
	m_LandingPreviewSwitch->OnHover = [](Vec2<int32_t>) { Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };

	m_MusicSwitch->OnChange = [this](SwitchStatesE state) {Globals::Options.MusicToggle = (bool)state; m_MusicVolumeSlider->SetActive((bool)state); };
	m_SFXSwitch->OnChange = [](SwitchStatesE state) {Globals::Options.SFXToggle = (bool)state; };
	m_SoftDropSwitch->OnChange = [](SwitchStatesE state) { Globals::Options.SoftDropToggle = (bool)state; };
	m_HardDropSwitch->OnChange = [](SwitchStatesE state) { Globals::Options.HardDropToggle = (bool)state; };
	m_LandingPreviewSwitch->OnChange = [](SwitchStatesE state) {Globals::Options.LandingPreviewToggle = (bool)state; };

	
	
	SliderProperties<float> sliderProperties{
		.BaseTexture = Globals::Textures::SliderBase,
		.HighlightTexture = Globals::Textures::SliderHighlight,
		.HandleTexture = Globals::Textures::SliderHandle,
		.LowerLimit = 0,
		.UpperLimit = 100,
		.Step = .1f
	};
	m_MusicVolumeSlider = new Slider<float>({300, 300}, nullptr, sliderProperties);
	m_MusicVolumeSlider->OnChange = [](int32_t prevVal, int32_t newVal) {Globals::Options.MusicVolume = newVal / 100.f; };
	m_MusicVolumeSlider->SetValue(Globals::Options.MusicVolume * 100.f);

	ButtonProperties buttonProperties{
		.Font = &Globals::TetrisFont,
		.FontSize = 28.f,
		.BorderSegments = 32
	};
	m_ControlsButton = Button({ (GetRenderWidth() - 200) / 2, 570 }, { 200,50 }, "Controls", buttonProperties);
	
	m_ControlsButton.OnClick = []() {
		States::ChangeScreen(ScreensE::Controls);
		Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::ClickSound);
	};
	m_ControlsButton.OnHover = []() {
		Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound);
	};

	m_BackButton = Button({ (GetRenderWidth() - 200) / 2, 650}, {200, 50}, "Back", buttonProperties);
	m_BackButton.OnClick = [this]() {
		States::ChangeScreen(m_ScrBefOptions); 
		m_ScrBefOptions = ScreensE::None;
		Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::ClickSound);
	};
	m_BackButton.OnHover = []() { 
		Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); 
	};
}

void OptionsScreen::Update() {
	if (m_ScrBefOptions == ScreensE::None) {
		m_ScrBefOptions = States::LastScreen;
	}

	m_MusicSwitch->Update();
	m_SFXSwitch->Update();
	m_SoftDropSwitch->Update();
	m_HardDropSwitch->Update();
	m_LandingPreviewSwitch->Update();

	//m_MusicVolumeSlider->Update();
	m_ControlsButton.Update();
	m_BackButton.Update();
}

void OptionsScreen::Draw() {
	//ClearBackground(Globals::Colors::BackgroundColor);

	m_Title.Draw();


	DrawTextEx(Globals::TetrisFont, "Music", m_MusicSwitchTextPos, 28.f, 1.f, WHITE);
	DrawTextEx(Globals::TetrisFont, "SFX", m_SFXSwitchTextPos, 28.f, 1.f, WHITE);
	DrawTextEx(Globals::TetrisFont, "Soft Drop", m_SoftDropSwitchTextPos, 28.f, 1.f, WHITE);
	DrawTextEx(Globals::TetrisFont, "Hard Drop", m_HardDropSwitchTextPos, 28.f, 1.f, WHITE);
	DrawTextEx(Globals::TetrisFont, "Landing Preview", m_LandingPreviewSwitchTextPos, 28.f, 1.f, WHITE);


	m_MusicSwitch->Draw();
	m_SFXSwitch->Draw();
	m_SoftDropSwitch->Draw();
	m_HardDropSwitch->Draw();
	m_LandingPreviewSwitch->Draw();
	
	//m_MusicVolumeSlider->Draw();
	m_ControlsButton.Draw();
	m_BackButton.Draw();

}