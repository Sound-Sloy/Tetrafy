#pragma once
#include "Vec2.h"
#include <raylib.h>
#include <iostream>
#include "AnimatedSprite.h"
#include "Globals.h"

class Cell {
public:
	Cell();
	Cell(Vec2<int32_t> gridPos, Vec2<int32_t> boardPos, int32_t size, Color color, int32_t padding, bool shown = false, bool _virtual = false, bool ghost = false);
	void Draw();
	void SetShown(bool show);
	bool IsShown() const;
	void SetColor(Color color);
	Color GetColor() const;
	void SetVirtual(bool _virtual);
	bool IsVirtual() const;
	void SetVirtualColor(Color virtualColor);
	Color GetVirtualColor() const;
	void SetGhost(bool ghost);
	bool IsGhost() const;
	void SetGhostColor(Color ghostColor);
	Color GetGhostColor() const;

	int32_t GetPadding() const;

	void SetBlinking(bool blinking);
	void RestartBlinking();

	void SetDisolve(bool disolve);
	void RestartDisolve();
	bool CanBeRemoved() const;
	bool IsDisolving() const;

private:
	Color m_Color;
	Vec2<int32_t> m_GridPos;
	Vec2<int32_t> m_BoardPos;
	int32_t m_Size;
	int32_t m_Padding;
	bool m_bIsShown = false;
	Color m_VirtualColor;
	bool m_bIsVirtual = false; // whether this cell is used to render the teromino
	Color m_GhostColor;
	bool m_bGhost = false;
	bool m_bBlinking = false;
	bool m_bDisolve = false;

	AnimatedSprite m_BlinkingSprite;
	AnimatedSprite m_DisolveSprite;
};