#include "OptionsScreen.h"

OptionsScreen::OptionsScreen()
{
	m_Padding *= Globals::Options.GUIScale;
	m_Title = Text("Options", { GetRenderWidth() / 2,static_cast<int>(125 * Globals::Options.GUIScale) }, { .5f,.5f }, Globals::TetrisFontBig, 72.f * Globals::Options.GUIScale);

	m_MusicSwitchTextPos.SetX(static_cast<int32_t>(Globals::Options.GUIScale * m_MusicSwitchTextPos.GetX()));
	m_MusicSwitchTextPos.SetY(static_cast<int32_t>(Globals::Options.GUIScale * m_MusicSwitchTextPos.GetY()));

	Vector2 musicSwitchTextMeasurements = MeasureTextEx(Globals::TetrisFont, "Music", 28.f * Globals::Options.GUIScale, 1.f);
	Vector2 SFXSwitchTextMeasurements = MeasureTextEx(Globals::TetrisFont, "SFX", 28.f * Globals::Options.GUIScale, 1.f);
	Vector2 softDropSwitchTextMeasurements = MeasureTextEx(Globals::TetrisFont, "Soft Drop", 28.f * Globals::Options.GUIScale, 1.f);
	Vector2 hardDropSwitchTextMeasurements = MeasureTextEx(Globals::TetrisFont, "Hard Drop", 28.f * Globals::Options.GUIScale, 1.f);
	Vector2 landingPrevwSwitchTextMeasurements = MeasureTextEx(Globals::TetrisFont, "Landing Preview", 28.f * Globals::Options.GUIScale, 1.f);
	Vector2 guiScaleCounterTextMeasurements = MeasureTextEx(Globals::TetrisFont, "GUI Scale", 28.f * Globals::Options.GUIScale, 1.f);
	Vector2 animatedBackgroundSwitchMeasurements = MeasureTextEx(Globals::TetrisFont, "Animated Background", 28.f * Globals::Options.GUIScale, 1.f);

	SwitchProperties switchProperties{
		.Size = { static_cast<int>(48 * Globals::Options.GUIScale),static_cast<int>(24 * Globals::Options.GUIScale) },
		.OnTexture = Globals::Textures::SwitchOn,
		.OffTexture = Globals::Textures::SwitchOff,
		.InactiveTexture = Globals::Textures::SwitchOff
	};

	CounterProperties counterProperties{
		.Font = &Globals::TetrisFont,
		.FontSize = 28.f * Globals::Options.GUIScale,
		.Size = { static_cast<int>(48 * Globals::Options.GUIScale),static_cast<int>(24 * Globals::Options.GUIScale) },
		.Values = Globals::GUIScales,
		.BorderSegments = 32,
	};


	int32_t maxX = static_cast<int32_t>(Utils::max<float>({
		musicSwitchTextMeasurements.x, SFXSwitchTextMeasurements.x, softDropSwitchTextMeasurements.x,
		hardDropSwitchTextMeasurements.x, landingPrevwSwitchTextMeasurements.x, guiScaleCounterTextMeasurements.x, animatedBackgroundSwitchMeasurements.x
	}));

	m_MusicSwitchTextPos.SetX((GetRenderWidth() - maxX - m_Padding - 48) / 2);
	m_SFXSwitchTextPos = m_MusicSwitchTextPos + Vec2<int32_t>{0, (int32_t)musicSwitchTextMeasurements.y + m_Padding};
	m_SoftDropSwitchTextPos = m_SFXSwitchTextPos + Vec2<int32_t>{0, (int32_t)SFXSwitchTextMeasurements.y + m_Padding};
	m_HardDropSwitchTextPos = m_SoftDropSwitchTextPos + Vec2<int32_t>{0, (int32_t)softDropSwitchTextMeasurements.y + m_Padding};
	m_LandingPreviewSwitchTextPos = m_HardDropSwitchTextPos + Vec2<int32_t>{0, (int32_t)hardDropSwitchTextMeasurements.y + m_Padding};
	m_GUIScaleCounterTextPos = m_LandingPreviewSwitchTextPos + Vec2<int32_t>{0, (int32_t)landingPrevwSwitchTextMeasurements.y + m_Padding};
	m_AnimatedBackgroundTextPos = m_GUIScaleCounterTextPos + Vec2<int32_t>{0, (int32_t)guiScaleCounterTextMeasurements.y + m_Padding};

	int32_t switchXCoord = m_MusicSwitchTextPos.GetX() + maxX + m_Padding;
	Vec2<int32_t> musicSwitchPos				= { switchXCoord, m_MusicSwitchTextPos.GetY() + (int32_t)(musicSwitchTextMeasurements.y - switchProperties.Size.GetY()) / 2};
	Vec2<int32_t> SFXSwitchPos					= { switchXCoord, m_SFXSwitchTextPos.GetY() + (int32_t)(SFXSwitchTextMeasurements.y - switchProperties.Size.GetY()) / 2 };
	Vec2<int32_t> softDropSwitchPos				= { switchXCoord, m_SoftDropSwitchTextPos.GetY() + (int32_t)(softDropSwitchTextMeasurements.y - switchProperties.Size.GetY()) / 2 };
	Vec2<int32_t> hardDropSwitchPos				= { switchXCoord, m_HardDropSwitchTextPos.GetY() + (int32_t)(hardDropSwitchTextMeasurements.y - switchProperties.Size.GetY()) / 2 };
	Vec2<int32_t> landingPrevwSwitchPos			= { switchXCoord, m_LandingPreviewSwitchTextPos.GetY() + (int32_t)(landingPrevwSwitchTextMeasurements.y - switchProperties.Size.GetY()) / 2 };
	Vec2<int32_t> guiScaleCounterPos			= { switchXCoord, m_GUIScaleCounterTextPos.GetY() + (int32_t)(guiScaleCounterTextMeasurements.y - counterProperties.Size.GetY()) / 2};
	Vec2<int32_t> animatedBackgroundSwitchPos	= { switchXCoord, m_AnimatedBackgroundTextPos.GetY() + (int32_t)(animatedBackgroundSwitchMeasurements.y - switchProperties.Size.GetY()) / 2};

	m_MusicSwitch					= std::make_unique<Switch>(musicSwitchPos, switchProperties);
	m_SFXSwitch						= std::make_unique<Switch>(SFXSwitchPos, switchProperties);
	m_SoftDropSwitch				= std::make_unique<Switch>(softDropSwitchPos, switchProperties);
	m_HardDropSwitch				= std::make_unique<Switch>(hardDropSwitchPos, switchProperties);
	m_LandingPreviewSwitch			= std::make_unique<Switch>(landingPrevwSwitchPos, switchProperties);
	m_GUIScaleCounter				= std::make_unique<Counter>(guiScaleCounterPos, counterProperties);
	m_AnimatedBackgroundSwitch		= std::make_unique<Switch>(animatedBackgroundSwitchPos, switchProperties);

	m_MusicSwitch->SetState(static_cast<SwitchStatesE>(Globals::Options.MusicToggle));
	m_SFXSwitch->SetState(static_cast<SwitchStatesE>(Globals::Options.SFXToggle));
	m_SoftDropSwitch->SetState(static_cast<SwitchStatesE>(Globals::Options.SoftDropToggle));
	m_HardDropSwitch->SetState(static_cast<SwitchStatesE>(Globals::Options.HardDropToggle));
	m_LandingPreviewSwitch->SetState(static_cast<SwitchStatesE>(Globals::Options.LandingPreviewToggle));
	m_GUIScaleCounter->SetIndex(Globals::GUIScaleToIndexMap[Globals::Options.GUIScale]);
	m_AnimatedBackgroundSwitch->SetState(static_cast<SwitchStatesE>(Globals::Options.AnimatedBackgroundToggle));



	m_MusicSwitch->OnHover = [](Vec2<int32_t>) { Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };
	m_SFXSwitch->OnHover = [](Vec2<int32_t>) { Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };
	m_SoftDropSwitch->OnHover = [](Vec2<int32_t>) { Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };
	m_HardDropSwitch->OnHover = [](Vec2<int32_t>) { Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };
	m_LandingPreviewSwitch->OnHover = [](Vec2<int32_t>) { Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };
	m_GUIScaleCounter->OnHover = [](Vec2<int32_t>) { Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };
	m_AnimatedBackgroundSwitch->OnHover = [](Vec2<int32_t>) { Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };


	m_MusicSwitch->OnChange = [this](SwitchStatesE state) {Globals::Options.MusicToggle = (bool)state;/* m_MusicVolumeSlider->SetActive((bool)state);*/ };
	m_SFXSwitch->OnChange = [](SwitchStatesE state) {Globals::Options.SFXToggle = (bool)state; };
	m_SoftDropSwitch->OnChange = [](SwitchStatesE state) { Globals::Options.SoftDropToggle = (bool)state; };
	m_HardDropSwitch->OnChange = [](SwitchStatesE state) { Globals::Options.HardDropToggle = (bool)state; };
	m_LandingPreviewSwitch->OnChange = [](SwitchStatesE state) {Globals::Options.LandingPreviewToggle = (bool)state; };
	m_GUIScaleCounter->OnChange = [](std::string val, int32_t ind) {Globals::Options.GUIScale = 1 + 0.1 * ind; States::Flags::ForceReconstructScreens = true; States::Flags::ForceReloadAssets = true; };
	m_AnimatedBackgroundSwitch->OnChange = [](SwitchStatesE state) {Globals::Options.AnimatedBackgroundToggle = (bool)state; };
		
	
	SliderProperties<float> sliderProperties{
		.BaseTexture = Globals::Textures::SliderBase,
		.HighlightTexture = Globals::Textures::SliderHighlight,
		.HandleTexture = Globals::Textures::SliderHandle,
		.LowerLimit = 0,
		.UpperLimit = 100,
		.Step = .1f
	};

	SliderProperties<float> guiScaleSliderProperties{
		.BaseTexture = Globals::Textures::SliderBase,
		.HighlightTexture = Globals::Textures::SliderHighlight,
		.HandleTexture = Globals::Textures::SliderHandle,
		.LowerLimit = 1,
		.UpperLimit = 2,
		.Step = .2f
	};

	//m_MusicVolumeSlider = std:::make_unique<Slider<float>>({300, 300}, nullptr, sliderProperties);
	//m_MusicVolumeSlider->OnChange = [](int32_t prevVal, int32_t newVal) {Globals::Values.MusicVolume = newVal / 100.f; };
	//m_MusicVolumeSlider->SetValue(Globals::Values.MusicVolume * 100.f);

	ButtonProperties buttonProperties{
		.Font = &Globals::TetrisFont,
		.FontSize = 28.f * Globals::Options.GUIScale,
		.BorderSegments = 32
	};

	Vec2<int32_t> size = {static_cast<int>(200 * Globals::Options.GUIScale), static_cast<int>(50 * Globals::Options.GUIScale) };
	m_ControlsButton = Button({ (GetRenderWidth() - size.GetX()) / 2, static_cast<int>(570 * Globals::Options.GUIScale) }, size, "Controls", buttonProperties);
	
	m_ControlsButton.OnClick = []() {
		States::ChangeScreen(ScreensE::Controls);
		Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::ClickSound);
	};
	m_ControlsButton.OnHover = []() {
		Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound);
	};

	m_BackButton = Button({ (GetRenderWidth() - size.GetX()) / 2, static_cast<int>(650 * Globals::Options.GUIScale) }, size, "Back",
	                      buttonProperties);
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

	m_GUIScaleCounter->SetActive(m_ScrBefOptions != ScreensE::Pause);

	m_MusicSwitch->Update();
	m_SFXSwitch->Update();
	m_SoftDropSwitch->Update();
	m_HardDropSwitch->Update();
	m_LandingPreviewSwitch->Update();
	m_GUIScaleCounter->Update();
	m_AnimatedBackgroundSwitch->Update();

	//m_MusicVolumeSlider->Update();
	m_ControlsButton.Update();
	m_BackButton.Update();
}

