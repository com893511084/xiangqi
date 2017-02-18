#include "SceneGane.h"



SceneGane::SceneGane()
{
}


SceneGane::~SceneGane()
{
	_steps->release();
}

CCScene *SceneGane::scene(bool color)
{
	CCScene *scene = CCScene::create();
	SceneGane *layer = SceneGane::create(color);
	scene->addChild(layer);
	return scene;
}
SceneGane *SceneGane::create(bool color)
{
	SceneGane *cr = new SceneGane();
	cr->init(color);
	cr->autorelease();
	return cr;
}

bool SceneGane::init(bool color)
{
	if(CCLayer::init())
	{
		red = color;

		selectsprite = CCSprite::create("selected.png");
		selectsprite->setZOrder(100);
		addChild(selectsprite);
		selectsprite->setScale(1.2);
		//��ѡ�п���������
		selectsprite->setVisible(false);

		plateoffset = ccp(20, 15);
		stoneoffset = ccp(80, 45);
		d = 76;

		_steps = CCArray::create();
		_steps->retain();

		_redTrun = true;

		CCSize winsize = CCDirector::sharedDirector()->getWinSize();

		CCSprite *desk = CCSprite::create("floor.jpg");
		addChild(desk);
		desk->setPosition(winsize.width / 2, winsize.height / 2);
		desk->setScaleX(winsize.width / desk->getContentSize().width);
		desk->setScaleY(winsize.height / desk->getContentSize().height);

		CCSprite *plate = CCSprite::create("background.png");
		plate->setAnchorPoint(ccp(0, 0));
		addChild(plate);
		plate->setScale((winsize.height - plateoffset.y * 2) / plate->getContentSize().height);
		plate->setPosition(plateoffset);


		for(int i = 0; i < 32; i++)
		{
			stone[i] = Stone::create(i, color);
			addChild(stone[i]);
			stone[i]->setPosition(ccp(stone[i]->getX()* d, stone[i]->getY()*d) + stoneoffset);

			stone[i]->setPosition(ccp(CCRANDOM_0_1()*winsize.width,
									  CCRANDOM_0_1()* winsize.height));
			CCMoveTo* move = CCMoveTo::create(1, this->getStonepos(stone[i]->getX(), stone[i]->getY()));
			stone[i]->runAction(move);
		}

		setTouchEnabled(true);
		setTouchMode(kCCTouchesOneByOne);

		//���尴ť
		CCMenu *menu = CCMenu::create();
		CCMenuItem* item = CCMenuItemImage::create("regret.jpg", "regret.jpg",
												   this, menu_selector(SceneGane::back));
		menu->addChild(item);
		addChild(menu);
		item->setPositionX(item->getPositionX() + 300);

		return true;
	}
	return false;
}
bool SceneGane::onTouchBegan(CCTouch* touch, CCEvent *)
{
	CCPoint ptwin = touch->getLocation();
	int x, y;
	if(!getClickPos(ptwin, x, y))
	{
		return false;
	}

	int clickid = getStone(x, y);
	if(_selectd == -1)
	{
		SetSelectId(clickid);
	}
	else
	{
		moveStone(_selectd, clickid, x, y);

	}

	return true;
}
void SceneGane::back(CCObject *)
{
	if(_steps->count() == 0)
		return;

	Step* step = (Step*)_steps->lastObject();
	stone[step->_moveid]->setX(step->_xFrom);
	stone[step->_moveid]->setY(step->_yFrom);
	stone[step->_moveid]->setPosition(getStonepos(step->_xFrom, step->_yFrom));

	if(step->_killid != -1)
	{
		stone[step->_killid]->setVisible(true);
		stone[step->_killid]->setDead(false);
	}

	_redTrun = !_redTrun;
	//ɾ�����һ������
	_steps->removeLastObject();
}

