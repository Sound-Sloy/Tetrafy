#pragma once
#include <iostream>
#include <raylib.h>
#include "Button.h"
#include "Globals.h"
#include "States.h"

class MainScreen {
public:
	MainScreen();
	void Update();
	void Draw();
private:
	Button* m_PlayButton;
	Button* m_OptionsButton;
	Button* m_ExitButton;
	//TextureButton* m_OptionsTexButton;

	Vector2 m_TitleTextMeasurements = { 0.f,0.f };
};