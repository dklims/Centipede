#include "CentipedeSegment.h"
#include "CentipedeBase.h"
#include "CentipedeSegmentFactory.h"
#include "CentipedeHeadFactory.h"

CentipedeSegment::CentipedeSegment()
{
	spriteSheetDim = { 8,2 };
	animationFrameRange = { 0, 7 };
	animationFPS = 15.0f;
	rotation = 0;
	scale = { 2,2 };

	

	//getTextures
	bitmap = ResourceManager::GetTextureBitmap("CentipedeSegment");
	SetCollider(MainSprite, bitmap);
 	MainSprite = AnimatedSprite(ResourceManager::GetTexture("CentipedeSegment"), spriteSheetDim.x, spriteSheetDim.y, animationFPS);
	MainSprite.SetAnimation(animationFrameRange.x, animationFrameRange.y);
	

	//Get Directions from Head
//	ConsoleMsg::WriteLine("Into Centipede Segment");
//	ConsoleMsg::WriteLine("directions copied");


	//set sprite
	MainSprite.setScale(scale);

	//origin
	origin = { MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f };
	MainSprite.setOrigin(origin);
	

	//RegisterCollision<CentipedeSegment>(*this);
}

void CentipedeSegment::Update()
{
	MainSprite.Update();

	if (arrayIt < 0)
	{ 
		prevDirection = direction;
		direction = prev->getOrders();
		arrayIt = 7;
	}
	

  	//ConsoleMsg::WriteLine("Segment DIRECTION[" + Tools::ToString(arrayIt) + "] = " + Tools::ToString(direction[arrayIt]));
	movement(direction);

	
}

void CentipedeSegment::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}

void CentipedeSegment::Initialize(sf::Vector2f headPos, int segmentCount)
{
	gridHandle = MushroomGrid::GetPtrInstance(); 
	pos = headPos;
	MainSprite.setPosition(pos);
	currentSegmentCount = segmentCount;
	createSegment(currentSegmentCount);
	arrayIt = 8;

	direction = (sf::Vector2f*)noSpeed;
	prevDirection = direction;
	RegisterCollision<CentipedeSegment>(*this);
}

void CentipedeSegment::movement(sf::Vector2f* direction)
{
	//ConsoleMsg::WriteLine("directions = " + Tools::ToString(directions[arrayIt]));
	
	pos += direction[arrayIt];
	MainSprite.setPosition(pos);
	arrayIt--;

}

void CentipedeSegment::createSegment(int segmentCount)
{
//	ConsoleMsg::WriteLine("segmentCount = " + Tools::ToString(segmentCount));
	if (segmentCount > 0)
	{
		segmentCount--;
		CentipedeSegment *centipedeSegment;
		centipedeSegment = CentipedeSegmentFactory::CreateSegment(pos, segmentCount);
		next = centipedeSegment;
		next->prev = this;
	
		//ConsoleMsg::WriteLine(Tools::ToString(segmentCount));
	}
}

void CentipedeSegment::destroySegment()
{
	MarkForDestroy();
}



void CentipedeSegment::Collision(Bullet *other)
{

	ExplosionFactory::CreateExplosion(pos); //explosion----
	if (prev != nullptr)
	{
		prev->next = nullptr;
	}
   	
	
	if (next != nullptr)
	{
		WaveManager::IncrementCentipedeHead(); //head count for wave manager
		CentipedeHead *centipedeHead = CreateHead();

		if (next->next != nullptr)
		{
			centipedeHead->next = next->next;
			next->next->prev = centipedeHead;
		}
		next->MarkForDestroy();
		
	}
	PlaceMushroom(direction, gridHandle);

	MarkForDestroy();
}

CentipedeHead* CentipedeSegment::CreateHead()
{
	CentipedeHead *centipedeHead;
	centipedeHead = CentipedeHeadFactory::CreateCentipedeHead(false, next->getCurrentDirection(), arrayIt, next->getPosition());
	return centipedeHead;
}

void CentipedeSegment::Destroy()
{
	DeregisterCollision<CentipedeSegment>(*this); 
	next = nullptr;
	prev = nullptr;

	
}
