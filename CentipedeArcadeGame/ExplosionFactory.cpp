#include "Game Components\TEAL\CommonElements.h"
#include "ExplosionFactory.h"
#include "CentipedeSegmentFactory.h"
#include "WaveManager.h"

std::stack<Explosion*> ExplosionFactory::recycledItems;
ExplosionFactory *ExplosionFactory::instance = nullptr;

ExplosionFactory::ExplosionFactory()
{

}

Explosion* ExplosionFactory::CreateExplosion(sf::Vector2f pos)
{
	return GetInstance().PrivateCreateExplosion(pos);
}

Explosion* ExplosionFactory::PrivateCreateExplosion(sf::Vector2f pos)
{
	Explosion* explosion;

	if (recycledItems.empty())
	{
		ConsoleMsg::WriteLine("New Explosion"); // For illustration purposes

		explosion = new Explosion();


		// Declares that this object should be returned here (rather than deleted) when destroyed
		explosion->SetExternalManagement(RecycleExplosion);
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled Explosion"); // For illustration purposes
		explosion = recycledItems.top();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

								// Tell the object to register itself to the scene
		explosion->RegisterToCurrentScene();
	}

	explosion->Initialize(pos);

	return explosion;



}

void ExplosionFactory::RecycleExplosion(GameObject * explosion)
{
	GetInstance().PrivateRecycleExplosion(explosion);
}

void ExplosionFactory::PrivateRecycleExplosion(GameObject * explosion)
{
	recycledItems.push((Explosion*)explosion);
}


void ExplosionFactory::Terminate()
{
	delete instance;
	instance = nullptr;
}

ExplosionFactory::~ExplosionFactory()
{
	// forcefully delele all recycled gameobjects
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
}