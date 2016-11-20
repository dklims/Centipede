//Bullet.h
//David Klimavich, November 2016

#ifndef _Bullet
#define _Bullet

#include "Game Components\TEAL\CommonElements.h"
//#include "Mushroom.h"
//#include "Blaster.h"

//Forward declarations
class Mushroom;
class Scorpion;
class Spider;
class Blaster;
class CentipedeHead;
class CentipedeSegment;

class Bullet : public GameObject
{
public:
	Bullet();

	bool *BulletAlivePtr = new bool();

	//void Initialize(sf::Vector2f p);

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();


	virtual void Collision(GameObject *go) {};
	virtual void Collision(Mushroom *other);
	virtual void Collision(Scorpion *other);
	virtual void Collision(Spider *other);
	virtual void Collision(CentipedeHead * other);
	virtual void Collision(CentipedeSegment * other);

	void Initialize(sf::Vector2f p, Blaster *blaster);


private:

	Blaster *player;

	sf::Vector2f scale;
	sf::Vector2f origin;
	sf::Vector2f animationFrameRange;

	int animationFrameStart;
	int animationFrameEnd;

	float SPEED;

	sf::Vector2f Pos;
	AnimatedSprite MainSprite;
	CollisionTools::TextureBitmap bitmap;

};

#endif _Bullet