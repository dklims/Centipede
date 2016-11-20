//MushroomFactory.h
//David Klimavich, November 2016

#ifndef _MushroomFactory
#define _MushroomFactory

#include <stack>

#include "Mushroom.h"
#include "MushroomGrid.h"



class MushroomFactory
{


public:
	static std::stack<Mushroom*> recycledItems;

	MushroomFactory();
	~MushroomFactory();

	static Mushroom* CreateMushroom(sf::Vector2i gridLoc, sf::Vector2f onScreenLoc, MushroomGrid *mushroomGrid);
	static void RecycleMushroom(GameObject *go);
	//static void Terminate();

private:
	static Mushroom* PrivateCreateMushroom(sf::Vector2i gridLoc, sf::Vector2f onScreenLoc, MushroomGrid *mushroomGrid);
	static void PrivateRecycleMushroom(GameObject *go);

	//singleton Function
	static MushroomFactory* instance;

	static MushroomFactory& GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new MushroomFactory();
		}
		return *instance;
	}

};


#endif _MushroomFactory
