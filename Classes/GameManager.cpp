#include "GameManager.h"

GameManager* GameManager::instance;

GameManager* GameManager::getInstance()
{
	if (instance == NULL)
		instance = new GameManager();
	return instance;
}

void GameManager::setInstance(int tag)
{
	SLOTNUM = tag;

	sprintf(SLOTX_ISEXIT, "Slot%d", tag); 

	sprintf(LEVELX_ISDOWN, "Slot%d", tag); 
	strcat(LEVELX_ISDOWN,"_Level_%d");

	sprintf(LEVELX_STARNUM, "Slot%d", tag); 
	strcat(LEVELX_STARNUM,"_Level_%d_star");

	sprintf(SLOTX_DOWNCOUNT, "Slot%d_DownCount", tag); 

	sprintf(LEVELX_NEWDOWN, "Slot%d_NewDown", tag); 

	sprintf(SLOTX_STAR, "Slot%d_Star", tag); 

	sprintf(SLOTX_STARLEFT, "Slot%d_StarLeft", tag); 

	sprintf(SLOTX_GEM, "Slot%d_Gem", tag); 

	sprintf(SLOTX_SHOP, "Slot%d", tag); 
	strcat(SLOTX_SHOP,"_Shop_%d");
}

void GameManager::eraseAll()
{
	instance->monsterVector.clear();
    //instance->towerVector.clear();
}