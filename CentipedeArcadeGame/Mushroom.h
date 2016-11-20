//Mushroom.h
//David Klimavich, November 2016
#ifndef _Mushroom
#define _Mushroom

#include "MushroomGrid.h"
#include "Game Components\TEAL\CommonElements.h"
#include "ScoreManager.h"

class Spider;
class Bullet;

class Mushroom : public GameObject
{
public:
	Mushroom();
	//virtual void Update(); 
	virtual void Draw();
	virtual void Destroy();
	virtual void KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey);
	
	virtual void Collision(GameObject *go);
	virtual void Collision(Bullet *other);
	virtual void Collision(Spider *other);

	void KillSelf();
	void setPoison();
	void UnPoison();
	void RestoreHealth();
	void updateSprite();

	void Initialize(sf::Vector2i gridLoc, sf::Vector2f onScreenGridLoc, MushroomGrid *mushroomGrid);


private:

	MushroomGrid *mushroomField;

	sf::Vector2f scale;
	sf::Vector2f origin;
	sf::Vector2i animationFrameRange;
	AnimatedSprite MainSprite;
	sf::Vector2f Pos;
	sf::Vector2i localArrayLocation;
	sf::Vector2i spriteSheetDim;

	//collisions

	CollisionTools::TextureBitmap bitmap;

	int animationFrameStart;
	int animationFrameEnd;
	int poisonAnimationStart;




	int currentHealth;
	int maxHealth;

	//point value
	int points;
	

};
#endif _Mushroom