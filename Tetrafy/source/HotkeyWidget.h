#pragma once
#include <iostream>
#include <raylib.h>
#include <functional>
#include <unordered_map>
#include <assert.h>
#include "Vec2.h"
#include "Keyboard.h"
#include "Text.h"

#define HotkeyEvent void

enum class HotkeyTextAlignment {
	Left,
	Center,
	Right
};

struct HotkeyProperties {
	Texture2D& ActiveTexture;
	Texture2D& InactiveTexture;
	Texture2D& HoveredTexture;
	Texture2D& ClickedTexture;
	Texture2D& FocusedTexture;

	HotkeyTextAlignment TextAlignment = HotkeyTextAlignment::Center;
	Font* Font = nullptr;
	float FontSize = 16.f;
	float FontSpacing = 1.f;

	Color ForegroundColor = WHITE;
};

class Hotkey {
public:
	Hotkey() = default;
	
	/// <summary>
	/// The most explicit constructor
	/// </summary>
	/// <param name="pos">The pos</param>
	/// <param name="size">On texture mode, if size == {0,0} then size will be the size of ActiveTexture.</param>
	/// <param name="origin">The origin. Range [0.f,1.f]; {.60f, .20f} => 60% of size.x and 20% of size.y</param>
	/// <param name="hotkey">The variable to modify & get the starting value. Leave as nullptr to disable this feature (SetHotkey() & GetHotkey() can be used instead)</param>
	/// <param name="properties">HotkeyProperties object</param>
	Hotkey(Vec2<int32_t> pos, Vec2<int32_t> size, Vec2<float> origin, KeyboardKey* hotkey, HotkeyProperties properties);
	Hotkey(int32_t posX, int32_t posY, int32_t sizeX, int32_t sizeY, float originX, float originY, KeyboardKey* hotkey, HotkeyProperties properties);
	Hotkey(Vec2<int32_t> pos, Vec2<int32_t> size, Vec2<float> origin, HotkeyProperties properties);
	Hotkey(int32_t posX, int32_t posY, int32_t sizeX, int32_t sizeY, float originX, float originY, HotkeyProperties properties);
	Hotkey(Vec2<int32_t> pos, Vec2<int32_t> size, HotkeyProperties properties);
	Hotkey(int32_t posX, int32_t posY, int32_t sizeX, int32_t sizeY, HotkeyProperties properties);

	void Update(float deltaTime);
	void Draw();

	bool IsActive() const;
	void SetActive(bool active = true);

	/// <summary>
	/// HotkeyEvent OnChange(KeyboardKey lastHotkey, KeyboardKey newHotkey)
	/// </summary>
	std::function<HotkeyEvent(KeyboardKey, KeyboardKey)> OnChange = nullptr;
	std::function<HotkeyEvent()> OnHover = nullptr;
	/// <summary>
	/// HotkeyEvent OnClick(bool focus)
	/// focus = true if the widget accepts input. Else, focus = false
	/// </summary>
	std::function<HotkeyEvent(bool focus)> OnClick = nullptr;

private:
	Vec2<int32_t> m_Pos = { 0,0 };
	Vec2<int32_t> m_Size = { 75,40 };
	Vec2<int32_t> m_Origin = { 0,0 };
	bool m_bActive = true;
	bool m_bFocus = false;
	bool m_WasHovered = false;
	float m_PulseClock = 0.f;
	bool m_TextPulseShow = true;

	Font m_DefaultFont = GetFontDefault();
	
	HotkeyProperties m_Properties;
	KeyboardKey m_LocalHotkey = KeyboardKey::KEY_NULL;
	KeyboardKey* m_pHotkey = &m_LocalHotkey;

	Text m_Text;

	bool IsHovered();
	bool IsClicked();

	void DrawHoverEffect();
	void DrawClickEffect();
};