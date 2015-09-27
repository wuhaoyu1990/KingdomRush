#ifndef _BOSS_EFREETI_H_
#define _BOSS_EFREETI_H_

#include "BaseMonster.h"

class Boss_Efreeti : public BaseMonster
{
public:
	virtual bool init() override;    
	static Boss_Efreeti* createMonster(std::vector<Point> points,std::vector<std::vector<std::vector<Point>>> sonPath);
	void getHurt();
	void death();
	void explosion();
	void skill(float dt);
	std::vector<std::vector<std::vector<Point>>> sonPath;
	void addSons();
	Sprite* cloud;
	void laugh();
	void frozen();
};

#endif