#include "ControlsScreen.h"

ControlsScreen::ControlsScreen()
{
	m_TitleScreen = Text("Controls", { GetRenderWidth() / 2,125 }, { .5f,.5f }, Globals::TetrisFontBig, 72.f);
	
	int32_t widgetWidth = 300;
	
	m_LeftText = Text("Move Left", {GetRenderWidth() / 2 - widgetWidth / 2, 250}, {0.f, .5f}, Globals::TetrisFont, 28.f);
	m_RightText = Text("Move Right", {GetRenderWidth() / 2 - widgetWidth / 2, 300}, {0.f, .5f}, Globals::TetrisFont, 28.f);
	m_RotateCWText = Text("Rotate CW", {GetRenderWidth() / 2 - widgetWidth / 2, 350}, {0.f, .5f}, Globals::TetrisFont, 28.f);
	m_RotateCCWText = Text("Rotate CCW", {GetRenderWidth() / 2 - widgetWidth / 2, 400}, {0.f, .5f}, Globals::TetrisFont, 28.f);
	m_SoftDropText = Text("Soft Drop", {GetRenderWidth() / 2 - widgetWidth / 2, 450}, {0.f, .5f}, Globals::TetrisFont, 28.f);
	m_HardDropText = Text("Hard Drop", {GetRenderWidth() / 2 - widgetWidth / 2, 500}, {0.f, .5f}, Globals::TetrisFont, 28.f);
	m_HoldText = Text("Hold", {GetRenderWidth() / 2 - widgetWidth / 2, 550}, {0.f, .5f}, Globals::TetrisFont, 28.f);

	HotkeyProperties hotkeyProperties {
		.ActiveTexture = Globals::Textures::HotkeyActive,
		.InactiveTexture = Globals::Textures::HotkeyInactive,
		.HoveredTexture = Globals::Textures::HotkeyHovered,
		.ClickedTexture = Globals::Textures::HotkeyClicked,
		.FocusedTexture = Globals::Textures::HotkeyFocus,
		.Font = &Globals::TetrisFontMedium,
		.FontSize = 20.f,
		.FontSpacing = 1.f
	};

	m_LeftHotkey = new Hotkey({ GetRenderWidth() / 2 + widgetWidth / 2, 250 }, { 0,0 }, { 1.f,.5f }, &Globals::Options.KeyLeft, hotkeyProperties);
	m_RightHotkey = new Hotkey({ GetRenderWidth() / 2 + widgetWidth / 2, 300 }, { 0,0 }, { 1.f,.5f }, &Globals::Options.KeyRight, hotkeyProperties);
	m_RotCWHotkey = new Hotkey({ GetRenderWidth() / 2 + widgetWidth / 2, 350 }, { 0,0 }, { 1.f,.5f }, &Globals::Options.KeyRotateCW, hotkeyProperties);
	m_RotCCWHotkey = new Hotkey({ GetRenderWidth() / 2 + widgetWidth / 2, 400 }, { 0,0 }, { 1.f,.5f }, &Globals::Options.KeyRotateCCW, hotkeyProperties);
	m_SoftDropHotkey = new Hotkey({ GetRenderWidth() / 2 + widgetWidth / 2, 450 }, { 0,0 }, { 1.f,.5f }, &Globals::Options.KeySoftDrop, hotkeyProperties);
	m_HardDropHotkey = new Hotkey({ GetRenderWidth() / 2 + widgetWidth / 2, 500 }, { 0,0 }, { 1.f,.5f }, &Globals::Options.KeyHardDrop, hotkeyProperties);
	m_HoldHotkey = new Hotkey({ GetRenderWidth() / 2 + widgetWidth / 2, 550 }, { 0,0 }, { 1.f,.5f }, &Globals::Options.KeyHold, hotkeyProperties);
}


void ControlsScreen::Update() {
	float deltaTime = GetFrameTime();
	m_LeftHotkey->Update(deltaTime);
	m_RightHotkey->Update(deltaTime);
	m_RotCWHotkey->Update(deltaTime);
	m_RotCCWHotkey->Update(deltaTime);
	m_SoftDropHotkey->Update(deltaTime);
	m_HardDropHotkey->Update(deltaTime);
	m_HoldHotkey->Update(deltaTime);
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

	m_LeftHotkey->Draw();
	m_RightHotkey->Draw();
	m_RotCWHotkey->Draw();
	m_RotCCWHotkey->Draw();
	m_SoftDropHotkey->Draw();
	m_HardDropHotkey->Draw();
	m_HoldHotkey->Draw();
}