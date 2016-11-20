#ifndef _ExplosionFactory
#define _ExplosionFactory

#include <stack>

#include "Explosion.h"
//#include "WaveManager.h"


class ExplosionFactory
{

public:
	static std::stack<Explosion*> recycledItems;

	ExplosionFactory();
	~ExplosionFactory();

	static Explosion * CreateExplosion(sf::Vector2f pos);
	static void RecycleExplosion(GameObject *go);
	static void Terminate();

	

private:
	static ExplosionFactory* instance;

	static ExplosionFactory& GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new ExplosionFactory();
		}
		return *instance;

	}


	Explosion * PrivateCreateExplosion(sf::Vector2f pos);
	static void PrivateRecycleExplosion(GameObject *go);


	//Singlton function

	


};

#endif _ExplosionFactory
