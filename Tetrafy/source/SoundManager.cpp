#include "SoundManager.h"

SoundManager::SoundManager(OptionsS& options, Music& mainMusicStream)
	: m_Options(options), m_MusicStream(mainMusicStream)
{
	if (!IsAudioDeviceReady()) {
		InitAudioDevice();
	}
}

//SoundManager* SoundManager::GetInstance() const {
//	return (SoundManager*)this;
//}

void SoundManager::PlaySoundNow(Sound& sound) {
	if (m_Options.SFXToggle) {
		SetSoundVolume(sound, m_Options.SFXVolume);
		PlaySound(sound);
	}
}

void SoundManager::PlaySoundNowUnique(Sound& sound) {
	if (m_Options.SFXToggle and !IsSoundPlaying(sound)) {
		//StopSound(sound);
		SetSoundVolume(sound, m_Options.SFXVolume);
		PlaySound(sound);
	}
}

void SoundManager::Update() {

	if (m_Options.MusicToggle) {
		SetMusicVolume(m_MusicStream, m_Options.MusicVolume);
		UpdateMusicStream(m_MusicStream);
		PlayMusicStream(m_MusicStream);
	}
}