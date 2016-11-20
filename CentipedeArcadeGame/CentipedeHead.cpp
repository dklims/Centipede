#include "CentipedeHead.h"
#include "MushroomGrid.h"
#include "CentipedeHeadFactory.h"
#include "CentipedeSegmentFactory.h"
#include "WaveManager.h"



CentipedeHead::CentipedeHead()
{
	//passed in variables
	gridHandle = MushroomGrid::GetPtrInstance();
	

	//Boundaries
	SetBoundaries();

	//animation info
	SetAnimationInfo();
	
	//set up variables for sprite, and the actual srite itself.
	SetSprite();

	//movement
	prevDirection = nullptr;
	direction = nullptr;

	
	
}

//======================================UPDATE===============================================//
void CentipedeHead::Update()
{
	MainSprite.Update(); //update sprite everyframe
	
	if (arrayIt < 0)
	{
		ResetVariables();
		DetermineNextDirection();
	}

	//apply movement according to direction
	movement(direction);
}	
//===========================================================================================//

void CentipedeHead::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}

void CentipedeHead::movement(sf::Vector2f* direction)
{
//	ConsoleMsg::WriteLine("Movemenet Direction = " + Tools::ToString(direction[arrayIt]));
	pos += direction[arrayIt];
	MainSprite.setPosition(pos);
	arrayIt--;
}

sf::Vector2f* CentipedeHead::ChangeDirection(sf::Vector2f* direction)
{
	if (direction == right)
	{
//		ConsoleMsg::WriteLine("rotation = " + Tools::ToString(faceLeft));
		rotation = faceLeft;
		//MainSprite.setRotation(faceLeft);
		return (sf::Vector2f*)left;
	}
	else if (direction == left)
	{
//		ConsoleMsg::WriteLine("rotation = " + Tools::ToString(faceRight));
		rotation = faceRight;
		//MainSprite.setRotation(faceRight);
		return (sf::Vector2f*)right;
	}
}

void CentipedeHead::turnDown()
{
	nextDirection = ChangeDirection(direction); //calculate the next direction after down turn
	offset = -offset;
	direction = (sf::Vector2f*)down; //centipede go down
	MainSprite.setRotation(faceDown); //rotate down

} //for what?

void CentipedeHead::createSegment()
{
	//centipedeUnits = 3;
	if (centipedeUnits > 0)
	{
		centipedeUnits--;
		CentipedeSegment *centipedeSegment;
		centipedeSegment = CentipedeSegmentFactory::CreateSegment(pos, centipedeUnits);
		next = centipedeSegment;
		next->prev = this;
	
	}
}

void CentipedeHead::Collision(Bullet * other)
{
	ExplosionFactory::CreateExplosion(pos);

 	if (next != nullptr)
	{
		CreateHead();
	}
	else
	{
		WaveManager::DecrementCentipedeHead();
	}
	PlaceMushroom(direction, gridHandle);
		
	//END MUSHROOM PLACEMENT

	ScoreManager::AddCentipedeHeadPoints();
	

	MarkForDestroy();
}


void CentipedeHead::Collision(GameObject *go)
{
	
}

void CentipedeHead::CreateHead()
{
	
	CentipedeHead *centipedeHead;
	centipedeHead = CentipedeHeadFactory::CreateCentipedeHead(false, next->getCurrentDirection(), arrayIt, next->getPosition());
	
	if (next->next != nullptr)
	{
		centipedeHead->next = next->next;
		next->next->prev = centipedeHead;
	}
	next->MarkForDestroy();
	

//	ConsoleMsg::WriteLine("NEW CENTIPEDE HEAD POS = " + Tools::ToString(centipedeHead->pos));
	MarkForDestroy();
}

void CentipedeHead::ResetVariables()
{
	MainSprite.setRotation(rotation);
	prevDirection = direction; // direction pulled by segment (this->next).
	arrayIt = 7;
}

void CentipedeHead::DetermineNextDirection()
{
	if (direction == (sf::Vector2f*)right || direction == (sf::Vector2f*)left)
	{
		//if next space is out of bounds or occupied by a mushroom
		if (gridHandle->gridSpaceEmpty(pos, offset) == false || pos.x - 8 < leftWall || pos.x + 8 > rightWall)
		{
			turnDown(); //for what?
		}
	}
	//if cant go opposite direction then before going down, go down again. 

	else if (gridHandle->gridSpaceEmpty(pos, offset) == false)
	{
		direction = (sf::Vector2f*)down;
	}
	else
	{
		direction = nextDirection;
	}
}

void CentipedeHead::SetSprite()
{
	//gettextures-------------------------------------------------------------------------

	MainSprite = AnimatedSprite(ResourceManager::GetTexture("Centipede"), spriteSheetDim.x, spriteSheetDim.y, animationFPS);
	MainSprite.SetAnimation(animationFrameRange.x, animationFrameRange.y);

	//collision
	bitmap = ResourceManager::GetTextureBitmap("Centipede");
	RegisterCollision<CentipedeHead>(*this);
	SetCollider(MainSprite, bitmap);


	//set scale
	scale = { 2,2 };
	MainSprite.setScale(scale);

	//set origin
	origin = { float(MainSprite.getTextureRect().width / 2.0f), float(MainSprite.getTextureRect().height) / 2.0f };
	//origin = { 4,4 };
	MainSprite.setOrigin(origin);

	//set pos
	
	//gridHandle->GridLocationToOnScreenLocation({ 15, -1 });

	//set rotation
	MainSprite.setRotation(faceDown);

}

void CentipedeHead::SetBoundaries()
{
	boundaries = { WindowManager::MainWindow.getView().getSize().x, WindowManager::MainWindow.getView().getSize().y };
	leftWall = 8;
	rightWall = int(boundaries.x - 8);
	ceiling = 8;
	floor = int(boundaries.y + 8);
}

void CentipedeHead::SetAnimationInfo()
{
	spriteSheetDim = { 8,2 };
	animationFrameRange = { 0, 7 };
	animationFPS = 15.0f;
	rotation = faceLeft;
}

void CentipedeHead::FirstHeadVariables()
{
	//WaveManager::GetInstance();
	WaveManager::IncrementCentipedeHead(); //head count for wave manager
	nextDirection = (sf::Vector2f*)left; //next direction to go
	centipedeUnits = WaveManager::GetCentipedeLength();
	offset = { -1,0 }; //current direction
}

void CentipedeHead::NewHeadVariables()
{
	centipedeUnits = 0;
	nextDirection = ChangeDirection(direction);
	if (direction == (sf::Vector2f*)left)
	{
		offset = { 1,0 };
	}
	else
	{
		offset = { +1,0 };
	}
}

void CentipedeHead::Initialize(bool firstHeadPassed, sf::Vector2f *passedInDirection, int passedInArrayIt, sf::Vector2f startingPos)
{
	
	arrayIt = passedInArrayIt;
	gridHandle = MushroomGrid::GetPtrInstance();
	pos = startingPos;
	MainSprite.setPosition(pos);
	firstHead = firstHeadPassed;
	direction = (sf::Vector2f*)down;//passedInDirection;
	prevDirection = (sf::Vector2f*)right;
	RegisterCollision<CentipedeHead>(*this);



	if (firstHead == false)
	{
		NewHeadVariables(); //created from the collision event of this class
	}
	else
	{
		FirstHeadVariables(); //created from the critter manager
		createSegment();
	}
}

void CentipedeHead::Destroy()
{
	next = nullptr;
	DeregisterCollision<CentipedeHead>(*this);
	

}