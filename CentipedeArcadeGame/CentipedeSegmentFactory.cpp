//CentipedSegmentFactory.cpp
//David Klimavich, November 2016

#include "Game Components\TEAL\CommonElements.h"
#include "CentipedeSegmentFactory.h"


std::stack<CentipedeSegment*> CentipedeSegmentFactory::recycledItems;
std::stack<CentipedeSegment*> CentipedeSegmentFactory::onScreenItems;
CentipedeSegmentFactory *CentipedeSegmentFactory::instance = nullptr;

CentipedeSegmentFactory::CentipedeSegmentFactory()
{
	
}

CentipedeSegmentFactory::~CentipedeSegmentFactory()
{
}

CentipedeSegment * CentipedeSegmentFactory::CreateSegment(sf::Vector2f headPos, int segmentCount)
{
	return GetInstance().PrivateCreateSegment(headPos, segmentCount);
}

CentipedeSegment * CentipedeSegmentFactory::PrivateCreateSegment(sf::Vector2f headPos, int segmentCount)
{
	CentipedeSegment* centipedeSegment;
	if (recycledItems.empty())
	{
		ConsoleMsg::WriteLine("New Segment"); // For illustration purposes
		centipedeSegment = new CentipedeSegment();
		centipedeSegment->SetExternalManagement(RecycleSegment);
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled Segment"); // For illustration purposes
		centipedeSegment = recycledItems.top();
		recycledItems.pop();
		centipedeSegment->RegisterToCurrentScene();
	}

	centipedeSegment->Initialize(headPos, segmentCount);

	onScreenItems.push(centipedeSegment);

	return centipedeSegment;
}

void CentipedeSegmentFactory::RecycleSegment(GameObject *centipedeSegment)
{
	GetInstance().PrivateRecycleSegment(centipedeSegment);
	
}

void CentipedeSegmentFactory::PrivateRecycleSegment(GameObject *centipedeSegment)
{
	recycledItems.push((CentipedeSegment*)centipedeSegment);
	ConsoleMsg::WriteLine("Recycled segment Stack Size: " + Tools::ToString(recycledItems.size()));
}

void CentipedeSegmentFactory::DestroySegments()
{
	GetInstance().PrivateDestroySegments();
}

void CentipedeSegmentFactory::PrivateDestroySegments()
{
	while (!onScreenItems.empty())
	{
		onScreenItems.top()->MarkForDestroy();
		onScreenItems.pop();
	}
}


void CentipedeSegmentFactory::Terminate()
{
	delete instance;
	instance = nullptr;
}