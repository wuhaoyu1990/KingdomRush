
#include "EnemyDesc.h"

USING_NS_CC;

EnemyDesc* EnemyDesc::createEnemyDesc(std::string name)
{
	auto enemyDesc = new EnemyDesc();
	if(enemyDesc && enemyDesc->myinit(name))
	{
		enemyDesc->autorelease();
		return enemyDesc;
	}
	CC_SAFE_DELETE(enemyDesc);
	return NULL;
}

bool EnemyDesc::myinit(std::string name)
{
	if(!Sprite::init())
	{
		return false;
	}
	enemyDescPic = Sprite::createWithSpriteFrameName(name);
	addChild(enemyDescPic);

	return true;
}

void EnemyDesc::setData(
				Sprite* enemyDescPic,
				int num,
				std::string enemyThumbFileName,
				std::string enemyDescFileName,

				std::string enemyName,
				std::string enemyDesc,

				std::string bloodValue,
				std::string attackValue,
				std::string defenseValue,

				std::string magicDefenseValue,
				std::string movementSpeed,
				std::string lifeNumber,
				std::string note){
	//³õÊ¼»¯
	this->enemyDescPic = enemyDescPic;

	this->num = num;

	this->enemyThumbFileName = enemyThumbFileName;
	this->enemyDescFileName = enemyDescFileName;

	this->enemyName = enemyName;
	this->enemyDesc = enemyDesc;

	this->bloodValue = bloodValue;
	this->attackValue  = attackValue;
	this->defenseValue = defenseValue;

	this->magicDefenseValue = magicDefenseValue;
	this->movementSpeed = movementSpeed;
	this->lifeNumber = lifeNumber;
	this->note = note;
}

