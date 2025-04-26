#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <filesystem>
#include <cassert>

class ScoreFileHandler {
public:
	struct PlayerScore {
	public:
		uint64_t BytePosInFile = 0;
		std::time_t Timestamp = std::time(nullptr);
		uint32_t TimeSpent = 0;
		uint64_t Score = 0;
		uint64_t Flags = 0x0;
		uint64_t Checksum = 0;


		bool IsTampered() const
		{
			return m_bTampered;
		}

		uint64_t ComputeChecksum()
		{
			uint64_t sum = BytePosInFile + Timestamp + TimeSpent + Score + Flags;
			Checksum = sum ^ 0x5EEB00B5DEADBEEF;
			return sum ^ 0x5EEB00B5DEADBEEF;
		}

		constexpr bool operator== (const PlayerScore& rhs) const 
		{
			return this->TimeSpent == rhs.TimeSpent and this->BytePosInFile == rhs.BytePosInFile and this->Checksum == rhs.Checksum and this->Flags == rhs.Flags and this->Score == rhs.Score and this->Timestamp == rhs.Timestamp and this->m_bTampered == rhs.m_bTampered;
		}

		void Dump(std::fstream& file);
		bool Load(std::fstream& file);

	private:
		bool m_bTampered = false;

		uint64_t GenerateKey() {
			return (Timestamp ^ 0xDEADBEEFCAFEBABEULL) ^ ((Timestamp << 13) | (Timestamp >> 51));
		}

		uint64_t EncryptScore() {
			uint64_t key = GenerateKey();
			return Score ^ key;
		}

		uint64_t DecryptScore(uint64_t encryptedScore) {
			uint64_t key = GenerateKey();
			return encryptedScore ^ key;
		}
	};

	struct ScoreFile {
	public:
		uint64_t ScoreFileHandlerVersion = c_SCORE_FILE_HANDLER_VERSION;
		uint64_t ObjectCount = 0;
		std::vector<PlayerScore> Scores;
		uint64_t Checksum = 0;

		uint64_t ComputeChecksum()
		{
			uint64_t sum = ScoreFileHandlerVersion + ObjectCount;
			Checksum = sum ^ 0x5EEB00B5DEADBEEF;
			return sum ^ 0x5EEB00B5DEADBEEF;
		}
	};

	ScoreFileHandler(std::filesystem::path filePath = "");
	~ScoreFileHandler();

	void Load();
	void Save();

	bool IsFileTampered() const;

	void AddScoreEntry(ScoreFileHandler::PlayerScore score);
	std::vector<PlayerScore> GetScores() const;

public:
	static constexpr uint64_t c_SCORE_FILE_HANDLER_VERSION = 0x1;

private:
	ScoreFile m_ScoreFile;
	std::filesystem::path m_ScoreFilePath;
	std::fstream m_File;

	bool m_bTampered = false;
};

