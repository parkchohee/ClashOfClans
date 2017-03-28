#include "stdafx.h"
#include "TileMapSetting.h"


TileMapSetting::TileMapSetting()
{
}


TileMapSetting::~TileMapSetting()
{
}

HRESULT TileMapSetting::init()
{
	_offsetX = 0;
	_offsetY = 0;

	_offsetMoveX = false;
	_offsetMoveY = false;

	// Tile Setting
	mapTile[0][0].rc = RectMake(IMAGEMANAGER->findImage("background")->getWidth() / 2 - 25, 34, 50, 34);
	
	createTile();
	
	return S_OK;
}

void TileMapSetting::release()
{
}

void TileMapSetting::update()
{
	setBackgroundOffset();
}

void TileMapSetting::render()
{
	IMAGEMANAGER->findImage("background")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _offsetX, _offsetY);

	//타일맵 테스트.
	//for (int i = 0; i < TILEMAX; i++)
	//{
	//	for (int j = 0; j < TILEMAX; j++)
	//	{
	//		//Rectangle(getMemDC(), mapTile[j][i].rc.left, mapTile[j][i].rc.top, mapTile[j][i].rc.right, mapTile[j][i].rc.bottom);

	//		LineMake(getMemDC(), mapTile[j][i].p1.x, mapTile[j][i].p1.y, mapTile[j][i].p2.x, mapTile[j][i].p2.y);
	//		LineMake(getMemDC(), mapTile[j][i].p2.x, mapTile[j][i].p2.y, mapTile[j][i].p3.x, mapTile[j][i].p3.y);
	//		LineMake(getMemDC(), mapTile[j][i].p3.x, mapTile[j][i].p3.y, mapTile[j][i].p4.x, mapTile[j][i].p4.y);
	//		LineMake(getMemDC(), mapTile[j][i].p4.x, mapTile[j][i].p4.y, mapTile[j][i].p1.x, mapTile[j][i].p1.y);
	//	}
	//}

	
}


void TileMapSetting::setBackgroundOffset()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		_offsetMoveX = true;
		_offsetMoveY = true;
		_startX = _ptMouse.x;
		_startY = _ptMouse.y;
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))
	{
		_offsetMoveX = false;
		_offsetMoveY = false;
	}

	if (_offsetMoveX)
	{
		if (_offsetX < 0)
		{
			_offsetX = 0;
			_offsetMoveX = false;
		}
		else if (_offsetX > IMAGEMANAGER->findImage("background")->getWidth() - WINSIZEX)
		{
			_offsetX = IMAGEMANAGER->findImage("background")->getWidth() - WINSIZEX;
			_offsetMoveX = false;
		}
		else if (_offsetX >= 0 && _offsetX <= IMAGEMANAGER->findImage("background")->getWidth() - WINSIZEX)
		{
			_offsetX = _offsetX + _startX - _ptMouse.x;
			_startX = _ptMouse.x;
		
		}
	}

	if (_offsetMoveY)
	{
		if (_offsetY < 0)
		{
			_offsetY = 0;
			_offsetMoveY = false;
		}
		else if (_offsetY > IMAGEMANAGER->findImage("background")->getHeight() - WINSIZEY + 100)
		{
			_offsetY = IMAGEMANAGER->findImage("background")->getHeight() - WINSIZEY + 100;
			_offsetMoveY = false;
		}
		else if (_offsetY >= 0 && _offsetY <= IMAGEMANAGER->findImage("background")->getHeight() - WINSIZEY + 100)
		{
			_offsetY = _offsetY + _startY - _ptMouse.y;
			_startY = _ptMouse.y;
		}
	}


	if (_offsetMoveX || _offsetMoveY)
	{
		mapTile[0][0].rc = RectMake(IMAGEMANAGER->findImage("background")->getWidth() / 2 - 25 - _offsetX, 34 - _offsetY, 50, 34);
		createTile();
	}
	


}

