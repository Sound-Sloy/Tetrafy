#include "ControlsScreen.h"

ControlsScreen::ControlsScreen()
{
	m_Title = Text("Controls", { GetRenderWidth() / 2,125 }, { .5f,.5f }, Globals::TetrisFontBig, 72.f);
	
	int32_t widgetWidth = 300;
	
	m_LeftText		= Text("Move Left", {GetRenderWidth() / 2 - widgetWidth / 2, 250}, {0.f, .5f}, Globals::TetrisFont, 28.f);
	m_RightText		= Text("Move Right", {GetRenderWidth() / 2 - widgetWidth / 2, 300}, {0.f, .5f}, Globals::TetrisFont, 28.f);
	m_RotateCWText	= Text("Rotate CW", {GetRenderWidth() / 2 - widgetWidth / 2, 350}, {0.f, .5f}, Globals::TetrisFont, 28.f);
	m_RotateCCWText	= Text("Rotate CCW", {GetRenderWidth() / 2 - widgetWidth / 2, 400}, {0.f, .5f}, Globals::TetrisFont, 28.f);
	m_SoftDropText	= Text("Soft Drop", {GetRenderWidth() / 2 - widgetWidth / 2, 450}, {0.f, .5f}, Globals::TetrisFont, 28.f);
	m_HardDropText	= Text("Hard Drop", {GetRenderWidth() / 2 - widgetWidth / 2, 500}, {0.f, .5f}, Globals::TetrisFont, 28.f);
	m_HoldText		= Text("Hold", {GetRenderWidth() / 2 - widgetWidth / 2, 550}, {0.f, .5f}, Globals::TetrisFont, 28.f);

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

	m_LeftHotkey		= std::make_unique<Hotkey>(Vec2{ GetRenderWidth() / 2 + widgetWidth / 2, 250 }, Vec2{ 0,0 }, Vec2{ 1.f,.5f }, &Globals::Options.KeyLeft, hotkeyProperties);
	m_RightHotkey		= std::make_unique<Hotkey>(Vec2{ GetRenderWidth() / 2 + widgetWidth / 2, 300 }, Vec2{ 0,0 }, Vec2{ 1.f,.5f }, &Globals::Options.KeyRight, hotkeyProperties);
	m_RotCWHotkey		= std::make_unique<Hotkey>(Vec2{ GetRenderWidth() / 2 + widgetWidth / 2, 350 }, Vec2{ 0,0 }, Vec2{ 1.f,.5f }, &Globals::Options.KeyRotateCW, hotkeyProperties);
	m_RotCCWHotkey		= std::make_unique<Hotkey>(Vec2{ GetRenderWidth() / 2 + widgetWidth / 2, 400 }, Vec2{ 0,0 }, Vec2{ 1.f,.5f }, &Globals::Options.KeyRotateCCW, hotkeyProperties);
	m_SoftDropHotkey	= std::make_unique<Hotkey>(Vec2{ GetRenderWidth() / 2 + widgetWidth / 2, 450 }, Vec2{ 0,0 }, Vec2{ 1.f,.5f }, &Globals::Options.KeySoftDrop, hotkeyProperties);
	m_HardDropHotkey	= std::make_unique<Hotkey>(Vec2{ GetRenderWidth() / 2 + widgetWidth / 2, 500 }, Vec2{ 0,0 }, Vec2{ 1.f,.5f }, &Globals::Options.KeyHardDrop, hotkeyProperties);
	m_HoldHotkey		= std::make_unique<Hotkey>(Vec2{ GetRenderWidth() / 2 + widgetWidth / 2, 550 }, Vec2{ 0,0 }, Vec2{ 1.f,.5f }, &Globals::Options.KeyHold, hotkeyProperties);

	m_LeftHotkey->OnHover		= []() {Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };
	m_RightHotkey->OnHover		= []() {Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };
	m_RotCWHotkey->OnHover		= []() {Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };
	m_RotCCWHotkey->OnHover		= []() {Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };
	m_SoftDropHotkey->OnHover	= []() {Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };
	m_HardDropHotkey->OnHover	= []() {Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };
	m_HoldHotkey->OnHover		= []() {Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound); };

	m_LeftHotkey->OnClick		= [](bool currstate) {Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::ClickSound); };
	m_RightHotkey->OnClick		= [](bool currstate) {Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::ClickSound); };
	m_RotCWHotkey->OnClick		= [](bool currstate) {Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::ClickSound); };
	m_RotCCWHotkey->OnClick		= [](bool currstate) {Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::ClickSound); };
	m_SoftDropHotkey->OnClick	= [](bool currstate) {Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::ClickSound); };
	m_HardDropHotkey->OnClick	= [](bool currstate) {Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::ClickSound); };
	m_HoldHotkey->OnClick		= [](bool currstate) {Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::ClickSound); };

	ButtonProperties buttonProperties = {
		.TextAlignment = ButtonTextAlignment::Center,
		.Font = &Globals::TetrisFont,
		.FontSize = 28.f,
		.FontSpacing = 1.f
	};
	m_BackButton = Button({ {GetRenderWidth() / 2 - 200 / 2, 650}, {200,50}, "Back", buttonProperties });
	m_BackButton.OnClick = []() {
		States::ChangeScreen(States::LastScreen);
		Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::ClickSound);
	};
	m_BackButton.OnHover = []() {
		Globals::SoundManagerInstance->PlaySoundNowUnique(Globals::Sounds::HoverSound);
	};
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

	m_BackButton.Update();
}

void ControlsScreen::Draw() {
	m_Title.Draw();
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

	m_BackButton.Draw();
}