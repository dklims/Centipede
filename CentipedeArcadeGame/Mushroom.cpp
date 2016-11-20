//Mushroom.cpp
//David Klimavich 

#include "Mushroom.h"
#include "MushroomGrid.h"
#include "Bullet.h"

Mushroom::Mushroom()
{
	//mushroomField = MushroomGrid::GetInstance();

	//animation
	poisonAnimationStart = 8;
	animationFrameStart = 4;


	currentHealth = 4;
	scale = { 1,1 };
	
	spriteSheetDim = { 4,2 };
	animationFrameRange = { animationFrameStart - currentHealth, animationFrameStart - currentHealth };


	MainSprite = AnimatedSprite(ResourceManager::GetTexture("Mushroom"),spriteSheetDim.x, spriteSheetDim.y);
	MainSprite.SetAnimation(animationFrameRange.x, animationFrameRange.y);

	//set origin/scale
	origin = { MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f };
	MainSprite.setOrigin(origin.x, origin.y);
	MainSprite.setScale(scale.x, scale.y);
	
	//setting position based on mushroomgrid array




	//collision
	bitmap = ResourceManager::GetTextureBitmap("Mushroom");
	SetCollider(MainSprite, bitmap);


	//Input
	RegisterInput(InputFlags::KeyPressed);
}

void Mushroom::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}

void Mushroom::KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey)
{
	if (k == sf::Keyboard::K)
	{
		//MarkForDestroy();
		currentHealth -= 1;
	}
	else if (k == sf::Keyboard::P)
	{
		animationFrameRange.x += 4;
		animationFrameRange.y += 4;
		updateSprite();
	}
	
}



void Mushroom::Collision(GameObject * go)
{
	
}


void Mushroom::updateSprite()
{

	
	animationFrameRange = { animationFrameStart - currentHealth, animationFrameStart - currentHealth };
	MainSprite.SetAnimation(animationFrameRange.x, animationFrameRange.y);
	MainSprite.setPosition(Pos);
	MainSprite.Update();
}

void Mushroom::Initialize(sf::Vector2i gridLoc, sf::Vector2f onScreenGridLoc, MushroomGrid * mushroomGrid)
{
	currentHealth = 4;
//	MushroomGrid *test = mushroomGrid;
	mushroomField = mushroomGrid; // handle to the MushroomGrid to call public functions
	Pos = onScreenGridLoc;
	MainSprite.setPosition(Pos);
	localArrayLocation = gridLoc; //mushroom location in the grid
	RegisterCollision<Mushroom>(*this);
}

void Mushroom::Collision(Bullet * other)
{
	currentHealth -= 1;
	if (currentHealth <= 0)
	{
		MarkForDestroy(); //destroy when dead
		ScoreManager::AddMushroomPoints();
	}
	else
	{
		updateSprite();
	}
	
}

void Mushroom::Collision(Spider * other)
{
	MarkForDestroy();
}

void Mushroom::KillSelf()
{
	MarkForDestroy();
}

//set mushroom to poision
void Mushroom::setPoison()
{
	animationFrameStart = poisonAnimationStart;
	updateSprite();
}
void Mushroom::UnPoison()
{
	int startingFrame = 4; 
	animationFrameStart = startingFrame;
	updateSprite();
}

void Mushroom::RestoreHealth()
{
	currentHealth = 4;
	updateSprite();
}


void Mushroom::Destroy()
{
	mushroomField->MushroomDelete(localArrayLocation);
	DeregisterCollision<Mushroom>(*this);
	DeregisterInput();
}