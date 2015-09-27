#include "SoundManager.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h" 

using namespace CocosDenshion;
USING_NS_CC;

bool SoundManager::cheakEffectState()
{
	if(UserDefault::getInstance()->getIntegerForKey("backeffect",1)==1)
		return true;
	else
		return false;
}

void SoundManager::playEfreetiLaugh()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/boss_efreeti_evillaugh.wav");
}

void SoundManager::playWinStars()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Sound_WinStars.wav");
}

void SoundManager::playEfreetiDeath()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/boss_efreeti_death.wav");
}

void SoundManager::playEfreetiClap()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/boss_efreeti_clapping.wav");
}

void SoundManager::playClickEffect()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Sound_GUIButtonCommon.wav");
}

void SoundManager::playWelcomeBackMusic()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/savage_music_theme.wav");
	if(UserDefault::getInstance()->getIntegerForKey("backmusic",1)==0)
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void SoundManager::playDesertBattle()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/savage_music_desert_battle.wav");
	if(UserDefault::getInstance()->getIntegerForKey("backmusic",1)==0)
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void SoundManager::playJungleBattle()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/savage_music_jungle_battle.wav");
	if(UserDefault::getInstance()->getIntegerForKey("backmusic",1)==0)
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void SoundManager::playGameTheme1()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/Map_Theme_1.wav");
	if(UserDefault::getInstance()->getIntegerForKey("backmusic",1)==0)
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void SoundManager::playNextWaveReady()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Sound_NextWaveReady.wav");
}


void SoundManager::playIncomingWave()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Sound_WaveIncoming.wav");
}

void SoundManager::playArrowShoot1()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Sound_ArrowHit2.wav");
}

void SoundManager::playArrowShoot2()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Sound_ArrowHit3.wav");
}

void SoundManager::playTowerUpdate()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Sound_TowerUpgrade.wav");
}

void SoundManager::playTowerSell()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Sound_TowerSell.wav");
}

void SoundManager::playShipOpen()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/ship_path_break.wav");
}

void SoundManager::playTowerBuilding()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Sound_TowerBuilding.wav");
}

void SoundManager::playArcherReady()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Archer_Ready.wav");
}

void SoundManager::playTowerMenu()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Sound_GUIOpenTowerMenu.wav");
}

void SoundManager::playArcher2Ready()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Archer_Taunt1.wav");
}

void SoundManager::playArcher3Ready()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Archer_Taunt2.wav");
}

void SoundManager::playCrossbowReady()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/crossbow_taunt_ready.wav");
}

void SoundManager::playCrossbowMultishot()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/crossbow_multishot.wav");
}

void SoundManager::playCrossbowEagle()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/crossbow_eagle.wav");
}

void SoundManager::playTotemReady()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/axlethrower_taunt_totem1.wav");
}

void SoundManager::playTotemShot()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/axlethrower_totem_vanish.wav");
}

void SoundManager::playTotemSpirits()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/axlethrower_totem_spirits.wav");
}

void SoundManager::playTotemWeakness()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/axlethrower_totem_weakness.wav");
}

void SoundManager::playEarthquakeReady()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/earthquake_taunt_ready.wav");
}

void SoundManager::playEarthquakeHit()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/dwaarp_attack.wav");
}

void SoundManager::playEarthquakeDrillin()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/dwaarp_drillIn.wav");
}

void SoundManager::playEarthquakeDrillOut()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/dwaarp_drillOut.wav");
}

void SoundManager::playEarthquakeLava()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/dwaarp_lavaSmash.wav");
}

void SoundManager::playMechReady()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/mecha_taunt_ready.wav");
}


void SoundManager::playMechWalk()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/mecha_walk.wav");
}


void SoundManager::playMechShit()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/mecha_dropoil.wav");
}

void SoundManager::playMechLoading()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/mecha_spawn.wav");
}

void SoundManager::playArtilleryReady()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Artillery_Ready.wav");
}


void SoundManager::playArtillery2Ready()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Artillery_Taunt1.wav");
}


void SoundManager::playArtillery3Ready()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Artillery_Taunt2.wav");
}

void SoundManager::playBarrackReady()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Barrack_Ready.wav");
}

void SoundManager::playBarrack2Ready()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Barrack_Taunt1.wav");
}

void SoundManager::playBarrack3Ready()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Barrack_Taunt2.wav");
}

void SoundManager::playBarrackOpendoor()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Sound_TowerOpenDoor.wav");
}

void SoundManager::playBarrackMove()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Barrack_Move.wav");
}

void SoundManager::playArchmageReady()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/archmage_taunt_ready.wav");
}

void SoundManager::playArchmageShot()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/archmage_attack.wav");
}

void SoundManager::playArchmageTwister()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/archmage_twister.wav");
}

void SoundManager::playArchmagePrecharge()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/archmage_precharge.wav");
}

void SoundManager::playMageTowerReady()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Mage_Ready.wav");
}

void SoundManager::playMageTower2Ready()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Mage_Taunt1.wav");
}

void SoundManager::playMageTower3Ready()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Mage_Taunt2.wav");
}

void SoundManager::playMageTowerShot()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Sound_MageShot.wav");
}

void SoundManager::playNecTowerReady()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/necromancer_taunt_ready.wav");
}

void SoundManager::playDKReady()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/necromancer_taunt_dknight.wav");
}

void SoundManager::playNecShot()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/necromancer_attack.wav");
}

void SoundManager::playDKTaunt()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/necromancer_deathknight_taunt_2.wav");
}

void SoundManager::playArrowRelease()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Sound_ArrowRelease2.wav");
}

void SoundManager::playBomb()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Sound_Bomb1.wav");
}

void SoundManager::playFireballHit()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Sound_FireballHit.wav");
}

void SoundManager::playFireballUnleash()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Sound_FireballUnleash.wav");
}

void SoundManager::playQuestCompleted()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Sound_QuestCompleted.wav");
}

void SoundManager::playQuestFailed()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Sound_QuestFailed.wav");
}

void SoundManager::playAssassinMove()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/assassin_taunt_ready.wav");
}

void SoundManager::playReinforcement()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Reinforcements_Event2.wav");
}

void SoundManager::playCash()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/inapp_cash.wav");
}

void SoundManager::playFreeze()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/inapp_freeze.wav");
}

void SoundManager::playHearts()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/inapp_hearts.wav");
}

void SoundManager::playRallyPointPlaced()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Sound_RallyPointPlaced.wav");
}

void SoundManager::playChestdrum()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/boss_mono_chestdrum.wav");
}

void SoundManager::playChimps_1()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/boss_mono_chimps_1.wav");
}

void SoundManager::playChimps_2()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/boss_mono_chimps_2.wav");
}

void SoundManager::playChimps_3()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/boss_mono_chimps_3.wav");
}

void SoundManager::playMonoDeath()
{
	if(cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/boss_mono_death.wav");
}
