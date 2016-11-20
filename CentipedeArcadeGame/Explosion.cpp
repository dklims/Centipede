//Explosion.cpp
//David Klimavich, November 2016

#include "Explosion.h"

Explosion::Explosion()
{
	spriteSheetDim = { 8,2 };
	animationFPS = 60.0f;

	MainSprite = AnimatedSprite(ResourceManager::GetTexture("Explosion"),
		spriteSheetDim.x, spriteSheetDim.y, animationFPS);
	
	origin = { MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f };
	MainSprite.setOrigin(origin);

	scale = { 1,1 };
	MainSprite.setScale(scale);

	

	SetDrawOrder(1001); 

	//Initialize({200,200});
}

void Explosion::Initialize(sf::Vector2f p)
{
	pos = p;
	MainSprite.setPosition(pos);
	frameCounter = spriteSheetDim.x * spriteSheetDim.y;
	MainSprite.SetAnimation(0, (spriteSheetDim.x * spriteSheetDim.y));
}

void Explosion::Update()
{
	MainSprite.Update();
	if (frameCounter <= 0)
	{
		MarkForDestroy();
	}
	frameCounter--;
}

void Explosion::Draw()
{
	WindowManager::MainWindow.draw(MainSprite); 
}

void Explosion::Destroy()
{
	//stuff
}