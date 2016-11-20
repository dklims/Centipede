#include "SpiderFactory.h"


std::stack<Spider*> SpiderFactory::recycledItems;
SpiderFactory *SpiderFactory::instance = nullptr;
SpiderFactory::SpiderFactory()
{

}

Spider * SpiderFactory::CreateSpider()
{
	return GetInstance().PrivateCreateSpider();
}
Spider * SpiderFactory::PrivateCreateSpider()
{
	Spider* spider;
	if (recycledItems.empty())
	{

		ConsoleMsg::WriteLine("New Spider"); // For illustration purposes
		spider = new Spider();
		spider->SetExternalManagement(RecycleSpider);
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled Spider"); // For illustration purposes
		spider = recycledItems.top();
		recycledItems.pop();
		spider->RegisterToCurrentScene();
	}

	spider->Initialize();
	return spider;
}

void SpiderFactory::RecycleSpider(GameObject *Spider)
{
	GetInstance().PrivateRecycleSpider(Spider);
}

void SpiderFactory::PrivateRecycleSpider(GameObject *spider)
{
	recycledItems.push((Spider*)spider);
	ConsoleMsg::WriteLine("Recycled Spider Stack Size: " + Tools::ToString(recycledItems.size()));
}

void SpiderFactory::Terminate()
{
	delete(instance);
	instance = nullptr;
}

SpiderFactory::~SpiderFactory()
{
	ConsoleMsg::WriteLine("Spider Stack Size Before Deletion: " + Tools::ToString(recycledItems.size()));
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
	ConsoleMsg::WriteLine("Deleteing recycled Spiders");
}