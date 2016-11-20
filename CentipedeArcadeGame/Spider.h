#ifndef _Spider
#define _Spider

#include "CritterBase.h"
//#include <math.h>
#include "Mushroom.h"
#include "ExplosionFactory.h"
#include "WaveManager.h"


class Blaster;
class Spider : public CritterBase
{
public:
	Spider();
	virtual void Update();
	virtual void Draw();
	virtual void Destroy();
	
	//collision
	virtual void Collision(GameObject *go) {};
	virtual void Collision(Mushroom *other);
	virtual void Collision(Blaster *other);
	virtual void Collision(Bullet *other);

	void Initialize();
	



private:
	sf::Vector2f* direction;
	
	void Movement();
	void RandomMovement(); 

	const int maxYstart = 496; 
	const int minYstart = 400; 
	//const int vertRange = (maxYstart - minYstart) / 2;

	int randomNum;
	int arrayIt;

	sf::Vector2f startingPos;




	
	const float xSpeed = WaveManager::GetSpiderXSpeed();//1.0f;
	const float ySpeed = WaveManager::GetSpiderYSpeed();//3.0f;

	const sf::Vector2f DownVect = { 0,ySpeed };
	const sf::Vector2f Down[8]
	{
		DownVect,DownVect,DownVect,DownVect,DownVect,DownVect,DownVect,DownVect
	};

	const sf::Vector2f DownRightVect = { xSpeed,ySpeed };
	const sf::Vector2f DownRight[8]
	{
		DownRightVect,DownRightVect,DownRightVect,DownRightVect,DownRightVect,DownRightVect,DownRightVect,DownRightVect
	};

	const sf::Vector2f DownLeftVect = { -xSpeed,ySpeed };
	const sf::Vector2f DownLeft[8]
	{
		DownLeftVect,DownLeftVect,DownLeftVect,DownLeftVect,DownLeftVect,DownLeftVect,DownLeftVect,DownLeftVect
	};

	const sf::Vector2f UpRightVect = { xSpeed,-ySpeed };
	const sf::Vector2f UpRight[8]
	{
		UpRightVect,UpRightVect,UpRightVect,UpRightVect,UpRightVect,UpRightVect,UpRightVect,UpRightVect
	};

	const sf::Vector2f UpLeftVect = { -xSpeed,-ySpeed };
	const sf::Vector2f UpLeft[8]
	{
		UpLeftVect,UpLeftVect,UpLeftVect,UpLeftVect,UpLeftVect,UpLeftVect,UpLeftVect,UpLeftVect
	};
};

#endif // !_Spider
