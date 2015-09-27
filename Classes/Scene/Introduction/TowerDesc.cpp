
#include "TowerDesc.h"

USING_NS_CC;

TowerDesc* TowerDesc::createTowerDesc(std::string name)
{
	auto towerDesc = new TowerDesc();
	if(towerDesc && towerDesc->myinit(name))
	{
		towerDesc->autorelease();
		return towerDesc;
	}
	CC_SAFE_DELETE(towerDesc);
	return NULL;
}

bool TowerDesc::myinit(std::string name)
{
	if(!Sprite::init())
	{
		return false;
	}
	towerDescPic = Sprite::createWithSpriteFrameName(name);
	addChild(towerDescPic);

	return true;
}

void TowerDesc::setData(
				Sprite* towerDescPic,
				
				std::string towerThumbFileName,
				std::string towerDescFileName,
				int num,
				std::string towerName,

				std::string attackSpeed,
				std::string attackValue,
				std::string attackRange,

				std::string note){
	//³õÊ¼»¯
	this->towerDescPic = towerDescPic;

	this->towerThumbFileName = towerThumbFileName;
	this->towerDescFileName = towerDescFileName;
	this->num = num;

	this->towerName = towerName;

	this->attackSpeed = attackSpeed;
	this->attackValue  = attackValue;
	this->attackRange = attackRange;

	this->note = note;
}
