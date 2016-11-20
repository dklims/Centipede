//SpiderFactory.h
//David Klimavich, November 2016

#ifndef _SpiderFactory
#define _SpiderFactory

#include "Spider.h"
#include <stack>


class SpiderFactory
{
public:
	static std::stack<Spider*> recycledItems;

	SpiderFactory();
	~SpiderFactory();

	static Spider * CreateSpider();
	static void RecycleSpider(GameObject *go);
	static void Terminate();

private:
	static Spider * PrivateCreateSpider();
	static void PrivateRecycleSpider(GameObject *go);

	//singleton Function
	static SpiderFactory* instance;

	static SpiderFactory& GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new SpiderFactory();
		}
		return *instance;
	}

};
#endif _SpiderFactory
