#include "Sprite.h"

Sprite::Sprite(Texture2D& texture, float size) :
	m_Texture(texture),
	m_Scale(size)
{}

void Sprite::Draw(Vec2<int32_t> pos, float size) {
	if (size <= 0) {
		TraceLog(LOG_FATAL, "Invalid sprite size");
		return;
	}

	if (m_Texture.width <= 0 or m_Texture.height <= 0) {
		TraceLog(LOG_FATAL, "Invalid sprite texture given to Draw call");
		return;
	}

	DrawTexturePro(m_Texture, { 0,0,(float)m_Texture.width,(float)m_Texture.height }, { (float)pos.GetX(), (float)pos.GetY(), m_Texture.width * size, m_Texture.height * size }, { 0,0 }, m_Radians, WHITE);
}

void Sprite::Draw(int32_t posX, int32_t posY, float size) {
	Sprite::Draw({ posX,posY }, size);
}

void Sprite::RotateAt(float radians) {
	m_Radians = radians;
}

void Sprite::RotateBy(float radians) {
	m_Radians += radians;
}