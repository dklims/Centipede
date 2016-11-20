//ScorpionFactory.cpp
//David Klimavich, November 2016

#include "ScorpionFactory.h"

std::stack<Scorpion*> ScorpionFactory::recycledItems;
ScorpionFactory *ScorpionFactory::instance = nullptr;
ScorpionFactory::ScorpionFactory()
{

}

Scorpion * ScorpionFactory::CreateScorpion()
{
	return GetInstance().PrivateCreateScorpion();
}
Scorpion * ScorpionFactory::PrivateCreateScorpion()
{
	Scorpion* scorpion;
	if (recycledItems.empty())
	{

		ConsoleMsg::WriteLine("New Scorpion"); // For illustration purposes
		scorpion = new Scorpion();
		scorpion->SetExternalManagement(RecycleScorpion);
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled Scorpion"); // For illustration purposes
		scorpion = recycledItems.top();
		recycledItems.pop();
		scorpion->RegisterToCurrentScene();
	}

	scorpion->Initialize();
	return scorpion;
}

void ScorpionFactory::RecycleScorpion(GameObject *Scorpion)
{
	GetInstance().PrivateRecycleScorpion(Scorpion);
}

void ScorpionFactory::PrivateRecycleScorpion(GameObject *scorpion)
{
	recycledItems.push((Scorpion*)scorpion);
	ConsoleMsg::WriteLine("Recycled Scorpion Stack Size: " + Tools::ToString(recycledItems.size()));
}

void ScorpionFactory::Terminate()
{
	delete(instance);
	instance = nullptr;
}

ScorpionFactory::~ScorpionFactory()
{
	ConsoleMsg::WriteLine("Scorpion Stack Size Before Deletion: " + Tools::ToString(recycledItems.size()));
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
	ConsoleMsg::WriteLine("Deleteing recycled Scorpions");
}