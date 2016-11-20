//HUD.h
//David Klimavich, November 2016

#ifndef _HUD
#define _HUD


#include "Game Components/TEAL/CommonElements.h"
#include <list>
class Glyph;
#include "AwesomeFont.h"
#include "player.h"

class HUD : public GameObject
{
public:
	

	//virtual void TextEntered(sf::Uint32 UnicodeValue);
	virtual void Draw();

	static void UpdateHUD(int score);
	static void UpdateHighScoreHUD(int passedScore);
	static void UpdateLivesHUD();
	static void ScoreClear();
	//static AwesomeFont GetAwesomeFont();

	static void Terminate();

private:

	static HUD* instance;
	HUD();
	HUD(const HUD&) = delete;
	HUD& operator = (const HUD&) = delete;

	static HUD& Instance()
	{
		if (!instance)
		{
			instance = new HUD;
		}

		return *instance;
	}

	//PRIVATE METHODS
	void PrivateUpdateHUD(int score);
	void PrivateUpdateHighScoreHUD(int passedScore);
	void PrivateUpdateLivesHUD();
	void PrivateScoreClear(); 
	//static AwesomeFont PrivateGetAwesomeFont();



	AwesomeFont myfont; //font to use
	static std::string text; //Text to be displayed
	static std::list<Glyph> symbols;
	static std::list<Glyph> HSSymbols;
	 //std::list<AnimatedSprite> shipLives;
	static sf::Vector2f nextPos;
	static sf::Vector2f nextHSPos;

	static AnimatedSprite BlasterSprite;

	static int lives;

	static const int maxLives = 3;
	static sf::Vector2f blasterPositions[maxLives];

};



#endif _HUD