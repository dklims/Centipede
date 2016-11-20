//BulletFactory.h
//David Klimavich, November 2016

#ifndef _BulletFactory
#define _BulletFactory

#include <stack>
#include "Bullet.h"
#include "Blaster.h"

//class Blaster;
class BulletFactory 
{
public:
	static std::stack<Bullet*> recycledItems;

	BulletFactory();
	~BulletFactory();

	static Bullet * CreateBullet(sf::Vector2f pos, Blaster * blaster);
	static void RecycleBullet(GameObject *go);
	static void Terminate();

private:
	Bullet* PrivateCreateBullet(sf::Vector2f pos, Blaster *blaster);

	static BulletFactory* instance;

	static void PrivateRecycleBullet(GameObject *go);

	//singleton functions
	static BulletFactory& GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new BulletFactory();
		}
		return *instance;

	};
};
#endif _BulletFactory
