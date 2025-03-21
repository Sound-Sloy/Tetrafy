#include "HotkeyWidget.h"

Hotkey::Hotkey(Vec2<int32_t> pos, Vec2<int32_t> size, Vec2<float> origin, KeyboardKey* hotkey, HotkeyProperties properties)
	: m_Pos(pos), m_Size(size), m_Properties(properties)
{
	if (m_Properties.Font == nullptr) {
		m_Properties.Font = &m_DefaultFont;
	}

	if (/*properties.TextureMode*/ true) {
		assert(IsTextureValid(properties.ActiveTexture));
		assert(IsTextureValid(properties.InactiveTexture));
		assert(IsTextureValid(properties.ClickedTexture));
		assert(IsTextureValid(properties.HoveredTexture));
		assert(IsTextureValid(properties.FocusedTexture));

		if (size == Vec2{ 0,0 }) {
			size = { properties.ActiveTexture.width, properties.ActiveTexture.height };
			m_Size = { properties.ActiveTexture.width, properties.ActiveTexture.height };
		}
	}
	

	m_Origin = { (int32_t)(origin.GetX() * size.GetX()), (int32_t)(origin.GetY() * size.GetY())};
	m_pHotkey = hotkey == nullptr ? &m_LocalHotkey : hotkey;

	int32_t xPos = pos.GetX() - m_Origin.GetX() + (int32_t)properties.TextAlignment * size.GetX() / 2;
	float xOrigin = (int32_t)properties.TextAlignment * .5f;

	std::string text = "";

	if (hotkey != nullptr)
		text = Keyboard::KeyNames[*hotkey];

	m_Text = Text(text, { xPos, pos.GetY() - m_Origin.GetY() + size.GetY() / 2 }, { xOrigin, .5f }, *properties.Font, properties.FontSize, properties.FontSpacing, 0.f, properties.ForegroundColor);
}

Hotkey::Hotkey(int32_t posX, int32_t posY, int32_t sizeX, int32_t sizeY, float originX, float originY, KeyboardKey* hotkey, HotkeyProperties properties)
	: Hotkey({ posX, posY }, { sizeX,sizeY }, { originX,originY }, hotkey, properties)
{}

Hotkey::Hotkey(Vec2<int32_t> pos, Vec2<int32_t> size, Vec2<float> origin, HotkeyProperties properties)
	: Hotkey(pos, size, origin, nullptr, properties)
{}

Hotkey::Hotkey(int32_t posX, int32_t posY, int32_t sizeX, int32_t sizeY, float originX, float originY, HotkeyProperties properties)
	: Hotkey({ posX, posY }, { sizeX,sizeY }, { originX,originY }, nullptr, properties)
{}

Hotkey::Hotkey(Vec2<int32_t> pos, Vec2<int32_t> size, HotkeyProperties properties)
	: Hotkey(pos, size, {0.f, 0.f}, nullptr, properties)
{}

Hotkey::Hotkey(int32_t posX, int32_t posY, int32_t sizeX, int32_t sizeY, HotkeyProperties properties)
	: Hotkey({ posX, posY }, { sizeX,sizeY }, { 0.f,0.f }, nullptr, properties)
{}

void Hotkey::Update(float deltaTime) {
	if (!m_bActive) {
		return;
	}
	
	KeyboardKey lastHotkey = *m_pHotkey;

	if (!IsHovered() and IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		m_bFocus = false;
	}

	if (IsClicked()) {
		m_bFocus = !m_bFocus;
		
		if (OnClick) OnClick(m_bFocus);
	}
	else if (IsHovered()) {
		if (OnHover and !m_WasHovered) {
			m_WasHovered = true;
			OnHover();
		}
	}
	else m_WasHovered = false;

	if (!m_bFocus) {
		return;
	}

	KeyboardKey pressedKey = Keyboard::GetKeyPressed();
	*m_pHotkey = pressedKey == KeyboardKey::KEY_NULL ? *m_pHotkey : pressedKey;

	if (pressedKey == KeyboardKey::KEY_ESCAPE) {
		*m_pHotkey = KeyboardKey::KEY_NULL;
		m_bFocus = false;
	}

	if (lastHotkey != *m_pHotkey) {
		
		m_Text.SetText(Keyboard::KeyNames[*m_pHotkey]);
		
		if(OnChange) OnChange(lastHotkey, *m_pHotkey);
	}

	m_PulseClock += deltaTime;
	if (m_PulseClock <= .3f) {
		m_TextPulseShow = true;
	}
	if (m_PulseClock > .3f) {
		m_TextPulseShow = false;
	}
	if (m_PulseClock >= .6f) {
		m_PulseClock -= .6f;
	}
}

void Hotkey::Draw() {

	if (!m_bActive) {
		DrawTexturePro(m_Properties.InactiveTexture, { 0,0,(float)m_Properties.InactiveTexture.width,(float)m_Properties.InactiveTexture.height }, { (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Size.GetX(), (float)m_Size.GetY() }, m_Origin, 0.f, WHITE);
		m_Text.Draw();
	}
	else {
		if (!m_bFocus) {
			DrawTexturePro(m_Properties.ActiveTexture, { 0,0,(float)m_Properties.ActiveTexture.width,(float)m_Properties.ActiveTexture.height }, { (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Size.GetX(), (float)m_Size.GetY() }, m_Origin, 0.f, WHITE);
			m_Text.Draw();
			return;
		}
	}
	if (m_bFocus) {
		DrawTexturePro(m_Properties.FocusedTexture, { 0,0,(float)m_Properties.FocusedTexture.width,(float)m_Properties.FocusedTexture.height }, { (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Size.GetX(), (float)m_Size.GetY() }, m_Origin, 0.f, WHITE);
		if (m_TextPulseShow) m_Text.Draw();
	}

}

bool Hotkey::IsActive() const {
	return m_bActive;
}

void Hotkey::SetActive(bool active) {
	m_bActive = active;
}

bool Hotkey::IsHovered() {
	Vector2 mousePos = GetMousePosition();
	return CheckCollisionPointRec(mousePos,
		{ (float)m_Pos.GetX() - (float)m_Origin.GetX(), (float)m_Pos.GetY() - (float)m_Origin.GetY(),
		(float)m_Size.GetX(), (float)m_Size.GetY() });
}

bool Hotkey::IsClicked() {
	return IsHovered() and IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT);
}

void Hotkey::DrawHoverEffect() {
	if (/*m_Properties.TextureMode */ true) {
		DrawTexturePro(m_Properties.HoveredTexture, { 0,0,(float)m_Properties.HoveredTexture.width,(float)m_Properties.HoveredTexture.height }, { (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Size.GetX(), (float)m_Size.GetY() }, m_Origin, 0.f, WHITE);
		return;
	}
	/*DrawRectangleRounded({ (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Size.GetX(), (float)m_Size.GetY() },
		m_Properties.BorderRoundness, m_Properties.BorderSegments, m_Properties.HoverColor);*/
}

void Hotkey::DrawClickEffect() {
	if (/*m_Properties.TextureMode */ true) {
		DrawTexturePro(m_Properties.ClickedTexture, { 0,0,(float)m_Properties.ClickedTexture.width,(float)m_Properties.ClickedTexture.height }, { (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Size.GetX(), (float)m_Size.GetY() }, m_Origin, 0.f, WHITE);
		return;
	}
	/*DrawRectangleRounded({ (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Size.GetX(), (float)m_Size.GetY() },
		m_Properties.BorderRoundness, m_Properties.BorderSegments, m_Properties.ClickColor);*/
}
