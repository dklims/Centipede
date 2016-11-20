#ifndef _CritterBase
#define _CritterBase

#include "Game Components\TEAL\CommonElements.h"
#include "MushroomGrid.h"
#include "ScoreManager.h"
//#include "WaveManager.h"

class CritterBase : public GameObject
{
public:
	
	void ResetFrameCount();

protected:

	AnimatedSprite MainSprite;
	CollisionTools::TextureBitmap *bitmap;
	sf::Vector2i spriteSheetDim;
	sf::Vector2f scale;
	sf::Vector2f origin;
	sf::Vector2f pos;
	sf::Vector2i animationRange;
	float animationFPS;
	int speed;
	int frameCounter;
	const int spriteSize = 16; 
	MushroomGrid *gridHandle;

	//for flee and mushroom
	float health; 
};


#endif _CritterBase
