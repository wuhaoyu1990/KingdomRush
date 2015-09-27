#ifndef _TRANSITION_GAME_H_
#define _TRANSITION_GAME_H_
#include <cocos2d.h>
USING_NS_CC;

class TransitionGame : public TransitionScene
{
public:
    TransitionGame();
    virtual ~TransitionGame();
    void onEnter();
    static TransitionGame *create(float t, Scene *scene);
	static TransitionGame *createWithRenderTexture(float t, Scene *scene,RenderTexture *sqr);
private:
	void initRenderTexture(RenderTexture *sqr);
    void LRFinish(void);
	void OnSencondActionFinish(void);
private:
    int m_FinishCnt;
};
#endif