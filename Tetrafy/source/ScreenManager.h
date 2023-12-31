#pragma once
#include <iostream>
#include "ScreensEnum.h"
#include "PauseScreen.h"
#include "OptionsScreen.h"
#include "MainScreen.h"
#include "Board.h"
#include "States.h"
#include "ControlsScreen.h"

class ScreenManager {
public:
	ScreenManager();

	void SetScreen(ScreensE screen);
	ScreensE GetCurrentScreen() const;

	void Update(float deltaTime);
	void Draw();

	ScreenManager* GetInstance() const;
	const PauseScreen* PauseScreenInstance;

private:
	ScreensE& m_Screen = States::CurrentScreen;

	std::unique_ptr<Board> m_Board;
	PauseScreen m_PauseScreen;
	OptionsScreen* m_OptionsScreen = new OptionsScreen();
	MainScreen* m_MainScreen = new MainScreen();
	ControlsScreen m_ControlsScreen;
};

//#endif