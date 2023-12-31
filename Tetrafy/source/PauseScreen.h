#pragma once
#include "Screen.h"
#include "Switch.h"
#include "Globals.h"
#include "States.h"
#include "Utils.h"
#include "Button.h"
#include "Text.h"

class PauseScreen {
public:
	PauseScreen();

	void Update();
	void Draw();

	void SetActive(bool active);
	bool IsActive() const;

	bool FlagShouldRestartBoard = false;
private:
	bool m_Active = false;

	Text m_TitleText;

	Button m_ResumeButton;
	Button m_RestartButton;
	Button m_ExitButton;
	Button m_OptionsButton;
};