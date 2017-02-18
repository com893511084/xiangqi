#include "Stone.h"



Stone::Stone()
{
}


Stone::~Stone()
{
}

Stone::initpos Stone::_initpos[16] =
{
	{0,0,Stone::CHE},
	{1,0,Stone::MA},
	{2,0,Stone::XIANG},
	{3,0,Stone::SHI},
	{4,0,Stone::JIANG},
	{5,0,Stone::SHI},
	{ 6,0,Stone::XIANG },
	{ 7,0,Stone::MA },
	{ 8,0,Stone::CHE },

	{ 1,2,Stone::PAO },
	{ 7,2,Stone::PAO },

	{ 0,3,Stone::BING},
	{ 2,3,Stone::BING },
	{ 4,3,Stone::BING },
	{ 6,3,Stone::BING },
	{ 8,3,Stone::BING },
};

void Stone::reset(bool color)
{
	this->setDead(false);
	if(color)
	{
		if(id < 16)
		{
			this->setX(_initpos[id]._x);
			this->setY(_initpos[id]._y);
		}
		else
		{
			this->setX(8 - _initpos[id - 16]._x);
			this->setY(9 - _initpos[id - 16]._y);
		}
	}
	else
	{
		if(id < 16)
		{
			this->setX(8 - _initpos[id]._x);
			this->setY(9 - _initpos[id]._y);
		}
		else
		{
			this->setX(_initpos[id - 16]._x);
			this->setY(_initpos[id - 16]._y);
		}
	}


}