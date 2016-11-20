//Flea.h
//David Klimavich, November 2016

#ifndef _Flea
#define _Flea

#include "CritterBase.h"
#include "math.h"
#include "ScoreManager.h"
#include "ExplosionFactory.h"

//#include "MushroomGrid.h"

class Bullet;

class Flea : public CritterBase
{
public:

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();
	Flea();

	void Move();

	//collision
	virtual void Collision(GameObject *go);
	virtual void Collision(Bullet *other);

	//initialize on creation
	void Initialize();


private:
	int randNum; 
	int mushroomFreq;

	//boundary
	float bottomOfScreen;

	//MushroomGrid *gridHandle;

	//points
	int points;

	//
	



};
#endif _Flea
