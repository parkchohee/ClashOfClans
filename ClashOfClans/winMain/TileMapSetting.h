#pragma once

#include "gameNode.h"

#define TILEMAX 30



class TileMapSetting : public gameNode
{

	int _offsetX;
	int _offsetY;

	bool _offsetMoveX;
	bool _offsetMoveY;
	int _startX, _startY;
	int _endX, _endY;

	int _touchX, _touchY;

public:
	TileMapSetting();
	~TileMapSetting();

	HRESULT init();
	void release();
	void update();
	void render();

	tagTile mapTile[TILEMAX][TILEMAX];

	void setBackgroundOffset();
	void createTile();

	bool ptInDiamond();
	bool diaCollisionCheck(POINT point, float m, POINT topPoint, POINT leftPoint, POINT bottomPoint, POINT rightPoint);
	bool pointInDiamond(int x, int y);

	int getTouchX() { return _touchX; }
	int getTouchY() { return _touchY; }
	int getOffsetX() { return _offsetX; }
	int getOffsetY() { return _offsetY; }
};

