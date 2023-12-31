#pragma once
#include <iostream>
#include <raylib.h>
#include <functional>
#include "Vec2.h"
#include "Globals.h"

template <typename T>
struct SliderProperties {
	Vec2<int32_t> Size = { 0,0 };

	Texture2D& BaseTexture;
	Texture2D& HighlightTexture;
	Texture2D& HandleTexture;

	T LowerLimit = 0;
	T UpperLimit = 0;
	T Step = 1;
};

template <typename T>
class Slider {
public:
	Slider() = default;
	Slider(Vec2<int32_t> pos, T* variable, SliderProperties<T> properties)
		: m_Pos(pos), m_Properties(properties)
	{
		if (variable != nullptr) {
			m_Value = variable;
		}
		if (m_Properties.Size == Vec2{0, 0}) {
			m_Properties.Size = {(int32_t)m_Properties.BaseTexture.width, (int32_t)m_Properties.BaseTexture.height};
		}
	}

	~Slider() = default;

	void SetValue(T value) {
		*m_Value = value;
	}
	T GetValue() const {
		return *m_Value;
	}

	void SetActive(bool active = true) {
		m_bActive = active;
	}
	bool IsActive() const {
		return m_bActive;
	}

	void Update() {
		if (!IsTextureReady(m_Properties.BaseTexture) or !IsTextureReady(m_Properties.HighlightTexture) or !IsTextureReady(m_Properties.HandleTexture)) {
			TraceLog(LOG_FATAL, "Invalid Slider Texture. Skipping Update call");
			return;
		}
		if (m_Properties.Size == Vec2{0, 0}) {
			m_Properties.Size = { m_Properties.BaseTexture.width, m_Properties.BaseTexture.height };
		}
		m_StepSize = (float)m_Properties.Size.GetX() / (float)(m_Properties.UpperLimit - m_Properties.LowerLimit);

		T lastValue = *m_Value;
		if (IsHandleGrabbed()) {
			float deltaX = GetMouseDelta().x;
			*m_Value += deltaX / m_StepSize;
		}
		if (OnChange and lastValue != *m_Value) {
			OnChange(lastValue, *m_Value);
		}

		if (*m_Value > m_Properties.UpperLimit) {
			*m_Value = m_Properties.UpperLimit;
		}
		if (*m_Value < m_Properties.LowerLimit) {
			*m_Value = m_Properties.LowerLimit;
		}

		m_HandlePos = m_Pos.GetX() + (*m_Value) * m_StepSize;
		m_HighlightLength = (*m_Value) * m_StepSize;
	}
	void Draw() {
		DrawTexturePro(m_Properties.BaseTexture,
			{ 0.f,0.f,(float)m_Properties.BaseTexture.width, (float)m_Properties.BaseTexture.height },
			{ (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Properties.Size.GetX(), (float)m_Properties.Size.GetY() },
			{ 0.f,0.f }, 0.f, WHITE);
		if (m_bActive) {
			DrawTexturePro(m_Properties.HighlightTexture,
				{ 0.f,0.f,(float)m_HighlightLength, (float)m_Properties.BaseTexture.height },
				{ (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_HighlightLength, (float)m_Properties.Size.GetY() },
				{ 0.f,0.f }, 0.f, WHITE);
			DrawTexturePro(m_Properties.HandleTexture,
				{ 0.f,0.f,(float)m_Properties.HandleTexture.width, (float)m_Properties.HandleTexture.height },
				{ (float)m_HandlePos - m_Properties.HandleTexture.width / 2, (float)m_Pos.GetY() + (float)(m_Properties.Size.GetY() - m_Properties.HandleTexture.height) / 2.f, (float)m_Properties.HandleTexture.width, (float)m_Properties.HandleTexture.height },
				{ 0.f,0.f }, 0.f, WHITE);
		}
	}

	std::function<void(T, T)> OnChange = nullptr;
	std::function<void()> OnClick = nullptr;
	std::function<void(Vec2<int32_t>)> OnHover = nullptr;
private:
	Vec2<int32_t> m_Pos = {0,0};
	int32_t m_HandlePos = 0; // The pos of the handle's center
	int32_t m_HighlightLength = 0;
	SliderProperties<T> m_Properties;
	T* m_Value = new T;
	float m_StepSize = 0;
	
	bool m_bActive = true;
	bool m_WasHovered = false;

	bool IsHovered() {
		if (!m_bActive) return false;
		Vector2 mousePos = GetMousePosition();
		if (mousePos.x >= m_Pos.GetX() and mousePos.x < m_Pos.GetX() + m_Properties.Size.GetX()
			and mousePos.y >= m_Pos.GetY() and mousePos.y < m_Pos.GetY() + m_Properties.Size.GetY())
		{
			if (OnHover and !m_WasHovered) {
				OnHover({ (int32_t)mousePos.x,(int32_t)mousePos.y });
			}
			m_WasHovered = true;
			return true;
		}
		m_WasHovered = false;
		return false;
	}

	bool IsClicked() {
		if (!m_bActive) {
			return false;
		}
		if (IsHovered() and IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT)) {
			if (OnClick) OnClick();
			return true;
		}
		return false;
	}

	bool IsHandleHovered() {
		if (!m_bActive) return false;
		Vector2 mousePos = GetMousePosition();
		if (mousePos.x >= (float)m_HandlePos - (float)m_Properties.Size.GetX() / 2.f
			and mousePos.x < (float)m_HandlePos + (float)m_Properties.Size.GetX() / 2.f
			and mousePos.y >= (float)m_Pos.GetY() + (float)(m_Properties.Size.GetY() - m_Properties.HandleTexture.height) / 2.f
			and mousePos.y < (float)m_Pos.GetY() + (float)(m_Properties.Size.GetY() + m_Properties.HandleTexture.height) / 2.f)
		{
			return true;
		}
		return false;
	}

	bool IsHandleGrabbed() {
		return IsHandleHovered() and IsMouseButtonDown(MOUSE_BUTTON_LEFT) and m_bActive;
	}
};