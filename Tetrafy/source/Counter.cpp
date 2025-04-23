#include "Counter.h"

Counter::Counter(Vec2<int32_t> pos, CounterProperties properties) :
	m_Pos(pos), m_Properties(properties)
{
	if (m_Properties.Size == Vec2{ 0,0 }) {
		TraceLog(LOG_WARNING, "Counter initialized with size {0,0}");
	}

	if (m_Properties.StartIndex >= 0 and m_Properties.StartIndex < m_Properties.Values.size()) {
		m_Properties.StartIndex = 0;
		m_Index = m_Properties.StartIndex;
	}
	else {
		TraceLog(LOG_WARNING, "Counter initialized with StartIndex out of bounds. StartIndex => 0");
		m_Index = 0;
	}
}

void Counter::Update()
{
	if (m_Properties.Font == nullptr) {
		m_DefaultFont = GetFontDefault();
		m_Properties.Font = &m_DefaultFont;
	}
	if (IsClicked() and m_bActive) {
		m_Index = (m_Index + 1) % m_Properties.Values.size();
		if (OnChange) OnChange(m_Properties.Values.at(m_Index), m_Index);
	}
	Vector2 mes = MeasureTextEx(*m_Properties.Font, m_Properties.Values.at(m_Index).c_str(), m_Properties.FontSize, m_Properties.FontSpacing);
	m_TextPos = { m_Pos.GetX() + (m_Properties.Size.GetX() - (int32_t)mes.x) / 2,m_Pos.GetY() + (m_Properties.Size.GetY() - (int32_t)mes.y) / 2 };

}

void Counter::Draw()
{
	if (!m_bActive) {
		DrawRectangleRounded({ (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Properties.Size.GetX(), (float)m_Properties.Size.GetY() }, m_Properties.BorderRoundness, m_Properties.BorderSegments, m_Properties.BackgroundColorInactive);
		DrawRectangleRoundedLinesEx({ (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Properties.Size.GetX(), (float)m_Properties.Size.GetY() }, m_Properties.BorderRoundness, m_Properties.BorderSegments, m_Properties.BorderSize, m_Properties.BorderColorInactive);

		DrawTextEx(*m_Properties.Font, m_Properties.Values.at(m_Index).c_str(), { (float)m_TextPos.GetX(), (float)m_TextPos.GetY() }, m_Properties.FontSize, m_Properties.FontSpacing, m_Properties.ForegroundColorInactive);

		return;
	}
	DrawRectangleRounded({ (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Properties.Size.GetX(), (float)m_Properties.Size.GetY() }, m_Properties.BorderRoundness, m_Properties.BorderSegments, m_Properties.BackgroundColor);
	DrawRectangleRoundedLinesEx({ (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Properties.Size.GetX(), (float)m_Properties.Size.GetY() }, m_Properties.BorderRoundness, m_Properties.BorderSegments, m_Properties.BorderSize, m_Properties.BorderColor);


	if (IsClicked()) {
		DrawRectangleRounded({ (float)m_Pos.GetX(),(float)m_Pos.GetY(), (float)m_Properties.Size.GetX(), (float)m_Properties.Size.GetY() }, m_Properties.BorderRoundness, m_Properties.BorderSegments, m_Properties.ClickColor);
	}
	else if (IsHovered()) {
		DrawRectangleRounded({ (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Properties.Size.GetX(), (float)m_Properties.Size.GetY() }, m_Properties.BorderRoundness, m_Properties.BorderSegments, m_Properties.HoverColor);
	}

	DrawTextEx(*m_Properties.Font, m_Properties.Values.at(m_Index).c_str(), { (float)m_TextPos.GetX(), (float)m_TextPos.GetY() }, m_Properties.FontSize, m_Properties.FontSpacing, m_Properties.ForegroundColor);
}

std::string Counter::GetValue() const
{
	return m_Properties.Values.at(m_Index);
}

void Counter::SetIndex(size_t index)
{
	if(index < m_Properties.Values.size()) {
		m_Index = index;
	}
}

void Counter::SetActive(bool active)
{
	m_bActive = active;
}

bool Counter::IsActive() const
{
	return m_bActive;
}

CounterProperties Counter::GetProperties() const
{
	return m_Properties;
}

bool Counter::IsHovered()
{
	if (!m_bActive) return false;
	Vector2 mousePos = GetMousePosition();
	if (mousePos.x >= m_Pos.GetX() and mousePos.x < m_Pos.GetX() + m_Properties.Size.GetX()
		and mousePos.y >= m_Pos.GetY() and mousePos.y < m_Pos.GetY() + m_Properties.Size.GetY())
	{
		if (this->OnHover and !m_WasHovered) {
			this->OnHover({ static_cast<int32_t>(mousePos.x),static_cast<int32_t>(mousePos.y) });
		}
		m_WasHovered = true;
		return true;
	}
	m_WasHovered = false;
	return false;
}

bool Counter::IsClicked()
{
	if (!m_bActive) return false;
	if (IsHovered() and IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT)) {
		if (this->OnClick) {
			this->OnClick();
		}
		return true;
	}
	return false;
}
