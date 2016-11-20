#include "FleaFactory.h"

std::stack<Flea*> FleaFactory::recycledItems;
FleaFactory *FleaFactory::instance = nullptr;
FleaFactory::FleaFactory()
{

}

Flea * FleaFactory::CreateFlea()
{
	return GetInstance().PrivateCreateFlea();
}
Flea * FleaFactory::PrivateCreateFlea()
{
	Flea* flea;
	if (recycledItems.empty())
	{

		ConsoleMsg::WriteLine("New Flea"); // For illustration purposes
		flea = new Flea();
		flea->SetExternalManagement(RecycleFlea);
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled Flea"); // For illustration purposes
		flea = recycledItems.top();
		recycledItems.pop();
		flea->RegisterToCurrentScene();
	}

	flea->Initialize();
	return flea;
}

void FleaFactory::RecycleFlea(GameObject *flea)
{
	GetInstance().PrivateRecycleFlea(flea);
}

void FleaFactory::PrivateRecycleFlea(GameObject *flea)
{
	recycledItems.push((Flea*)flea);
	ConsoleMsg::WriteLine("Recycled Flea Stack Size: " + Tools::ToString(recycledItems.size()));
}

void FleaFactory::Terminate()
{
	delete(instance);
	instance = nullptr;
}

FleaFactory::~FleaFactory()
{
	ConsoleMsg::WriteLine("Flea Stack Size Before Deletion: " + Tools::ToString(recycledItems.size()));
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
	ConsoleMsg::WriteLine("Deleteing recycled Fleas");
}