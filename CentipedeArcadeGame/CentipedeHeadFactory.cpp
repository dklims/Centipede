//CentipedeHeadFactory.cpp
//David Klimavich, November 2016

#include "Game Components\TEAL\CommonElements.h"
#include "CentipedeHeadFactory.h"
#include "CentipedeSegmentFactory.h"
#include "WaveManager.h"

std::stack<CentipedeHead*> CentipedeHeadFactory::recycledItems;
std::stack<CentipedeHead*> CentipedeHeadFactory::onScreenItems;
CentipedeHeadFactory *CentipedeHeadFactory::instance = nullptr;

CentipedeHeadFactory::CentipedeHeadFactory()
{
	
}

CentipedeHead* CentipedeHeadFactory::CreateCentipedeHead(bool firstHeadPassed, sf::Vector2f *passedInDirection, int passedInArrayIt, sf::Vector2f startingPos)
{
	return GetInstance().PrivateCreateCentipedeHead(firstHeadPassed, passedInDirection, 
		passedInArrayIt, startingPos);
}

CentipedeHead* CentipedeHeadFactory::PrivateCreateCentipedeHead(bool firstHeadPassed, sf::Vector2f *passedInDirection, int passedInArrayIt, sf::Vector2f startingPos)
{
	//CH_Count++;
	CentipedeHead* centipedeHead;

	if (recycledItems.empty())
	{
		ConsoleMsg::WriteLine("New CentipedeHead"); // For illustration purposes

		centipedeHead = new CentipedeHead();
		

		// Declares that this object should be returned here (rather than deleted) when destroyed
		centipedeHead->SetExternalManagement(RecycleCentipedeHead);
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled CentipedeHead"); // For illustration purposes
		centipedeHead = recycledItems.top();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

								// Tell the object to register itself to the scene
		centipedeHead->RegisterToCurrentScene();
	}

	centipedeHead->Initialize(firstHeadPassed, passedInDirection, passedInArrayIt, startingPos);
	onScreenItems.push(centipedeHead);
	

	//counter++;

	ConsoleMsg::WriteLine("CH_COUNT: " + Tools::ToString(CH_Count));

	return centipedeHead;



}

void CentipedeHeadFactory::RecycleCentipedeHead(GameObject * centipedeHead)
{
	GetInstance().PrivateRecycleCentipedeHead(centipedeHead);

}



void CentipedeHeadFactory::PrivateRecycleCentipedeHead(GameObject * centipedeHead)
{
	recycledItems.push((CentipedeHead*)centipedeHead);
	//CH_Count--;

	// For illustration purposes
	ConsoleMsg::WriteLine("Recycled Head Stack Size: " + Tools::ToString(recycledItems.size()));
}


int CentipedeHeadFactory::GetCount()
{
	return GetInstance().PrivateGetCount();
}

int CentipedeHeadFactory::PrivateGetCount()
{
	return CH_Count;
}


void CentipedeHeadFactory::DestoryHeads()
{
	GetInstance().PrivateDestoryHeads();
}

void CentipedeHeadFactory::PrivateDestoryHeads()
{
	while (!onScreenItems.empty())
	{
		onScreenItems.top()->MarkForDestroy();
		onScreenItems.pop();
	}
}




void CentipedeHeadFactory::Terminate()
{
	delete instance;
	instance = nullptr;
}

CentipedeHeadFactory::~CentipedeHeadFactory()
{
	// forcefully delele all recycled gameobjects
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
}