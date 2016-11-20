//CentipedeBase.cpp
//David Klimavich, November 2016


#include "CentipedeBase.h"
#include "CentipedeHead.h"
#include "MushroomGrid.h"
#include "CentipedeSegment.h"


CentipedeBase::CentipedeBase()
{}

CentipedeBase::~CentipedeBase()
{
}

sf::Vector2f * CentipedeBase::getOrders()
{
	return prevDirection;
}

sf::Vector2f CentipedeBase::getPosition()
{
	return pos;
}

sf::Vector2f * CentipedeBase::getCurrentDirection()
{
	return direction;
}

void CentipedeBase::PlaceMushroom(sf::Vector2f *dir, MushroomGrid* mushroomGrid)
{
	//MUSHROOM PLACEMENT
	int mushPosX = (int(pos.x / spriteSize) * spriteSize);
	int mushPosY = (int(pos.y / spriteSize) * spriteSize);

	if (*dir == *right)
	{
		mushPosX += spriteSize / 2;
		mushPosY += spriteSize / 2;
	}
	else if (*dir == *left)
	{
		mushPosX += spriteSize / 2;
		mushPosY += spriteSize / 2;
	}

	else if (*dir == *up)
	{
		mushPosY -= spriteSize / 2;
		mushPosX -= spriteSize / 2;
	}
	else if (*dir == *down)
	{
		mushPosY += spriteSize / 2;
		mushPosX += spriteSize / 2;
	}

	//if left then no modification is needed. 
	mushroomGrid->placeMushroom({ (float)mushPosX, (float)mushPosY });
}

void CentipedeBase::Destroy()
{
	
}