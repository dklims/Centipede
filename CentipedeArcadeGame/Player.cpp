//player.cpp
//David Klimavich, November 2016

#include "player.h"
#include "HUD.h"

int Player::lives;
int Player::maxLives;
Player *Player::instance = nullptr;

Player::Player()
{
	maxLives = WaveManager::GetPlayerLives();
	lives = maxLives;
//	ResetLives();
}

//PUBLIC METHODS
void Player::DecrementLives()
{
	GetInstance().PrivateDecrementLives();
}

int Player::GetLives()
{
	return GetInstance().PrivateGetLives();
}

void Player::ResetLives()
{
	GetInstance().PrivateResetLives();
}

//PRIVATE METHODS

void Player::PrivateDecrementLives()
{
	lives--;
	HUD::UpdateLivesHUD();
}

int Player::PrivateGetLives()
{
	return lives;
}

void Player::PrivateResetLives()
{
	lives = maxLives;
}



