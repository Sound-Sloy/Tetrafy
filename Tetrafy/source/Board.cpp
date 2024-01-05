#include "Board.h"

Board::Board()
	: m_Pos({ 0,0 }),
	m_GridSize({ 0,0 }),
	m_CellPadding(2),
	m_FuturePiecesGUIComponent({ {0,0}, this->m_Tetrominos }),
	m_HeldTetrominoGUIComponent({ {0,0}, {0,0}, this->m_HeldTetromino })
{}

Board::Board(Vec2<int32_t> pos, Vec2<int32_t> gridSize, int32_t cellSize, int32_t cellPadding)
	: m_Pos(pos),
	m_GridSize(gridSize),
	m_CellSize(cellSize),
	m_CellPadding(cellPadding),
	m_FuturePiecesGUIComponent({ {pos.GetX() + gridSize.GetX() * (cellSize + cellPadding) + 10, 50}, this->m_Tetrominos }),
	m_ScoreGUIComponent({ pos.GetX() + gridSize.GetX() * (cellSize + cellPadding) + 10, 50 + 287 + 10 }, { 196, 75 }),
	m_LevelGUIComponent({ {pos.GetX() + gridSize.GetX() * (cellSize + cellPadding) + 10, 50 + 287 + 10 + 75 + 10}, {196, 75} }),
	m_HeldTetrominoGUIComponent({ {pos.GetX() + gridSize.GetX() * (cellSize + cellPadding) + 10, 50 + 287 + 10 + 75 + 10 + 75 + 10}, {196, 130}, this->m_HeldTetromino }),
	m_LinesClearedGUIComponent({ {pos.GetX() + gridSize.GetX() * (cellSize + cellPadding) + 10, 50 + 287 + 10 + 75 + 10 + 75 + 20 + 130}, {196, 75} })
{
	for (int32_t iY = 0; iY < gridSize.GetY(); ++iY) {
		for (int32_t iX = 0; iX < gridSize.GetX(); ++iX) {
			this->m_Cells.push_back(Cell({iX, iY}, m_Pos, cellSize, DARKGRAY, cellPadding));
		}
	}

	PlayMusicStream(Globals::Sounds::MainTheme);

}

void Board::Draw() {
	if (IsOver()) {
		m_DeathScreen->Draw();
		return;
	}
	if (m_Tetrominos.empty()) {
		return;
	}
	DrawRectangleLines(m_Pos.GetX() - 5, m_Pos.GetY() - 5, m_GridSize.GetX() * (m_CellSize + m_CellPadding) + 5 + m_CellPadding, m_GridSize.GetY() * (m_CellSize + m_CellPadding) + 5 + m_CellPadding, WHITE);
	this->m_Tetrominos.front().Draw();
	for (auto& cell : this->m_Cells) {
		cell.Draw();
	}
	m_FuturePiecesGUIComponent.Draw();
	m_ScoreGUIComponent.Draw();
	m_SplashTextController.Draw();
	m_LevelGUIComponent.Draw();
	m_HeldTetrominoGUIComponent.Draw();
	m_LinesClearedGUIComponent.Draw();
}

