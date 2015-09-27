#include "cocos2d.h"
#include "EncyclopaediaTips.h"
#include "EncyclopediaScene.h"
#include "SoundManager.h"

USING_NS_CC;


Scene* EncyclopaediaTips::createScene()
{   
	auto scene=Scene::create();
    auto layer=EncyclopaediaTips::create();
    scene->addChild(layer);
    return scene;
}


bool EncyclopaediaTips::init()
{
    if(!Layer::init())
    {
        return false;
    }

    //获取整个手机可视屏幕尺寸
    Size visibleSize = Director::getInstance()->getVisibleSize();
	//导入plist

/*****************************************************************************************************************/
	//第一层图片添加
   //// 图片的平铺
	for(int h = 0;h<4;h++){
		for(int k =0;k<5;k++){
			auto sprite = Sprite::createWithSpriteFrameName("encyclopedia_bgTile.png");
			sprite->setPosition(Point(h*310,k*150));
			sprite->setAnchorPoint(Point(0,0));
			addChild(sprite);
		}
	}
	i = 1;

/*===================================================================================================================*/
	//第二层图片添加
	auto sprite11 = Sprite::createWithSpriteFrameName("encyclopedia_tips_left.png");
	sprite11->setPosition(Point(visibleSize.width*0.21,visibleSize.height*0.5));
	this->addChild(sprite11,1);

	auto sprite12 = Sprite::createWithSpriteFrameName("encyclopedia_tips_middle.png");
	sprite12->setPosition(Point(visibleSize.width*0.50,visibleSize.height*0.5));//0.25
	sprite12->setScaleX(13.0f);
	this->addChild(sprite12,1);

	auto sprite27 = Sprite::createWithSpriteFrameName("encyclopedia_tips_left.png");
	sprite27->setPosition(Point(visibleSize.width*0.79,visibleSize.height*0.5));
	 //可以手动设置图形旋转和镜像
	sprite27->setFlippedX(true);
    sprite27->setRotation(360);//图片翻转的角度
	this->addChild(sprite27,1);

/*===========================================================================================================*/
	//第三层图片添加 
	//图片的切换
/***************************************************************************************************************/
	//关闭符号

	auto sprite28 =MenuItemSprite::create(Sprite::createWithSpriteFrameName("LevelSelect_Back_0001.png"),
	Sprite::createWithSpriteFrameName("LevelSelect_Back_0002.png"),CC_CALLBACK_1(EncyclopaediaTips::menuCallback,this));  
    auto ccmenuu = Menu::create(sprite28,NULL);  //实现三者之间的顺序切换  
    sprite28->setPosition(Point(visibleSize.width*0.8,visibleSize.height*0.81));  
	ccmenuu->setPosition(Vec2::ZERO);
    this->addChild(ccmenuu,2);  
///////////////////////////////////////////////////////////////////////////////////////////////////
	//左边箭头按钮
	//灰色箭头 表示不可点击
	auto sprite0 = Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_arrow_0001.png");
	sprite0->setFlippedX(true);
    sprite0->setRotation(360);
	/*sprite0->setPosition(Point(visibleSize.width*0.4,visibleSize.height*0.3));
	this->addChild(sprite0,2);*/

	//小箭头
	auto sprite01 = Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_arrow_0002.png");
	sprite01->setFlippedX(true);
    sprite01->setRotation(360);//(向左)

	//小箭头 （向右）
	auto sprite03 =  Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_arrow_0002.png");

	//大箭头(向右)
	auto sprite02 = Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_arrow_0003.png");
	//大箭头
	auto sprite04= Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_arrow_0003.png");
	sprite04->setFlippedX(true);
    sprite04->setRotation(360);//(向左)

	//灰色箭头 表示不可点击
	auto sprite05 = Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_arrow_0001.png");
	
	sprite0->cleanup();
	sprite29 = MenuItemSprite::create(sprite04,sprite01,sprite0,CC_CALLBACK_1(EncyclopaediaTips::starMenuCallback2,this));
	sprite29->setPosition(Point(visibleSize.width*0.4,visibleSize.height*0.3));
	
	auto ccmenuu1 = Menu::create(sprite29,NULL);  //实现三者之间的顺序切换  
	ccmenuu1->setPosition(Vec2::ZERO);
    this->addChild(ccmenuu1,2);  
	sprite29 ->setEnabled(false);
	
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     //数字
   
	lb = Label::createWithTTF("1", "arial.ttf", 24);
    lb->setPosition(Point(visibleSize.width*0.47, visibleSize.height*0.30));
	lb->setColor(Color3B(0,0,0));
    addChild(lb,2);

//***************************************************************************************************//	 
	string[0] = "  ENEMIES AND SOLDIERS WITH ARMOR  \n        RECIEIVE LESS PHYSICAL DAMAGE.";
	string[1] = "    SUPPORT BARRACKS WITH RANGED  \n        ROWERS TO MAXIMIZE ENEMY     \n                     EXPOSURE.";
    string[2] =" REINFORCEMENTS ARE A GREAT WAY  \n          TO SPLIT ENEMY FORCES." 	;	 
	string[3] = "    ARTILLERY WORKS BEST AGAINST   \n   HIGH CONCENTRATIONS OF ENEMES.";
	string[4] ="  ARTILLERY DAMAGE IS HEGHEST IN THE\n         CENTER OF THE EXPLOSION.";
	string[5] =" USE REINFORCEMENTS CONSTANTLY\n    TO SLOW AND DAMAGE THE ENEMY.";
	string[6] = "     ALWAYS AIM RAIN FO FIRE A LITTLE\n           AHEAD OF YOUR TARGET.";
	string[7] ="     REARRANGING YOUR UPGRAND \n    POINTS IS A GOOD WAY TO ANAPT \n              YOUR  STRAATEGY.";
	string[8] =" MAGIC DAMAGE ID THE BEST WAY TO\n      DEAL WITH ARMORED ENEMIES.";
	string[9] = "  FLYING ENEMIES CANNOT BE BLOCKED\nBY BARRACK AND WONTBE TARGETEDBY\n                 MOST ARTILLERY.";
	string[10] ="   ENEMIES WITH MAGIC RESISTANCE \n    RECEIVE LESS DAMAGE FROM MAGIC \n                      ATTACKS.";
	string[11] ="         ADJUST THE RALLY POINT OF\n          SOLDIERS TO CREATE BETTER \n                    STRATEGIES";
	string[12] = "   SOMETIMES IT IS BETTER TO BUILD\n         MORE TOWERS INSTEAND OF\n              UPGRANDING A FEW.";
	string[13] ="       PESTILENCE DAMAGE IGNORES \n                        ARMOR.";
	string[14] =" UPGRANDING A BARR ACK INSTANTLY\n             TRAINS NEW SOLDIERS.";
	string[15] ="       CALLING AN EARLY WAVE GIVES\n      BONUS CASH AND REDUCES SPELL\n                 COOLDOWNS A BIT.";
	string[16] = " ARTILLERY EXPLOSIONS CAN DAMAGE\n  FLYING ENEMIES EVEN THOUGH THEY\n   CANNOT TARGET THEM DIRECTLY.";
	string[17] ="USE BARRACKS OR REINFORCEMENTS \n   TO ISOLATE TROUBLESOME ENEMIES.";
	string[18] ="  EFFECTS THAT KILL INSTANTLY ARE A\n     GREAT WAY TO DEAL WITH TOUGH \n                      ENENIES.";
	string[19] = "   KEEP YOUR EYE OUT FOR ENEMIES\n   THAT TROUBLE YOUR DEFENSES.MORE \n                 MAY COME SOON.";
	string[20] = " YOU CAN CHECK WHAT EMEMIES ARE\n   IN THE INCOMING WAVE BY TAPPENG\n             THE WAVE ICON ONCE.";
	string[21] ="         DONT BE AFRAID OF SELLING A\n        TOWER AND REPLACING IT WITH A \n              MORE SUTIABLE ONE.";
    string[22] ="   HEROES AND SOLDIERS HEAL WHEN\n                 THEY ARE IDLE." 	;	 
	string[23] = "  CALLING A WAVE EARLIER DOESN'T\nREDUCE COOLDOWN OF TOEWER ABILITIES.";
	string[24] =" SOMETIMES IT IS WISSE TO SAVE SOME\n   COLD TO ADAPT TO UNEXPECTED\n                    ENEMIES.";
	string[25] ="     SAVAGES HEAL THEMSELVES AND \n   BECOME STRONGER EVERY TIME THEY\n                           EAT.";
	string[26] = " SAND WRAITHS CAN'T RAISE COFFINS\n                 WHILE BLOCKED.";
	string[27] ="       POISON FROM ENEMIES IS NOT\n     LETHAL.RETREAT YOUR  POISONED\n            SOLDIERS TO SAVE THEM.";
	string[28] ="THE EXECUTIIONER CANNOT EXECUTE\n                        HEROES.";
	string[29] = "      COMBINED SHAMAN AURAS CAN\n     MAKE SAVAGES NEARLY INVINCIBLE.";   //  /n可以使字符串换行
/********************************************************************************************************************************************/

     ch = Label::createWithTTF(string[0], "arial.ttf",26);
     ch->setPosition(Point(visibleSize.width*0.55, visibleSize.height*0.4));
	 ch->setColor(Color3B(0,0,0));
	 ch->setLineBreakWithoutSpace(true); //来支持自动换行功能
	 ch->setDimensions(visibleSize.width*0.55,visibleSize.height*0.4); //来控制自动换行
     this->addChild(ch, 2);
	 
	

	//右边箭头按钮
	//Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_arrow_0003.png"表示从大图中获取小图
    sprite30 = MenuItemSprite::create(sprite02,sprite03,sprite05,CC_CALLBACK_1(EncyclopaediaTips::starMenuCallback1,this));
	sprite30->setPosition(Point(visibleSize.width*0.6,visibleSize.height*0.3));
	auto ccmenuu2 = Menu::create(sprite30,NULL);  //实现切换  
	ccmenuu2->setPosition(Vec2::ZERO);
    this->addChild(ccmenuu2,2);  
	
/***************************************************************************************************************/


	auto label1 = Label::createWithTTF("/30", "arial.ttf", 24);
    label1->setPosition(Point(visibleSize.width*0.50, visibleSize.height*0.30));
	label1->setColor(Color3B(0,0,0));
    this->addChild(label1, 2);

	auto label4 = Label::createWithTTF("TIPS", "arial.ttf",36);
    label4->setPosition(Point(visibleSize.width*0.5, visibleSize.height*0.7));
	label4->setColor(Color3B(87,0,17));
    this->addChild(label4, 2);


    return true;
}

