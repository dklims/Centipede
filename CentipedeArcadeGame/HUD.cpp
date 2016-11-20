//HUD.cpp
//David Klimavich, November 2016

#include "HUD.h"
#include "Glyph.h"

HUD* HUD::instance = nullptr;
std::string HUD::text;
std::list<Glyph> HUD::symbols;
std::list<Glyph> HUD::HSSymbols;
sf::Vector2f HUD::nextPos;
sf::Vector2f HUD::nextHSPos;
int HUD::lives;
//AwesomeFont HUD::myfont;
AnimatedSprite HUD::BlasterSprite;
sf::Vector2f HUD::blasterPositions[];

HUD::HUD()
{
	//UpdateHUD();
	BlasterSprite = AnimatedSprite(ResourceManager::GetTexture("Blaster"),1,1);
	BlasterSprite.SetAnimation(0, 0);
	BlasterSprite.setScale(1, 1);

	//Update HS
	//UpdateHighScoreHUD(10000);

	lives = Player::GetLives();
}



void HUD::Draw()
{
	//regular score
	std::list<Glyph>::iterator it;
	for (it = symbols.begin(); it != symbols.end(); it++)
		it->Draw();

	//Draw Blasters for lives on HUD
	for (int i = 0; i < lives - 1; i++)
	{
		BlasterSprite.setPosition(blasterPositions[i]);
		WindowManager::MainWindow.draw(BlasterSprite);
	
	}

	//highscore
	std::list<Glyph>::iterator HS_it;
	for (HS_it = HSSymbols.begin(); HS_it != HSSymbols.end(); HS_it++)
		HS_it->Draw(); 
}

void HUD::UpdateHUD(int passedScore)
{
	Instance().PrivateUpdateHUD(passedScore);
	Instance().PrivateUpdateLivesHUD();
}

void HUD::UpdateHighScoreHUD(int passedScore)
{
	Instance().PrivateUpdateHighScoreHUD(passedScore);
}

void HUD::UpdateLivesHUD()
{
	Instance().PrivateUpdateLivesHUD();
}

void HUD::ScoreClear()
{
	Instance().PrivateScoreClear(); 
}
//PRIVATE METHODS
void HUD::PrivateScoreClear()
{
	symbols.clear();
}
void HUD::PrivateUpdateHUD(int passedScore)
{
	text = Tools::ToString(passedScore);
	nextPos = { float(WindowManager::MainWindow.getSize().x / 8),0 };

	for (size_t i = 0; i < text.length(); i++)
	{
		symbols.push_back(HUD::myfont.GetGlyph(text.at(i), nextPos));
		nextPos.x += myfont.CellWidth() * 2; // x2 becauase the scale of the sprites are 2. 
	}

}

void HUD::PrivateUpdateHighScoreHUD(int passedScore)
{
	std::string highscore = Tools::ToString(passedScore);
	nextHSPos = { 200, 0 };

	for (size_t i = 0; i < highscore.length(); i++)
	{
		HSSymbols.push_back(myfont.GetGlyph(highscore.at(i), nextHSPos));
		nextHSPos.x += myfont.CellWidth() * 2;
	}
}

void HUD::PrivateUpdateLivesHUD()
{
	//stores locaions to draw Blaster icons next to the current score. 
	nextPos = { float(WindowManager::MainWindow.getSize().x / 8 + text.length() * (myfont.CellWidth() * 2)),0.0f };
	lives = Player::GetLives();
	for (int i = 0; i < lives-1; i++)
	{
		blasterPositions[i] = nextPos;
		nextPos.x += myfont.CellWidth() * 2;
	}
}






void HUD::Terminate()
{
//	delete (instance); 
	instance = nullptr; 
}