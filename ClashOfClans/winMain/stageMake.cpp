#include "stdafx.h"
#include "stageMake.h"


stageMake::stageMake()
{
}


stageMake::~stageMake()
{
}

HRESULT stageMake::init()
{
	_tile = new TileMapSetting;
	_tile->init();

	for (int i = 0; i < STAGEMAX; i++)
	{
		char str[100];
		sprintf_s(str, "stage%d", (i + 1));
		_stageNames[i] = str;
	}

	buildingSlotSetting();

	_selectStageNum = 0;

	_prev = RectMake(20, 25, 20, 20);
	_next = RectMake(230, 25, 20, 20);
	_save = RectMake(20, 60, 128, 40);
	_cancel = RectMake(148, 60, 128, 40);
	_remove = RectMake(20, 100, 128, 40);
	_allRemove = RectMake(148, 100, 128, 40);

	_bulidingRc = RectMake(0, 0, 0, 0);
	_bulidingColiisionRc = RectMake(0, 0, 0, 0);

	_isCollision = false;


	loadMap();


	return S_OK;
}

void stageMake::release()
{
	_tile->release();
	SAFE_DELETE(_tile);
}

void stageMake::update()
{
	_tile->update();

	btnClick();
	offsetSetting();
}

void stageMake::render()
{
	_tile->render();

	char str[100];
	sprintf_s(str, "%s", _stageNames[_selectStageNum].c_str());

	HFONT myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Supercell-Magic");
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);
	TextOut(getMemDC(), 70, 20, str, strlen(str) );
	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);

	IMAGEMANAGER->findImage("btn_slot")->render(getMemDC(), 20, 60);


	Rectangle(getMemDC(), _prev.left, _prev.top, _prev.right, _prev.bottom);
	Rectangle(getMemDC(), _next.left, _next.top, _next.right, _next.bottom);
	//Rectangle(getMemDC(), _save.left, _save.top, _save.right, _save.bottom);
	//Rectangle(getMemDC(), _cancel.left, _cancel.top, _cancel.right, _cancel.bottom);
	//Rectangle(getMemDC(), _remove.left, _remove.top, _remove.right, _remove.bottom);
	//Rectangle(getMemDC(), _allRemove.left, _allRemove.top, _allRemove.right, _allRemove.bottom);


	for (int i = 0; i < _vRect.size(); i++)
	{
		if (_vRect[i]->size == 1)
		{
			_vRect[i]->img->render(getMemDC(), _vRect[i]->rc.left - 13, _vRect[i]->rc.top - 27);

		}
		else if (_vRect[i]->size == 3)
		{
			IMAGEMANAGER->findImage("building_bottom_3_3")->render(getMemDC(), _vRect[i]->rc.left, _vRect[i]->rc.top);
			_vRect[i]->img->render(getMemDC(), _vRect[i]->rc.left + 30, _vRect[i]->rc.top - 20);

		}
	}

	sprintf_s(str, "%d %d", _selectBuildingType, _vRect.size());
	TextOut(getMemDC(), 0,150, str, strlen(str));

	sprintf_s(str, "%d %d", _x, _y);
	TextOut(getMemDC(), 0, 170, str, strlen(str));


	//Rectangle(getMemDC(), _bulidingRc.left, _bulidingRc.top, _bulidingRc.right, _bulidingRc.bottom);
	//Rectangle(getMemDC(), _bulidingColiisionRc.left, _bulidingColiisionRc.top, _bulidingColiisionRc.right, _bulidingColiisionRc.bottom);


	IMAGEMANAGER->findImage("slot_background_bottom")->render(getMemDC(), 0, 660);

	for (int i = 0; i < _vBuildings.size(); i++)
	{
		//Rectangle(getMemDC(), _vBuildings[i]->rc.left, _vBuildings[i]->rc.top, _vBuildings[i]->rc.right, _vBuildings[i]->rc.bottom);
		IMAGEMANAGER->findImage("slot_background")->render(getMemDC(), _vBuildings[i]->rc.left, _vBuildings[i]->rc.top);

		_vBuildings[i]->img->render(getMemDC(), _vBuildings[i]->rc.left, _vBuildings[i]->rc.top);

		sprintf_s(str, "%f, %d", _vBuildings[i]->count, _vBuildings[i]->size);
		TextOut(getMemDC(), _vBuildings[i]->rc.left, _vBuildings[i]->rc.top, str, strlen(str));

	}
}

