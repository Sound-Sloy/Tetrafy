#pragma once
#include <iostream>
#include <raylib.h>
#include <deque>
#include "Options.h"

class SoundManager {
public:
	SoundManager() = default;
	SoundManager(OptionsS& options, Music& mainMusicStream);
	void PlaySoundNow(Sound& sound);
	void PlaySoundNowUnique(Sound& sound);
	void Update();
	//SoundManager* GetInstance() const;
private:
	OptionsS& m_Options;

	Music& m_MusicStream;
};