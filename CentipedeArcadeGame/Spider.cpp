#include "Spider.h"

Spider::Spider()
{
	//pointer to the mushroom grid
	gridHandle = MushroomGrid::GetPtrInstance();
	//spider speed
	speed = 2;
	
	//sprite
	spriteSheetDim = { 4,2 };
	animationFPS = 15.0f;
	
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("Spider"), spriteSheetDim.x, spriteSheetDim.y, animationFPS);
	MainSprite.SetAnimation(0, 7);
	
	origin = { MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f };
	MainSprite.setOrigin(origin);

	scale = { 2,2 };
	MainSprite.setScale(scale);


	//set the position
	startingPos = { -8,400 };
	pos = {-8,400 }; //tempp=================================================================
	MainSprite.setPosition(pos);

	//first direction
	direction = (sf::Vector2f*)DownRight;


	//collision
	bitmap = &ResourceManager::GetTextureBitmap("Spider");
	SetCollider(MainSprite, *bitmap);
	RegisterCollision<Spider>(*this);
	
	arrayIt = 7;
}

void Spider::Update()
{
	MainSprite.Update();
	if (arrayIt < 0)
	{
		arrayIt = 7;
		RandomMovement();
	}
	Movement();

}

void Spider::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}


void Spider::Movement()
{
	pos += direction[arrayIt];
	MainSprite.setPosition(pos);
	arrayIt--;
	
}

void Spider::RandomMovement()
{
	if (pos.y < minYstart)
	{
		randomNum = rand() % 2;
		if (randomNum == 0)
		{
			direction = (sf::Vector2f*)Down;
		}
		else
		{
			direction = (sf::Vector2f*) DownRight;
		}

	}
	else if (pos.y + spriteSize / 2 > maxYstart)
	{
		direction = (sf::Vector2f*) UpRight;
	}
}


void Spider::Collision(Mushroom *other)
{
	
}

void Spider::Collision(Blaster *other)
{
	//kill the player
}

void Spider::Collision(Bullet *other)
{
	MarkForDestroy();
}

void Spider::Initialize()
{
	pos = startingPos;
	MainSprite.setPosition(pos);
	RegisterCollision<Spider>(*this);
}

void Spider::Destroy()
{
	DeregisterCollision<Spider>(*this);
	ExplosionFactory::CreateExplosion(pos); //explosion----
}

