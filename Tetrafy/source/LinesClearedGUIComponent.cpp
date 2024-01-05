#include "LinesClearedGUIComponent.h"

LinesClearedGUIComponent::LinesClearedGUIComponent(Vec2<int32_t> pos, Vec2<int32_t> size)
	: m_Pos(pos), m_Size(size)
{
	m_TitleText = Text("Lines", {pos.GetX() + size.GetX() / 2, pos.GetY() + CPadding}, {.5f, 0.f}, Globals::TetrisFont, 28.f);
	m_ValueText = Text("0", { pos.GetX() + size.GetX() / 2, pos.GetY() + 28 + 2 * CPadding }, { .5f, 0.f }, Globals::TetrisFontMedium, 20.f, 1.f, 0.f, LIGHTGRAY);
}

void LinesClearedGUIComponent::Draw()
{
	DrawRectangleLines(m_Pos.GetX() - 5, m_Pos.GetY() - 5, m_Size.GetX() + 5, m_Size.GetY() + 5, RAYWHITE);
	
	m_TitleText.Draw();
	m_ValueText.Draw();
}

void LinesClearedGUIComponent::SetValue(int32_t value) {
	if (value == m_Value) {
		return;
	}
	m_Value = value;
	m_ValueText.SetText(std::to_string(value));
}

int32_t LinesClearedGUIComponent::GetValue() const {
	return m_Value;
}