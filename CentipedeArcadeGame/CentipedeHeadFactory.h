//CentipedeHeadFactory.h
//David Klimavich, November 2016

#ifndef _CentipedeHeadFactory
#define _CentipedeHeadFactory

#include <stack>

#include "CentipedeHead.h"
//#include "WaveManager.h"


class CentipedeHeadFactory
{

public:
	

	CentipedeHeadFactory();
	~CentipedeHeadFactory();

	static CentipedeHead * CreateCentipedeHead(bool firstHeadPassed, sf::Vector2f *passedInDirection, int passedInArrayIt, sf::Vector2f startingPos);
	static int GetCount();
	static void RecycleCentipedeHead(GameObject *go);
	static void DestoryHeads();

	static void Terminate();

	//Singlton function

	

private:
	static std::stack<CentipedeHead*> recycledItems;
	static std::stack<CentipedeHead*> onScreenItems;

	int CH_Count;

	CentipedeHead * PrivateCreateCentipedeHead(bool firstHeadPassed, sf::Vector2f *passedInDirection, int passedInArrayIt, sf::Vector2f startingPos);
	void PrivateRecycleCentipedeHead(GameObject *go);
	int PrivateGetCount();
	void PrivateDestoryHeads();


	static CentipedeHeadFactory* instance;

	static CentipedeHeadFactory& GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new CentipedeHeadFactory();
		}
		return *instance;

	}


};

#endif _CentipedeHeadFactory
