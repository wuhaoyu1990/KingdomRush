#include "SimpleMageTowerlvl1.h"
#include "SimpleMageTowerlvl2.h"
#include "UpdatePanleLayer.h"
#include "BaseMap.h"
#include "GameManager.h"
#include "MageBolt.h"

bool SimpleMageTowerlvl1::init()
{
	if(!Sprite::init())
	{
		return false;
	}
	setTowerType(MAGE_1);
	setLevel(1);
	addTerrain();
	buildingAnimation();

	setScope(160);
	setUpdateMoney(160);
	setBuildMoney(100);
	isUpdateMenuShown=false;
	return true;
}
 void SimpleMageTowerlvl1::buildingAnimation()
 {
	auto building = Sprite::create();
	auto constructing = Sprite::createWithSpriteFrameName("tower_constructing_0003.png");
	auto hpBgSprite = Sprite::createWithSpriteFrameName("buildbar_bg.png");
	hpBgSprite->setPosition(Point(constructing->getContentSize().width / 2, constructing->getContentSize().height /2+10));
	auto hpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("buildbar.png"));
	hpBar->setType(ProgressTimer::Type::BAR);
	hpBar->setMidpoint(Point(0, 0.5f));
	hpBar->setBarChangeRate(Point(1, 0));
	hpBar->setPercentage(0);
    hpBar->setPosition(Point(hpBgSprite->getContentSize().width / 2, hpBgSprite->getContentSize().height / 2 ));
    hpBgSprite->addChild(hpBar);
	constructing->addChild(hpBgSprite);
	building->addChild(constructing);
	building->setPosition(Point(0,-10));
	addChild(building);

	hpBar->runAction(Sequence::create(ProgressTo::create(0.5f, 100)
		, CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, building))
                                           , NULL));
	scheduleOnce(schedule_selector(SimpleMageTowerlvl1::buildingSmokeAnimation),0.5f);
 }

 void SimpleMageTowerlvl1::buildingSmokeAnimation(float dt)
{
	auto smoke = Sprite::createWithSpriteFrameName("effect_buildSmoke_0001.png");
	addChild(smoke,99);
	smoke->runAction(Sequence::create(
		Animate::create(AnimationCache::getInstance()->getAnimation("build_smoke")),
		CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, smoke)),NULL));
	initTower(1);
	setListener();
	schedule(schedule_selector(SimpleMageTowerlvl1::shoot), 2.0f);
	SoundManager::playMageTowerReady();
}

void SimpleMageTowerlvl1::updateTower()
{
	auto simpleMageTowerlvl2 = SimpleMageTowerlvl2::create();
	simpleMageTowerlvl2->setMyTerrain(myTerrain);
	simpleMageTowerlvl2->setTag(myTerrain->getTag());
	simpleMageTowerlvl2->setPosition(Point(0,20));
	myTerrain->addChild(simpleMageTowerlvl2);
	this->removeTower();
}

void SimpleMageTowerlvl1::showUpdateMenu()
{
	auto updatePanleLayer = UpdatePanleLayer::create();
	updatePanleLayer->setTag(myTerrain->getTag()+100);
	updatePanleLayer->setTower(this);
	updatePanleLayer->setPosition(this->getParent()->getPosition());
	static_cast<BaseMap*>(this->getParent()->getParent())->mTouchLayer->addChild(updatePanleLayer);
	if(GameManager::getInstance()->LEVEL <=0){
		updatePanleLayer->couldUpdate = false;
	}
	updatePanleLayer->inAnimation();
	isUpdateMenuShown = true;
}

Bullet* SimpleMageTowerlvl1::MageTowerBullet()
{
	auto bullet = MageBolt::create();
	bullet->setPosition(Point(10,45));
	bullet->setMaxForce(15);
	this->getParent()->addChild(bullet);
    return bullet;
}