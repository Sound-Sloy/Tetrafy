#include "ScoreFileHandler.h"

void ScoreFileHandler::PlayerScore::Dump(std::fstream& file)
{
	assert(file.is_open());
	uint64_t pos = file.tellp();
	BytePosInFile = file.tellp();

	file.write((char*)&BytePosInFile, sizeof(BytePosInFile));
	file.write((char*)&Timestamp, sizeof(Timestamp));
	file.write((char*)&TimeSpent, sizeof(TimeSpent));

	uint64_t encryptedScore = EncryptScore();
	file.write((char*)&encryptedScore, sizeof(encryptedScore));

	file.write((char*)&Flags, sizeof(Flags));
	ComputeChecksum();
	file.write((char*)&Checksum, sizeof(Checksum));
}

bool ScoreFileHandler::PlayerScore::Load(std::fstream& file)
{
	assert(file.is_open());

	uint64_t curPos = static_cast<uint64_t>(file.tellp());

	file.read((char*)&this->BytePosInFile,	sizeof(this->BytePosInFile));

	if(this->BytePosInFile != curPos) {
		return false;
	}

	file.read((char*)&this->Timestamp,		sizeof(this->Timestamp));
	file.read((char*)&this->TimeSpent,		sizeof(this->TimeSpent));
	file.read((char*)&this->Score,			sizeof(this->Score));
	this->Score = DecryptScore(this->Score);
	file.read((char*)&this->Flags,			sizeof(this->Flags));
	uint64_t checksum = 0;

	file.read((char*)&checksum,		sizeof(checksum));

	ComputeChecksum();

	if (this->Checksum != checksum) {
		this->m_bTampered = true;
		this->Checksum = checksum;
		return false;
	}

	return true;
}

ScoreFileHandler::ScoreFileHandler(std::filesystem::path filePath) :
	m_ScoreFilePath(filePath)
{
	
}

ScoreFileHandler::~ScoreFileHandler()
{
	if(m_File.is_open()) {
		m_File.close();
	}
}

void ScoreFileHandler::Load()
{
	if(m_File.is_open()) {
		m_File.close();
	}

	if(!std::filesystem::exists(m_ScoreFilePath) or !std::filesystem::is_regular_file(m_ScoreFilePath)) {
		return;
	}

	m_File.open(m_ScoreFilePath, std::ios::binary | std::ios::in);

	m_File.read((char*)&m_ScoreFile.ScoreFileHandlerVersion, sizeof(m_ScoreFile.ScoreFileHandlerVersion));
	m_File.read((char*)&m_ScoreFile.ObjectCount, sizeof(m_ScoreFile.ObjectCount));

	for(uint64_t _ = 0; _ < m_ScoreFile.ObjectCount; ++_) {
		PlayerScore playerScore;
		playerScore.Load(m_File);
		m_ScoreFile.Scores.emplace_back(playerScore);
		if(playerScore.IsTampered()) {
			m_bTampered = true;
		}
	}
	uint64_t checksum = 0;
	m_File.read((char*)&checksum, sizeof(checksum));

	if(checksum != m_ScoreFile.ComputeChecksum()) {
		m_bTampered = true;
	}
	m_ScoreFile.Checksum = checksum;

	m_File.close();
}

void ScoreFileHandler::Save()
{
	if (m_File.is_open()) {
		m_File.close();
	}

	assert(m_ScoreFile.ObjectCount == m_ScoreFile.Scores.size());
	//assert(std::filesystem::is_regular_file(m_ScoreFilePath));

	if (m_ScoreFile.ObjectCount == 0) return;

	m_File.open(m_ScoreFilePath, std::ios::binary | std::ios::out);

	m_File.write((char*)&m_ScoreFile.ScoreFileHandlerVersion, sizeof(m_ScoreFile.ScoreFileHandlerVersion));
	m_File.write((char*)&m_ScoreFile.ObjectCount, sizeof(m_ScoreFile.ObjectCount));


	for(PlayerScore& score : m_ScoreFile.Scores) {
		score.Dump(m_File);
	}
	m_ScoreFile.ComputeChecksum();
	m_File.write((char*)&m_ScoreFile.Checksum, sizeof(m_ScoreFile.Checksum));
}

bool ScoreFileHandler::IsFileTampered() const
{
	return m_bTampered;
}

void ScoreFileHandler::AddScoreEntry(ScoreFileHandler::PlayerScore score)
{
	m_ScoreFile.Scores.emplace_back(score);
	m_ScoreFile.ObjectCount = m_ScoreFile.Scores.size();
}

std::vector<ScoreFileHandler::PlayerScore> ScoreFileHandler::GetScores() const
{
	return m_ScoreFile.Scores;
}
