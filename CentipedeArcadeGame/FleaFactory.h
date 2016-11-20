//FleaFactory.h
//David Klimavich, November 2016

#ifndef _FleaFactory
#define _FleaFactory

#include "Flea.h"
#include <stack>
#include "MushroomGrid.h"

class FleaFactory
{
public:
	static std::stack<Flea*> recycledItems;

	FleaFactory();
	~FleaFactory();

	static Flea * CreateFlea();
	static void RecycleFlea(GameObject *go);
	static void Terminate();

private:
	static Flea * PrivateCreateFlea();
	static void PrivateRecycleFlea(GameObject *go);
	
	//singleton Function
	static FleaFactory* instance;

	static FleaFactory& GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new FleaFactory();
		}
		return *instance;
	}
	
};
#endif _FleaFactory
