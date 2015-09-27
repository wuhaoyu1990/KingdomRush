#include "Shit.h"
#include "GameManager.h"

bool Shit::init()
{
	if(!Bullet::init()){
		return false;
	}
	sprite = Sprite::createWithSpriteFrameName("Mecha_Shit.png");
	addChild(sprite);
	return true;
}

void Shit::shoot(){
	auto instance = GameManager::getInstance();

	auto monsterVector = instance->monsterVector;

	for (int j = 0; j < monsterVector.size(); j++)
	{
		auto monster = monsterVector.at(j);
		auto monsterPosition = monster->baseSprite->getPosition();
		if(monster!=NULL && (this->getPosition()+this->getParent()->getPosition()).distance(monsterPosition)<= 100 && monster->getAttackByTower())
		{
			monster->slowRunSpeed(3,15);
		}
	}
	removeBullet();
}
void Shit::removeBullet()
{
	sprite->runAction(Sequence::create(
		DelayTime::create(2.0f),
		FadeOut::create(1.0f),
		CallFuncN::create(CC_CALLBACK_0(Shit::removeFromParent, this)), 
		NULL));
}