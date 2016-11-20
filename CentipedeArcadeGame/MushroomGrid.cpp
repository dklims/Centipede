//MushroomGrid
//David Klimavich
#include "MushroomGrid.h"
#include "Mushroom.h"
#include "math.h"
#include "time.h"
#include "CentipedeHead.h"
#include "MushroomFactory.h"

#include "CritterManager.h"

MushroomGrid *MushroomGrid::instance = nullptr; 
MushroomGrid::MushroomGrid()
{

	spriteSize = 16;
	gridRows = 32;
	mushroomRows = 30;
	gridCollumns = 30;
	MushroomsPerRow = 2;
	//TESTING
	//RegisterInput(InputFlags::KeyPressed);


	//initialize mushroom grid array
	InitializeGridToNull();

	//---------------------------------
	//TempField();
	//CreateField();
	
	//mushroomsInPlayerArea = 5 * MushroomsPerRow;
}

//cleanup mushroom after death
void MushroomGrid::MushroomDelete(sf::Vector2i arrayLocation)
{
	MushroomArray[arrayLocation.x][arrayLocation.y] = nullptr;
	if (arrayLocation.y > 27)
	{
		mushroomsInPlayerArea--;
		if (mushroomsInPlayerArea < 5)
		{
			CritterManager::GetInstance().SpawnFlea();
		}
		
	}
	

   
	
}

//place mushroom at specified on screen location
void MushroomGrid::placeMushroom(sf::Vector2f onScreenLocation)
{
	sf::Vector2i gridLoc = onScreenLocationToGridLocation(onScreenLocation);
	
	if (MushroomArray[gridLoc.x][gridLoc.y] == nullptr)
	{
		MushroomArray[gridLoc.x][gridLoc.y] = MushroomFactory::CreateMushroom(gridLoc, onScreenLocation, this);
	}
	
	
}

//convert a position on screen to a position within the grid array
sf::Vector2i MushroomGrid::onScreenLocationToGridLocation(sf::Vector2f onScreenLocation)
{
	return GetInstance().PrivateonScreenLocationToGridLocation(onScreenLocation);
}
sf::Vector2i MushroomGrid::PrivateonScreenLocationToGridLocation(sf::Vector2f onScreenLocation)
{
	return{ int(onScreenLocation.x / spriteSize), int(onScreenLocation.y / spriteSize) };
}

//converts a position in the gird to a position on screen
sf::Vector2f MushroomGrid::GridLocationToOnScreenLocation(sf::Vector2f GridLocation)
{
	return GetInstance().PrivateGridLocationToOnScreenLocation(GridLocation);
}
sf::Vector2f MushroomGrid::PrivateGridLocationToOnScreenLocation(sf::Vector2f GridLocation)
{
	return{ float((GridLocation.x * spriteSize) + (spriteSize / 2)), float((GridLocation.y * spriteSize) + (spriteSize / 2)) };
}

//returns handle to a game object. 

Mushroom* MushroomGrid::returnMushroom(sf::Vector2f onScreenLocation)
{
	return GetInstance().PrivateReturnMushroom(onScreenLocation);
}
Mushroom * MushroomGrid::PrivateReturnMushroom(sf::Vector2f onScreenLocation)
{
	sf::Vector2i gridLocc = onScreenLocationToGridLocation(onScreenLocation);
	return MushroomArray[gridLocc.x][gridLocc.y];
}


//check next grid space for centipede movement
bool MushroomGrid::gridSpaceEmpty(sf::Vector2f objectPos, sf::Vector2i offset) 
{
	return GetInstance().PrivateGridSpaceEmpty(objectPos, offset);
}
bool MushroomGrid::PrivateGridSpaceEmpty(sf::Vector2f objectPos, sf::Vector2i offset)
{
	sf::Vector2f objectPosition = objectPos;
	sf::Vector2i GridPos = onScreenLocationToGridLocation(objectPosition);
	//	ConsoleMsg::WriteLine("MushroomArray = " + Tools::ToString(GridPos));

	if (MushroomArray[GridPos.x + offset.x][GridPos.y] != nullptr)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void MushroomGrid::CreateField()
{
	GetInstance().PrivateCreateField();
}
void MushroomGrid::PrivateCreateField()
{
	for (int row = 1; row < mushroomRows + 1; row++)
	{
		for (int j = 0; j < MushroomsPerRow; j++)
		{
			ranCollumn = rand() % gridCollumns;
			gridLoc = { ranCollumn,row };
			onScreenLoc = GridLocationToOnScreenLocation(sf::Vector2f(gridLoc)); // assign on-screen mushroom location. 
			MushroomArray[gridLoc.x][gridLoc.y] = MushroomFactory::CreateMushroom(gridLoc, onScreenLoc, this); // true means mushroom in spot.
		}
	}

	mushroomsInPlayerArea = 0;
	int topOfplayerZone = 26;
	for (int i = topOfplayerZone; i < mushroomRows; i++)
	{
		for (int collumn = 0; collumn < gridCollumns; collumn++)
		{
			if (MushroomArray[collumn][i] != nullptr)
			{
				mushroomsInPlayerArea++;
			}
		}
	}
}

void MushroomGrid::TempField()
{
	for (int row = 1; row < mushroomRows + 1; row++)
	{
		int collumn = 29; 
		ranCollumn = rand() % gridCollumns;
		gridLoc = { collumn,row };
		onScreenLoc = GridLocationToOnScreenLocation(sf::Vector2f(gridLoc)); // assign on-screen mushroom location. 
		MushroomArray[gridLoc.x][gridLoc.y] = MushroomFactory::CreateMushroom(gridLoc, onScreenLoc, this); // true means mushroom in spot.
	}
}

void MushroomGrid::InitializeGridToNull()
{
	for (int row = 0; row <= gridRows; row++)
	{
		for (int collumn = 0; collumn < gridCollumns; collumn++)
		{
			MushroomArray[collumn][row] = nullptr;
		}
	}
}

void MushroomGrid::RestoreField()
{
	GetInstance().PrivateRestoreField();
}

void MushroomGrid::PrivateRestoreField()
{
	for (int row = 1; row < mushroomRows + 1; row++)
	{
		for (int collumn = 0; collumn < gridCollumns; collumn++)
		{
			if (MushroomArray[collumn][row] != nullptr)
			{
				MushroomArray[collumn][row]->RestoreHealth();
				MushroomArray[collumn][row]->UnPoison();
			}
		}
	}
}

void MushroomGrid::ResetGrid()
{
	GetInstance().PrivateResetGrid();
}
void MushroomGrid::PrivateResetGrid()
{
	for (int row = 0; row < gridRows; row++)
	{
		for (int collumn = 0; collumn < gridCollumns; collumn++)
		{
			if (MushroomArray[collumn][row] != nullptr)
			{
				MushroomArray[collumn][row]->MarkForDestroy();
				MushroomArray[collumn][row] = nullptr;
			}

		}
	}
	CreateField();
}

MushroomGrid * MushroomGrid::GetPtrInstance()
{
	return GetInstance().PrivateGetPtrInstance();
}

MushroomGrid * MushroomGrid::PrivateGetPtrInstance()
{
	return instance; 
}
/*
void MushroomGrid::Terminate()
{
	for (int row = 0; row < gridRows; row++)
	{
		for (int collumn = 0; collumn < gridCollumns; collumn++)
		{
			if (MushroomArray[collumn][row] != nullptr)
			{
				//MushroomArray[collumn][row]->MarkForDestroy();
				//MushroomArray[collumn][row] = nullptr;
			}
		
		}
	}
}
*/