#ifndef _EARTHQUAKE_SMOKE_H_
#define _EARTHQUAKE_SMOKE_H_

#include "cocos2d.h"
#include "Bullet.h"

class EarthquakeSmoke:public Bullet

{
public :
	bool init();
	CREATE_FUNC(EarthquakeSmoke);
	void shoot();
	Vector<Sprite*> smokes;
};
#endif