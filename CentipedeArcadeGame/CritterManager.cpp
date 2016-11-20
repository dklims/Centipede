#include "CritterManager.h"
//#include "WaveManager.h"

//factories
//#include "CentipedeHeadFactory.h"
//#include "SpiderFactory.h"
//#include "ScorpionFactory.h"
//class CentipedeHead;

CritterManager *CritterManager::instance = nullptr;
CritterManager::CritterManager()
{
	spiderTimerMax = WaveManager::GetSpiderSpawnTimeMax();
	spiderTimerMin = WaveManager::GetSpiderSpawnTimeMin();

	scorpionTimerMax = WaveManager::GetScorpionSpawnTimeMax();
	scorpionTimerMin = WaveManager::GetScorpionSpawnTimeMin();

	Initialize();

	gridHandle = MushroomGrid::GetPtrInstance();
	RegisterInput(InputFlags::KeyPressed);
	const float windowSizeX = WindowManager::MainWindow.getView().getSize().x;
	const float windowSizey = WindowManager::MainWindow.getView().getSize().y;
	
	
	//SetAlarm(0, spiderTimer);
	//SetAlarm(1, 15);

}

void CritterManager::Alarm0()
{
	SpawnSpider();
	SetAlarm(0, spiderTimer);
}

void CritterManager::Alarm1()
{
	SpawnScorpion();
	SetAlarm(1, scorpionTimer);
}
void CritterManager::Update()
{

}

void CritterManager::SpawnSpider()
{
	SpiderFactory::CreateSpider();
}

void CritterManager::SpawnScorpion()
{
	ScorpionFactory::CreateScorpion(/*{ -8,248 }*/);
}

CritterManager::~CritterManager()
{

}

void CritterManager::SpawnFlea()
{
	FleaFactory::CreateFlea();
}

void CritterManager::KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey)
{
	//spawn Scorpion
	if (k == sf::Keyboard::Num1)
	{
		Scorpion *scorpion;
		scorpion = ScorpionFactory::CreateScorpion();
	}

	//spawn Centipede
	if (k == sf::Keyboard::Num2)
	{
		CentipedeHeadFactory::CreateCentipedeHead(true, (sf::Vector2f*)down, 7, { 248,-8 });
	}


	//spawn Spider
	if (k == sf::Keyboard::Num3)
	{
		FleaFactory::CreateFlea();
	}

	if (k == sf::Keyboard::Num4)
	{
		Spider *spider;
		spider = SpiderFactory::CreateSpider();
	}
}

void CritterManager::Initialize()
{
	//WaveManager::GetInstance().StartWave();
	spiderTimer = rand() % (spiderTimerMax - spiderTimerMin) + spiderTimerMin;
	SetAlarm(0, spiderTimer);

	srand(unsigned int(time));
	scorpionTimer = rand() % (scorpionTimerMax - scorpionTimerMin) + scorpionTimerMin;
	SetAlarm(1, scorpionTimer);
	
}