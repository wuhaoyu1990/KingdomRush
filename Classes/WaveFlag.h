#ifndef _WAVE_FLAG_H_
#define _WAVE_FLAG_H_

#include "cocos2d.h"

USING_NS_CC;

class WaveFlag : public Sprite
{
public:
	virtual bool WaveFlagInit();
    CREATE_FUNC(WaveFlag);
	static WaveFlag* createWaveFlag();
	float getWavePercentage();
	void restartWaveFlag();
	void stopRespiration();
	void setWavePercentage(float per);
	ProgressTimer* waveProgressTimer;
	Sprite* selected;
	bool isShown;
	void setSelected();
private:
	float percentage;
	void startRespiration(float dt);
};

#endif