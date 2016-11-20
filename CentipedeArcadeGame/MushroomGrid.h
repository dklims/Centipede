//MushroomGrid
//David Klimavich

#ifndef _MushroomGrid
#define _MushroomGrid

#include "Game Components/TEAL/CommonElements.h"




class Mushroom;
class MushroomGrid : public GameObject
{
public:

	static MushroomGrid *GetPtrInstance();
	MushroomGrid();
	//static void Terminate();
	void MushroomDelete(sf::Vector2i arrayLocation);
	void placeMushroom(sf::Vector2f onScreenLocation);
	//virtual void Update();
	
	
	static sf::Vector2i onScreenLocationToGridLocation(sf::Vector2f onScreenLocation);
	static sf::Vector2f GridLocationToOnScreenLocation(sf::Vector2f GridLocation);
	static Mushroom * returnMushroom(sf::Vector2f onScreenLocation);
	static bool gridSpaceEmpty(sf::Vector2f centipedePos, sf::Vector2i offset);
	static void RestoreField();
	static void ResetGrid();
	static void CreateField();

private:
	//Private Methods
	sf::Vector2i PrivateonScreenLocationToGridLocation(sf::Vector2f onScreenLocation);
	sf::Vector2f PrivateGridLocationToOnScreenLocation(sf::Vector2f GridLocation);
	Mushroom * PrivateReturnMushroom(sf::Vector2f onScreenLocation);
	bool PrivateGridSpaceEmpty(sf::Vector2f centipedePos, sf::Vector2i offset);
	void PrivateRestoreField();
	void PrivateResetGrid();
	void PrivateCreateField();
	MushroomGrid *PrivateGetPtrInstance();


	static MushroomGrid* instance;

	static MushroomGrid &GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new MushroomGrid();
		}
		return *instance;
	}

	static const int rows = 32;
	static const int collumns = 30;

	Mushroom *MushroomArray[collumns][rows];
	int gridRows;
	int mushroomRows;
	int gridCollumns;
	int MushroomsPerRow;
	int mushroomsInPlayerArea;

	
	void TempField();
	void InitializeGridToNull();
	

	int spriteSize; 

	sf::Vector2f Pos;
	int ranCollumn;
	sf::Vector2f onScreenLoc;
	sf::Vector2i gridLoc;


};
#endif  _MushroomGrid

