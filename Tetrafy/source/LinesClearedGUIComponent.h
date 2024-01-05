#pragma once
#include <raylib.h>
#include "Text.h"
#include "Globals.h"

class LinesClearedGUIComponent {
public:
	LinesClearedGUIComponent() = default;
	LinesClearedGUIComponent(Vec2<int32_t> pos, Vec2<int32_t> size);
	void SetValue(int32_t value);
	int32_t GetValue() const;
	void Draw();
private:
	Vec2<int32_t> m_Pos{ 0,0 };
	Vec2<int32_t> m_Size{ 0,0 };
	int32_t m_Value = 0;
	Text m_TitleText;
	Text m_ValueText;
	int32_t CPadding = 5;
};