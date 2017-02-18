#ifndef  __Stone_h__
#define  __Stone_h__
#include "cocos2d.h"
USING_NS_CC;

class Stone :public CCSprite
{
public:
	Stone();
	~Stone();
	
	enum TYPE
	{
		JIANG, SHI, XIANG, CHE, MA, PAO, BING
	};
	//棋子的属性
	CC_SYNTHESIZE(TYPE, type, Type);
	//在棋盘上的横坐标
	CC_SYNTHESIZE(int, x, X);
	//在棋盘上的纵坐标
	CC_SYNTHESIZE(int, y, Y);
	//数组下标
	CC_SYNTHESIZE(int, id, ID);
	//棋子是否被吃
	CC_SYNTHESIZE(bool, dead, Dead);
	//棋子颜色
	CC_SYNTHESIZE(bool, color, COLOR);

	static Stone*create(int id,bool color)
	{

		Stone *s = new Stone();
		s->init(id, color);
		s->autorelease();
		return s;
	}

	void reset(bool color);
	bool init(int _id, bool _color)
	{
		id = _id;
		color = _id < 16;
		if(_id < 16)
			type = _initpos[_id]._type;
		else
			type = _initpos[_id - 16]._type;
	    reset(_color);
		const char* stonePic[14] = {
			"rjiang.png",
			"rshi.png",
			"rxiang.png",
			"rche.png",
			"rma.png",
			"rpao.png",
			"rbing.png",

			"bjiang.png",
			"bshi.png",
			"bxiang.png",
			"bche.png",
			"bma.png",
			"bpao.png",
			"bbing.png"
		};

		int idx = (color ? 0 : 1) * 7 + type;
		CCSprite::initWithFile(stonePic[idx]);
		setScale(1.3);

		return true;
	}

	


	//定义一个结构体存放数组位置
	static struct initpos
	{
		int _x;
		int _y;
		Stone::TYPE _type;
	}_initpos[16];
};


#endif