void TileMapSetting::createTile()
{
	for (int i = 0; i < TILEMAX; i++)
	{
		for (int j = 0; j < TILEMAX; j++)
		{
			if (i == 0 && j != 0)
			{
				mapTile[j][i].rc = RectMake(mapTile[j - 1][i].rc.left + 25, mapTile[j - 1][i].rc.top + 17, 50, 34);
			}
			else if (i != 0 && j == 0)
			{
				mapTile[j][i].rc = RectMake(mapTile[j][i - 1].rc.left - 25, mapTile[j][i - 1].rc.top + 17, 50, 34);
			}
			else if (i != 0 && j != 0)
			{
				mapTile[j][i].rc = RectMake(mapTile[j - 1][i].rc.left + 25, mapTile[j - 1][i].rc.top + 17, 50, 34);
			}

			mapTile[j][i].p1 = pointMake((mapTile[j][i].rc.left + mapTile[j][i].rc.right) / 2, mapTile[j][i].rc.top);
			mapTile[j][i].p2 = pointMake(mapTile[j][i].rc.left, (mapTile[j][i].rc.top + mapTile[j][i].rc.bottom) / 2);
			mapTile[j][i].p3 = pointMake((mapTile[j][i].rc.left + mapTile[j][i].rc.right) / 2, mapTile[j][i].rc.bottom);
			mapTile[j][i].p4 = pointMake(mapTile[j][i].rc.right, (mapTile[j][i].rc.top + mapTile[j][i].rc.bottom) / 2);

			mapTile[j][i].x = j;
			mapTile[j][i].y = i;
			mapTile[j][i].parent = NULL;
			mapTile[j][i].F = 10000;
			mapTile[j][i].G = 0;
			mapTile[j][i].H = 0;
			mapTile[j][i].state = NORMAL_NODE;

		}
	}
}

bool TileMapSetting::ptInDiamond()
{
	for (int i = 0; i < TILEMAX; i++)
	{
		for (int j = 0; j < TILEMAX; j++)
		{
			// 마름모 기울기
			float m = (float)(mapTile[j][i].rc.bottom - mapTile[j][i].rc.top)
				/ (float)(mapTile[j][i].rc.right - mapTile[j][i].rc.left);

			// 직선의 방정식			
			float d1 = mapTile[j][i].p1.y - (m * mapTile[j][i].p1.x);
			float d2 = mapTile[j][i].p2.y - (-m * mapTile[j][i].p2.x);
			float d3 = mapTile[j][i].p3.y - (m * mapTile[j][i].p3.x);
			float d4 = mapTile[j][i].p4.y - (-m * mapTile[j][i].p4.x);

			// 점의 위치 계산
			float result1 = _ptMouse.y - (m * _ptMouse.x) - d1;
			float result2 = _ptMouse.y - (-m * _ptMouse.x) - d2;
			float result3 = _ptMouse.y - (m * _ptMouse.x) - d3;
			float result4 = _ptMouse.y - (-m * _ptMouse.x) - d4;

			if (result1 > 0.0f && result2 > 0.0f && result3 < 0.0f && result4 < 0.0f)
			{
				_touchX = j;
				_touchY = i;

				return true;
			}
		}
	}

	return false;
}

bool TileMapSetting::diaCollisionCheck(POINT point, float m, POINT topPoint, POINT leftPoint, POINT bottomPoint, POINT rightPoint)
{

	// 직선의 방정식			
	float d1 = topPoint.y - (m * topPoint.x);
	float d2 = leftPoint.y - (-m * leftPoint.x);
	float d3 = bottomPoint.y - (m * bottomPoint.x);
	float d4 = rightPoint.y - (-m * rightPoint.x);

	// 점의 위치 계산
	float result1 = point.y - (m * point.x) - d1;
	float result2 = point.y - (-m * point.x) - d2;
	float result3 = point.y - (m * point.x) - d3;
	float result4 = point.y - (-m * point.x) - d4;

	if (result1 > 0.0f && result2 > 0.0f && result3 < 0.0f && result4 < 0.0f)
	{
		return true;
	}

	return false;
}

bool TileMapSetting::pointInDiamond(int x, int y)
{
	for (int i = 0; i < TILEMAX; i++)
	{
		for (int j = 0; j < TILEMAX; j++)
		{
			// 마름모 기울기
			float m = (float)(mapTile[j][i].rc.bottom - mapTile[j][i].rc.top)
				/ (float)(mapTile[j][i].rc.right - mapTile[j][i].rc.left);

			// 직선의 방정식			
			float d1 = mapTile[j][i].p1.y - (m * mapTile[j][i].p1.x);
			float d2 = mapTile[j][i].p2.y - (-m * mapTile[j][i].p2.x);
			float d3 = mapTile[j][i].p3.y - (m * mapTile[j][i].p3.x);
			float d4 = mapTile[j][i].p4.y - (-m * mapTile[j][i].p4.x);

			// 점의 위치 계산
			float result1 = y - (m * x) - d1;
			float result2 = y - (-m * x) - d2;
			float result3 = y - (m * x) - d3;
			float result4 = y - (-m * x) - d4;

			if (result1 > 0.0f && result2 > 0.0f && result3 < 0.0f && result4 < 0.0f)
			{
				_touchX = j;
				_touchY = i;

				return true;
			}
		}
	}

	return false;
}

void tagSlot::attack(int pow)
{
	currentHp -= pow;

	if (currentHp < 0)
	{
		destroyed = true;
	}
}
