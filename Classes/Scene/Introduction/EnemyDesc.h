#include "cocos2d.h"
#include <string>

USING_NS_CC;

class EnemyDesc : public Sprite{

public:
	virtual bool myinit(std::string name);
	static EnemyDesc* createEnemyDesc(std::string name);
	CREATE_FUNC(EnemyDesc);

//private:
	Sprite* enemyDescPic;

	std::string enemyThumbFileName;
	std::string enemyDescFileName;

	int num;
	std::string enemyName;
	std::string enemyDesc;

	std::string bloodValue;
	std::string attackValue;
	std::string defenseValue;

	std::string magicDefenseValue;
	std::string movementSpeed;
	std::string lifeNumber;	

	std::string note;

	//·½·¨
	void setData(
				Sprite* enemyDescPic,

				int num,std::string enemyThumbFileName,std::string enemyDescFileName,

				std::string enemyName,std::string enemyDesc,

				std::string bloodValue,std::string attackValue,std::string defenseValue,

				std::string magicDefenseValue,std::string movementSpeed,std::string lifeNumber,
				
				std::string note);

};