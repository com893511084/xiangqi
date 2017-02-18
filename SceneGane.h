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
	//���̵�ƫ����
	CCPoint plateoffset;
	//���ӵ�ƫ����
	CCPoint stoneoffset;
	//���ӵ�ֱ��
	float d;
	//����32������
	Stone *stone [32];

	int _selectd = -1;

	bool onTouchBegan(CCTouch* touch, CCEvent *);
	//void onTouchEnded(CCTouch* touch, CCEvent *);
	//�����������λ����û������
	bool getClickPos(CCPoint ptwin, int& x, int &y);
	//�õ�����ID
	int getStone(int x, int y);
	//�������û�б�ѡ�� ��ѡ������
	void SetSelectId(int id);
	//����ѡ�п���
	CCSprite *selectsprite;
	//�ƶ�����
	void moveStone(int moveid, int killid, int x, int y);
	//��������λ��
	CCPoint getStonepos(int x, int y);
	//��¼���߻��Ǻ���
	bool _redTrun;
	//���庯��
	void back(Object *);
	//������¼��һ��������
	CCArray* _steps;
	//��¼����ߺ�
	bool red;
	//�����ƶ���Ч
	void moveComplete(CCNode *moveStone, void *_killid);
	//���ӵ����巽ʽ
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
