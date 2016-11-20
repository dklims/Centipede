// FirstScene

#include "FirstScene.h"
#include "../Explosion.h"
#include "../player.h"

void FirstScene::Initialize()
{
	
	new KeyEventTest;
	new Blaster;



	MushroomGrid::CreateField();
	WaveManager::StartWave();
	ScoreManager::ResetScore();
	HUD::UpdateLivesHUD();



	//TEST
	new Explosion();


	//new Spider();
	//HUD::Instance().UpdateHighScoreHUD(10000);
	//new Centipede;
	
	CollisionTestPair<Bullet, Mushroom>();
	CollisionTestPair<Bullet, Scorpion>();
	CollisionTestPair<Blaster, Scorpion>();
	CollisionTestPair<Blaster, Mushroom>();
	CollisionTestPair < Bullet, CentipedeHead>();
	CollisionTestPair <Bullet, CentipedeSegment>();
	CollisionTestPair<Bullet, Flea>();
	CollisionTestPair<Blaster, Spider>();
	CollisionTestPair<Mushroom, Spider>();
	CollisionTestPair<Bullet, Spider>();
	CollisionTestPair<Blaster, CentipedeHead>();
	CollisionTestPair<Blaster, CentipedeSegment>();
	//new Mushroom(300, 300);
}

void FirstScene::Terminate()
{
	BulletFactory::Terminate();
	FleaFactory::Terminate();
	ScorpionFactory::Terminate();
	CentipedeSegmentFactory::Terminate();
	CentipedeHeadFactory::Terminate();
	SpiderFactory::Terminate();
	ScoreManager::Terminate();
	WaveManager::Terminate();

	//MushroomGrid::Terminate();
	
}