#include "BulletFactory.h"

std::stack<Bullet*> BulletFactory::recycledItems;
BulletFactory* BulletFactory::instance = nullptr;

BulletFactory::BulletFactory()
{
	
}

Bullet* BulletFactory::CreateBullet(sf::Vector2f pos, Blaster *blaster)
{
	return GetInstance().PrivateCreateBullet(pos, blaster);
}

Bullet * BulletFactory::PrivateCreateBullet(sf::Vector2f pos, Blaster * blaster)
{
	Bullet* bullet;

	if (recycledItems.empty())
	{
		ConsoleMsg::WriteLine("New Bullet"); // For illustration purposes

		bullet = new Bullet();

		// Declares that this object should be returned here (rather than deleted) when destroyed
		bullet->SetExternalManagement(RecycleBullet);
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled Bullet"); // For illustration purposes
		bullet = recycledItems.top();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

								// Tell the object to register itself to the scene
		bullet->RegisterToCurrentScene();
	}

	bullet->Initialize(pos, blaster);

	return bullet;
}


void BulletFactory::RecycleBullet(GameObject *bullet)
{
	GetInstance().PrivateRecycleBullet(bullet);
}

void BulletFactory::PrivateRecycleBullet(GameObject *bullet)
{
	recycledItems.push((Bullet*)bullet);
	// For illustration purposes
	ConsoleMsg::WriteLine("Recycled Bullet Stack Size: " + Tools::ToString(recycledItems.size()));
}

void BulletFactory::Terminate()
{
	delete(instance);
	instance = nullptr;
}



BulletFactory::~BulletFactory()
{
	ConsoleMsg::WriteLine("BulletStackSize = " + Tools::ToString(recycledItems.size()));
	// forcefully delele all recycled gameobjects
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
	ConsoleMsg::WriteLine("Deleting recycled Bullets");
}


