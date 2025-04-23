#pragma once
#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <raylib.h>
#include "Vec2.h"


struct CounterProperties {
	Font* Font = nullptr;
	float FontSize = 16.f;
	float FontSpacing = 1.f;

	Vec2<int32_t> Size = { 0,0 };

	
	std::vector<std::string> Values;
	size_t StartIndex = 0;

	Color ForegroundColor = WHITE;
	Color ForegroundColorInactive = LIGHTGRAY;
	Color BackgroundColor = Color(0.f, 0.f, 0.f, 0.f);
	Color BackgroundColorInactive = Color(0.f, 0.f, 0.f, 0.f);
	Color BorderColor = WHITE;
	Color BorderColorInactive = DARKGRAY;
	Color ClickColor = Color(255.f, 255.f, 255.f, 100.f);
	Color HoverColor = Color(255.f, 255.f, 255.f, 50.f);
	int32_t BorderSize = 2;
	float BorderRoundness = 4.f;
	int32_t BorderSegments = 4;
};


class Counter {
public:
	Counter() = default;
	Counter(Vec2<int32_t> pos, CounterProperties properties);
	void Update();
	void Draw();
	std::string GetValue() const;
	void SetIndex(size_t index);

	void SetActive(bool active = true);
	bool IsActive() const;
	CounterProperties GetProperties() const;

	std::function<void(Vec2<int32_t>)> OnHover = nullptr;
	std::function<void()> OnClick = nullptr;
	std::function<void(std::string, int32_t)> OnChange = nullptr; // Value and Index

private:
	Vec2<int32_t> m_Pos = {};
	Vec2<int32_t> m_TextPos = { -10000,-10000 };
	bool m_bActive = true;

	bool m_WasHovered = false;

	Font m_DefaultFont = GetFontDefault();

	int32_t m_Index = 0;

	CounterProperties m_Properties;

	bool IsHovered();
	bool IsClicked();

};