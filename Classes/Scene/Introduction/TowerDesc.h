#include "cocos2d.h"
#include <string>

USING_NS_CC;

class TowerDesc : public Sprite{

public:
	virtual bool myinit(std::string name);
	static TowerDesc* createTowerDesc(std::string name);
	CREATE_FUNC(TowerDesc);

	Sprite* towerDescPic;

	std::string towerThumbFileName;
	std::string towerDescFileName;

	int num;
	std::string towerName;

	std::string attackSpeed;
	std::string attackValue;
	std::string attackRange;

	std::string note;

	//·½·¨
	void setData(
				Sprite* towerDescPic,
				std::string towerThumbFileName,
				std::string towerDescFileName,
				int num,
				std::string towerName,

				std::string attackSpeed,
				std::string attackValue,
				std::string attackRange,

				std::string note
				);

};