#include "SceneStart.h"
#include "SceneGane.h"


Scene* SceneStart::scene()
{
    auto scene = Scene::create();
    
    auto layer = SceneStart::create();

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool SceneStart::init()
{
	CCLayer::init();
	//�õ����ڴ�С

	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	
	CCSprite *bkg1 = CCSprite::create("bkg1.png");
	//����bkg1��λ��
	bkg1->setPosition(ccp(winsize.width / 2 - 200, winsize.height/2));
	bkg1->setScale(2);
	addChild(bkg1);

	CCSprite *bkg2 = CCSprite::create("bkg2.png");
	//����bkg2��λ��
	bkg2->setPosition(ccp(winsize.width / 2 + 200, winsize.height/2));
	addChild(bkg2);
	bkg2->setScale(2);

	_bkg1 = bkg1;
	_bkg2 = bkg2;


	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);

	return true;
}

bool SceneStart::onTouchBegan(CCTouch *, CCEvent *)
{
	return true;
}
void SceneStart::onTouchEnded(CCTouch *touch, CCEvent *)
{

	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pt = touch->getLocation();
	bool open = false;
	if(_bkg1->boundingBox().containsPoint(pt))
	{
		//ѡ���ɫ Ϊfalse
		color = false;
		open = true;
	}
	else if(_bkg2->boundingBox().containsPoint(pt))
	{
	    //ѡ���ɫ Ϊtrue
		color = true;
		open = true;
	}
	if(open == true)
	{
		CCMoveBy *move1 = CCMoveBy::create(1, ccp(+200, 0));
		CCMoveBy *move2 = CCMoveBy::create(1, ccp(-200, 0));
		CCRotateBy *rota1 = CCRotateBy::create(1, 360);
		CCRotateBy *rota2 = CCRotateBy::create(1, -360);

		CCSpawn *spawn1 = CCSpawn::create(move1, rota1, NULL);
		CCSpawn *spawn2 = CCSpawn::create(move2, rota2, NULL);

		_bkg1->runAction(spawn1);
		_bkg2->runAction(spawn2);

		//������ʱ��
		scheduleUpdate();
	}

}
void SceneStart::update(float)
{
	float x1 = _bkg1->getPositionX();
	float x2 = _bkg2->getPositionX();
	if(abs(x1 - x2) < _bkg1->getContentSize().width+50)
	{
		CCDirector::sharedDirector()->replaceScene(SceneGane::scene(color));
	}
}