#pragma once
#include <iostream>
#include <functional>
#include <raylib.h>
#include "Vec2.h"

enum class SwitchStatesE {
	ON = 1,
	OFF = 0
};

enum class SwitchTextureResizingModesE {
	KeepX,
	KeepY,
	Stretch
};

struct SwitchProperties {
	SwitchStatesE StartingState = SwitchStatesE::OFF;
	/// <summary>
	/// {0,0} - Uses the texture sizes
	/// {any,any} - Stretches the texture
	/// </summary>
	Vec2<int32_t> Size = { 0,0 };
	
	Texture2D& OnTexture;
	Texture2D& OffTexture;
	Texture2D& InactiveTexture;
};

class Switch {
public:
	Switch() = default;
	Switch(Vec2<int32_t> pos, SwitchProperties properties);
	void Update();
	void Draw();
	void Toggle();

	SwitchStatesE GetState() const;
	void SetState(SwitchStatesE state);
	void SetActive(bool active = true);
	bool IsActive() const;
	SwitchProperties GetProperties() const;

	std::function<void(Vec2<int32_t>)> OnHover = nullptr;
	std::function<void()> OnClick = nullptr;
	std::function<void(SwitchStatesE)> OnChange = nullptr;


private:
	SwitchStatesE m_State = SwitchStatesE::OFF;
	Vec2<int32_t> m_Pos = {};
	bool m_bActive = true;

	bool m_WasHovered = false;

	SwitchProperties m_Properties;

	bool IsHovered();
	bool IsClicked();
	
};