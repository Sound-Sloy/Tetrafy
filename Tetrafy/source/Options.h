#pragma once
#include "nlohmann/json.hpp"

struct OptionsS {
	float MusicVolume = 1.f;
	bool MusicToggle = true;
	float SFXVolume = 1.f;
	bool SFXToggle = true;
	bool SoftDropToggle = true;
	bool HardDropToggle = true;
	bool LandingPreviewToggle = true;
};

inline void to_json(nlohmann::json& j, const OptionsS& p) {
	j = nlohmann::json{ 
		{"MusicVolume", p.MusicVolume}, 
		{"MusicToggle", p.MusicToggle}, 
		{"SFXVolume", p.SFXVolume}, 
		{"SFXToggle", p.SFXToggle},
		{"SoftDropToggle", p.SoftDropToggle},
		{"HardDropToggle", p.HardDropToggle},
		{"LandingPreviews", p.LandingPreviewToggle}
	};
}

inline void from_json(const nlohmann::json& j, OptionsS& p) {
	j.at("MusicVolume").get_to(p.MusicVolume);
	j.at("MusicToggle").get_to(p.MusicToggle);
	j.at("SFXVolume").get_to(p.SFXVolume);
	j.at("SFXToggle").get_to(p.SFXToggle);
	j.at("SoftDropToggle").get_to(p.SoftDropToggle);
	j.at("HardDropToggle").get_to(p.HardDropToggle);
	j.at("LandingPreviews").get_to(p.LandingPreviewToggle);
}