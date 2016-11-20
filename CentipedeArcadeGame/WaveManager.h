//WaveManager.h
//David Klimavich, November 2016

#ifndef _WaveManager
#define _WaveManager

#include "MushroomGrid.h"
//#include "CritterManager.h"
#include "MovementArrays.h"

//#include "CentipedeHeadFactory.h"
#include <fstream>
#include <iostream>

class WaveManager : public MovementArrays
{
public:
	WaveManager();
	WaveManager(const WaveManager&) = delete;
	WaveManager& operator=(const WaveManager&) = delete;
	
	static void StartWave();
	static void RestartWave();
	static void DecrementCentipedeHead();
	static void IncrementCentipedeHead();

	//PLAYER
	static int GetPlayerLives();

	//CENTIPEDE STATS
	static int GetCentipedeLength();

	//SPIDER STATS
	static float GetSpiderSpawnTimeMin();
	static float GetSpiderSpawnTimeMax();
	static float GetSpiderXSpeed();
	static float GetSpiderYSpeed();

	//SCORPION STATS
	static int GetScorpionSpawnTimeMin();
	static int GetScorpionSpawnTimeMax();
	static float GetScorpionSpawnTop();
	static float GetScorpionSpawnBottom();



	static void Terminate();




private:

	void PrivateStartWave();
	static void RestartGame();

	static WaveManager* instance;

	static WaveManager& GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new WaveManager;
		}
		return *instance;
	}

	std::ifstream settings;
	char lineToRead[30];
	std::string line;

	std::string ReturnVariableValue();

	void SetPlayerStats();
	void SetCentipedeStats();
	void SetSpiderStats();
	void SetScorpionStats();

	template <typename T>
	void SetStats(T &stat, std::string txtName);

	MushroomGrid *gridHandle;

	//player variables
	static int playerLives;

	//centipede variables
	static int CentipedeSpeed;
	static int CentipedeLength;
	static int CH_Count;


	//spider variables
	float spiderSpawnIntervalMin;
	float spiderSpawnIntervalMax;
	float spiderXSpeed;
	float SpiderYSpeed;

	//Scorpion Variables
	float scorpionSpawnIntervalMin;
	float scorpionSpawnIntervalMax;
	float scorpionTopSpawn;
	float scorpionBottomSpawn;

	//==============================================================PRIVATE METHODS
	void PrivateDecrementCentipedeHead();
	void PrivateIncrementCentipedeHead();

	//Player
	int PrivateGetPlayerLives();

	//CENTIPEDE STATS
	int PrivateGetCentipedeLength();

	//SPIDER STATS
	float PrivateGetSpiderSpawnTimeMin();
	float PrivateGetSpiderSpawnTimeMax();
	float PrivateGetSpiderXSpeed();
	float PrivateGetSpiderYSpeed();

	//SCORPION STATS
	int PriavteGetScorpionSpawnTimeMin();
	int PriavteGetScorpionSpawnTimeMax();
	float PrivateGetScorpionSpawnTop();
	float PrivateGetScorpionSpawnBottom();
};


#endif 