#include "TotemTower.h"
#include "GameManager.h"
#include "TotemAxe.h"
#include "RedTotem.h"
#include "VioletTotem.h"
#include "SimplePanleLayer.h"
#include "BaseMap.h"

bool TotemTower::init()
{
	if(!BaseArrowTower::init()){
		return false;
	}
	addTerrain();
	setTowerType(TOTEMTOWER);
	setScope(200.0f);
	towerBase = Sprite::createWithSpriteFrameName("TotemTower.png");

	shooter_1 = Sprite::createWithSpriteFrameName("TotemTower_Shooter_0001.png");
	shooter_2 = Sprite::createWithSpriteFrameName("TotemTower_Shooter_0001.png");

	shooter_1->setPosition(Point(towerBase->getContentSize().width/2-10,towerBase->getContentSize().height/2+28));
	shooter_2->setPosition(Point(towerBase->getContentSize().width/2+10,towerBase->getContentSize().height/2+28));

	towerBase->addChild(shooter_1);
	towerBase->addChild(shooter_2);

	addChild(towerBase);

	shootTag = RIGHT_ARCHER_SHOT;

	setListener();
	eyesDown = Sprite::createWithSpriteFrameName("TotemTower_EyesDown_0001.png");
	eyesDown->setPosition(Point(0,-25));
	addChild(eyesDown);
	totemCD = true;
	eyesDown->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("TotemTower_EyesDown"))));
	schedule(schedule_selector(TotemTower::shoot), 1.0f);
	schedule(schedule_selector(TotemTower::TotemCD), 5.0f);
	SoundManager::playTotemReady();
	return true;
}


void TotemTower::showUpdateMenu()
{
	auto simplePanleLayer = SimplePanleLayer::create();
	simplePanleLayer->setTag(myTerrain->getTag()+100);
	simplePanleLayer->setTower(this);
	simplePanleLayer->setPosition(this->getParent()->getPosition());
	static_cast<BaseMap*>(this->getParent()->getParent())->mTouchLayer->addChild(simplePanleLayer);
	simplePanleLayer->inAnimation();
	isUpdateMenuShown = true;
}

void TotemTower::TotemCD(float dt)
{
	totemCD = true;
}

Bullet* TotemTower::ArrowTowerBullet()
{
	auto bullet = TotemAxe::create();
	bullet->setRotation(90.0f);
	bullet->setMaxForce(24);
	this->getParent()->addChild(bullet);
    return bullet;
}

void TotemTower::checkNearestMonster()
{
	monstersCount = 0;
    auto instance = GameManager::getInstance();
    auto monsterVector = instance->monsterVector;
    
	auto currMinDistant = this->scope;
    
	BaseMonster *monsterTemp = NULL;
	for(int i = 0; i < monsterVector.size(); i++)
	{
		auto monster = monsterVector.at(i);
		double distance = this->getParent()->getPosition().getDistance(monster->baseSprite->getPosition());

		if (distance < currMinDistant && monster->getAttackByTower()) {
			currMinDistant = distance;
            monsterTemp = monster;
			monstersCount++;
		}
	}
    nearestMonster = monsterTemp;
}

void TotemTower::shoot(float dt)
{
    auto instance = GameManager::getInstance();
	checkNearestMonster();
	if(nearestMonster!=NULL && nearestMonster->getCurrHp() > 0 )
    {
		if(monstersCount <= 5){
		auto currBullet = ArrowTowerBullet();

		Point shootVector = nearestMonster->baseSprite->getPosition() - this->getParent()->getPosition();
		if(totemCD){
			SoundManager::playTotemSpirits();
			auto redTotem = RedTotem::create();
			this->getParent()->addChild(redTotem);
			redTotem->shoot(nearestMonster->baseSprite->getPosition() - this->getParent()->getPosition() + Point(20,20));

			auto violetTotem = VioletTotem::create();
			this->getParent()->addChild(violetTotem);
			violetTotem->shoot(nearestMonster->baseSprite->getPosition() - this->getParent()->getPosition()- Point(20,20));
			totemCD = false;
		}
		if(shootVector.x - currBullet->getPosition().x<=0)//Ïò×ó¹¥»÷
		{
			if(shootTag == 1)//ÂÖµ½1ºÅ¹­¼ýÊÖ
			{
				currBullet->setPosition(Point(0,30));//×Óµ¯ÉèÖÃÔÚ¹­¼ýÊÖËùÔÚÎ»ÖÃ	
				shooter_1->setFlippedX(true);
				if(shootVector.y - currBullet->getPosition().y<=0)
				{
					//¹¥»÷¶¯»­
					shooter_1->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("TotemTower_Shooter_down")));
				}else{
					shooter_1->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("TotemTower_Shooter_up")));
				}
					shootTag = 2;
				}
			else//ÂÖµ½2ºÅ¹­¼ýÊÖ
			{
				currBullet->setPosition(Point(10,30));		
				shooter_2->setFlippedX(true);
				if(shootVector.y - currBullet->getPosition().y<=0)
				{
					shooter_2->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("TotemTower_Shooter_down")));
				}else{
					shooter_2->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("TotemTower_Shooter_up")));
				}
				shootTag = 1;
			}
		}else
		{
			if(shootTag == 1)
			{
				currBullet->setPosition(Point(0,30));		
				shooter_1->setFlippedX(false);
				if(shootVector.y - currBullet->getPosition().y<=0)
				{
					shooter_1->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("TotemTower_Shooter_down")));
				}else{
					shooter_1->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("TotemTower_Shooter_up")));
				}
				shootTag = 2;
			}
			else
			{
				currBullet->setPosition(Point(10,30));		
				shooter_2->setFlippedX(false);
				if(shootVector.y - currBullet->getPosition().y<=0)
				{
					shooter_2->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("TotemTower_Shooter_down")));
				}else{
					shooter_2->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("TotemTower_Shooter_up")));
				}
				shootTag = 1;
			}
		}
		//»¡Ïß
		SoundManager::playTotemShot();
		auto action = Spawn::create(MoveTo::create(0.5f, shootVector),RotateTo::create(0.5f,1080.0f),NULL);
		//¹¥»÷ÊôÐÔ¸ø¹­¼ý
		currBullet->setBulletAction(action);
		currBullet->shoot();
		currBullet = NULL;			
		}
	}
}