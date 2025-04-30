#pragma once
#include <iostream>
#include <raylib.h>
#include "Globals.h"
#include "States.h"
#include "Button.h"
#include "Switch.h"
#include "Slider.h"
#include "Counter.h"
#include "Vec2.h"
#include "Utils.h"
#include "Text.h"

class OptionsScreen {
public:
	OptionsScreen();

	void Update();
	void Draw();

	
private:
	ScreensE m_ScrBefOptions = ScreensE::None;

	Text m_Title;
	std::unique_ptr<Switch> m_MusicSwitch = nullptr;
	std::unique_ptr<Switch> m_SFXSwitch = nullptr;
	std::unique_ptr<Switch> m_SoftDropSwitch = nullptr;
	std::unique_ptr<Switch> m_HardDropSwitch = nullptr;
	std::unique_ptr<Switch> m_LandingPreviewSwitch = nullptr;
	std::unique_ptr<Switch> m_AnimatedBackgroundSwitch = nullptr;
	Button m_BackButton;
	Button m_ControlsButton;
	std::unique_ptr<Counter> m_GUIScaleCounter = nullptr;
	//Slider<float>* m_MusicVolumeSlider;
	//Slider<float>* m_SFXVolumeSlider;


	int32_t m_Padding = 15;

	Vec2<int32_t> m_MusicSwitchTextPos = { (728 - 229 - m_Padding - 48)/2,200 };
	Vec2<int32_t> m_SFXSwitchTextPos = { 0,0 };   
	Vec2<int32_t> m_SoftDropSwitchTextPos = { 0,0 };
	Vec2<int32_t> m_HardDropSwitchTextPos = { 0,0 };
	Vec2<int32_t> m_LandingPreviewSwitchTextPos = { 0,0 };
	Vec2<int32_t> m_GUIScaleCounterTextPos = { 0,0 };
	Vec2<int32_t> m_AnimatedBackgroundTextPos = { 0,0 };
};