void Board::Update(float deltaTime) {	
	if (IsOver()) {
		m_DeathScreen->Update();
		return;
	}

	ResetVirtualCells();
	ResetGhostCells();
	ResetBlinkingCells();

	while (this->m_Tetrominos.size() < 4) {
		if (this->m_HeldTetromino.Exists()) {
			this->m_Tetrominos.push_front(Tetromino(this->m_HeldTetromino.GetShape(), this->m_GridSize, this->m_CellSize, m_Cells));
			this->m_HeldTetromino.Clear();
			continue;
		}
		this->m_Tetrominos.push_back(Tetromino(NextShape(), this->m_GridSize, this->m_CellSize, m_Cells));
	}
	this->m_Tetrominos.front().Update(deltaTime, m_Level);

	int32_t fullLinesCount = 0;
	bool finishedRowRemoval = false;
	for (int32_t iY = 0; iY < this->m_GridSize.GetY(); ++iY) {
		bool fullLine = true;
		for (int32_t iX = 0; iX < this->m_GridSize.GetX(); ++iX) {
			int32_t cellID = iY * this->m_GridSize.GetX() + iX;
			if (cellID >= this->m_Cells.size()) {
				std::cout << "Uhh? Board::Update(float) >>> cellID out of bounds\n";
				continue;
			}
			if (!this->m_Cells[cellID].IsShown()) {
				fullLine = false;
				break;
			}
		}
		if (fullLine) {
			fullLinesCount++;
			for (int32_t iX = 0; iX < this->m_GridSize.GetX(); ++iX) {
				int32_t cellID = iY * this->m_GridSize.GetX() + iX;
				if (cellID >= this->m_Cells.size()) {
					TraceLog(LOG_WARNING, "Uhh? Board::Update(float) >>> cellID out of bounds");
					continue;
				}
				if (!this->m_Cells[cellID].CanBeRemoved()) {
					//this->m_Cells[cellID].RestartDisolve();
					this->m_Cells[cellID].SetDisolve(true);
				}
				else {
					for (int32_t iY2 = iY; iY2 > 0; --iY2) {
						int32_t cellID = iY2 * this->m_GridSize.GetX() + iX;
						int32_t cellAboveID = (iY2 - 1) * this->m_GridSize.GetX() + iX;
						if (cellID >= this->m_Cells.size()) {
							TraceLog(LOG_WARNING, "Uhh? Board::Update(float) >>> cellID out of bounds");
							continue;
						}
						this->m_Cells[cellID].SetShown(this->m_Cells[cellAboveID].IsShown());
						this->m_Cells[cellID].SetColor(this->m_Cells[cellAboveID].GetColor());
						this->m_Cells[cellID].SetDisolve(false);
						this->m_Cells[cellID].RestartDisolve();
						finishedRowRemoval = true;
					}
				}
			}
		}
		else {
			for (int32_t iX = 0; iX < this->m_GridSize.GetX(); ++iX) {
				int32_t cellID = iY * this->m_GridSize.GetX() + iX;
				if (cellID >= this->m_Cells.size()) {
					TraceLog(LOG_WARNING, "Uhh? Board::Update(float) >>> cellID out of bounds");
					continue;
				}
				this->m_Cells[cellID].SetDisolve(false);
				this->m_Cells[cellID].RestartDisolve();
			}
		}
	}

	if (fullLinesCount and finishedRowRemoval) {
		this->m_TotalLinesCleared += fullLinesCount;
		this->m_Level = 1 + m_TotalLinesCleared / 10;

		int32_t fullLinesCountCapped = fullLinesCount <= 4 ? fullLinesCount : 4;
		int32_t scoringBase[] = { 0, 100, 300 ,500, 800 };
		int32_t scoreToAdd = scoringBase[fullLinesCountCapped] * this->m_Level;
		m_ScoreGUIComponent.AddScore(scoreToAdd);
		m_SplashTextController.SpawnSplash("+ " + std::to_string(scoreToAdd), Globals::TetrisFont, 28.f, { 180,255,255,255 },
			GetRandomPosInsideBoard(), 2.f);
		
		HandleBravo(fullLinesCount);
	}

	if (this->m_Tetrominos.front().IsSolid()) {
		m_ScoreGUIComponent.AddScore(this->m_Tetrominos.front().GetAccumulatedScore());
		this->m_Tetrominos.pop_front();
		this->m_ComboCount = fullLinesCount ? this->m_ComboCount + 1 : -1;
		if (this->m_ComboCount > 0) {
			int32_t scoreToAddCombo = 50 * this->m_ComboCount * this->m_Level;
			m_ScoreGUIComponent.AddScore(scoreToAddCombo);
			m_SplashTextController.SpawnSplash("+ " + std::to_string(scoreToAddCombo) + " COMBO", Globals::TetrisFont, 32.f, {180,100,255,255},
				GetRandomPosInsideBoard(), 4.f);
		}
	}

	if (IsKeyPressed(Globals::Options.KeyHold)) {
		if (!this->m_HeldTetromino.Exists()) {
			this->m_HeldTetromino = { this->m_Tetrominos.front() };
			this->m_Tetrominos.pop_front();
			this->m_Tetrominos.push_back(Tetromino(this->m_HeldTetromino.GetShape(), this->m_GridSize, this->m_CellSize, m_Cells));

		}
	}

	for (int32_t i = 0; i < this->m_GridSize.GetX(); ++i) {
		if (this->m_Cells[i].IsShown()) {
			SetOver(true);
			return;
		}
	}

	this->m_FuturePiecesGUIComponent.Update();
	m_SplashTextController.Update(deltaTime);
	m_LevelGUIComponent.SetLevel(this->m_Level);
	m_LinesClearedGUIComponent.SetValue(this->m_TotalLinesCleared);
}

