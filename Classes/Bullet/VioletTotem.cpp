#include "VioletTotem.h"
#include "GameManager.h"

VioletTotem* VioletTotem::createVioletTotem(Point point)
{
	auto violetTotem = new VioletTotem();
 
    if (violetTotem && violetTotem->init())
    {
        violetTotem->autorelease();
		violetTotem->shoot(point);
        return violetTotem;
    }
    CC_SAFE_DELETE(violetTotem);
    return NULL;
}

bool VioletTotem::init()
{
	if(!Sprite::init()){
		return false;
	}
	sprite = Sprite::createWithSpriteFrameName("TotemTower_VioletTotem_0001.png");
	addChild(sprite);
	return true;
}

void VioletTotem::shoot(Point point)
{
	this->setPosition(point);
	sprite->runAction(Sequence::create(
		CallFuncN::create(CC_CALLBACK_0(VioletTotem::boom,this)),
		Animate::create(AnimationCache::getInstance()->getAnimation("TotemTower_VioletTotem")),
		CallFuncN::create(CC_CALLBACK_0(VioletTotem::removeBullet,this)),NULL));
}

void VioletTotem::boom()
{
	auto instance = GameManager::getInstance();
  
	auto bombPostion = this->getPosition() + this->getParent()->getPosition();

	auto monsterVector = instance->monsterVector;

	for (int j = 0; j < monsterVector.size(); j++)
	{
		auto monster = monsterVector.at(j);
		auto monsterPosition = monster->baseSprite->getPosition();

		if(monster!=NULL && bombPostion.distance(monsterPosition)<= 50 && monster->getAttackBySoldier())
		{
			monster->slowRunSpeed(3.0f,10);
		}		
	}	
}

void VioletTotem::removeBullet()
{
	this->removeFromParent();
}