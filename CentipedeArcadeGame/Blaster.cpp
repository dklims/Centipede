//Blaster.cpp
//David Klimavich, November 2016

#include "Blaster.h"
#include "Bullet.h"
#include "BulletFactory.h"
#include "Explosion.h"

//#include "GameController.h"
//#include "ShipExplosion.h"
//#include "Widget.h"
//#include "Asteroid.h"


Blaster::Blaster()
{
	offScreenPos = { -100,-100 };
	SPEED = 225; //double for double res
	HBORDER = 15;
	//TBORDER = 600;

	topPlayerWall = 400;
	bottomPlayerWall = 496;
	leftPlayerWall = 0;
	rightPlayerWall = 464;

	scale = {1, 1};
	origin = { MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f };
	animationFrameRange = { 0,0 };
	animationFrameStart = 1;
	animationFrameEnd = 1;
	BulletAlive = false;
	GunOffset = sf::Vector2f(0,0);

	//gettextures
	bitmap = ResourceManager::GetTextureBitmap("Blaster");
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("Blaster"), animationFrameStart, animationFrameEnd);
	MainSprite.SetAnimation(animationFrameRange.x, animationFrameRange.y);

	//set sprite, scale and pos
	MainSprite.setOrigin(origin.x,origin.y);
	MainSprite.setScale(scale.x, scale.y);
	MainSprite.setPosition(Pos);

	SetCollider(MainSprite, bitmap);
	RegisterCollision<Blaster>(*this);

	Pos = sf::Vector2f(WindowManager::MainWindow.getView().getSize().x / 2.0f, WindowManager::MainWindow.getView().getSize().y - 2.0f * MainSprite.getTextureRect().width);
	Impulse = sf::Vector2f(0, 0);
	friction = 0.f;

	//SetCollider(MainSprite, bitmap, true);
	//RegisterCollision<Ship>(*this);
	FireSnd.setBuffer(ResourceManager::GetSound("fire"));
	FireSnd.setPitch(2);
	FireSnd.setVolume(25);

	SetDrawOrder(1000); // place Blaster on top of everything

	RegisterInput(InputFlags::KeyPressed); // Recieve single-presses events
}

void Blaster ::Destroy()
{
	DeregisterInput();
	//DeregisterCollision<Ship>(*this);
}



void Blaster::Update()
{

	MainSprite.Update();
	prevPos = Pos;
	offset = SPEED * Game::FrameTime();
	// Continuous key-down tests
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))Impulse += sf::Vector2f(-offset, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))Impulse += sf::Vector2f(offset, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) Impulse += sf::Vector2f(0, -offset);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) Impulse += sf::Vector2f(0, offset);

	Pos += Impulse;

	//setting player boundaries.
	Tools::Clamp<float>(Pos.x, leftPlayerWall, rightPlayerWall); 
	Tools::Clamp<float>(Pos.y, topPlayerWall, bottomPlayerWall); 
	MainSprite.setPosition(Pos);
	

	Impulse *= friction;
}

void Blaster::KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey)
{

	if (k == sf::Keyboard::Space)
	{
		
		if (BulletAlive == false)
		{

			ConsoleMsg::WriteLine("Pew! Pew!");
			//instansiate new bullet
			Bullet *bullet;
			bullet = BulletFactory::CreateBullet(Pos, this);
			BulletAlive = true;

			FireSnd.play();
		}
	}
	
}

void Blaster::KillBullet()
{
	BulletAlive = false;
}


void Blaster::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}

void Blaster::Collision(Spider *other)
{
	PlayerDead();
}


void Blaster::Collision(CentipedeHead * other)
{
	PlayerDead();
}

void Blaster::Collision(CentipedeSegment * other)
{
	PlayerDead();
}



void Blaster::PlayerDead()
{
	ExplosionFactory::CreateExplosion(Pos);
	Pos = sf::Vector2f(WindowManager::MainWindow.getView().getSize().x / 2.0f, WindowManager::MainWindow.getView().getSize().y - 2.0f * MainSprite.getTextureRect().width);
	MainSprite.setPosition(Pos);
	Player::DecrementLives();
	WaveManager::RestartWave();

}

void Blaster::Collision(Mushroom *other)
{
	Pos = prevPos;
	MainSprite.setPosition(prevPos);
}

