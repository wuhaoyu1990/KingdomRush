#include "BaseArrowTower.h"
#include "UpdatePanleLayer.h"
#include "BaseMap.h"
#include "GameManager.h"

void BaseArrowTower::initTower(int level)
{
	towerBase = Sprite::createWithSpriteFrameName(String::createWithFormat("archer_tower_000%d.png",level)->getCString());

	shooter_1 = Sprite::createWithSpriteFrameName(String::createWithFormat("tower_archer_lvl%d_shooter_0001.png",level)->getCString());
	shooter_2 = Sprite::createWithSpriteFrameName(String::createWithFormat("tower_archer_lvl%d_shooter_0001.png",level)->getCString());

	shooter_1->setPosition(Point(towerBase->getContentSize().width/2-10,towerBase->getContentSize().height/2+18));
	shooter_2->setPosition(Point(towerBase->getContentSize().width/2+10,towerBase->getContentSize().height/2+18));

	towerBase->addChild(shooter_1);
	towerBase->addChild(shooter_2);

	addChild(towerBase);

	shootTag = RIGHT_ARCHER_SHOT;
}

void BaseArrowTower::addTerrain()
{
	terrain = Sprite::createWithSpriteFrameName("terrain_archer_0004.png");
	terrain->setAnchorPoint(Point(0.5,1));
	addChild(terrain,-1);
}

Bullet* BaseArrowTower::ArrowTowerBullet()
{
    return NULL;
}

void BaseArrowTower::shoot(float dt)
{
    auto instance = GameManager::getInstance();
    //auto bulletVector = instance->bulletVector;
	checkNearestMonster();
	char temp1[20]; 
	sprintf(temp1, "level%d_shoot_down", level); 
	char temp2[20]; 
	sprintf(temp2, "level%d_shoot_top", level); 
	if(nearestMonster!=NULL && nearestMonster->getCurrHp() > 0 )
    {
		auto currBullet = ArrowTowerBullet();
		//instance->bulletVector.pushBack(currBullet);

		Point shootVector = nearestMonster->baseSprite->getPosition() - this->getParent()->getPosition();


		float startAngle = currBullet->getRotation();
		float endAngle = 0;

		auto pVectr = currBullet->getPosition()-shootVector;
        float angleRadians=atan(pVectr.y/pVectr.x);
        float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
		
		if(shootVector.x - currBullet->getPosition().x<=0)//向左攻击
		{
			startAngle = startAngle + abs(angleDegrees);//初始弓箭角度
			endAngle = -90;//结束角度
			if(shootTag == 1)//轮到1号弓箭手
			{
				currBullet->setPosition(Point(0,30));//子弹设置在弓箭手所在位置	
				shooter_1->setFlippedX(true);
				if(shootVector.y - currBullet->getPosition().y<=0)
				{
					//攻击动画
					shooter_1->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(temp1)));
				}else{
					shooter_1->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(temp2)));
				}
				shootTag = 2;
			}
			else//轮到2号弓箭手
			{
				currBullet->setPosition(Point(10,30));		
				shooter_2->setFlippedX(true);
				if(shootVector.y - currBullet->getPosition().y<=0)
				{
					shooter_2->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(temp1)));
				}else{
					shooter_2->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(temp2)));
				}
				shootTag = 1;
			}
		}else
		{
			startAngle = startAngle - abs(angleDegrees);
			endAngle = 270;
			if(shootTag == 1)
			{
				currBullet->setPosition(Point(0,30));		
				shooter_1->setFlippedX(false);
				if(shootVector.y - currBullet->getPosition().y<=0)
				{
					shooter_1->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(temp1)));
				}else{
					shooter_1->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(temp2)));
				}
				shootTag = 2;
			}
			else
			{
				currBullet->setPosition(Point(10,30));		
				shooter_2->setFlippedX(false);
				if(shootVector.y - currBullet->getPosition().y<=0)
				{
					shooter_2->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(temp1)));
				}else{
					shooter_2->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(temp2)));
				}
				shootTag = 1;
			}
		}
		//弧线
		ccBezierConfig bezier;
		if(shootTag == 1)
			SoundManager::playArrowShoot1();
		else
			SoundManager::playArrowShoot2();
		//两个控制点
		bezier.controlPoint_1 = Point(currBullet->getPosition().x,currBullet->getPosition().y+200); 
		bezier.controlPoint_2 = Point(shootVector.x,shootVector.y+200);; 
		bezier.endPosition = shootVector;

		auto action = Spawn::create(BezierTo::create(0.5f, bezier),RotateTo::create(0.5f,endAngle),NULL);
		//攻击属性给弓箭
		currBullet->setBulletAction(action);
		currBullet->shoot();
		currBullet = NULL;
	}
}