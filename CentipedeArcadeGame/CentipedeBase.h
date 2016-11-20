//CentipedeBase.h
//David Klimavich, November 2016

#ifndef _CentipedeManagement
#define _CentipedeManagement

#include "Game Components\TEAL\CommonElements.h"
#include "MushroomGrid.h"
#include "ScoreManager.h"
#include "MovementArrays.h"

class CentipedeBase : public MovementArrays
{
public:
	//sf::Vector2f *directions;
	CentipedeBase *next = nullptr;
	CentipedeBase *prev = nullptr;

	sf::Vector2f *getOrders(); 
	sf::Vector2f getPosition();
	sf::Vector2f *getCurrentDirection();

	virtual void Destroy();
	
protected:

	void PlaceMushroom(sf::Vector2f *dir, MushroomGrid* mushroomGrid);
	//directions
	// size of 7 for 8 frame cycles.
	CentipedeBase();
	virtual ~CentipedeBase();
	const int spriteSize = 16;

	//void PlaceMushroom(sf::Vector2f *dir, MushroomGrid* mushroomGrid);

	sf::Vector2f *direction;
	sf::Vector2f *prevDirection;
	sf::Vector2f pos; 

	

	
	

private:
	

	
	
};

#endif _Centipedemanagement
