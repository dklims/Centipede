// LoadAllResources.cpp
// Andre Berthiaume, June 2012
//
// The user fills the method with all resources that need loading

#include "ResourceManager.h"
#include "../FirstScene.h"

void ResourceManager::LoadAllResources()
{
	SetStartScene( new FirstScene() );

	//Fonts
	AddTexture("AwesomeFont", "../Game Components/Sprites/FONT.bmp");
	AddFont("MyDefaultFont", "../Game Components/TEAL/Arial.ttf");
	//TEXTURES

		//CRITTERS
	AddTexture("Spider", "../Game Components/Sprites/spider.png");
	AddTexture("Scorpion", "../Game Components/Sprites/scorpion.png");
	AddTexture("Flea", "../Game Components/Sprites/flea.png");

		//Centipede
	AddTexture("Centipede", "../Game Components/Sprites/Centipede_head.png");
	AddTexture("CentipedeSegment", "../Game Components/Sprites/centipede_segment.png");

	AddTexture("Bullet", "../Game Components/Sprites/bullet.png");
	AddTexture("Blaster", "../Game Components/Sprites/blaster.png");

	AddTexture("Mushroom", "../Game Components/Sprites/mushroom.png");

		//Explosion
	AddTexture("Explosion", "../Game Components/Sprites/death.png");





	//SOUNDS
	AddSound("fire", "../Game Components/Sounds/fire1.wav");
	//AddSound("ScorpionStep", "../Game Components/Sounds/scorpion_new.wav");



}

