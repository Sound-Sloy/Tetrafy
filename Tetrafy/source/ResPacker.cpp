#include "ResPacker.h"

ResPacker::Loader::Loader(std::string filePath)
{
	assert(std::filesystem::is_regular_file(filePath));
	m_File.open(filePath, std::ios::binary | std::ios::in);

	assert(m_File.is_open());

	m_File.read((char*)&m_Structure.ObjCnt, sizeof(m_Structure.ObjCnt));

	for (uint32_t _ = 0; _ < m_Structure.ObjCnt; ++_) {
		Object obj;

		m_File.read((char*)&obj.BytePosInFile, sizeof(obj.BytePosInFile));
		
		m_File.read((char*)&obj.IDSize, sizeof(obj.IDSize));
		obj.ID = new uint8_t[obj.IDSize];
		m_File.read((char*)obj.ID, obj.IDSize);

		m_File.read((char*)&obj.ExtSize, sizeof(obj.ExtSize));
		obj.Ext = new uint8_t[obj.ExtSize];
		m_File.read((char*)obj.Ext, obj.ExtSize);


		m_File.read((char*)&obj.Type, sizeof(obj.Type));
		m_File.read((char*)&obj.DataSize, sizeof(obj.DataSize));
	
		m_File.seekg(obj.DataSize, m_File.cur);

		m_Structure.Objects.push_back(obj);

		std::ostringstream oss;
		for (uint32_t __ = 0; __ < obj.IDSize; ++__) {
			oss << obj.ID[__];
		}
		m_IDToIndexMap[oss.str()] = _;
		delete[] obj.ID;
		delete[] obj.Ext;
	}

	
}

ResPacker::Loader::~Loader()
{
	m_File.close();
}

void ResPacker::Loader::LoadAllRaw()
{
	for (auto mapentry : m_IDToIndexMap) {
		LoadObjectDataRaw(mapentry.first);
	}
}

void ResPacker::Loader::UnloadAllData()
{
	for (auto mapentry : m_IDToIndexMap) {
		UnloadObjectDataRaw(mapentry.first);
	}
}

void ResPacker::Loader::LoadObjectDataRaw(std::string ID)
{
	uint32_t index = m_IDToIndexMap[ID];
	if (m_Structure.Objects[index].Data != nullptr) {
		return;
	}
	if (!m_File.is_open()) {
		return;
	}
	m_File.flush();
	m_File.seekg(m_Structure.Objects[index].BytePosInFile + 17 + m_Structure.Objects[index].IDSize + m_Structure.Objects[index].ExtSize, std::ios::beg);
	m_Structure.Objects[index].Data = new uint8_t[m_Structure.Objects[index].DataSize];
	m_File.read((char*)m_Structure.Objects[index].Data, m_Structure.Objects[index].DataSize);
}

void ResPacker::Loader::UnloadObjectDataRaw(std::string ID)
{
	uint32_t index = m_IDToIndexMap[ID];
	if (m_Structure.Objects[index].Data == nullptr) {
		return;
	}
	delete[] m_Structure.Objects[index].Data;
	m_Structure.Objects[index].Data = nullptr;
}

std::string ResPacker::Loader::GetExtension(std::string ID)
{
	uint32_t index = m_IDToIndexMap[ID];
	std::ostringstream oss;
	for (uint32_t _ = 0; _ < m_Structure.Objects[index].ExtSize; ++_) {
		oss << m_Structure.Objects[index].Ext[_];
	}
	if (oss.str().starts_with(".")) {
		return oss.str();
	}
	return "." + oss.str();
}

