#ifndef _Player
#define _Player

#include "WaveManager.h"

class Player
{
public:
	
	static void DecrementLives();
	static int GetLives();
	static void ResetLives();


private:

	Player();
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;

	static int lives; 
	static int maxLives;

	static Player* instance;
	static Player& GetInstance()
	{
		if (!instance)
		{
			instance = new Player;
		}
		return *instance;
	}

	//PRIVATE METHODS
	static void PrivateDecrementLives();
	static int  PrivateGetLives();
	static void PrivateResetLives();

};
#endif  _Player
