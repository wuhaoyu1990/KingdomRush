#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

class SoundManager
{
public:
	static void playClickEffect();
	static void playIncomingWave();
	static void playNextWaveReady();
	
	//ÒôÐ§
	static void playTowerMenu();
	static void playShipOpen();
	static void playWinStars();
	//·ÀÓùËþ
	static void playTowerBuilding();
	static void playTowerUpdate();
	static void playTowerSell();
	//Ò°ÈËËþ
	static void playTotemReady();
	static void playTotemShot();
	static void playTotemSpirits();
	static void playTotemWeakness();
	//¼ýËþ
	static void playArrowShoot1();
	static void playArrowShoot2();
	static void playArrowRelease();
	static void playArcherReady();
	static void playArcher2Ready();
	static void playArcher3Ready();
	//åóËþ
	static void playCrossbowReady();
	static void playCrossbowMultishot();
	static void playCrossbowEagle();
	//µØÕðËþ
	static void playEarthquakeReady();
	static void playEarthquakeHit();
	static void playEarthquakeDrillin();
	static void playEarthquakeDrillOut();
	static void playEarthquakeLava();
	//»úÆ÷ÈË
	static void playMechReady();
	static void playMechWalk();
	static void playMechShit();
	static void playMechLoading();
	//ÅÚËþ
	static void playArtilleryReady();
	static void playArtillery2Ready();
	static void playArtillery3Ready();
	static void playBomb();
	//±øÓªËþ
	static void playRallyPointPlaced();
	static void playBarrackReady();
	static void playBarrack2Ready();
	static void playBarrack3Ready();
	static void playBarrackOpendoor();
	static void playBarrackMove();
	static void playAssassinMove();
	//Áú¾í·çËþ
	static void playArchmageReady();
	static void playArchmageShot();
	static void playArchmageTwister();
	static void playArchmagePrecharge();
	//»ù´¡Ä§·¨Ëþ
	static void playMageTowerReady();
	static void playMageTower2Ready();
	static void playMageTower3Ready();
	static void playMageTowerShot();
	//NEC
	static void playNecTowerReady();
	static void playDKReady();
	static void playNecShot();
	static void playDKTaunt();
	//ÔÉÊ¯
	static void playFireballHit();
	static void playFireballUnleash();
	//¹Ø¿¨½áÊø
	static void playQuestCompleted();
	static void playQuestFailed();
	//¼¼ÄÜ
	static void playReinforcement();
	static void playCash();
	static void playFreeze();
	static void playHearts();
	//ÐÉÐÉBOSS
	static void playChestdrum();
	static void playChimps_1();
	static void playChimps_2();
	static void playChimps_3();
	static void playMonoDeath();
public:
	static void playWelcomeBackMusic();
	static void playJungleBattle();
	static void playDesertBattle();
	static void playGameTheme1();
public:
	//BOSS 100
	static void playEfreetiLaugh();
	static void playEfreetiClap();
	static void playEfreetiDeath();
private:
	static bool cheakEffectState();
};

#endif