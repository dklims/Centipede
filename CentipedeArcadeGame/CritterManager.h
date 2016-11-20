#ifndef _CritterManager
#define _CritterManager

#include "Game Components\TEAL\CommonElements.h"
#include "CentipedeBase.h"

//factories
#include "CentipedeHeadFactory.h"
#include "ScorpionFactory.h"
#include "FleaFactory.h"
#include "SpiderFactory.h"



class CritterManager : public CentipedeBase
{
public:
	CritterManager();
	CritterManager(const CritterManager&) = delete;
	CritterManager& operator=(const CritterManager&) = delete;
	void Initialize();

	virtual void Alarm0();
	virtual void Alarm1();

	virtual void Update();
	virtual void KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey);

	void SpawnFlea();
	void SpawnSpider();
	void SpawnScorpion();

	//Singlton function

	static CritterManager* instance;

	static CritterManager& GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new CritterManager();
		}
		return *instance;

	}

private:
	~CritterManager();
	MushroomGrid *gridHandle;

	//spider variables
	int spiderTimer;
	int spiderTimerMin;
	int spiderTimerMax;
	
	//scorpion variables
	int scorpionTimer;
	int scorpionTimerMin;
	int scorpionTimerMax;
	
};

#endif _CritterManager