// Ship
// Andre Berthiaume, Aug 2012

#ifndef _Blaster
#define _Blaster

#include "Game Components\TEAL\CommonElements.h"
#include "player.h"
#include "ExplosionFactory.h"


// Forward declarations
//class Widget;
//class Asteroid;
class Spider;
class Mushroom; 
class CentipedeHead;
class CentipedeSegment;

class Blaster : public GameObject
{
public:
	Blaster();
	virtual void Update();
	virtual void Draw();
	virtual void Destroy();
	virtual void KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey);

	void KillBullet();

	virtual void Collision(GameObject *other) {};
	virtual void Collision(Spider *other);
	virtual void Collision(CentipedeHead *other);
	virtual void Collision(CentipedeSegment *other);
	//virtual void Collision()

	void Collision(Mushroom * other);

	
	
	//virtual void Collision(GameObject *other) {};
	//void Collision(Widget *other);
	//void Collision(Asteroid *other);

private:

	//Lives
	int lives;


	//Player Boundaries
	sf::Vector2f offScreenPos;
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

	//player death
	void PlayerDead();

	sf::Sound FireSnd;
};

#endif _Blaster