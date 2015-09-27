#include "LoadingScene.h"
#include "SimpleAudioEngine.h" 
#include "WelcomeScene.h"
#include "MyAnimation.h"

using namespace CocosDenshion;
USING_NS_CC;


Scene* LoadingScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = LoadingScene::create();

    scene->addChild(layer);

    return scene;
}

bool LoadingScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	numberOfLoadedRes = 0;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto back = Sprite::create("Default@2x.png");
	back->setRotation(-90.0f);
	back->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	addChild(back);
	schedule(schedule_selector(LoadingScene::logic));
	return true;
}

void LoadingScene::loadSouce()
{
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/savage_music_theme.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/savage_music_desert_battle.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/Map_Theme_1.wav");

	SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Sound_GUIButtonCommon.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Sound_GUIOpenTowerMenu.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("sound/GUITransitionClose.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/GUITransitionOpen.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("sound/Archer_Ready.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Artillery_Ready.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Mage_Ready.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Barrack_Ready.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("sound/Sound_WaveIncoming.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Sound_WinStars.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Sound_LooseLife.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Sound_NextWaveReady.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Sound_TowerBuilding.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Sound_TowerOpenDoor.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Sound_TowerSell.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Sound_TowerUpgrade.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Sound_VictoryCheer.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("sound/Sound_ArrowHit2.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Sound_ArrowHit3.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Sound_ArrowRelease3.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Sound_ArrowRelease2.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Sound_Bomb1.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Sound_MageShot.wav");
	
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Sound_QuestCompleted.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Sound_QuestFailed.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("sound/Sound_FireballUnleash.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Sound_FireballHit.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("sound/Archer_Taunt1.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Archer_Taunt2.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Barrack_Taunt1.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Barrack_Taunt2.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Mage_Taunt1.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Mage_Taunt2.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Barrack_Move.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Artillery_Taunt1.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Artillery_Taunt2.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("sound/crossbow_eagle.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/crossbow_multishot.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/crossbow_taunt_ready.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("sound/axlethrower_totem_vanish.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/axlethrower_totem_weakness.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/axlethrower_totem_spirits.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/axlethrower_taunt_totem1.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("sound/dwaarp_attack.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/dwaarp_drillIn.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/dwaarp_drillOut.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/dwaarp_lavaSmash.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("sound/mecha_dropoil.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/mecha_spawn.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/mecha_taunt_ready.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/mecha_walk.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("sound/archmage_attack.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/archmage_precharge.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/archmage_taunt_ready.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/archmage_twister.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("sound/necromancer_attack.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/necromancer_deathknight_taunt_2.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/necromancer_taunt_dknight.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/necromancer_taunt_ready.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("sound/assassin_taunt_ready.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("sound/Reinforcements_Event2.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("sound/inapp_cash.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/inapp_freeze.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/inapp_hearts.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("sound/Sound_RallyPointPlaced.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("sound/earthquake_taunt_ready.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("sound/boss_efreeti_clapping.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/boss_efreeti_death.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/boss_efreeti_evillaugh.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("sound/boss_mono_chestdrum.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/boss_mono_chimps_1.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/boss_mono_chimps_2.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/boss_mono_chimps_3.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/boss_mono_death.wav");

	numberOfLoadedRes++;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainmenu_spritesheet_32_1-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainmenu_spritesheet_32_2-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_16_a-hd.plist"); 
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ingame_gui-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common_spritesheet_16_a_2-hd.plist"); 
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_16_a_3-hd.plist"); 
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_32_2-hd.plist");  
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_16_na-hd.plist"); 
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_32-hd.plist"); 
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("towers-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common_spritesheet_16_na_2_IPAD2-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common_spritesheet_32-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gui_menu_sprite_campaign_32-hd.plist"); 
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gui_menu_sprite_iron_32-hd.plist"); 
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gui_menu_sprite_heroic_32-hd.plist"); 
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common_spritesheet_16_na-hd.plist"); 
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_16_na_2-hd.plist"); 
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("cinematics_comic1-hd.plist"); 
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies_desert_3-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies_desert-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies_jungle-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies_jungle_2-hd.plist");
	/*SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies_underground-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies_underground_2-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies_underground_3-hd.plist");*/

	MyAnimation::getInstance()->init_jungle();
	MyAnimation::getInstance()->init_desert();
	//MyAnimation::getInstance()->init_underground();
	MyAnimation::getInstance()->init();
	numberOfLoadedRes++;
}

void LoadingScene::logic(float dt)
{
	if(numberOfLoadedRes == 0)
	{
		loadSouce();
	}
    if (numberOfLoadedRes == 2)
    {
		auto scene = WelcomeScene::createScene();
		Director::getInstance()->runWithScene(scene);
    }
}