void OptionsScreen::Draw() {
	//ClearBackground(Globals::Colors::BackgroundColor);

	m_Title.Draw();


	DrawTextEx(Globals::TetrisFont, "Music", m_MusicSwitchTextPos.CastAs<Vector2, float>(), 28.f * Globals::Options.GUIScale, 1.f, WHITE);
	DrawTextEx(Globals::TetrisFont, "SFX", m_SFXSwitchTextPos.CastAs<Vector2, float>(), 28.f * Globals::Options.GUIScale, 1.f, WHITE);
	DrawTextEx(Globals::TetrisFont, "Soft Drop", m_SoftDropSwitchTextPos.CastAs<Vector2, float>(), 28.f * Globals::Options.GUIScale, 1.f, WHITE);
	DrawTextEx(Globals::TetrisFont, "Hard Drop", m_HardDropSwitchTextPos.CastAs<Vector2, float>(), 28.f * Globals::Options.GUIScale, 1.f, WHITE);
	DrawTextEx(Globals::TetrisFont, "Landing Preview", m_LandingPreviewSwitchTextPos.CastAs<Vector2, float>(), 28.f * Globals::Options.GUIScale, 1.f, WHITE);
	DrawTextEx(Globals::TetrisFont, "GUI Scale", m_GUIScaleCounterTextPos.CastAs<Vector2, float>(), 28.f * Globals::Options.GUIScale, 1.f, m_ScrBefOptions != ScreensE::Pause ? WHITE : DARKGRAY);
	DrawTextEx(Globals::TetrisFont, "Animated Background", m_AnimatedBackgroundTextPos.CastAs<Vector2, float>(), 28.f * Globals::Options.GUIScale, 1.f, WHITE);


	m_MusicSwitch->Draw();
	m_SFXSwitch->Draw();
	m_SoftDropSwitch->Draw();
	m_HardDropSwitch->Draw();
	m_LandingPreviewSwitch->Draw();
	m_GUIScaleCounter->Draw();
	m_AnimatedBackgroundSwitch->Draw();

	
	//m_MusicVolumeSlider->Draw();
	m_ControlsButton.Draw();
	m_BackButton.Draw();

}