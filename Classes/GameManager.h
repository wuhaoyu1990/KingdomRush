#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include "Bullet.h"
#include "cocos2d.h"
#include "BaseMonster.h"
#include "BaseTower.h"
#include "TouchLayer.h"

USING_NS_CC;

class GameManager
{
public:
    void CreateGameManager(int slot);

    Vector<BaseMonster*> monsterVector;
    //Vector<Bullet*> bulletVector;
    //Vector<BaseTower*> towerVector;
    
	static GameManager* getInstance();


	//某存档是否已经新建，true表示新建，false表示未新建
	char SLOTX_ISEXIT[20];

    //某关卡是否完成,0表示未完成，1表示完成
	char LEVELX_ISDOWN[20];

	//某关卡得到的星星数目
	char LEVELX_STARNUM[20];
	//剩余星星数目
	char SLOTX_STARLEFT[20];
	//某存档通关数
	char SLOTX_DOWNCOUNT[20];

	//某存档最新开启的
	char LEVELX_NEWDOWN[20];

	//总星星数
	char SLOTX_STAR[20];

	//商店
	char SLOTX_SHOP[20];

	//宝石
	char SLOTX_GEM[20];
	int SLOTNUM;
	//实时金钱
	int MONEY;
	//实时生命
	int LIFE;
	
	int LEVEL;

	void setInstance(int tag);
	static void eraseAll();
private:
	static GameManager * instance;
};
#endif /* defined(__thiefTD__GameManager__) */
