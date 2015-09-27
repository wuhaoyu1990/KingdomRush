#include "GameScene.h"
#include "Level0.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"
#include "Level6.h"
#include "Level7.h"
#include "Level8.h"
#include "Level9.h"
#include "Level10.h"
#include "Level11.h"
#include "Level12.h"
#include "PlayerStateMenu.h"
#include "GameManager.h"

Scene* GameScene::playGame(int Level,int Difficulty)
{            
	auto scene = new GameScene();
	if(scene && scene->initGame(Level,Difficulty)){
		scene->autorelease();
		return scene;
	}
	CC_SAFE_DELETE(scene);
	return NULL;
}

bool GameScene::initGame(int Level,int difficulty)
{
	auto playerStateMenu = PlayerStateMenu::create();
	BaseMap* game;
	GameManager::getInstance()->LEVEL = Level;
	switch (Level)
	{
	case(0):{
		game = Level0::createGame(difficulty);}
		break;
	case(1):{
		game = Level1::createGame(difficulty);}
		break;
	case(2):{
		game = Level2::createGame(difficulty);}
		break;
	case(3):{
		game = Level3::createGame(difficulty);}
		break;
	case(4):{
		game = Level4::createGame(difficulty);}
		break;
	case(5):{
		game = Level5::createGame(difficulty);}
		break;
	case(6):{
		game = Level6::createGame(difficulty);}
		break;
	case(7):{
		game = Level7::createGame(difficulty);}
		break;
	case(8):{
		game = Level8::createGame(difficulty);}
		break;
	case(9):{
		game = Level9::createGame(difficulty);}
		break;
	case(10):{
		game = Level10::createGame(difficulty);}
		break;
	case(11):{
		game = Level11::createGame(difficulty);}
		break;
	case(12):{
		game = Level12::createGame(difficulty);}
		break;
	}
	
	game->bindPlayerStateMenu(playerStateMenu);
	playerStateMenu->setLevel(Level);
	playerStateMenu->setDifficult(difficulty);
	playerStateMenu->initGameOption();
	addChild(game);	
	addChild(playerStateMenu);
	return true;
}