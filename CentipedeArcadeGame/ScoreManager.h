//ScoreManager.h
//David Klimavich, November 2016

#ifndef _ScoreManager
#define _ScoreManager

#include "Game Components\TEAL\CommonElements.h"
#include "HUD.h"

class ScoreManager : public GameObject //game object for demonstration ONLY
{
public:
	
	ScoreManager();
	ScoreManager(const ScoreManager&) = delete;
	ScoreManager& operator=(const ScoreManager&) = delete;
	 

	//===================for demonstration ONLY================
	virtual void Update();
	virtual void Destroy();
	//======================================================

	

	//reset the score to 0
	static void ResetScore();
	//get total points
	int GetScore();

	//add points
	static void AddSpiderPoints();
	static void AddScorpionPoints();
	static void AddMushroomPoints();
	static void AddCentipedeHeadPoints();
	static void AddCentipedeBodyPoints();


	static void Terminate();

private:

	static ScoreManager* instance;
	static ScoreManager& Instance()
	{
		if (!instance)
		{
			instance = new ScoreManager;
		}

		return *instance;
	};

	//Private Methods
	static void PrivateAddSpiderPoints();
	static void PrivateAddScorpionPoints();
	static void PrivateAddMushroomPoints();
	static void PrivateAddCentipedeHeadPoints();
	static void PrivateAddCentipedeBodyPoints();
	static void PrivateResetScore();


	
	static std::string highScoreSTR;
	static int highScoreINT;
	static void UpdateHUD(int currentScore);
	static void UpdateHUD_HS(int passedHS);
	static bool newHS;
	//HUD *scoreHUD;

	//points
	static int TotalScore;
	static int spiderPoints;
	static int fleaPoints;
	static int scorpionPoints;
	static int mushroomPoints;
	static int centipedeHeadPoints;
	static int centipedeBodyPoints;
};

#endif _ScoreManager