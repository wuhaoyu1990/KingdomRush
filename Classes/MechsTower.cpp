#include "MechsTower.h"
#include "SimplePanleLayerWithFlag.h"
#include "BaseMap.h"

bool MechsTower::init()
{
	if(!BaseTower::init()){
		return false;
	}
	setTowerType(MECHS);
	addTerrain();
	setScope(220.0f);
	setBuildMoney(550);
	SoundManager::playMechLoading();
	auto layer1 = Sprite::createWithSpriteFrameName("tower_mechs_layer1_0001.png");
	auto layer2 = Sprite::createWithSpriteFrameName("tower_mechs_layer2_0001.png");
	auto layer3 = Sprite::createWithSpriteFrameName("tower_mechs_layer3_0001.png");
	auto layer4 = Sprite::createWithSpriteFrameName("tower_mechs_layer4_0001.png");
	auto layer5 = Sprite::createWithSpriteFrameName("tower_mechs_layer5_0001.png");
	auto layer6 = Sprite::createWithSpriteFrameName("tower_mechs_layer6_0001.png");
	auto layer7 = Sprite::createWithSpriteFrameName("tower_mechs_layer7_0001.png");
	auto layer8 = Sprite::createWithSpriteFrameName("tower_mechs_layer8_0001.png");
	auto layer9 = Sprite::createWithSpriteFrameName("tower_mechs_layer9_0001.png");

	addChild(layer1);
	//addChild(layer2);
	addChild(layer3);
	addChild(layer4);
	addChild(layer5);
	addChild(layer6);
	addChild(layer7);
	addChild(layer8);
	addChild(layer9);

	//layer2->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("MechsTower_layer2")));
	layer3->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("MechsTower_layer3")));
	layer4->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("MechsTower_layer4")));
	layer6->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("MechsTower_layer6")));
	layer7->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("MechsTower_layer7")));
	layer8->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("MechsTower_layer8")));
	layer9->runAction(Sequence::create(
		Animate::create(AnimationCache::getInstance()->getAnimation("MechsTower_layer9")),
		CallFuncN::create(CC_CALLBACK_0(MechsTower::initMech,this)),NULL));
	
	layer3->runAction(Sequence::create(
		DelayTime::create(2.0f),
		Animate::create(AnimationCache::getInstance()->getAnimation("MechsTower_layer3_r"))
		,NULL));
	layer4->runAction(Sequence::create(
		DelayTime::create(2.0f),
		Animate::create(AnimationCache::getInstance()->getAnimation("MechsTower_layer4_r")),
		CallFuncN::create(CC_CALLBACK_0(MechsTower::playReadySound,this))
		,NULL));
	
	setScope(200);
	setListener();
	return true;
}

void MechsTower::playReadySound()
{
	SoundManager::playMechReady();
}

void MechsTower::initMech()
{
	mecha = Mecha::create();
	mecha->setPosition(Point(0,40));
	this->getParent()->addChild(mecha);
}

void MechsTower::sellTower()
{
	if(mecha!=NULL){
		mecha->stopAllActions();
		mecha->unscheduleAllCallbacks();
		mecha->removeFromParent();
	}
	static_cast<Terrain*>(this->getParent())->smokeEffect();
	static_cast<Terrain*>(this->getParent())->terrain->setVisible(true);
	this->unscheduleAllCallbacks();
	this->removeAllChildren();
	this->removeFromParent();
}

void MechsTower::showUpdateMenu()
{
	auto updatePanleLayer = SimplePanleLayerWithFlag::create();
	updatePanleLayer->setTag(myTerrain->getTag()+100);
	updatePanleLayer->setTower(this);
	updatePanleLayer->setPosition(this->getParent()->getPosition());
	static_cast<BaseMap*>(this->getParent()->getParent())->mTouchLayer->addChild(updatePanleLayer);
	updatePanleLayer->inAnimation();
	isUpdateMenuShown = true;
}

void MechsTower::setRallyPoint(Point location)
{
	mecha->runToLocation(location - this->getParent()->getPosition());
}