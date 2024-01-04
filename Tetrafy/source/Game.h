#pragma once

#include <assert.h>
#include <iostream>
#include <raylib.h>
#include <fstream>
#include <filesystem>
#include "Globals.h"
#include "ScreenManager.h"
#include "Vec2.h"
#include "Keyboard.h"
#include "nlohmann/json.hpp"

#include "ResPacker.h"

class Game
{
public:
	Game(int32_t width, int32_t height, std::string windowTitle);
	//Game(const Game& other) = delete;
	//Game& operator=(const Game& other) = delete;
	~Game() noexcept;
	bool GameShouldClose() const;
	void Tick();
	void LoadOptions();
	void SaveOptions();

private:
	void Update();
	void Draw();

	ScreenManager* m_ScreenManager;
};