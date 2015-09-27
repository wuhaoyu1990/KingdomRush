#ifndef _MY_ANIMATION_H_
#define _MY_ANIMATION_H_

#include "cocos2d.h"
USING_NS_CC;

class MyAnimation
{
public:
	static MyAnimation* getInstance();

	void init();
	void init_desert();
	void init_jungle();
	void init_ArcherTower();
	void init_ArtilleryTower();
	void init_Executioner();

	void init_Wasp_Queen();	
	void init_Wasp_Hornet();
	void init_Scorpion();
	void init_Munra();
	void init_Thug();
	void init_Raider();
	void init_Gorilla();
	void init_Priest();
	void init_Shaman();
	void init_Hunter();
	void init_Canibal();


	void init_Shield();
	void init_WingRider();
	void init_Wolf();
	void init_reinforce();
	void init_Immortal();
	void init_Tremor();
	void init_Fallen();

	void init_blazefang();
	void init_broodguard();
	void init_elite();
	void init_myrmidon();
	void init_nightscale();
	void init_Quetza();
	void init_underground();

	void init_earthquakeTower();
	void init_ArchMageTower();
	void init_mechsTower();
	void init_NecromancerTower();
	void init_BarracksTower();
	void init_MageTower();
	void init_CossbowHunterTower();
	void init_TotemTower();
	void init_monster_blood();

	void init_BossCanibal();
	void release_BossEfreeti();
	void init_BossEfreeti();
	void release_BossCanibal();

	Animation* createAnimation(const char* prefixName, int start,int end, float delay);
	Animation* createAnimationR(const char* prefixName, int start,int end, float delay);
	Animation* createAnimation(const char* prefixName, int start,int end, float delay,std::string lastFrame);
	void init_others();
private:
	static MyAnimation * instance;
};

#endif