#include "WaveFlag.h"

bool WaveFlag::WaveFlagInit()
{
	if (!Sprite::init())
	{
		return false;
	}
	waveProgressTimer = ProgressTimer::create(Sprite::createWithSpriteFrameName("waveFlag_0003.png"));
	waveProgressTimer->setType(ProgressTimer::Type::RADIAL);
	auto flag = Sprite::createWithSpriteFrameName("waveFlag_0001.png");
	flag->setPosition(Point(waveProgressTimer->getContentSize().width/2,waveProgressTimer->getContentSize().height/2));
	selected = Sprite::createWithSpriteFrameName("waveFlag_selected.png");
	selected->setPosition(Point(waveProgressTimer->getContentSize().width/2,waveProgressTimer->getContentSize().height/2));
	waveProgressTimer->addChild(flag);
	waveProgressTimer->addChild(selected);
	selected->setVisible(false);
	addChild(waveProgressTimer);
	setScale(0.8f);
	setVisible(false);
	isShown = false;
	return true;
}

void WaveFlag::startRespiration(float dt)
{
	waveProgressTimer->setPercentage(percentage);
	runAction(Sequence::create(ScaleTo::create(0.25f,0.6f,0.6f),ScaleTo::create(0.25f,0.8f,0.8f),NULL));
	percentage = percentage + 2.5f;
	if(percentage >100){
		isShown = false;
		setVisible(false);
		unschedule(schedule_selector(WaveFlag::startRespiration));
	}
}

void WaveFlag::stopRespiration()
{
	waveProgressTimer->setPercentage(100);
	isShown = false;
	setVisible(false);
	unschedule(schedule_selector(WaveFlag::startRespiration));
}

void WaveFlag::restartWaveFlag()
{
	isShown = true;
	setVisible(true);
	waveProgressTimer->setPercentage(0);
	percentage = 0;
	schedule(schedule_selector(WaveFlag::startRespiration),0.5f);
}

float WaveFlag::getWavePercentage()
{
	return waveProgressTimer->getPercentage();
}

void WaveFlag::setWavePercentage(float per)
{
	 waveProgressTimer->setPercentage(per);
}

void WaveFlag::setSelected()
{
	if(selected->isVisible()){
		selected->setVisible(false);
	}else{
		selected->setVisible(true);
	}
}

WaveFlag* WaveFlag::createWaveFlag()
{
	auto waveFlag = new WaveFlag();
 
	if (waveFlag && waveFlag->WaveFlagInit())
    {
        waveFlag->autorelease();
        return waveFlag;
    }
    CC_SAFE_DELETE(waveFlag);
    return NULL;
}