Sound ResPacker::Loader::LoadAsSound(std::string ID, std::string ext)
{
	uint32_t index = m_IDToIndexMap[ID];

	Sound emptySound = { 0 };

	if (m_Structure.Objects[index].Data == nullptr) {
		TraceLog(LOG_FATAL, (std::string("Failed to load sound (") + ID + std::string(")")).c_str());
		return emptySound;
	}

	if (ext == "") {
		ext = GetExtension(ID);
	}
	Wave wave = LoadWaveFromMemory(ext.c_str(), m_Structure.Objects[index].Data, m_Structure.Objects[index].DataSize);
	if (!IsWaveValid(wave)) {
		TraceLog(LOG_FATAL, (std::string("Failed to load wave while loading sound (") + ID + std::string(")")).c_str());
		return emptySound;
	}

	Sound sound = LoadSoundFromWave(wave);
	UnloadWave(wave);
	return sound;
}

Music ResPacker::Loader::LoadAsMusicStream(std::string ID, std::string ext)
{
	uint32_t index = m_IDToIndexMap[ID];

	Music emptyMusic = { 0 };

	if (m_Structure.Objects[index].Data == nullptr) {
		TraceLog(LOG_FATAL, (std::string("Failed to load music stream (") + ID + std::string(")")).c_str());
		return emptyMusic;
	}

	if (ext == "") {
		ext = GetExtension(ID);
	}
	return LoadMusicStreamFromMemory(ext.c_str(), m_Structure.Objects[index].Data, m_Structure.Objects[index].DataSize);
}

Texture2D ResPacker::Loader::LoadAsTexture2D(std::string ID, std::string ext)
{
	uint32_t index = m_IDToIndexMap[ID];

	Texture2D emptyTexture = { 0 };

	if (m_Structure.Objects[index].Data == nullptr) {
		TraceLog(LOG_FATAL, (std::string("Failed to load texture (") + ID + std::string(")")).c_str());
		return emptyTexture;
	}

	if (ext == "") {
		ext = GetExtension(ID);
	}

	Image image = LoadImageFromMemory(ext.c_str(), m_Structure.Objects[index].Data, m_Structure.Objects[index].DataSize);

	if (!IsImageValid(image)) {
		TraceLog(LOG_FATAL, (std::string("Failed to load image while loading texture (") + ID + std::string(")")).c_str());
		return emptyTexture;
	}

	Texture2D tex = LoadTextureFromImage(image);
	UnloadImage(image);
	return tex;
}

Font ResPacker::Loader::LoadAsFont(std::string ID, std::string ext, int32_t fontSize, int32_t* codepoints, int32_t cpCount)
{
	uint32_t index = m_IDToIndexMap[ID];

	if (m_Structure.Objects[index].Data == nullptr) {
		TraceLog(LOG_FATAL, (std::string("Failed to load font (") + ID + std::string("). Using default font.")).c_str());

		return GetFontDefault();
	}

	if (ext.empty()) {
		ext = GetExtension(ID);
	}

	return LoadFontFromMemory(ext.c_str(), m_Structure.Objects[index].Data, m_Structure.Objects[index].DataSize, fontSize, codepoints, cpCount);
}

ResPacker::Dumper::Dumper(std::string fileName)
{
	if (std::filesystem::is_regular_file(fileName)) {
		std::cout << "[Error] Dump file already exists!" << std::endl;
		return;
	}

	m_File.open(fileName, std::ios::binary | std::ios::out);
	m_File.flush();
	m_File.write("0000", 4);
}

ResPacker::Dumper::~Dumper()
{
	if (m_File.is_open()) {
		m_File.close();
	}
}

