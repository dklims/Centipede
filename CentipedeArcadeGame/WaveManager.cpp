//WaveManager.cpp
//David Klimavich, November 2016

#include "WaveManager.h"
#include "CentipedeHeadFactory.h"
#include "CentipedeSegmentFactory.h"
#include "CritterManager.h"


WaveManager *WaveManager::instance = nullptr;
int WaveManager::CentipedeSpeed;
int WaveManager::CentipedeLength;
int WaveManager::playerLives;
int WaveManager::CH_Count = 0;

WaveManager::WaveManager() 
{
	//instance = this; //CHANGE
	gridHandle = MushroomGrid::GetPtrInstance();
	CH_Count = CentipedeHeadFactory::GetCount();

	settings.open("waveManager.txt");

	
	if (settings.is_open())
	{
		while (settings)
		{
			settings.getline(lineToRead, sizeof(lineToRead));
			line = std::string(lineToRead);

			if (line == "[CENTIPEDE]")
				SetCentipedeStats();
			
			if (line == "[SPIDER]")
				SetSpiderStats();

			if (line == "[SCORPION]")
				SetScorpionStats();

			if (line == "[PLAYER]")
				SetPlayerStats();
		}
		
	}
	
	settings.close();

	
	//StartWave();
}

void WaveManager::StartWave()
{
	GetInstance().PrivateStartWave();
}
void WaveManager::PrivateStartWave() 
{ 
	CH_Count = 0;
	//WaveManager::WaveManager();

	//============================================
	static float speed = 2.0f;
	static const sf::Vector2f downVect = { 0,speed };
	static const sf::Vector2f down[8]
	{
		downVect, downVect, downVect, downVect, downVect, downVect, downVect, downVect
	};

	sf::Vector2f startingPos = { 248,8 };
	CentipedeHeadFactory::CreateCentipedeHead(true, (sf::Vector2f*)down, 7, startingPos);
	gridHandle->RestoreField();
	CritterManager::GetInstance().Initialize();
	
}

void WaveManager::RestartWave()
{
	int livesTemp = Player::GetLives();
	if (livesTemp <= 0)
	{
		RestartGame();
	}
	
	
	CentipedeHeadFactory::DestoryHeads();
	CentipedeSegmentFactory::DestroySegments();
	StartWave();


}

void WaveManager::RestartGame()
{
	//mushrooomgrid restart
	MushroomGrid::ResetGrid();

	//reset score
	ScoreManager::ResetScore();
	
	//reset lives
	Player::ResetLives();

	//reset HUD
	HUD::ScoreClear();
	HUD::UpdateHUD(0);
	
}

void WaveManager::DecrementCentipedeHead()
{
	GetInstance().PrivateDecrementCentipedeHead();
}

void WaveManager::IncrementCentipedeHead()
{
	GetInstance().PrivateIncrementCentipedeHead();
}

void WaveManager::SetPlayerStats()
{
	SetStats(playerLives, "MAX LIVES");
}

void WaveManager::SetCentipedeStats()
{
	SetStats(CentipedeSpeed, "SPEED");
	SetStats(CentipedeLength, "LENGTH");
}

void WaveManager::SetSpiderStats()
{
	SetStats(spiderSpawnIntervalMin, "SPAWN INTERVAL MIN");
	SetStats(spiderSpawnIntervalMax, "SPAWN INTERVAL MAX");
	SetStats(spiderXSpeed, "SPIDER X SPEED");
	SetStats(SpiderYSpeed, "SPIDER Y SPEED");
}

template <typename T>
void WaveManager::SetStats(T &stat, std::string txtName)
{
	settings.getline(lineToRead, sizeof(lineToRead));
	line = std::string(lineToRead);

	std::string statStr = "";
	//std::string LengthStr = "";

	while (line != "")
	{
		//set speed
		if (line.find(txtName) != std::string::npos)
		{
			statStr = ReturnVariableValue();
			stat = std::stoi(statStr);
			ConsoleMsg::WriteLine(txtName + " = " + Tools::ToString(stat));
			break;
		}

		settings.getline(lineToRead, sizeof(lineToRead));
		line = std::string(lineToRead);
		
	}
}
void WaveManager::SetScorpionStats()
{
	SetStats(scorpionSpawnIntervalMin, "SPAWN INTERVAL MIN");
	SetStats(scorpionSpawnIntervalMax, "SPAWN INTERVAL MAX");
	SetStats(scorpionTopSpawn, "TOP SPAWN RANGE");
	SetStats(scorpionBottomSpawn, "BOTTOM SPAWN RANGE");
}
int WaveManager::GetCentipedeLength()
{
	return GetInstance().PrivateGetCentipedeLength();
}

float WaveManager::GetSpiderSpawnTimeMin()
{
	return GetInstance().PrivateGetSpiderSpawnTimeMin();
}
float WaveManager::GetSpiderSpawnTimeMax()
{
	return GetInstance().PrivateGetSpiderSpawnTimeMax();
}

float WaveManager::GetSpiderXSpeed()
{
	return GetInstance().PrivateGetSpiderXSpeed();
}

float WaveManager::GetSpiderYSpeed()
{
	return GetInstance().PrivateGetSpiderYSpeed();
}

int WaveManager::GetScorpionSpawnTimeMin()
{
	return GetInstance().PrivateGetSpiderSpawnTimeMin();
}
int WaveManager::GetScorpionSpawnTimeMax()
{
	return GetInstance().PrivateGetSpiderSpawnTimeMax();
}

float WaveManager::GetScorpionSpawnTop()
{
	return GetInstance().PrivateGetScorpionSpawnTop();
}

float WaveManager::GetScorpionSpawnBottom()
{
	return GetInstance().PrivateGetScorpionSpawnBottom();
}

int WaveManager::GetPlayerLives()
{
	return GetInstance().PrivateGetPlayerLives();
}
std::string WaveManager::ReturnVariableValue()
{
	std::string returnString = "";

	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] == '=')
		{
			for (int j = i + 2; j < line.length(); j++)
			{
				returnString += (line[j]);
			}

			break;
		}
	}
	return returnString;
}

//=========private methods=====================//



void WaveManager::Terminate()
{
	instance = nullptr;
}

//CentipedeHead
void WaveManager::PrivateDecrementCentipedeHead()
{
	CH_Count--;
	if (CH_Count <= 0)
	{
		StartWave();
	}
}

void WaveManager::PrivateIncrementCentipedeHead()
{
	CH_Count++;
}

int WaveManager::PrivateGetCentipedeLength()
{
	return CentipedeLength;
}

//Spider
float WaveManager::PrivateGetSpiderSpawnTimeMin()
{
	return spiderSpawnIntervalMin;
}

float WaveManager::PrivateGetSpiderSpawnTimeMax()
{
	return spiderSpawnIntervalMax;
}

float WaveManager::PrivateGetSpiderXSpeed()
{
	return spiderXSpeed;
}

float WaveManager::PrivateGetSpiderYSpeed()
{
	return SpiderYSpeed;
}

//SCORPION
int WaveManager::PriavteGetScorpionSpawnTimeMin()
{
	return scorpionSpawnIntervalMin;
}

int WaveManager::PriavteGetScorpionSpawnTimeMax()
{
	return scorpionSpawnIntervalMax;
}

float WaveManager::PrivateGetScorpionSpawnTop()
{
	return scorpionTopSpawn;
}

float WaveManager::PrivateGetScorpionSpawnBottom()
{
	return scorpionBottomSpawn;
}

//PLAYER
int WaveManager::PrivateGetPlayerLives()
{
	return playerLives;
}