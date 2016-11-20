//Flea.cpp
//David Klimavich, November 2016

#include "Flea.h"
#include "Game Components\TEAL\CommonElements.h"

Flea::Flea()
{
//=============================================================================================
	bottomOfScreen = float(WindowManager::MainWindow.getView().getSize().y);

	//gridHandle
	//gridHandle = mushroomGrid; ->in initialize

	//Sprite animation Info
	spriteSheetDim = { 2,2 };
	animationFPS = 15;
	

	//Sprite creation
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("Flea"), 
		spriteSheetDim.x, spriteSheetDim.y, animationFPS);

	//Animation frame range set
	animationRange = { 0,3 };
	MainSprite.SetAnimation(animationRange.x, animationRange.y);
	
	//Scale set
	scale = { 1,1 };
	MainSprite.setScale(scale);

	//Origin set
	origin = { float(MainSprite.getTextureRect().width / 2.0f), float(MainSprite.getTextureRect().height) / 2.0f };
	MainSprite.setOrigin(origin);
	
	

	//set FrameCounter
	ResetFrameCount();

	//set Mushroom chance to spawn
	mushroomFreq = 5;

	//Collision
	bitmap = &ResourceManager::GetTextureBitmap("Flea");
	SetCollider(MainSprite, *bitmap);



	//points
	points = 200;

//=============================================================================================


}


void Flea::Update()
{
	if (frameCounter < 0)
	{
		if (pos.y + spriteSize > bottomOfScreen)
		{
			MarkForDestroy();
		}
		ResetFrameCount();

		randNum = rand() % mushroomFreq;
		if (randNum == 0 && pos.y > 16 && pos.y < bottomOfScreen - 16)
		{
			gridHandle->placeMushroom(pos);
		}
	}

	Move();
	
	frameCounter--;
}

void Flea::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}

void Flea::Destroy()
{
	ConsoleMsg::WriteLine("DESTROYED");
	DeregisterCollision<Flea>(*this);
}

void Flea::Move()
{
	pos.y += speed;
	MainSprite.setPosition(pos);
	MainSprite.Update();
}

void Flea::Collision(GameObject * go)
{
}

void Flea::Collision(Bullet * other)
{
	health--;
	if (health <= 0)
	{
		ScoreManager::AddScorpionPoints();
		ExplosionFactory::CreateExplosion(pos); //explosion----
		MarkForDestroy();
	}

	speed *= 2;
}

void Flea::Initialize()
{
	gridHandle = MushroomGrid::GetPtrInstance();

	//Set pos
	randNum = rand() % int(WindowManager::MainWindow.getView().getSize().x) / spriteSize; // picks a random number between 0 and the screen width
	randNum *= spriteSize;
	randNum += spriteSize / 2;
	pos = { float(randNum),-8 };
	MainSprite.setPosition(pos);

	//Set Speed (pixles to move per frame (*4)
	speed = 1;
	speed *= 1;

	//set Health
	health = 2;

	//collision
	RegisterCollision<Flea>(*this);

	//set frameCounter to default
	ResetFrameCount();
}