void SceneGane::moveStone(int moveid, int killid, int x, int y)
{
	if(killid != -1 && stone[killid]->getCOLOR() == stone[moveid]->getCOLOR())
	{
		SetSelectId(killid);
		return;
	}

	bool bcanmove = canmove(moveid, killid, x, y);
	if(bcanmove == false)
		return;

	Step *step = Step::create(moveid, killid, stone[moveid]->getX(), stone[moveid]->getY(), x, y);
	_steps->addObject(step);

	if(killid != -1)
	{
		stone[killid]->setDead(true);
		stone[killid]->setVisible(false);

		//�жϽ��Ƿ񱻳���
		if(killid == 4 || killid == 20)
		{
			CCDirector::sharedDirector()->replaceScene(SceneGane::scene(!red));
		}
	}
	stone[moveid]->setX(x);
	stone[moveid]->setY(y);

	CCMoveTo* move = CCMoveTo::create(.5f, getStonepos(x, y));
	CCCallFuncND* call = CCCallFuncND::create(this,
											  callfuncND_selector(SceneGane::moveComplete),
											  (void*)(intptr_t)killid);
	CCSequence* seq = CCSequence::create(move, call, NULL);
	stone[moveid]->setZOrder(stone[moveid]->getZOrder() + 1);
	stone[moveid]->runAction(seq);


}
bool SceneGane::canMoveJiang(int moveid, int killid, int x, int y)
{
	Stone *skill = stone[killid];
	if(skill->getType() == Stone::JIANG)
	{
		return canMoveChe(moveid, x, y);
	}
	Stone *s = stone[moveid];
	int x1 = s->getX(); 
	int y1 = s->getY();
	int x2 = abs(x1 - x);
	int y2 = abs(y1 - y);
	//ֻ����һ��
	if(x2 > 1)
		return false;
	if(y2 > 1)
		return false;
	if(x2 + y2 != 1)
		return false;
	//���ܳ��Ź�
	if(x < 3 || x>5)
		return false;
	if(red == s->getCOLOR())
	{
		if(y < 0 || y>2)
			return false;
	}
	else
	{
		if(y < 7 || y>9)
			return false;
	}

	return true;
}
bool SceneGane::canMoveShi(int moveid, int x, int y)
{
	Stone *s = stone[moveid];
	int x1 = s->getX();
	int y1 = s->getY();
	int x2 = abs(x1 - x);
	int y2 = abs(y1 - y);
	//ֻ��б����һ��
	if(x2 != 1)
		return false;
	if(y2 != 1)
		return false;

	//���ܳ��Ź�
	if(x < 3 || x>5)
		return false;
	if(red == s->getCOLOR())
	{
		if(y < 0 || y>2)
			return false;
	}
	else
	{
		if(y < 7 || y>9)
			return false;
	}

	return true;
}
bool SceneGane::canMoveXiang(int moveid, int x, int y)
{
	Stone *s = stone[moveid];
	int x1 = s->getX();
	int y1 = s->getY();
	int x2 = abs(x1 - x);
	int y2 = abs(y1 - y);
	//ֻ��������
	if(x2 != 2)
		return false;
	if(y2 != 2)
		return false;
	//�ж���������û������
	int x3 = (x1 + x) / 2;
	int y3 = (y1 + y) / 2;
	int ID = getStone(x3, y3);
	if(ID != -1)
		return false;
	//��û�й���
	if(red == s->getCOLOR())
	{
		if(y > 4)
			return false;
	}
	else
	{
		if(y < 5)
			return false;
	}


	return true;
}
bool SceneGane::canMoveMa(int moveid, int x, int y)
{
	Stone *s = stone[moveid];
	int x1 = s->getX();
	int y1 = s->getY();
	int x2 = abs(x1 - x);
	int y2 = abs(y1 - y);
	//ֻ������
	if(x2 + y2 != 3)
		return false;
	//�Ƿ񱻵�ס��
	int xm, ym;
	if(y2 == 2)
	{
		xm = x1;
		ym = (y1 + y) / 2;
	}
	else
	{
		xm = (x1 + x) / 2;
		ym = y1;
	}
	if(getStone(xm, ym) != -1)
		return false;

	return true;
}
bool SceneGane::canMoveChe(int moveid, int x, int y)
{
	Stone *s = stone[moveid];
	int x1 = s->getX();
	int y1 = s->getY();
	int x2 = abs(x1 - x);
	int y2 = abs(y1 - y);
	//�ж��Ƿ���һ������
	if(x1 != x&&y1 != y)
		return false;
	if(x1 == x&&y1 == y)
		return false;
	//�ж��м��Ƿ�������
	int ret = 0;
	if(x1 == x)
	{
		int min = y1 < y ? y1 : y;
		int max = y1 > y ? y1 : y;
		for(int yy = min + 1; yy < max; yy++)
		{
			if(getStone(x, yy) != -1) 
				++ret;
		}
	}
	else
	{
		int min = x1 < x ? x1 : x;
		int max = x1 > x ? x1 : x;
		for(int xx = min + 1; xx < max; xx++)
		{
			if(getStone(xx, y) != -1)
				++ret;
		}
	}
	if(ret != 0)
		return false;


	return true;
}
bool SceneGane::canMovePao(int moveid, int killid, int x, int y)
{
	Stone *s = stone[moveid];
	int x1 = s->getX();
	int y1 = s->getY();
	int x2 = abs(x1 - x);
	int y2 = abs(y1 - y);

	//�ж��Ƿ���һ������
	if(x1 != x&&y1 != y)
		return false;
	if(x1 == x&&y1 == y)
		return false;
	//�ж�·�����Ӹ���
	int ret = 0;
	if(x1 == x)
	{
		int min = y1 < y ? y1 : y;
		int max = y1 > y ? y1 : y;
		for(int yy = min + 1; yy < max; yy++)
		{
			if(getStone(x, yy) != -1)
				++ret;
		}
	}
	else
	{
		int min = x1 < x ? x1 : x;
		int max = x1 > x ? x1 : x;
		for(int xx = min + 1; xx < max; xx++)
		{
			if(getStone(xx, y) != -1)
				++ret;
		}
	}

	if(killid != -1 && ret == 1)
		return true;
	return canMoveChe(moveid, x, y);
}
bool SceneGane::canMoveBing(int moveid, int x, int y)
{
	Stone *s = stone[moveid];
	int x1 = s->getX();
	int y1 = s->getY();
	int x2 = abs(x1 - x);
	int y2 = abs(y1 - y);
	//ֻ����һ��
	if((x2 + y2) != 1)
		return false;
	//�Ƿ����
	if(red == s->getCOLOR())
	{
		//���ܺ���
		if(y < y1)
			return false;
		if(y1 >4)
		{

		}
		else
		{
			//û���Ӳ��ܺ�����
			if(y1 == y)
				return false;
		}			
	}
	else
	{
		//���ܺ���
		if(y > y1)
			return false;
		if(y1 < 5)
		{

		}
		else
		{
			//û���Ӳ��ܺ�����
			if(y1 == y)
				return false;
		}
			
	}

	return true;
}
bool SceneGane::canmove(int moveid, int killid, int x, int y)
{
	switch(stone[moveid]->getType())
	{
	case Stone::JIANG:
		return canMoveJiang(moveid, killid, x, y);
	case Stone::SHI:
		return canMoveShi(moveid, x, y);
	case Stone::XIANG:
		return canMoveXiang(moveid, x, y);
	case Stone::MA:
		return canMoveMa(moveid, x, y);
	case Stone::CHE:
		return canMoveChe(moveid, x, y);
	case Stone::PAO:
		return canMovePao(moveid, killid, x, y);
	case Stone::BING:
		return canMoveBing(moveid, x, y);
	}
	return false;
}