bool ResPacker::Dumper::DumpFileBinary(std::string filePath, std::string ID, ObjectType type)
{
	if (!m_File.is_open()) {
		std::cout << "[Error] Out file not initialized!" << std::endl;
		return false;
	}
	if (!std::filesystem::is_regular_file(filePath)) {
		std::cout << "[Error] No such file: " << filePath << std::endl;
		return false;
	}
	for (auto id : m_IDs) {
		if (id == ID) {
			std::cout << "[Error] ID has already been used: " << ID << std::endl;
			return false;
		}
	}

	m_ObjectCnt++;
	Object obj;
	
	obj.BytePosInFile = (uint32_t)m_File.tellp();
	m_File.write((char*)&obj.BytePosInFile, sizeof(obj.BytePosInFile));
	
	obj.IDSize = ID.length();
	m_File.write((char*)&obj.IDSize, sizeof(obj.IDSize));
	m_File.write(ID.data(), obj.IDSize);
	
	obj.ExtSize = std::filesystem::path(filePath).extension().string().length();
	m_File.write((char*)&obj.ExtSize, sizeof(obj.ExtSize));
	m_File.write(std::filesystem::path(filePath).extension().string().data(), obj.ExtSize);

	obj.Type = (uint8_t)type;
	m_File.write((char*)&obj.Type, sizeof(obj.Type));

	uint32_t filesize = (uint32_t)std::filesystem::file_size(filePath);
	std::fstream rFile(filePath, std::ios::in | std::ios::binary);
	if (!rFile.is_open()) {
		std::cout << "[Error] Failed to open file: " << filePath << std::endl;
		return false;
	}
	
	m_File.write((char*)&filesize, sizeof(filesize));

	uint8_t* buf = nullptr;

	uint32_t bulkSize = 4 * 1024 * 1024;
	uint32_t bulkCnt = 0;

	uint32_t bytesRemaining = filesize;
	while (bytesRemaining > 0) {
		if (buf != nullptr) {
			delete[] buf;
			buf = nullptr;
		}

		uint32_t bufSize = 0;

		if (bytesRemaining >= bulkSize) {
			bytesRemaining -= bulkSize;
			buf = new uint8_t[bulkSize];
			bufSize = bulkSize;
		}
		else {
			buf = new uint8_t[bytesRemaining];
			bufSize = bytesRemaining;
			bytesRemaining = 0;
		}

		rFile.read((char*)buf, bufSize);
		m_File.write((char*)buf, bufSize);
		bulkCnt++;
	}

	if (buf != nullptr) {
		delete[] buf;
		buf = nullptr;
	}

	std::cout << "[Info] Wrote " << ID << " in " << bulkCnt << "bulks." << std::endl;
	rFile.close();

	m_File.seekp(0, std::ios::beg);
	m_File.write((char*)&m_ObjectCnt, sizeof(m_ObjectCnt));
	m_File.seekp(0, std::ios::end);

	return true;
}

bool ResPacker::Dumper::DumpDataRaw(std::string ID, ObjectType type, std::string ext, uint8_t* data, uint32_t dataSize)
{
	if (!m_File.is_open()) {
		std::cout << "[Error] Out file not initialized!" << std::endl;
		return false;
	}
	for (auto id : m_IDs) {
		if (id == ID) {
			std::cout << "[Error] ID has already been used: " << ID << std::endl;
			return false;
		}
	}
	if (ID.empty()) {
		std::cout << "[Error] ID cannot be empty!" << std::endl;
		return false;
	}
	if (!ext.starts_with(".") and !ext.empty()) {
		ext = "." + ext;
	}

	m_ObjectCnt++;
	Object obj;

	obj.BytePosInFile = (uint32_t)m_File.tellp();
	m_File.write((char*)&obj.BytePosInFile, sizeof(obj.BytePosInFile));

	obj.IDSize = ID.length();
	m_File.write((char*)&obj.IDSize, sizeof(obj.IDSize));
	m_File.write(ID.data(), obj.IDSize);

	obj.ExtSize = ext.length();
	m_File.write(ext.data(), obj.ExtSize);

	obj.Type = (uint8_t)type;
	m_File.write((char*)&obj.Type, sizeof(obj.Type));

	m_File.write((char*)&dataSize, sizeof(dataSize));
	m_File.write((char*)data, dataSize);

	m_File.seekp(0, std::ios::beg);
	m_File.write((char*)&m_ObjectCnt, sizeof(m_ObjectCnt));
	m_File.seekp(0, std::ios::end);

	return true;
}
