//Scorpion.cpp
//David Klimavich, November 2016

#include "Scorpion.h"


Scorpion::Scorpion()
{
	//Position
	speed = 2;
	windowSizeX = (WindowManager::MainWindow.getView().getSize().x);
	leftScreenSide = 0;
	rightScreenSide = windowSizeX;
	

	//Sprite
	spriteSheetDim = { 4,1 };
	animationFPS = 15.0f;
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("Scorpion"), spriteSheetDim.x, spriteSheetDim.y, animationFPS);
	MainSprite.SetAnimation(0, 3);
	origin = {MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f};
	MainSprite.setOrigin(origin);
	MainSprite.setScale(1, 1);


	//Collision
	bitmap = &ResourceManager::GetTextureBitmap("Scorpion");
	SetCollider(MainSprite, *bitmap);

	/*
	//Sound
	ScorpionStep.setBuffer(ResourceManager::GetSound("ScorpionSound"));
	ScorpionStep.setPitch(2);
	ScorpionStep.setVolume(25);
	ScorpionStep.setLoop(true);
	ScorpionStep.play();
	*/

	
}

void Scorpion::Update()
{
	MainSprite.Update();
	pos.x += speed;
	if (frameCounter < 0)
	{
		ResetFrameCount();

		if (pos.x > windowSizeX || pos.x < 0)
		{
			MarkForDestroy();
		}
		else if (gridHandle->gridSpaceEmpty(pos, { 0, 0}) == false)
		{
			mushroom = gridHandle->returnMushroom({pos.x, pos.y});
			mushroom->setPoison();
		}
	
	}

	MainSprite.setPosition(pos);

	frameCounter--;
}

void Scorpion::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}

void Scorpion::Destroy()
{
	DeregisterCollision<Scorpion>(*this);
	//ScorpionStep.stop();
}

void Scorpion::Collision(Bullet *other) //Collide with bullet
{
	ExplosionFactory::CreateExplosion(pos); //explosion----
	ScoreManager::AddScorpionPoints();
	MarkForDestroy();
}

void Scorpion::Initialize()
{
	gridHandle = MushroomGrid::GetPtrInstance();
	int minSpawnHeight = WaveManager::GetScorpionSpawnTop();
	int maxSpawnHeight = WaveManager::GetScorpionSpawnBottom();
	int randNum = spriteSize * (rand() % (maxSpawnHeight - minSpawnHeight) + minSpawnHeight) + spriteSize/2;

	int randomSide = rand() % 2;

	if (randomSide == 0)
	{
		direction = 1; //moving left to right
		screenSide = leftScreenSide;
	}
	else
	{
		direction = -1;
		screenSide = rightScreenSide;
	}

	speed = abs(speed) * direction;



	pos = { screenSide,float(randNum) };

	MainSprite.setPosition(pos);
	RegisterCollision<Scorpion>(*this);
	ResetFrameCount(); //reset the frame when recycled
}

