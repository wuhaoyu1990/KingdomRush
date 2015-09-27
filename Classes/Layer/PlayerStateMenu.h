#ifndef _PLAYER_STATE_MENU_H_
#define _PLAYER_STATE_MENU_H_

#include "cocos2d.h"
#include "TouchLayer.h"
#include "GameManager.h"
#include "BaseTower.h"
#include "BaseMonster.h"
#include "GameOption.h"

USING_NS_CC;

#define TOWER_INFO 1001
#define MONSTER_INFO 1002

class PlayerStateMenu : public Layer
{
public:
	void startProgressTimers();
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(PlayerStateMenu);
	void onEnterTransitionDidFinish();
	/*void showOption();*/
	Sprite* stateSprite;
	Sprite* pause;
	Label* lifeLabel;
	Label* goldLabel;
	Label* waveLabel;

	//zhanglei-begin - 定义雷石，伞兵，锦囊三个精灵
	Sprite* thunderStoneSprite;
	Sprite* paratrooperSprite;
	Sprite* packSprite;
	Sprite* backPackSprite;
	//六侠
	Sprite* backPack_icons_Sprite[6];
	std::string stringForSkillFileName;
	void updateStoneProgress(float Dt);
	void updateParatrooperProgress(float Dt);
	bool completeThunder;
	bool completeParatrooper;
	ProgressTimer* paratrooperTimer;
	ProgressTimer* stoneTimer;
	//zhanglei-end

	GameManager* instance;
	TouchLayer* mTouchLayer;
	void setLife(int life);
	void setGold(int gold);
	void setWave(int thisWave,int totalWave);

	void startParatrooper();
	void startStone();
	void showTowerInfo(TowerType towerType);
	void removeTowerInfo();

	void showMonsterInfo(BaseMonster* monster);
	void removeMonsterInfo();
	void removeGameOption();
private:
	CC_SYNTHESIZE(int, level, Level);
	CC_SYNTHESIZE(int, difficult, Difficult);
	void shopSkill(int type);
	void frozenMonsters();
	void reFrozenMonsters(float dt);
	void clearMonsters();
	bool isFrozen;
	GameOption *gameOption;
	void addGameOption();
	void pauseGame();
	void initGameOption();
};

#endif