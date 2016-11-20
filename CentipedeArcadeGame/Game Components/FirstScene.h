// FirstScene
// Andre Berthiaume, March 2013

#ifndef _FirstScene
#define _FirstScene

#include "TEAL\CommonElements.h"
//Blaster
#include "../Blaster.h"
#include "../Bullet.h"
//Mushrooms
#include "../MushroomGrid.h"
#include "../Mushroom.h"
//Centipedes
#include "../CentipedeHead.h"
#include "../CentipedeSegment.h"
//Critters
#include "../CritterManager.h"
#include "../Scorpion.h"
#include "../Flea.h"
#include "../Spider.h"
//=======================
#include "KeyEventTest.h"
#include "../ScoreManager.h"
#include "../HUD.h"

//wave manager
#include "../WaveManager.h"

//terminates
#include "../BulletFactory.h"
#include "../FleaFactory.h"
#include "../ScorpionFactory.h"
#include "../CentipedeSegmentFactory.h"
#include "../CentipedeHeadFactory.h"
#include "../SpiderFactory.h"

class FirstScene : public Scene
{
public:
	virtual void Initialize();
	virtual void Terminate();
};

#endif _FirstScene