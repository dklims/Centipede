#ifndef _ScoreText
#define _ScoreText


#include "Game Components/TEAL/CommonElements.h"
#include <list>
class Glyph;
#include "AwesomeFont.h"

class ScoreText : public GameObject
{
public:
	static ScoreText* instance;
	ScoreText();
	ScoreText(const ScoreText&) = delete;
	ScoreText& operator = (const ScoreText&) = delete;

	static ScoreText& Instance()
	{
		if (!instance)
		{
			instance = new ScoreText;
		}

		return *instance;
	}

	//virtual void TextEntered(sf::Uint32 UnicodeValue);
	virtual void Draw();

	void UpdateScore(std::string passedScore = "00");

private:
	AwesomeFont myfont; //font to use
	std::string text; //Text to be displayed

	std::list<Glyph> symbols;
	sf::Vector2f nextPos;

};


#endif _ScoreText