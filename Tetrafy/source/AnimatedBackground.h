#pragma once
#include <chrono>
#include <memory>
#include <random>
#include <raylib.h>
#include <vector>
#include <unordered_map>
#include "Vec2.h"

class AnimatedBackground {
public:
	AnimatedBackground(float guiScale = 1.0);
	~AnimatedBackground();

	void Update(float deltaTime);
	void Draw();
private:

	class Element {
	public:
		Element(std::weak_ptr<Texture2D> texture, float rotationRad = 0.f, Vec2<int32_t> pos = {-1000, -1000});

		void Update(float deltaTime);
		void Draw(Color col) const;
	private:
		std::weak_ptr<Texture2D> m_Texture;
		float m_Rotation = 0; // radians
		float m_RotationLastFrame = 0; // radians
		Vec2<float> m_Pos;
		Vec2<float> m_PosLastFrame;
		bool m_bInitialized = false;
		Vec2<float> m_GoalPos;
		Vec2<float> m_GoalMoveVector;
		float m_GoalRotation = 0.f;
		float m_GoalRotationSign = 1.f;
		bool m_bAchievedGoal = false;

		float m_NeededTime = 0.f;
		float m_TimeSinceGoalGen = 0.f;


		static constexpr float C_MOVE_SPEED = 15.f;


		//float m_MoveSpeed = 0.f;		// pix / sec
		float m_RotationSpeed = 1.f;	// rad / sec

		std::mt19937_64 m_RNG{ static_cast<std::mt19937_64::result_type>(
		std::chrono::steady_clock::now().time_since_epoch().count()
		) };

		void GenerateGoal();
		bool CheckGoalCompletion() const;
	};

	enum class TetrominosE_Shadow {
		Straight = 0,
		Tee,
		El,
		Jay,
		LeftZigZag,
		RightZigZag,
		Square
	};

	struct TetrominoSprite_Shadow {
		inline static Vec2<int32_t> GetSpriteMatSize(TetrominosE_Shadow shape) {
			int32_t sizeX = 3;
			int32_t sizeY = 2;
			switch (shape)
			{
			case TetrominosE_Shadow::Straight:
				sizeX = 4, sizeY = 1;
				break;
			case TetrominosE_Shadow::Square:
				sizeX = 2, sizeY = 2;
				break;
			default:
				sizeX = 3, sizeY = 2;
				break;
			}
			return { sizeX, sizeY };
		}
		inline static Vec2<int32_t> GetSpriteSize(TetrominosE_Shadow shape, int32_t cellSize, int32_t padding) {
			Vec2<int32_t> matSize = TetrominoSprite_Shadow::GetSpriteMatSize(shape);
			int32_t xSize = matSize.GetX() * cellSize + (matSize.GetX() - 1) * padding;
			int32_t ySize = matSize.GetY() * cellSize + (matSize.GetY() - 1) * padding;
			return { xSize, ySize };
		}
		inline static std::vector<bool> GetShapeMatrix(TetrominosE_Shadow shape) {
			return shapeMatrices[shape];
		}
		inline static void DrawSprite(TetrominosE_Shadow shape, int32_t cellSize, int32_t padding);
	private:
		inline static std::unordered_map<TetrominosE_Shadow, std::vector<bool>> spriteMatrices = {
			{TetrominosE_Shadow::Straight, { 1,1,1,1 }},
			{TetrominosE_Shadow::Tee, { 0,1,0,1,1,1 }},
			{TetrominosE_Shadow::El, { 0,0,1,1,1,1 }},
			{TetrominosE_Shadow::Jay, { 1,0,0,1,1,1 }},
			{TetrominosE_Shadow::LeftZigZag, { 1,1,0,0,1,1 }},
			{TetrominosE_Shadow::RightZigZag, { 0,1,1,1,1,0 }},
			{TetrominosE_Shadow::Square, {1,1,1,1}}
		};
		inline static std::unordered_map<TetrominosE_Shadow, Color> colors = {
			{TetrominosE_Shadow::Straight, Color(10, 220, 230, 255)},
			{TetrominosE_Shadow::Tee, Color(145, 75, 255, 255)},
			{TetrominosE_Shadow::El, Color(255, 115, 75, 255)},
			{TetrominosE_Shadow::Jay, Color(55, 100, 250, 255)},
			{TetrominosE_Shadow::LeftZigZag, Color(250, 55, 55, 255)},
			{TetrominosE_Shadow::RightZigZag, Color(140, 250, 55, 255)},
			{TetrominosE_Shadow::Square, Color(240, 250, 55, 255)}
		};
		inline static std::unordered_map<TetrominosE_Shadow, std::vector<bool>> shapeMatrices{
			{TetrominosE_Shadow::Straight, { 0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0 }},
			{TetrominosE_Shadow::Tee, { 0,1,0,1,1,1,0,0,0 }},
			{TetrominosE_Shadow::El, { 0,0,1,1,1,1,0,0,0 }},
			{TetrominosE_Shadow::Jay, { 1,0,0,1,1,1,0,0,0 }},
			{TetrominosE_Shadow::LeftZigZag, { 1,1,0,0,1,1,0,0,0 }},
			{TetrominosE_Shadow::RightZigZag, { 0,1,1,1,1,0,0,0,0 }},
			{TetrominosE_Shadow::Square, { 1,1,1,1 }}
		};
	};
	

	static constexpr uint32_t C_SPACING = 2;
	static constexpr Color C_COLOR = Color(255,255,255,20);
	std::vector<std::shared_ptr<Texture2D>> m_Textures;

	std::vector<Element> m_Elements;

	int32_t m_CurTet = 0;

	std::mt19937_64 m_RNG{ static_cast<std::mt19937_64::result_type>(
		std::chrono::steady_clock::now().time_since_epoch().count()
		) };
};