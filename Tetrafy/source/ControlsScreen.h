#pragma once
#include <iostream>
#include "Globals.h"
#include "Text.h"
//#include "KeyInputWidget.h" maybe ????

class ControlsScreen {
public:

	ControlsScreen();

	void Update();
	void Draw();
private:
	Text m_TitleScreen;

	Text m_LeftText;
	Text m_RightText;
	Text m_RotateCWText;
	Text m_RotateCCWText;
	Text m_SoftDropText;
	Text m_HardDropText;
	Text m_HoldText;
};