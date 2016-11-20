//Bullet.h
//David Klimavich, November 2016

#include "Bullet.h"
#include "Blaster.h"
#include "Mushroom.h"


Bullet::Bullet()
{	
	animationFrameStart = 1;
	animationFrameEnd = 1;
	animationFrameRange = { 0,0 };
	scale = { 1,1 };
	origin = { MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f };
	SPEED = 800; 

	
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("Bullet"), animationFrameStart, animationFrameEnd);
	MainSprite.SetAnimation(animationFrameRange.x, animationFrameRange.y);
	MainSprite.setOrigin(origin.x, origin.y);

	MainSprite.setScale(scale.x, scale.y);

	//collision
	bitmap = ResourceManager::GetTextureBitmap("Bullet");
	SetCollider(MainSprite, bitmap);
	
	
}



void Bullet::Update()
{
	MainSprite.Update();

	Pos.y += Game::FrameTime() * -SPEED;

	if (Pos.x > WindowManager::MainWindow.getSize().x) MarkForDestroy();

	MainSprite.setPosition(Pos);

	if (Pos.y < 0)
	{
		player->KillBullet();
		MarkForDestroy();
		
	}
}

void Bullet::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}

void Bullet::Destroy()
{
	
	DeregisterCollision<Bullet>(*this);
	
}




void Bullet::Collision(Mushroom *other)
{
	player->KillBullet();
	MarkForDestroy();
}
 
void Bullet::Collision(Scorpion *other) //Destroy bullet on collision with Scorpion
{
	player->KillBullet();
	MarkForDestroy();
}

void Bullet::Collision(Spider *other)
{
	player->KillBullet();
	MarkForDestroy();
}

void Bullet::Collision(CentipedeHead *other)
{
	player->KillBullet();
	MarkForDestroy();
}

void Bullet::Collision(CentipedeSegment *other)
{
	player->KillBullet();
	MarkForDestroy();
}

void Bullet::Initialize(sf::Vector2f p, Blaster * blaster)
{
	player = blaster;
	Pos = p;
	MainSprite.setPosition(Pos);

	RegisterCollision<Bullet>(*this);
}
