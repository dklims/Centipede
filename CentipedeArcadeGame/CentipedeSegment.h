//CentipedeSegment.h
//David Klimavich, November 2016

#ifndef _CentipedeSegment
#define _CentipedeSegment

#include "Game Components\TEAL\CommonElements.h"
#include "CentipedeHead.h"
#include "CentipedeBase.h"
#include "MushroomGrid.h"



class Bullet;
class CentipedeSegment : public CentipedeBase
{
public:

//	CentipedeHead *prev = nullptr;

	CentipedeSegment();

	virtual void Draw();
	virtual void Update();
	virtual void Destroy();

	void Initialize(sf::Vector2f headPos, int segmentCount);
	void movement(sf::Vector2f* direction);
	void createSegment(int segmentCount);
	void destroySegment();

//	void Destroy();
	
	//Collision
	virtual void Collision(GameObject *go) {};
	virtual void Collision(Bullet *other);
	CentipedeHead * CreateHead();

private:

	//sf::Vector2f* direction;

	

	sf::Vector2i spriteSheetDim;
	sf::Vector2i animationFrameRange;
	float animationFPS;
	int rotation;
	sf::Vector2f scale;
	sf::Vector2f origin;

	int arrayIt;
	int currentSegmentCount;
	//int centipedeUnits; 

	AnimatedSprite MainSprite;
	CollisionTools::TextureBitmap bitmap;
	//CollisionTolls::TextureBitmap 

	//MUSHROOM GRID
	MushroomGrid *gridHandle;
};
#endif _CentipedeSegment
