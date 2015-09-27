#include "CossbowHunterTower.h"
#include "GameManager.h"
#include "Arrow.h"
#include "SimplePanleLayer.h"
#include "BaseMap.h"

bool CossbowHunterTower::init()
{
	if(!BaseArrowTower::init()){
		return false;
	}
	setTowerType(COSSBOW);
	addTerrain();
	setBuildMoney(550);
	setScope(200.0f);
	towerBase = Sprite::createWithSpriteFrameName("CossbowHunter_tower.png");

	shooter_1 = Sprite::createWithSpriteFrameName("CossbowHunter_shooter_0001.png");
	shooter_2 = Sprite::createWithSpriteFrameName("CossbowHunter_shooter_0001.png");

	shooter_1->setPosition(Point(towerBase->getContentSize().width/2-10,towerBase->getContentSize().height/2+28));
	shooter_2->setPosition(Point(towerBase->getContentSize().width/2+10,towerBase->getContentSize().height/2+28));

	towerBase->addChild(shooter_1);
	towerBase->addChild(shooter_2);

	addChild(towerBase);

	shootTag = RIGHT_ARCHER_SHOT;
	attackCount = 0;
	setListener();
	hawk = Sprite::createWithSpriteFrameName("CossbowHunter_hawk_0001.png");
	hawk->setPosition(Point(0,20));
	addChild(hawk);
	hawk->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("CossbowHunter_hawk"))));
	schedule(schedule_selector(CossbowHunterTower::shoot), 0.5f);
	SoundManager::playCrossbowReady();
	return true;
}

void CossbowHunterTower::showUpdateMenu()
{
	auto simplePanleLayer = SimplePanleLayer::create();
	simplePanleLayer->setTag(myTerrain->getTag()+100);
	simplePanleLayer->setTower(this);
	simplePanleLayer->setPosition(this->getParent()->getPosition());
	static_cast<BaseMap*>(this->getParent()->getParent())->mTouchLayer->addChild(simplePanleLayer);
	simplePanleLayer->inAnimation();
	isUpdateMenuShown = true;
}

Bullet* CossbowHunterTower::ArrowTowerBullet()
{
	auto bullet = Arrow::create();
	bullet->setRotation(90.0f);
	bullet->setMaxForce(24);
	this->getParent()->addChild(bullet);
    return bullet;
}

void CossbowHunterTower::shoot(float dt)
{
    auto instance = GameManager::getInstance();

	checkNearestMonster();
	if(nearestMonster!=NULL && nearestMonster->getCurrHp() > 0 )
    {
		attackCount ++;
		if(attackCount < 3){
			auto currBullet = ArrowTowerBullet();

			Point shootVector = nearestMonster->baseSprite->getPosition() - this->getParent()->getPosition();


			auto position=currBullet->getPosition()-shootVector;
			auto rotation=atan2(position.y,position.x);
			float angleDegrees = CC_RADIANS_TO_DEGREES(rotation);
			currBullet->setRotation(180.0f-angleDegrees);
		
			if(shootVector.x - currBullet->getPosition().x<=0)//Ïò×ó¹¥»÷
			{
				if(shootTag == 1)//ÂÖµ½1ºÅ¹­¼ýÊÖ
				{
					currBullet->setPosition(Point(0,30));//×Óµ¯ÉèÖÃÔÚ¹­¼ýÊÖËùÔÚÎ»ÖÃ	
					shooter_1->setFlippedX(true);
					if(shootVector.y - currBullet->getPosition().y<=0)
					{
						//¹¥»÷¶¯»­
						shooter_1->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("CossbowHunter_shooter_down")));
					}else{
						shooter_1->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("CossbowHunter_shooter_up")));
					}
					shootTag = 2;
				}
				else//ÂÖµ½2ºÅ¹­¼ýÊÖ
				{
					currBullet->setPosition(Point(10,30));		
					shooter_2->setFlippedX(true);
					if(shootVector.y - currBullet->getPosition().y<=0)
					{
						shooter_2->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("CossbowHunter_shooter_down")));
					}else{
						shooter_2->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("CossbowHunter_shooter_up")));
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
						shooter_1->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("CossbowHunter_shooter_down")));
					}else{
						shooter_1->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("CossbowHunter_shooter_up")));
					}
					shootTag = 2;
				}
				else
				{
					currBullet->setPosition(Point(10,30));		
					shooter_2->setFlippedX(false);
					if(shootVector.y - currBullet->getPosition().y<=0)
					{
						shooter_2->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("CossbowHunter_shooter_down")));
					}else{
						shooter_2->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("CossbowHunter_shooter_up")));
					}
					shootTag = 1;
				}
			}
			//»¡Ïß
			if(shootTag == 1)
				SoundManager::playArrowShoot1();
			else
				SoundManager::playArrowShoot2();
			auto action = Spawn::create(MoveTo::create(0.3f, shootVector),NULL);
			//¹¥»÷ÊôÐÔ¸ø¹­¼ý
			currBullet->setBulletAction(action);
			currBullet->shoot();
			currBullet = NULL;
		}else{
			Point shootVector = nearestMonster->baseSprite->getPosition() - this->getParent()->getPosition();
			if(shootVector.x - this->getParent()->getPosition().x<=0)//Ïò×ó¹¥»÷
			{
				if(shootTag == 1)//ÂÖµ½1ºÅ¹­¼ýÊÖ
				{
					shooter_1->setFlippedX(false);
					if(shootVector.y - this->getParent()->getPosition().y<=0)
					{
						//¹¥»÷¶¯»­
						shooter_1->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("CossbowHunter_shooter_skill_down")));
					}else{
						shooter_1->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("CossbowHunter_shooter_skill_up")));
					}
					shootTag = 2;
				}
				else//ÂÖµ½2ºÅ¹­¼ýÊÖ
				{	
					shooter_2->setFlippedX(false);
					if(shootVector.y - this->getParent()->getPosition().y<=0)
					{
						shooter_2->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("CossbowHunter_shooter_skill_down")));
					}else{
						shooter_2->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("CossbowHunter_shooter_skill_up")));
					}
					shootTag = 1;
				}
			}else
			{
				if(shootTag == 1)
				{	
					shooter_1->setFlippedX(true);
					if(shootVector.y - this->getParent()->getPosition().y<=0)
					{
						shooter_1->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("CossbowHunter_shooter_skill_down")));
					}else{
						shooter_1->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("CossbowHunter_shooter_skill_up")));
					}
					shootTag = 2;
				}
				else
				{	
					shooter_2->setFlippedX(true);
					if(shootVector.y - this->getParent()->getPosition().y<=0)
					{
						shooter_2->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("CossbowHunter_shooter_skill_down")));
					}else{
						shooter_2->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("CossbowHunter_shooter_skill_up")));
					}
					shootTag = 1;
				}
			}

			auto currHp = nearestMonster->getCurrHp();
			SoundManager::playCrossbowMultishot();
			currHp =  currHp - 100;
                
			if(currHp <= 0){
				currHp = 0;
			}
			nearestMonster->setCurrHp( currHp );

			nearestMonster->getHpBar()->setPercentage((currHp/nearestMonster->getMaxHp())*100);
			nearestMonster->getHurt();
    
			if(currHp == 0){
				nearestMonster->death();
				instance->monsterVector.eraseObject(nearestMonster);
			}
			attackCount = 0;
		}
	}
}