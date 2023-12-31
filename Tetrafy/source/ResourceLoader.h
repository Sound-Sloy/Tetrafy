#pragma once
#include <iostream>
#include <raylib.h>
#include <string>


enum class ResLoadType {
	FilePath,
	ResFile
};

class ResourceLoader {
public:
	template <typename T>
	static T* LoadResource(std::string resourceID, ResLoadType loadType = ResLoadType::ResFile) {
		if (T == Font) {

		}
	}

};