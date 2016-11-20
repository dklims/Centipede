#ifndef _Scorpion
#define _Scorpion

//#include "Game Components\TEAL\CommonElements.h"
#include "CritterBase.h"
#include "ScoreManager.h"
#include "Mushroom.h"
#include "ExplosionFactory.h"
#include "WaveManager.h"
//Forward Declerations
class Bullet;


class Scorpion : public CritterBase
{
public:
	Scorpion();

	//Virtual Methods
	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	//Collision
	virtual void Collision(GameObject * go) {};
	void Collision(Bullet * other);

	//initialize varibales on creation
	void Initialize();

private:
	//Position
	float maxSpeed;
	sf::Vector2f tempPosition; //For use inside class
	float windowSizeX;
	float leftScreenSide;
	float rightScreenSide;

	//Sprite
	AnimatedSprite MainSprite;
	float animationFPS;

	//Collision

	//CollisionTools::TextureBitmap* bitmap;

	//refrence to mushroom

	Mushroom *mushroom;

	//Sound
	//sf::Sound ScorpionStep;

	//direction
	int direction;
	float screenSide;

};

#endif _Scorpion