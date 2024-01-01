#pragma once
#include <iostream>
#include "Globals.h"
#include "Text.h"
#include "HotkeyWidget.h"
#include "Button.h"
#include "States.h"

class ControlsScreen {
public:

	ControlsScreen();

	void Update();
	void Draw();
private:
	Text m_Title;

	Text m_LeftText;
	Text m_RightText;
	Text m_RotateCWText;
	Text m_RotateCCWText;
	Text m_SoftDropText;
	Text m_HardDropText;
	Text m_HoldText;

	std::unique_ptr<Hotkey> m_LeftHotkey;
	std::unique_ptr<Hotkey> m_RightHotkey;
	std::unique_ptr<Hotkey> m_RotCWHotkey;
	std::unique_ptr<Hotkey> m_RotCCWHotkey;
	std::unique_ptr<Hotkey> m_SoftDropHotkey;
	std::unique_ptr<Hotkey> m_HardDropHotkey;
	std::unique_ptr<Hotkey> m_HoldHotkey;

	Button m_BackButton;
};