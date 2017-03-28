#include "stdafx.h"
#include "units.h"


units::units()
{
}


units::~units()
{
}

HRESULT units::init(int x, int y, float angle, float speed, int pow, int type, POINT position, string name)
{
	_name = name;
	_Img = IMAGEMANAGER->findImage(name);
	
	_rc = RectMakeCenter(x, y, _Img->getFrameWidth(), _Img->getFrameHeight());
	_collisionRc = RectMakeCenter(x, y, _Img->getFrameWidth()/2, _Img->getFrameHeight()/2);
	_moveRc = RectMakeCenter(x, y, 15, 15);

	_x = x;
	_y = y;
	_angle = angle;
	_speed = speed;
	_pow = pow;
	_position = position;
	_type = type;

	_isRight = true;
	_attacked = false;

	_state = UNIT_MOVE;

	return S_OK;
}

void units::release()
{
}

void units::update()
{
	frameCount();

	if (_state == UNIT_MOVE)
	{
		move();
	}
	
}

void units::render()
{
	//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	//Rectangle(getMemDC(), _moveRc.left, _moveRc.top, _moveRc.right, _moveRc.bottom);
	//Rectangle(getMemDC(), _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
	char str[100];
	//sprintf_s(str, "%d", _type);
	//TextOut(getMemDC(), _rc.left, _rc.top, str, strlen(str));
	_Img->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);

	//for (int i = 0; i < _aStarRc.size(); i++)
	//{
	//	Rectangle(getMemDC(), _aStarRc[i].left, _aStarRc[i].top, _aStarRc[i].right, _aStarRc[i].bottom);
	//}

}

void units::frameCount()
{
	_count++;

	if (_count % 7 == 0)
	{
		_Img->setFrameX(_currentFrameX);
		_currentFrameX++;

		if (_currentFrameX > _Img->getMaxFrameX())
		{
			_attacked = false;
			_currentFrameX = 0;
		}
		_count = 0;
	}
	
	
}

void units::setOffset(int x, int y)
{
	_rc = { _rc.left - x, _rc.top - y, _rc.right - x, _rc.bottom - y };
	_moveRc = RectMakeCenter((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2, 15, 15);
	_collisionRc = RectMakeCenter((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2, (_rc.right - _rc.left) / 2, (_rc.bottom - _rc.top) / 2);

	for (int i = 0; i < _aStarRc.size(); i++)
	{
		_aStarRc[i] = { _aStarRc[i].left - x, _aStarRc[i].top - y, _aStarRc[i].right - x, _aStarRc[i].bottom - y };
	}

	_x = (_rc.left + _rc.right) / 2;
	_y = (_rc.top + _rc.bottom) / 2;
}

void units::move()
{
	setAngle();
	
	LONG x, y;

	x = cosf(_angle)*_speed;
	y = -sinf(_angle)*_speed;

	_rc = { _rc.left + x, _rc.top + y, _rc.right + x, _rc.bottom + y };
	_moveRc = RectMakeCenter((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2, 15, 15);
	_collisionRc = RectMakeCenter((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2, (_rc.right - _rc.left) / 2, (_rc.bottom - _rc.top) / 2);

	_x = (_rc.left + _rc.right) / 2;
	_y = (_rc.top + _rc.bottom) / 2;
}

void units::setUnitState(int state)
{
	_state = (unitState)state;
	setUnitImg();
}

void units::setUnitImg()
{
	if (_state == UNIT_MOVE)
		_Img = IMAGEMANAGER->findImage(_name);
	else if(_state == UNIT_ATTACK)
		_Img = IMAGEMANAGER->findImage(_name + "Attack");

}

void units::setAStarWay(vector<POINT> aStarWay)
{
	_aStarRc.clear();

	for (int i = 0; i < aStarWay.size(); i++)
	{
		RECT temp = RectMakeCenter(aStarWay[i].x - _offsetX, aStarWay[i].y - _offsetY, 10, 10);

		_aStarRc.push_back(temp);
	}
	
}

void units::setAngle()
{
	float angle;
	int frame;

	if (_aStarRc.size() > 0)
	{
		_angle = MY_UTIL::getAngle((_moveRc.left + _moveRc.right) / 2, (_moveRc.top + _moveRc.bottom) / 2, (_aStarRc[0].left + _aStarRc[0].right) / 2, (_aStarRc[0].top + _aStarRc[0].bottom) / 2);
		
		// angle에따라 FrameY의 값을 바꿔준다.
		angle = _angle + PI6;
		if (angle > PI2) angle -= PI2;

		_currentFrameY = FLOAT_TO_INT(angle / PI3);
		_Img->setFrameY(_currentFrameY);

		//_position = pointMake(); 


		if (_aStarRc[0].left > _moveRc.left &&
			_aStarRc[0].top > _moveRc.top &&
			_aStarRc[0].right < _moveRc.right &&
			_aStarRc[0].bottom < _moveRc.bottom)
		{
			_aStarRc.erase(_aStarRc.begin());
		}

		
	}

}
