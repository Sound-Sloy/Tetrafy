#include "Cell.h"

Cell::Cell() : 
	m_GridPos(Vec2<int32_t>(0,0)), 
	m_Color(RAYWHITE), 
	m_Size(32), 
	m_bIsShown(false), 
	m_bIsVirtual(false), 
	m_VirtualColor(RAYWHITE),
	m_BlinkingSprite(Globals::Animations::CellBlinkingAnimation),
	m_DisolveSprite(Globals::Animations::CellDisolveAnimation)
{}

Cell::Cell(Vec2<int32_t> gridPos, Vec2<int32_t> boardPos, int32_t size, Color color, int32_t padding,
	bool shown, bool _virtual, bool ghost)
	: m_GridPos(gridPos),
	m_BoardPos(boardPos),
	m_Size(size),
	m_Color(color),
	m_Padding(padding),
	m_bIsShown(shown),
	m_bIsVirtual(false),
	m_VirtualColor(RAYWHITE),
	m_bGhost(ghost),
	m_GhostColor(RAYWHITE),
	m_BlinkingSprite(Globals::Animations::CellBlinkingAnimation),
	m_DisolveSprite(Globals::Animations::CellDisolveAnimation)
{}

void Cell::Draw() {
	if (!(this->m_bIsShown or this->m_bIsVirtual or this->m_bGhost)) {
		return;
	}

	if (m_bDisolve) {
		m_DisolveSprite.Draw(m_BoardPos.GetX() + m_GridPos.GetX() * (m_Size + m_Padding),
			m_BoardPos.GetY() + m_GridPos.GetY() * (m_Size + m_Padding), Color{ (uint8_t)(m_Color.r * 0.8),(uint8_t)(m_Color.g * 0.8), (uint8_t)(m_Color.b * 0.8), m_Color.a });
		return;
	}

	if (m_bBlinking) {
		m_BlinkingSprite.Draw(m_BoardPos.GetX() + m_GridPos.GetX() * (m_Size + m_Padding),
			m_BoardPos.GetY() + m_GridPos.GetY() * (m_Size + m_Padding), m_Color);
		return;
	}
	if (this->m_bGhost and !this->m_bIsVirtual) {
		DrawRectangleLines(m_BoardPos.GetX() + m_GridPos.GetX() * (m_Size + m_Padding) + 2,
			m_BoardPos.GetY() + m_GridPos.GetY() * (m_Size + m_Padding) + 2,
			m_Size - 4, m_Size - 4, this->m_GhostColor);
	}
	else {
		DrawRectangle(m_BoardPos.GetX() + m_GridPos.GetX() * (m_Size + m_Padding),
			m_BoardPos.GetY() + m_GridPos.GetY() * (m_Size + m_Padding),
			m_Size, m_Size,
			this->m_bIsVirtual ? this->m_VirtualColor : this->m_Color);
	}
}

void Cell::SetShown(bool show) {
	this->m_bIsShown = show;
}

bool Cell::IsShown() const {
	return this->m_bIsShown;
}

void Cell::SetColor(Color color) {
	this->m_Color = color;
}

Color Cell::GetColor() const
{
	return this->m_Color;
}

void Cell::SetVirtual(bool _virtual) {
	this->m_bIsVirtual = _virtual;
}

void Cell::SetVirtualColor(Color virtualColor) {
	this->m_VirtualColor = virtualColor;
}

bool Cell::IsVirtual() const {
	return this->m_bIsVirtual;
}

Color Cell::GetVirtualColor() const {
	return this->m_VirtualColor;
}

void Cell::SetGhost(bool ghost) {
	this->m_bGhost = ghost;
}

bool Cell::IsGhost() const {
	return this->m_bGhost;
}

void Cell::SetGhostColor(Color ghostColor) {
	this->m_GhostColor = ghostColor;
}

Color Cell::GetGhostColor() const {
	return this->m_GhostColor;
}

int32_t Cell::GetPadding() const {
	return this->m_Padding;
}

void Cell::SetBlinking(bool blinking)
{
	m_bBlinking = blinking;
}

void Cell::RestartBlinking()
{
	m_BlinkingSprite.Restart();
}

void Cell::SetDisolve(bool disolve)
{
	m_bDisolve = disolve;
}

void Cell::RestartDisolve()
{
	m_DisolveSprite.Restart();
}

bool Cell::CanBeRemoved() const
{
	return m_bDisolve and m_DisolveSprite.GetRepeatCounter() > 0;
}

bool Cell::IsDisolving() const
{
	return m_bDisolve;
}
