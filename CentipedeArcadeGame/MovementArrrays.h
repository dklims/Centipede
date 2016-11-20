#ifndef _MovementArrays
#define _MovementArrays

#include "Game Components\TEAL\CommonElements.h"

class MovementArrays : public GameObject
{
public:
	MovementArrays();
	virtual ~MovementArrays();
	
	static MovementArrays* instance;
	static MovementArrays& GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new MovementArrays();
		}

		return *instance;
	}

protected:

	//NO MOVEMENT
	const float speed = 2.0f;
	const sf::Vector2f noSpeedVect = { 0,0 };
	const sf::Vector2f noSpeed[8]
	{
		noSpeedVect, noSpeedVect, noSpeedVect, noSpeedVect, noSpeedVect, noSpeedVect, noSpeedVect, noSpeedVect
	};

	//MOVING TO THE RIGHT
	const sf::Vector2f rightVect = { speed, 0 };
	const sf::Vector2f right[8]
	{
		rightVect, rightVect, rightVect, rightVect, rightVect, rightVect, rightVect, rightVect
	};

	//MOVING TO THE LEFT
	const sf::Vector2f leftVect = { -speed,0 };
	const sf::Vector2f left[8]
	{
		leftVect, leftVect, leftVect, leftVect, leftVect, leftVect, leftVect, leftVect,
	};

	//MOVING DOWN
	const sf::Vector2f downVect = { 0,speed };
	const sf::Vector2f down[8]
	{
		downVect, downVect, downVect, downVect, downVect, downVect, downVect, downVect
	};

	//MOVING UP
	const sf::Vector2f upVect = { 0,-speed };
	const sf::Vector2f up[8]
	{
		upVect, upVect, upVect, upVect, upVect, upVect, upVect, upVect
	};
	
};

#endif _MovementArrays