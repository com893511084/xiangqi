#ifndef  __SCENESTART_H__
#define  __SCENESTART_H__

#include "cocos2d.h"
USING_NS_CC;

class SceneStart : public CCLayer
{
public:
    static cocos2d::Scene* scene();

    bool init();
    
    CREATE_FUNC(SceneStart);

	CCSprite *_bkg1;
	CCSprite *_bkg2;

	bool color;

	bool onTouchBegan(CCTouch *, CCEvent *);
	void onTouchEnded(CCTouch *touch, CCEvent *);

	void update(float dt);

};

#endif 