int32_t Board::GetCellSize() const {
	return this->m_CellSize;
}

Vec2<int32_t> Board::GetGridSize() const {
	return this->m_GridSize;
}

void Board::SetOver(bool over) {
	this->m_bGameOver = over;
	if (over) {
		m_DeathScreen = std::make_unique<DeathScreen>((uint32_t)m_ScoreGUIComponent.GetScore(), Globals::HighScore, (uint32_t)m_LevelGUIComponent.GetLevel());
		Globals::HighScore = std::max((uint32_t)m_ScoreGUIComponent.GetScore(), Globals::HighScore);
	}
}

bool Board::IsOver() const {
	return this->m_bGameOver;
}

void Board::ResetVirtualCells() {
	for (Cell& cell : this->m_Cells) {
		cell.SetVirtual(false);
	}
}

void Board::ResetGhostCells() {
	for (Cell& cell : this->m_Cells) {
		cell.SetGhost(false);
	}
}

void Board::ResetBlinkingCells()
{
	for (Cell& cell : m_Cells) {
		cell.SetBlinking(false);
	}
}

Vec2<int32_t> Board::GetPXSize() const
{
	return this->m_GridSize * (this->m_CellSize + this->m_CellPadding) - Vec2<int32_t>(this->m_CellPadding, this->m_CellPadding);
}

void Board::SwapHeldTetromino()
{
	//this->m_HeldTetromino = {};
}

Vec2<int32_t> Board::GetRandomPosInsideBoard()
{
	std::uniform_int_distribution<> xDistrib{ this->m_Pos.GetX(), this->m_Pos.GetX() + this->m_GridSize.GetX() * (this->m_CellSize + this->m_CellPadding) - this->m_CellPadding};
	std::uniform_int_distribution<> yDistrib{ this->m_Pos.GetY(), this->m_Pos.GetY() + this->m_GridSize.GetY() * (this->m_CellSize + this->m_CellPadding) - this->m_CellPadding};

	return Vec2<int32_t>( xDistrib(RNG), yDistrib(RNG));
}

void Board::HandleBravo(int32_t lineCount)
{
	if (lineCount < 1) {
		return;
	}

	bool isBravo = true;
	for (auto& cell : this->m_Cells) {
		if (cell.IsShown()) {
			isBravo = false;
			break;
		}
	}

	if (isBravo) {
		int32_t scoringBase[] = { 0, 800, 1200, 1800, 2000 };
		if (lineCount > 4) {
			lineCount = 4;
		}
		int32_t scoreToAdd = scoringBase[lineCount] * this->m_Level;
		m_ScoreGUIComponent.AddScore(scoreToAdd);
		m_SplashTextController.SpawnSplash("+ " + std::to_string(scoreToAdd), Globals::TetrisFont, 28.f, { 180,50,50,255 },
			GetRandomPosInsideBoard(), 8.f);
		m_SplashTextController.SpawnSplash("BRAVO", Globals::TetrisFont, 48.f, {180,50,50,255},
			GetRandomPosInsideBoard(), 8.f);
	}
}

TetrominosE Board::NextShape() {
	if (this->m_NextShapes.empty()) {
		this->m_NextShapes = { TetrominosE::Straight, TetrominosE::Tee, TetrominosE::El, TetrominosE::Jay, TetrominosE::LeftZigZag, TetrominosE::RightZigZag, TetrominosE::Square };
		std::shuffle(this->m_NextShapes.begin(), this->m_NextShapes.end(), RNG);
	}
	if (this->m_NextShapes.size() < 7) {
		std::deque<TetrominosE> nextBucket = { TetrominosE::Straight, TetrominosE::Tee, TetrominosE::El, TetrominosE::Jay, TetrominosE::LeftZigZag, TetrominosE::RightZigZag, TetrominosE::Square };
		
		while (this->m_NextShapes.size() > 0 and nextBucket.front() == m_NextShapes.back()) {
			std::shuffle(nextBucket.begin(), nextBucket.end(), RNG);
		}

		// This should not get called often. But just in case...
		if (this->m_NextShapes.size() > 0 and nextBucket.front() == m_NextShapes.back()) {
			std::swap(nextBucket.front(), nextBucket.back());
		}

		this->m_NextShapes.append_range(nextBucket);
	}
	TetrominosE result = this->m_NextShapes.front();
	this->m_NextShapes.pop_front();
	return result;
}
