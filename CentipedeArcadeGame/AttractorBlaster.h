#ifndef _AttractorBlaster
#define _AttractorBlaster

#include "Game Components\TEAL\CommonElements.h"

class Spider;
class AttractorBlaster
{
public:
	AttractorBlaster();
	
	virtual void Update();
	virtual void Draw();
	virtual void Destroy();
	
	void KillBullet();

	virtual void Collision(GameObject *other);
	virtual void Collision(Spider *other);



private:


	//Player Boundaries
	int topPlayerWall;
	int bottomPlayerWall;
	int leftPlayerWall;
	int rightPlayerWall;

	sf::Vector2f scale;
	sf::Vector2f origin;
	sf::Vector2f animationFrameRange;

	int animationFrameStart;
	int animationFrameEnd;

	float SPEED;
	float HBORDER;
	float TBORDER;
	sf::Vector2f GunOffset;

	float offset;

	sf::Vector2f Pos;
	sf::Vector2f prevPos;
	sf::Vector2f Impulse;
	float friction;

	AnimatedSprite MainSprite;
	CollisionTools::TextureBitmap bitmap;

	bool BulletAlive;


};


#endif _AttractorBlaster