#include "ScoreText.h"
#include "Glyph.h"

ScoreText* ScoreText::instance = nullptr;
ScoreText::ScoreText()
{
	//UpdateScore();
}

void ScoreText::Draw()
{
	std::list<Glyph>::iterator it;
	for (it = symbols.begin(); it != symbols.end(); it++)
		it->Draw();
}

void ScoreText::UpdateScore(std::string passedScore)
{
	text = passedScore;
	nextPos = { 100,100 };

	for (size_t i = 0; i < text.length(); i++)
	{
		symbols.push_back(myfont.GetGlyph(text.at(i), nextPos));
		nextPos.x += myfont.CellWidth();
	}
}
