#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <raylib.h> // required only for clas Loader
#include <string>
#include <vector>
#include <unordered_map>
#include <assert.h>
#include "nlohmann/json.hpp"

namespace ResPacker {

	enum class ObjectType {
		None = 0,
		Image,
		TextU8,
		Wave,
		Font
		// Add more here
	};


	struct Object {
		/**
			IDdataLen (uint32_t)
			ID (IDdataLen * uint8_t)
			Type (uint8_t) // 0=none,1=image,2=text,3=wave .... 255=..4
			DataHash (16 * uint8_t)
			DataLen (uint32_t)
			Data (DataLen * uint8_t)
		*/
		uint32_t BytePosInFile = 0;
		uint32_t IDSize;
		uint8_t* ID = nullptr;
		uint32_t ExtSize;
		uint8_t* Ext = nullptr;
		uint8_t Type = (uint8_t)ObjectType::None;
		//maybe ? uint8_t Hash[16];
		uint32_t DataSize;
		uint8_t* Data = nullptr;
	};

	struct FileStructure {
		uint32_t ObjCnt;
		std::vector<Object> Objects;
	};
	
	class Loader {
	public:
		Loader(std::string fileName);
		~Loader();

		void LoadAllRaw();
		void UnloadAllData();
		void LoadObjectDataRaw(std::string ID);
		void UnloadObjectDataRaw(std::string ID);

		std::string GetExtension(std::string ID);


		Sound LoadAsSound(std::string ID, std::string ext = "");
		Music LoadAsMusicStream(std::string ID, std::string ext = "");
		Texture2D LoadAsTexture2D(std::string ID, std::string ext = "");
		Font LoadAsFont(std::string ID, std::string ext, int32_t fontSize, int32_t* codepoints = nullptr, int32_t cpCount = 512);



	private:
		FileStructure m_Structure;
		std::fstream m_File;
		std::unordered_map<std::string, uint32_t> m_IDToIndexMap;
	};

	class Dumper {
	public:
		Dumper(std::string fileName);
		~Dumper();

		bool DumpFileBinary(std::string filePath, std::string ID, ObjectType type);
		bool DumpDataRaw(std::string ID, ObjectType type, std::string ext, uint8_t* data, uint32_t dataSize);
	
	private:
		std::vector<std::string> m_IDs;
		uint32_t m_ObjectCnt = 0;

		std::fstream m_File;
	};
}