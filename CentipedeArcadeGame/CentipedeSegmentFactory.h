#ifndef _CentipedeSegmentFactory
#define _CentipedeSegmentFactory

#include <stack>
#include "CentipedeSegment.h"




class CentipedeSegmentFactory
{


public:


	CentipedeSegmentFactory();
	CentipedeSegmentFactory(const CentipedeSegmentFactory&) = delete;
	CentipedeSegmentFactory& operator=(const CentipedeSegmentFactory&) = delete;
	~CentipedeSegmentFactory();

	static CentipedeSegment* CreateSegment(sf::Vector2f headPos, int segmentCount);
	static void RecycleSegment(GameObject *go);
	static void DestroySegments();
	static void Terminate();
	
	

private:
	//singleton Function
	static CentipedeSegmentFactory* instance;

	static CentipedeSegmentFactory& GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new CentipedeSegmentFactory();
		}
		return *instance;
	}


	static std::stack<CentipedeSegment*> recycledItems;
	static std::stack<CentipedeSegment*> onScreenItems;
	int CS_Count; //centipede segment count

	CentipedeSegment* PrivateCreateSegment(sf::Vector2f headpos, int segmentCount);
	void PrivateRecycleSegment(GameObject *go);
	void PrivateDestroySegments();


	

};


#endif _CentipedeSegmentFactory
