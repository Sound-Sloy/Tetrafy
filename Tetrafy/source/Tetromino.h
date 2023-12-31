#pragma once
#include <iostream>
#include <raylib.h>
#include <vector>
#include <unordered_map>
#include <random>
#include <algorithm>
#include "Cell.h"
#include "Vec2.h"
#include "Globals.h"
#include "Keyboard.h"

enum class TetrominosE {
	Straight,
	Tee,
	El,
	Jay,
	LeftZigZag,
	RightZigZag,
	Square
};

enum class TetrominoRotation {
	Clockwise,
	Counterclockwise
};

enum class TetrominoOrientation {
	Up,
	Right,
	Down,
	Left
};

//static struct TetrominoCollection {
//	static std::unordered_map<TetrominosE, std::unordered_map<TetrominoOrientation, std::vector<bool>>> Orientations
//	{
//		{
//			TetrominosE::Straight,
//			{
//				TetrominoOrientation::Up,
//				{ 0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0 }
//			},
//			{
//
//			},
//			{
//
//			},
//			{
//
//			}
//		}
//
//	};
//};

struct TetrominoSprite {
	inline static Vec2<int32_t> GetSpriteMatSize(TetrominosE shape) {
		int32_t sizeX = 3;
		int32_t sizeY = 2;
		switch (shape)
		{
		case TetrominosE::Straight:
			sizeX = 4, sizeY = 1;
			break;
		case TetrominosE::Square:
			sizeX = 2, sizeY = 2;
			break;
		default:
			sizeX = 3, sizeY = 2;
			break;
		}
		return { sizeX, sizeY };
	}
	inline static Vec2<int32_t> GetSpriteSize(TetrominosE shape, int32_t cellSize, int32_t padding) {
		Vec2<int32_t> matSize = TetrominoSprite::GetSpriteMatSize(shape);
		int32_t xSize = matSize.GetX() * cellSize + (matSize.GetX() - 1) * padding;
		int32_t ySize = matSize.GetY() * cellSize + (matSize.GetY() - 1) * padding;
		return { xSize, ySize };
	}
	inline static Color GetTetrominoColor(TetrominosE shape) {
		return colors[shape];
	}
	inline static std::vector<bool> GetShapeMatrix(TetrominosE shape) {
		return shapeMatrices[shape];
	}
	inline static void DrawSprite(TetrominosE shape, Vec2<int32_t> pos, int32_t cellSize, int32_t padding);
private:
	inline static std::unordered_map<TetrominosE, std::vector<bool>> spriteMatrices = {
		{TetrominosE::Straight, { 1,1,1,1 }},
		{TetrominosE::Tee, { 0,1,0,1,1,1 }},
		{TetrominosE::El, { 0,0,1,1,1,1 }},
		{TetrominosE::Jay, { 1,0,0,1,1,1 }},
		{TetrominosE::LeftZigZag, { 1,1,0,0,1,1 }},
		{TetrominosE::RightZigZag, { 0,1,1,1,1,0 }},
		{TetrominosE::Square, {1,1,1,1}}
	};
	inline static std::unordered_map<TetrominosE, Color> colors = {
		{TetrominosE::Straight, Color(10, 220, 230, 255)},
		{TetrominosE::Tee, Color(145, 75, 255, 255)},
		{TetrominosE::El, Color(255, 115, 75, 255)},
		{TetrominosE::Jay, Color(55, 100, 250, 255)},
		{TetrominosE::LeftZigZag, Color(250, 55, 55, 255)},
		{TetrominosE::RightZigZag, Color(140, 250, 55, 255)},
		{TetrominosE::Square, Color(240, 250, 55, 255)}
	};
	inline static std::unordered_map<TetrominosE, std::vector<bool>> shapeMatrices{
		{TetrominosE::Straight, { 0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0 }},
		{TetrominosE::Tee, { 0,1,0,1,1,1,0,0,0 }},
		{TetrominosE::El, { 0,0,1,1,1,1,0,0,0 }},
		{TetrominosE::Jay, { 1,0,0,1,1,1,0,0,0 }},
		{TetrominosE::LeftZigZag, { 1,1,0,0,1,1,0,0,0 }},
		{TetrominosE::RightZigZag, { 0,1,1,1,1,0,0,0,0 }},
		{TetrominosE::Square, { 1,1,1,1 }}
	};
};

class Tetromino;

class HeldTetromino {
public:
	HeldTetromino() = default;
	HeldTetromino(Tetromino tetromino);
	HeldTetromino(TetrominosE shape, int32_t cellSize, int32_t padding);
	void Draw(Vec2<int32_t> pos) const;
	void Clear();
	bool Exists() const;
	TetrominosE GetShape() const;
private:
	TetrominosE m_Shape;
	int32_t m_CellSize;
	int32_t m_Padding;
	bool m_bExists = false;
};

class Tetromino
{
public:
	Tetromino(TetrominosE shape, Vec2<int32_t> gridSize, int32_t cellSize, std::vector<Cell>& cells);
	//Tetromino(const Tetromino& other) = delete;
	//Tetromino& operator=(const Tetromino& other) = default;
	~Tetromino();
	void Rotate(TetrominoRotation direction);
	void MoveRight();
	void MoveLeft();
	void Update(float deltaTime, int32_t level);
	void Draw();
	bool IsSolid() const;
	bool IsInSolidification() const;
	Vec2<int32_t> GetSpriteSize() const;
	void DrawAsSprite(Vec2<int32_t> pos) const;
	int32_t GetAccumulatedScore() const;

	TetrominosE GetShape() const;
	int32_t GetCellSize() const;
	int32_t GetPadding() const;

private:
	std::vector<bool> m_Matrix;
	TetrominosE m_Shape;
	Vec2<int32_t> m_GridSize;
	int32_t m_CellSize;
	int32_t m_Padding;
	std::vector<Cell>& m_Cells;
	Vec2<int32_t> m_SpriteSize;
	Vec2<int32_t> m_SpriteMatSize;
	bool m_bSolid = false;
	float m_SolidificationTimer = 2.f;
	bool m_bInSolidification = false;
	int32_t m_ScoreAccumulated = 0;


	Color m_Color;
	Vec2<int32_t> m_Pos;
	const float m_DownSpeed = 24.f;
	const float m_SoftDropMultiplier = 8;

	float m_RealDistanceToGoDown = 0.f;

	Vec2<int32_t> m_GhostPos = { -20,-20 };

	int32_t GetMatrixSizeXAxes() const;
	int32_t _LiniarPosFrom2D(int32_t row, int32_t column) const;
	void PlaceTetrominoInsideBounds();

	bool CanBeSolidified();
	void Solidify();

	Vec2<int32_t> GetLandingPos() const;
	void DrawGhost();
};

