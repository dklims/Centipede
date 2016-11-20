#ifndef _Explosion
#define _Explosion

#include "Game Components\TEAL\CommonElements.h"

class Explosion : public GameObject
{
public:
	Explosion();
	void Initialize(sf::Vector2f p);

	virtual void Draw();
	virtual void Update();
	virtual void Destroy(); 

private:
	AnimatedSprite MainSprite;
	sf::Vector2f spriteSheetDim;
	sf::Vector2f origin; 
	sf::Vector2f scale; 
	sf::Vector2f pos; 
	int animationFPS;

	int frameCounter; 

};


#endif _Explsion

