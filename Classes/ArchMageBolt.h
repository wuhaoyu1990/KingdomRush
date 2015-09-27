#ifndef _ARCHMAGEBOLT_H_
#define _ARCHMAGEBOLT_H_

#include "cocos2d.h"
#include "Bullet.h"
class ArchMageBolt:public Bullet

{
public :
	bool init();
	CREATE_FUNC(ArchMageBolt);
	void shoot();
	void removeBullet();
	void round();
};
#endif