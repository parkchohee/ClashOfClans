#pragma once

#include "gameNode.h"

enum unitState {
	UNIT_MOVE,
	UNIT_ATTACK,
	UNIT_DIE,
	UNIT_NULL
};

class units : public gameNode
{
	RECT _rc;
	RECT _collisionRc;
	RECT _moveRc;

	int _x, _y;
	float _speed;
	float _angle;
	int _pow;
	POINT _position;
	int _type;

	string _name;
	image* _Img;

	unitState _state;

	bool _isRight;
	int _count;
	int _currentFrameX, _currentFrameY;

	int _offsetX, _offsetY;

	bool _attacked;
	bool _search;



	vector<RECT> _aStarRc;


public:
	units();
	~units();

	HRESULT init(int x, int y, float angle, float speed, int pow, int type, POINT position, string name);
	void release();
	void update();
	void render();

	void frameCount();

	void setOffset(int x, int y);
	void move();


	void setUnitState(int state);
	void setUnitImg();

	int getPower() { _attacked = true; return _pow; }
	int getX() { return _x; }
	int getY() { return _y; }
	int getType() { return _type; }

	RECT getRect() { return _collisionRc; }


	bool getAttacked() { return _attacked; }

	void setPosition(POINT position) { _position = position; }
	void setAStarWay(vector<POINT> aStarWay);

	void setAngle();

	void setSearch(bool search) { _search = search; }
	bool getSearch() { return _search; }
};

