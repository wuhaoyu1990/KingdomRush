#include "cocos2d.h"

USING_NS_CC;

class EncyclopaediaTips : public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
	void menuCallback(Ref *pSender); //切换场景

   void starMenuCallback1(Ref* pSender); //按钮控制数字的切换

   void starMenuCallback2(Ref* pSender);//按钮控制文字的切换
   void leftChange(Ref *pSender);
  
private :
	 int i;
	 Label* ch;//声明文字
     Label* lb;//声明数字

	 MenuItemSprite *sprite29;
	 MenuItemSprite *sprite30;

	
	 std::string string[30];

    CREATE_FUNC(EncyclopaediaTips);

	
};