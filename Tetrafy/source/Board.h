#pragma once
#include <iostream>
#include <raylib.h>
#include <vector>
#include <deque>
#include <chrono>
#include <random>
#include <algorithm>
#include "Cell.h"
#include "Tetromino.h"
#include "FuturePiecesGUIComponent.h"
#include "Globals.h"
#include "Keyboard.h"
#include "Score.h"
#include "LevelGUIComponent.h"
#include "HeldTetrominoGUIComponent.h"
#include "Switch.h"
#include "DeathScreen.h"

class Board
{
public:
	Board();
	Board(Vec2<int32_t> pos, Vec2<int32_t> gridSize, int32_t cellSize = 32, int32_t cellPadding = 2);
	~Board() = default;
	//Board(const Board& other) = default;
	Board& operator=(const Board& other) = default;
	void Draw();
	void Update(float deltaTime);

	int32_t GetCellSize() const;
	/*Vec2<int32_t> GetPosForCellByID(int32_t ID) const;
	Vec2<int32_t> GetPosForCellByGridPos(Vec2<int32_t> gridPos) const;*/
	Vec2<int32_t> GetGridSize() const;

	void SetOver(bool over);
	bool IsOver() const;

	void ResetVirtualCells();
	void ResetGhostCells();
	void ResetBlinkingCells();

	bool FlagShouldRestart = false;
private:
	//Music m_ThemeSong;
	std::vector<Cell> m_Cells;
	Vec2<int32_t> m_Pos;
	Vec2<int32_t> m_GridSize;
	int32_t m_CellSize = 0;
	int32_t m_CellPadding;
	bool m_bGameOver = false;
	int32_t m_TotalLinesCleared = 0;
	int32_t m_Level = 1;
	int32_t m_ComboCount = 0;

	FuturePiecesGUIComponent m_FuturePiecesGUIComponent;
	ScoreGUIComponent m_ScoreGUIComponent;
	SplashTextController m_SplashTextController;
	LevelGUIComponent m_LevelGUIComponent;
	HeldTetrominoGUIComponent m_HeldTetrominoGUIComponent;

	std::mt19937 RNG{ static_cast<std::mt19937::result_type>(
		std::chrono::steady_clock::now().time_since_epoch().count()
		) };
	std::uniform_int_distribution<> m_TetrominoDistribution{ 0, 6 };

	
	std::deque<Tetromino> m_Tetrominos;
	HeldTetromino m_HeldTetromino;
	std::deque<TetrominosE> m_NextShapes;

	std::unique_ptr<DeathScreen> m_DeathScreen;

	Vec2<int32_t> GetPXSize() const;
	void HandleBravo(int32_t clearedLines);
	Vec2<int32_t> GetRandomPosInsideBoard();

	void SwapHeldTetromino();

	TetrominosE NextShape();
};

