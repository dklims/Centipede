#ifndef _ScorpionFactory
#define _ScorpionFactory

#include "Scorpion.h"
#include <stack>
#include "MushroomGrid.h"

class ScorpionFactory
{
public:
	static std::stack<Scorpion*> recycledItems;

	ScorpionFactory();
	~ScorpionFactory();

	static Scorpion * CreateScorpion();
	static void RecycleScorpion(GameObject *go);
	static void Terminate();

private:
	static Scorpion * PrivateCreateScorpion();
	static void PrivateRecycleScorpion(GameObject *go);

	//singleton Function
	static ScorpionFactory* instance;

	static ScorpionFactory& GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new ScorpionFactory();
		}
		return *instance;
	}

};
#endif // !_ScorpionFactory
