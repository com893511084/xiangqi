#ifndef  __SceneGane_h__
#define  __SceneGane_h__
#include "cocos2d.h"
#include "Stone.h"
USING_NS_CC;

class Step : public CCObject
{
public:
	int _moveid;
	int _killid;
	int _xFrom;
	int _yFrom;
	int _xTo;
	int _yTo;
	static Step* create(int moveid, int killid, int xFrom, int yFrom, int xTo, int yTo)
	{
		Step* step = new Step;
		step->_killid = killid;
		step->_moveid = moveid;
		step->_xFrom = xFrom;
		step->_xTo = xTo;
		step->_yFrom = yFrom;
		step->_yTo = yTo;
		step->autorelease();
		return step;
	}
};

class SceneGane :public CCLayer
{
public:
	SceneGane();
	~SceneGane();

	
	static CCScene *scene(bool color);

	bool init(bool color);
	//CREATE_FUNC(SceneGane);
	static SceneGane *create(bool color);
	//棋盘的偏移量
	CCPoint plateoffset;
	//棋子的偏移量
	CCPoint stoneoffset;
	//棋子的直径
	float d;
	//定义32个棋子
	Stone *stone [32];

	int _selectd = -1;

	bool onTouchBegan(CCTouch* touch, CCEvent *);
	//void onTouchEnded(CCTouch* touch, CCEvent *);
	//计算所点击的位置有没有棋子
	bool getClickPos(CCPoint ptwin, int& x, int &y);
	//得到棋子ID
	int getStone(int x, int y);
	//如果棋子没有被选定 就选定棋子
	void SetSelectId(int id);
	//创建选中框精灵
	CCSprite *selectsprite;
	//移动棋子
	void moveStone(int moveid, int killid, int x, int y);
	//计算棋子位置
	CCPoint getStonepos(int x, int y);
	//计录红走还是黑走
	bool _redTrun;
	//悔棋函数
	void back(Object *);
	//创建记录上一步的数组
	CCArray* _steps;
	//记录红或者黑
	bool red;
	//棋子移动特效
	void moveComplete(CCNode *moveStone, void *_killid);
	//棋子的走棋方式
	bool canmove(int moveid, int killid, int x, int y);

	bool canMoveJiang(int moveid, int killid, int x, int y);
	bool canMoveShi(int moveid, int x, int y);
	bool canMoveXiang(int moveid, int x, int y);
	bool canMoveChe(int moveid, int x, int y);
	bool canMoveMa(int moveid, int x, int y);
	bool canMovePao(int moveid, int killid, int x, int y);
	bool canMoveBing(int moveid, int x, int y);
};


#endif