//关闭按钮，返回前一次的场景 
void EncyclopaediaTips::menuCallback(Ref *pSender)  
{  
	SoundManager::playClickEffect();
	Director::getInstance()->popScene();
}  

//按钮控制数字的切换 数字递增 （右侧箭头）
void EncyclopaediaTips::starMenuCallback1(Ref* pSender)
{  
	SoundManager::playClickEffect();
	if(i<31 && i>0){
		i++;
	    if (i==1)
		{
			sprite29 ->setEnabled(false); //按钮不可用
			sprite30 ->setEnabled(true);  //按钮可用
		}
		else if(i==30)
		{
			sprite29 ->setEnabled(true);
			sprite30 ->setEnabled(false);
		}
		else
		{
			sprite29 ->setEnabled(true);
			sprite30 ->setEnabled(true);
		}

	//显示数字变化
		lb->setString(String::createWithFormat("%d",i)->getCString());

	//显示内容变化	
		ch->setString(string[i-1]);
		
	}

}

//按钮控制数字的切换 数字递减 （左侧箭头）
void EncyclopaediaTips::starMenuCallback2(Ref* pSender){
	
	SoundManager::playClickEffect();
	if(i<31 && i>0){
		i--;
	    if (i==1)
		{
			sprite29 ->setEnabled(false);
			sprite30 ->setEnabled(true);
		}
		else if(i==30)
		{
			sprite29 ->setEnabled(false);
			sprite30 ->setEnabled(true);
		}
		else
		{
			sprite29 ->setEnabled(true);
			sprite30 ->setEnabled(true);
		}

		//字符串转化为数字
		lb->setString(String::createWithFormat("%d",i)->getCString());

		
		ch->setString(string[i-1]);
		
	}


}

