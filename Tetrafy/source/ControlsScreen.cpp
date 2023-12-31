#include "ControlsScreen.h"

ControlsScreen::ControlsScreen()
{
	m_TitleScreen = Text("Controls", { GetRenderWidth() / 2,125 }, { .5f,.5f }, Globals::TetrisFontBig, 72.f);
	
	int32_t widgetWidth = 300;
	
	m_LeftText = Text("Move Left", {GetRenderWidth() / 2 - widgetWidth / 2, 250}, {0.f, 0.f}, Globals::TetrisFont, 28.f);
	m_RightText = Text("Move Right", {GetRenderWidth() / 2 - widgetWidth / 2, 300}, {0.f, 0.f}, Globals::TetrisFont, 28.f);
	m_RotateCWText = Text("Rotate CW", {GetRenderWidth() / 2 - widgetWidth / 2, 350}, {0.f, 0.f}, Globals::TetrisFont, 28.f);
	m_RotateCCWText = Text("Rotate CCW", {GetRenderWidth() / 2 - widgetWidth / 2, 400}, {0.f, 0.f}, Globals::TetrisFont, 28.f);
	m_SoftDropText = Text("Soft Drop", {GetRenderWidth() / 2 - widgetWidth / 2, 450}, {0.f, 0.f}, Globals::TetrisFont, 28.f);
	m_HardDropText = Text("Hard Drop", {GetRenderWidth() / 2 - widgetWidth / 2, 500}, {0.f, 0.f}, Globals::TetrisFont, 28.f);
	m_HoldText = Text("Hold", {GetRenderWidth() / 2 - widgetWidth / 2, 550}, {0.f, 0.f}, Globals::TetrisFont, 28.f);
}


void ControlsScreen::Update() {

}

void ControlsScreen::Draw() {
	m_TitleScreen.Draw();
	m_LeftText.Draw();
	m_RightText.Draw();
	m_RotateCWText.Draw();
	m_RotateCCWText.Draw();
	m_SoftDropText.Draw();
	m_HardDropText.Draw();
	m_HoldText.Draw();
}