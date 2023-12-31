#pragma once
#include <iostream>
#include <raylib.h>
#include "Vec2.h"
#include "Globals.h"
#include <string>

class LevelGUIComponent
{
public:
	LevelGUIComponent() = default;
	LevelGUIComponent(Vec2<int32_t> pos, Vec2<int32_t> size);
	void SetLevel(int32_t level);
	int32_t GetLevel() const;
	void Draw();
private:
	Vec2<int32_t> m_Pos{0,0};
	Vec2<int32_t> m_Size{0,0};
	int32_t m_Level = 0;
	Color m_LevelColor = LIGHTGRAY;
};
