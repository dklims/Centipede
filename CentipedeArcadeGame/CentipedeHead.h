//#pragma once

#ifndef _CentipedeHead
#define _CentipedeHead

#include "CentipedeBase.h"
//#include "CentipedeHeadFactory.h"
//#include "CentipedeSegmentFactory.h"
#include "MushroomGrid.h"
#include "ExplosionFactory.h"


//Forward 
//class MushroomGrid;
class CentipedeSegment;
class Bullet;
//class WaveManager;


class CentipedeHead : public CentipedeBase
{


public:
	CentipedeHead();
	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	void movement(sf::Vector2f* orders);
	sf::Vector2f* ChangeDirection(sf::Vector2f* direction);


	void turnDown(); //for what?

	void createSegment();
	void CreateHead();
	void ResetVariables();
	void DetermineNextDirection();
	void SetSprite();
	void SetBoundaries();
	void SetAnimationInfo();
	void FirstHeadVariables();
	void NewHeadVariables();

	void Initialize(bool firstHeadPassed, sf::Vector2f * passedInDirection, int passedInArrayIt, sf::Vector2f startingPos);

	//collision
	virtual void Collision(GameObject *go);
	virtual void Collision(Bullet *other);

private:
//void PlaceMushroom();


	int arrayIt;

	int centipedeUnits;

	AnimatedSprite MainSprite;
	CollisionTools::TextureBitmap bitmap;

	sf::Vector2f scale;
	sf::Vector2f origin;
	sf::Vector2i animationFrameRange;
	sf::Vector2i spriteSheetDim;

	float rotation;

	float animationFPS;

	//float offset;
	//int speed;
	//sf::Vector2i impulse;

	//boundaries
	sf::Vector2f boundaries;
	int leftWall;
	int rightWall; 
	int floor;
	int ceiling;
	int nextBlockDown;

	//sf::Vector2f* direction;
	sf::Vector2f* nextDirection;
	sf::Vector2i offset;

	//rotations
	float faceRight = 180;
	float faceDown = 90;
	float faceLeft = 0;
	float faceUp = 270;

	//body creation
	bool bodyCreated;
	bool firstHead;

	

	

//	WaveManager* waveHandle;
	MushroomGrid* gridHandle;
};
#endif _CentipedeHead
