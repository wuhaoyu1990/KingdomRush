#include "cocos2d.h"

USING_NS_CC;

class Information : public cocos2d::CCLayer
{

public:

	static Scene* createScene();

	virtual bool init();
	void initMap();
	void callBackMenu(Ref *pSpender);


	CREATE_FUNC(Information);
};