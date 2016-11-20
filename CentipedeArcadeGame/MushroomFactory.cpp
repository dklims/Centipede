//MushroomFactory.cpp
//David Klimavich, November 2016

#include "MushroomFactory.h"


std::stack<Mushroom*> MushroomFactory::recycledItems;
MushroomFactory *MushroomFactory::instance = nullptr;
MushroomFactory::MushroomFactory()
{
}

Mushroom * MushroomFactory::CreateMushroom(sf::Vector2i gridLoc, sf::Vector2f onScreenLoc, MushroomGrid *mushroomGrid)
{
	return GetInstance().PrivateCreateMushroom(gridLoc, onScreenLoc, mushroomGrid);
}

Mushroom * MushroomFactory::PrivateCreateMushroom(sf::Vector2i gridLoc, sf::Vector2f onScreenLoc, MushroomGrid * mushroomGrid)
{
	Mushroom *mushroom;
	if (recycledItems.empty())
	{
		mushroom = new Mushroom();
	}
	else
	{
		mushroom = recycledItems.top();
		recycledItems.pop();
	}

	mushroom->Initialize(gridLoc, onScreenLoc, mushroomGrid);
	return mushroom;
}

void MushroomFactory::RecycleMushroom(GameObject * mushroom)
{
	GetInstance().PrivateRecycleMushroom(mushroom);
}



void MushroomFactory::PrivateRecycleMushroom(GameObject *mushroom)
{
	recycledItems.push((Mushroom*)mushroom);
}

MushroomFactory::~MushroomFactory()
{
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
}
