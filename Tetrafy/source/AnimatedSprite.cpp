#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(Animation& animation, float scale) :
	m_Animation(animation)
{
	m_SpawnTime = (float)GetTime();
}

void AnimatedSprite::Draw(Vec2<int32_t> pos, Color color, float scale) {
	int32_t lastFrame = m_CurrentFrame;
	m_CurrentFrame = (int32_t)((GetTime() - m_SpawnTime) * m_Animation.FPS) % m_Animation.Rectangles.size();
	
	if (m_CurrentFrame == 0 and lastFrame > m_CurrentFrame) {
		m_RepeatCounter++;
	}

	DrawTexturePro(
		m_Animation.Atlas,
		m_Animation.Rectangles[m_CurrentFrame], 
		{
			(float)pos.GetX(), 
			(float)pos.GetY(), 
			m_Animation.Rectangles[m_CurrentFrame].width * scale, 
			m_Animation.Rectangles[m_CurrentFrame].height * scale
		}, 
		m_Animation.Origin, 
		m_Radians, 
		color
	);
}

void AnimatedSprite::Draw(int32_t posX, int32_t posY, Color color, float scale) {
	AnimatedSprite::Draw({ posX,posY }, color, scale);
}

void AnimatedSprite::RotateAt(float radians) {
	m_Radians = radians;
}

void AnimatedSprite::RotateBy(float radians) {
	m_Radians += radians;
}

void AnimatedSprite::Restart() {
	m_SpawnTime = (float)GetTime();
	m_CurrentFrame = 0;
	m_RepeatCounter = 0;
}

void AnimatedSprite::Pause() {
	m_bPaused = true;
}

void AnimatedSprite::Unpause() {
	m_bPaused = false;
}

float AnimatedSprite::GetRotation() const {
	return m_Radians;
}

int32_t AnimatedSprite::GetFrame() const {
	return m_CurrentFrame;
}

bool AnimatedSprite::IsPaused() const {
	return m_bPaused;
}

int32_t AnimatedSprite::GetRepeatCounter() const
{
	return m_RepeatCounter;
}
