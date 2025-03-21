#include "Switch.h"

Switch::Switch(Vec2<int32_t> pos, SwitchProperties properties) :
	m_Pos(pos), m_Properties(properties), m_State(properties.StartingState)
{
	if (!IsTextureValid(m_Properties.InactiveTexture) or !IsTextureValid(m_Properties.OffTexture) or !IsTextureValid(m_Properties.OnTexture)) {
		TraceLog(LOG_FATAL, "Trying to initialize Switch when textures are not ready");
		return;
	}
	if (m_Properties.Size == Vec2{ 0,0 }) {
		m_Properties.Size = { m_Properties.OnTexture.width, m_Properties.OnTexture.height };
	}
}

void Switch::Update() {
	if (IsClicked() and m_bActive) {
		Toggle();
		if (OnChange) OnChange(m_State);
	}
}

void Switch::Draw() {
	if (!m_bActive) {
		DrawTexturePro(m_Properties.InactiveTexture, { 0,0,(float)m_Properties.InactiveTexture.width, (float)m_Properties.InactiveTexture.height }, { (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Properties.Size.GetX(), (float)m_Properties.Size.GetY() }, { 0,0 }, 0.f, WHITE);
		return;
	}

	switch (m_State) {
	case SwitchStatesE::ON: {
		DrawTexturePro(m_Properties.OnTexture, { 0,0,(float)m_Properties.OnTexture.width, (float)m_Properties.OnTexture.height }, { (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Properties.Size.GetX(), (float)m_Properties.Size.GetY() }, { 0,0 }, 0.f, WHITE);
		break;
	}
	case SwitchStatesE::OFF: {
		DrawTexturePro(m_Properties.OffTexture, { 0,0,(float)m_Properties.OffTexture.width, (float)m_Properties.OffTexture.height }, { (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Properties.Size.GetX(), (float)m_Properties.Size.GetY() }, { 0,0 }, 0.f, WHITE);
		break;
	}
	}
}

void Switch::Toggle() {
	m_State = (SwitchStatesE)(!(int32_t)m_State);
}

SwitchStatesE Switch::GetState() const {
	return m_State;
}

void Switch::SetState(SwitchStatesE state) {
	m_State = state;
}

void Switch::SetActive(bool active)
{
	m_bActive = active;
}

bool Switch::IsActive() const {
	return m_bActive;
}

SwitchProperties Switch::GetProperties() const {
	return m_Properties;
}

bool Switch::IsHovered() {
	if (!m_bActive) return false;
	Vector2 mousePos = GetMousePosition();
	if (mousePos.x >= m_Pos.GetX() and mousePos.x < m_Pos.GetX() + m_Properties.Size.GetX()
		and mousePos.y >= m_Pos.GetY() and mousePos.y < m_Pos.GetY() + m_Properties.Size.GetY())
	{
		if (this->OnHover and !m_WasHovered) {
			this->OnHover({(int32_t)mousePos.x,(int32_t)mousePos.y});
		}
		m_WasHovered = true;
		return true;
	}
	m_WasHovered = false;
	return false;
}

bool Switch::IsClicked() {
	if (!m_bActive) return false;
	if (IsHovered() and IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT)) {
		if (this->OnClick) {
			this->OnClick();
		}
		return true;
	}
	return false;
}