#pragma once
#include <iostream>
#include <raylib.h>
#include "Globals.h"
#include "States.h"
#include "Button.h"
#include "Switch.h"
#include "Slider.h"
#include "Vec2.h"
#include "Utils.h"

class OptionsScreen {
public:
	OptionsScreen();

	void Update();
	void Draw();

	
private:
	Switch* m_MusicSwitch;
	Switch* m_SFXSwitch;
	Switch* m_SoftDropSwitch;
	Switch* m_HardDropSwitch;
	Switch* m_LandingPreviewSwitch;
	Button* m_BackButton;
	Slider<float>* m_MusicVolumeSlider;
	Slider<float>* m_SFXVolumeSlider;

	int32_t m_Padding = 30;

	Vec2<int32_t> m_MusicSwitchTextPos = { (728 - 229 - m_Padding - 48)/2,250 };
	Vec2<int32_t> m_SFXSwitchTextPos = { 0,0 };   
	Vec2<int32_t> m_SoftDropSwitchTextPos = { 0,0 };
	Vec2<int32_t> m_HardDropSwitchTextPos = { 0,0 };
	Vec2<int32_t> m_LandingPreviewSwitchTextPos = { 0,0 };
};