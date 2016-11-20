#include "ScoreManager.h"
#include <fstream>
#include <iostream>

ScoreManager* ScoreManager::instance = nullptr;
int ScoreManager::spiderPoints;
int ScoreManager::fleaPoints;
int ScoreManager::scorpionPoints;
int ScoreManager::mushroomPoints;
int ScoreManager::centipedeHeadPoints;
int ScoreManager::centipedeBodyPoints;
int ScoreManager::TotalScore;

std::string ScoreManager::highScoreSTR;
int ScoreManager::highScoreINT;
bool ScoreManager::newHS;



ScoreManager::ScoreManager()
{
	//Get HighScore from file
	std::ifstream HS_File;
	HS_File.open("highScore.txt");

	char c ; 
	HS_File.get(c);

	while (HS_File)
	{
		ConsoleMsg::WriteLine("Char = " + Tools::ToString(c));
		highScoreSTR += c;
		HS_File.get(c);
	}

	ConsoleMsg::WriteLine("HIGHSCORE = " + highScoreSTR);

 	HS_File.close();

	highScoreINT = std::stoi(highScoreSTR);

	//points
	spiderPoints = 300;
	fleaPoints = 5;
	scorpionPoints = 1000;
	mushroomPoints = 10;
	centipedeHeadPoints = 10;
	centipedeBodyPoints = 1;
	//ResetScore();

	//Score HUD
	//scoreHUD = new HUD();
	
	newHS = false; 
}

void ScoreManager::Update()
{
	//ConsoleMsg::WriteLine("TOTAL SCORE = " + Tools::ToString(TotalScore));
}

void ScoreManager::ResetScore()
{
	Instance().PrivateResetScore();
}


int ScoreManager::GetScore()
{
	return TotalScore;
}

void ScoreManager::AddSpiderPoints()
{
	Instance().PrivateAddSpiderPoints();
}


void ScoreManager::AddScorpionPoints()
{
	Instance().PrivateAddScorpionPoints();
}

void ScoreManager::AddMushroomPoints()
{
	Instance().PrivateAddMushroomPoints();
}

void ScoreManager::AddCentipedeHeadPoints()
{
	Instance().PrivateAddCentipedeHeadPoints();
}

void ScoreManager::AddCentipedeBodyPoints()
{
	Instance().PrivateAddCentipedeBodyPoints();
}



void ScoreManager::UpdateHUD(int score)
{
	HUD::UpdateHUD(score);

	if (score > highScoreINT)
	{
		UpdateHUD_HS(score);
		highScoreINT = score;
		newHS = true;
	}
	//ConsoleMsg::WriteLine("Current Score = " + score);
}

void ScoreManager::UpdateHUD_HS(int passedHS)
{
	HUD::UpdateHighScoreHUD(passedHS);
	
}

void ScoreManager::Destroy()
{
	if (newHS == true)
	{
		std::ofstream outputFile;
		outputFile.open("highScore.txt");
		outputFile << highScoreINT;
		outputFile.close();
	}
}

void ScoreManager::Terminate()
{
	HUD::Terminate();
	//delete(instance); --FIX
	instance = nullptr;
}

//PRIVATE METHODS
void ScoreManager::PrivateAddSpiderPoints()
{
	TotalScore += spiderPoints;
	UpdateHUD(TotalScore);
}

void ScoreManager::PrivateAddScorpionPoints()
{
	TotalScore += scorpionPoints;
	UpdateHUD(TotalScore);
}

void ScoreManager::PrivateAddMushroomPoints()
{
	TotalScore += mushroomPoints;
	UpdateHUD(TotalScore);
}

void ScoreManager::PrivateAddCentipedeHeadPoints()
{
	TotalScore += centipedeHeadPoints;
	UpdateHUD(TotalScore);
}

void ScoreManager::PrivateAddCentipedeBodyPoints()
{
	TotalScore += centipedeBodyPoints;
	UpdateHUD(TotalScore);
}

void ScoreManager::PrivateResetScore()
{
	TotalScore = 0;
	UpdateHUD(TotalScore);
	UpdateHUD_HS(highScoreINT);
}