void stageMake::btnClick()
{

	if (PtInRect(&_prev, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (_selectStageNum == 0)
				_selectStageNum = 9;
			else
				_selectStageNum--;
			
			loadMap();
		}
	}
	if (PtInRect(&_next, _ptMouse))
	{

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (_selectStageNum == 9)
				_selectStageNum = 0;
			else
				_selectStageNum++;

			loadMap();
		}
	}
	if (PtInRect(&_save, _ptMouse))
	{
		// 해당 stage에 맵을 저장한다. 
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			char str[100];
			sprintf_s(str, "%s.txt", _stageNames[_selectStageNum].c_str());
			
			COCDB->saveMap(str, _vRect, _offsetX, _offsetY);
		}
	}
	else if (PtInRect(&_cancel, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			SCENEMANAGER->changeScene("mainScene");
		}
	}
	else if (PtInRect(&_remove, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
		}
	}
	else if (PtInRect(&_allRemove, _ptMouse))
	{

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			for (_viRect = _vRect.begin(); _viRect != _vRect.end(); )
			{
				_viRect = _vRect.erase(_viRect);
			}
		}
	}

	
	for (int i = 0; i < _vBuildings.size(); i++)
	{
		if (PtInRect(&_vBuildings[i]->rc, _ptMouse))
		{

			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_selectBuildingType = i;
			}
		}
	}
	

	if (_tile->ptInDiamond())
	{
		_x = _tile->getTouchX();
		_y = _tile->getTouchY();

		if (_vBuildings[_selectBuildingType]->size == 1)
		{
			_bulidingRc = RectMakeCenter((_tile->mapTile[_x][_y].rc.left + _tile->mapTile[_x][_y].rc.right) / 2,
				(_tile->mapTile[_x][_y].rc.top + _tile->mapTile[_x][_y].rc.bottom) / 2, 50, 34);
			_bulidingColiisionRc = RectMakeCenter((_tile->mapTile[_x][_y].rc.left + _tile->mapTile[_x][_y].rc.right) / 2,
				(_tile->mapTile[_x][_y].rc.top + _tile->mapTile[_x][_y].rc.bottom) / 2, 25, 17);
		}
		else if (_vBuildings[_selectBuildingType]->size == 3)
		{
			_bulidingRc = RectMakeCenter((_tile->mapTile[_x][_y].rc.left + _tile->mapTile[_x][_y].rc.right) / 2,
				(_tile->mapTile[_x][_y].rc.top + _tile->mapTile[_x][_y].rc.bottom) / 2, 150, 102);
			_bulidingColiisionRc = RectMakeCenter((_tile->mapTile[_x][_y].rc.left + _tile->mapTile[_x][_y].rc.right) / 2,
				(_tile->mapTile[_x][_y].rc.top + _tile->mapTile[_x][_y].rc.bottom) / 2, 75, 51);
		}

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < _vRect.size(); i++)
			{
				if (IntersectRect(&RectMake(0, 0, 0, 0), &_bulidingColiisionRc, &_vRect[i]->collisionRc))
				{
					_isCollision = true;
					break;
				}
			}

			if (!_isCollision)
			{
				tagSlot* temp = new tagSlot;

				temp->name = _vBuildings[_selectBuildingType]->name;
				temp->img = _vBuildings[_selectBuildingType]->img;
				temp->size = _vBuildings[_selectBuildingType]->size;
				temp->type = _vBuildings[_selectBuildingType]->type;
				temp->level = _vBuildings[_selectBuildingType]->level;
				temp->maxLevel = _vBuildings[_selectBuildingType]->maxLevel;
				temp->maxUpdateTime = _vBuildings[_selectBuildingType]->maxUpdateTime;
				temp->maxCountTime = _vBuildings[_selectBuildingType]->maxCountTime;
				temp->count = _vBuildings[_selectBuildingType]->count;
				temp->currentHp = _vBuildings[_selectBuildingType]->maxHp;
				temp->maxHp = _vBuildings[_selectBuildingType]->maxHp;
				temp->rc = _bulidingRc;
				temp->collisionRc = _bulidingColiisionRc;
				temp->x = _x;
				temp->y = _y;
				temp->topPoint = pointMake((temp->rc.left + temp->rc.right) / 2, temp->rc.top);
				temp->bottomPoint = pointMake((temp->rc.left + temp->rc.right) / 2, temp->rc.bottom);
				temp->rightPoint = pointMake(temp->rc.right, (temp->rc.top + temp->rc.bottom) / 2);
				temp->leftPoint = pointMake(temp->rc.left, (temp->rc.top + temp->rc.bottom) / 2);

				_vRect.push_back(temp);
			}
			else
			{
				_isCollision = false;
			}

		}
	}


}