void SceneGane::moveComplete(CCNode *moveStone, void *_killid)
{
	moveStone->setZOrder(moveStone->getZOrder() - 1);

	int killid = (int)(intptr_t)_killid;

	if(killid != -1)
	{
		stone[killid]->setDead(true);
		stone[killid]->setVisible(false);

		if(stone[killid]->getType() == Stone::JIANG)
		{
			CCDirector::sharedDirector()->replaceScene(SceneGane::scene(!red));
		}
	}

	selectsprite->setVisible(false);
	_redTrun = !_redTrun;
	_selectd = -1;

}
CCPoint SceneGane::getStonepos(int x, int y)
{
	return ccp(x*d, y*d) + stoneoffset;
}
void SceneGane::SetSelectId(int id)
{
	if(id == -1)
		return;
	if(stone[id]->getCOLOR() != _redTrun)
		return;
	_selectd = id;
	selectsprite->setVisible(true);
	selectsprite->setPosition(stone[_selectd]->getPosition());


}
int SceneGane::getStone(int x, int y)
{
	Stone *s;
	for(int i = 0; i < 32; i++)
	{
		if(stone[i]->getX() == x&&stone[i]->getY() == y && !(stone[i]->getDead()))
		{
			return stone[i]->getID();
		}
	}
	return -1;
}
bool SceneGane::getClickPos(CCPoint ptwin, int& x, int &y)
{
	for(x = 0; x <= 8; x++)
	{
		for(y = 0; y <= 9; y++)
		{
			CCPoint ptInPlate = ccp(x*d, y*d) + stoneoffset;
			if(ptwin.getDistance(ptInPlate) < d / 2)
			{
				return true;
			}
		}
	}
	return false;
}