void stageMake::buildingSlotSetting()
{
	_vBuildings.clear();

	tagSlot* temp = new tagSlot;
	temp->img = IMAGEMANAGER->findImage("goblin_town");
	temp->name = "goblin_town";
	temp->level = 1;
	temp->maxLevel = 1;
	temp->size = 3;
	temp->type = TOWN_HALL;
	temp->maxHp = 100;
	temp->maxUpdateTime = 50.f;
	temp->maxCountTime = 50;
	temp->count = 0;
	temp->rc = RectMake(60, 700, 100, 100);

	_vBuildings.push_back(temp);

	temp = new tagSlot;
	temp->img = IMAGEMANAGER->findImage("wall_1");
	temp->name = "wall";
	temp->level = 1;
	temp->maxLevel = 1;
	temp->size = 1;
	temp->type = WALL;
	temp->maxHp = 100;
	temp->maxUpdateTime = 50.f;
	temp->maxCountTime = 50;
	temp->count = 0;
	temp->rc = RectMake(170, 700, 100, 100);

	_vBuildings.push_back(temp);

	temp = new tagSlot;
	temp->img = IMAGEMANAGER->findImage("mortar_1");
	temp->name = "mortar";
	temp->level = 1;
	temp->maxLevel = 1;
	temp->size = 3;
	temp->type = MORTER;
	temp->maxHp = 100;
	temp->maxUpdateTime = 50.f;
	temp->maxCountTime = 50;
	temp->count = 0;
	temp->rc = RectMake(280, 700, 100, 100);

	_vBuildings.push_back(temp);


}

void stageMake::offsetSetting()
{
	if (_offsetX != _tile->getOffsetX() || _offsetY != _tile->getOffsetY())
	{
		int x = _tile->getOffsetX() - _offsetX;
		int y = _tile->getOffsetY() - _offsetY;

		for (unsigned int i = 0; i < _vRect.size(); i++)
		{
			_vRect[i]->rc = { _vRect[i]->rc.left - x, _vRect[i]->rc.top - y, _vRect[i]->rc.right - x, _vRect[i]->rc.bottom - y };
			_vRect[i]->collisionRc = { _vRect[i]->collisionRc.left - x, _vRect[i]->collisionRc.top - y, _vRect[i]->collisionRc.right - x, _vRect[i]->collisionRc.bottom - y };

			_vRect[i]->topPoint = pointMake((_vRect[i]->rc.left + _vRect[i]->rc.right) / 2, _vRect[i]->rc.top);
			_vRect[i]->leftPoint = pointMake(_vRect[i]->rc.left, (_vRect[i]->rc.top + _vRect[i]->rc.bottom) / 2);
			_vRect[i]->rightPoint = pointMake(_vRect[i]->rc.right, (_vRect[i]->rc.top + _vRect[i]->rc.bottom) / 2);
			_vRect[i]->bottomPoint = pointMake((_vRect[i]->rc.left + _vRect[i]->rc.right) / 2, _vRect[i]->rc.bottom);

		}

		_offsetX = _tile->getOffsetX();
		_offsetY = _tile->getOffsetY();
	}
}

void stageMake::loadMap()
{
	_vRect.clear();
	
	char str[100];
	sprintf_s(str, "%s.txt", _stageNames[_selectStageNum].c_str());

	COCDB->loadMap(str, _offsetX, _offsetY);

	for (int i = 0; i < COCDB->getVMap().size(); i++)
	{
		_vRect.push_back(COCDB->getVMap()[i]);
	}
}
