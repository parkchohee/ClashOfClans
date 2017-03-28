#include "stdafx.h"
#include "playScene.h"


playScene::playScene()
{
}


playScene::~playScene()
{
}

HRESULT playScene::init()
{
	_unitManager = new unitManager;
	_unitManager->init();

	_tile = new TileMapSetting;
	_tile->init();

	_vBuildings.clear();

	_unitManager->setTileMapMomeryLink(_tile);

	_offsetX = _tile->getOffsetX();
	_offsetY = _tile->getOffsetY();
	
	

	mapSetting(selectPlayScene::sceneNum);

	for (int i = 0; i < UNITTYPEMAX; i++)
	{
		_unitRect[i] = RectMake(90 + (i * 286), 700, 250, 100);
	}

	_selectUnitType = 0;


	setTileState();

	_unitManager->setBuildingsMomeryLink(_vBuildings);


	_btnFinish = RectMake(10, 640, 115, 42);

	return S_OK;
}

void playScene::release()
{
	_tile->release();
	SAFE_DELETE(_tile);

	_unitManager->release();
	SAFE_DELETE(_unitManager);

}

void playScene::update()
{
	_tile->update();


	_unitManager->update();

	
	createUnit();
	offsetSetting();
}

void playScene::render()
{
	_tile->render();

	char str[100];

	IMAGEMANAGER->findImage("stage_mark")->render(getMemDC(), 15, 15);

	HFONT myFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Supercell-Magic");
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);
	sprintf_s(str, "stage1");				// 스테이지 이름
	TextOut(getMemDC(), 60, 25, str, strlen(str));	

	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);

	myFont = CreateFont(14, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Supercell-Magic");
	oldFont = (HFONT)SelectObject(getMemDC(), myFont);
	sprintf_s(str, "약탈할 자원");
	TextOut(getMemDC(), 35, 70, str, strlen(str));


	IMAGEMANAGER->findImage("gold_icon")->render(getMemDC(), 15, 90);
	IMAGEMANAGER->findImage("elixir_icon")->render(getMemDC(), 15, 115);
	sprintf_s(str, "%d", _gold);
	TextOut(getMemDC(), 40, 93, str, strlen(str));

	sprintf_s(str, "%d", _elixir);
	TextOut(getMemDC(), 40, 117, str, strlen(str));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);


//	sprintf_s(str, "%d", _selectUnitType);
//	TextOut(getMemDC(), 0, 200, str, strlen(str));



	for (unsigned int i = 0; i < _vBuildings.size(); i++)
	{
	
		if (_vBuildings[i]->size == 1)
		{
			if (_vBuildings[i]->destroyed)
			{
				IMAGEMANAGER->findImage("building_destroyed_1_1")->render(getMemDC(), _vBuildings[i]->rc.left, _vBuildings[i]->rc.top); 
			}
			else
			{
				_vBuildings[i]->img->render(getMemDC(), _vBuildings[i]->rc.left - 13, _vBuildings[i]->rc.top - 27);
			}
		}
		else if (_vBuildings[i]->size == 2)
		{

			IMAGEMANAGER->findImage("building_bottom_2_2")->render(getMemDC(), _vBuildings[i]->rc.left, _vBuildings[i]->rc.top);
			_vBuildings[i]->img->render(getMemDC(), _vBuildings[i]->rc.left + 30, _vBuildings[i]->rc.top - 20);

		}
		else if (_vBuildings[i]->size == 3)
		{
			IMAGEMANAGER->findImage("building_bottom_3_3")->render(getMemDC(), _vBuildings[i]->rc.left, _vBuildings[i]->rc.top);

			if (_vBuildings[i]->destroyed)
			{
				IMAGEMANAGER->findImage("building_destroyed_3_3")->render(getMemDC(), _vBuildings[i]->rc.left, _vBuildings[i]->rc.top);
			}
			else
			{
				_vBuildings[i]->img->render(getMemDC(), _vBuildings[i]->rc.left + 30, _vBuildings[i]->rc.top - 20);
			}
			
		}	
		else if (_vBuildings[i]->size == 4)
		{
			IMAGEMANAGER->findImage("building_bottom_4_4")->render(getMemDC(), _vBuildings[i]->rc.left, _vBuildings[i]->rc.top);
			_vBuildings[i]->img->render(getMemDC(), _vBuildings[i]->rc.left + 30, _vBuildings[i]->rc.top - 20);

		}

		//Rectangle(getMemDC(), _vBuildings[i]->rc.left, _vBuildings[i]->rc.top, _vBuildings[i]->rc.right, _vBuildings[i]->rc.bottom);

		//Rectangle(getMemDC(), _vBuildings[i]->collisionRc.left, _vBuildings[i]->collisionRc.top, _vBuildings[i]->collisionRc.right, _vBuildings[i]->collisionRc.bottom);
		

	//	sprintf_s(str, "%d %d", _vBuildings[i]->currentHp, _vBuildings[i]->maxHp);
	//	TextOut(getMemDC(), _vBuildings[i]->rc.left, _vBuildings[i]->rc.top, str, strlen(str));

	}
	for (int i = 0; i < _vBuildings.size(); i++)
	{
		if (_vBuildings[i]->currentHp != _vBuildings[i]->maxHp && !_vBuildings[i]->destroyed)
		{
			IMAGEMANAGER->findImage("hpBarBottom")->render(getMemDC(), _vBuildings[i]->rc.left + 40, _vBuildings[i]->rc.top - 20);
			IMAGEMANAGER->findImage("hpBarTop")->render(getMemDC(), _vBuildings[i]->rc.left + 40, _vBuildings[i]->rc.top - 20, 0, 0, ((float)_vBuildings[i]->currentHp / (float)_vBuildings[i]->maxHp) * 62, 12);
		}
	}

	_unitManager->render();

	IMAGEMANAGER->findImage("selectUnit")->render(getMemDC(), _unitRect[_selectUnitType].left - 11, _unitRect[_selectUnitType].top - 10);

	IMAGEMANAGER->findImage("money_slot")->render(getMemDC(), 1090, 10);
	IMAGEMANAGER->findImage("btn_attack_finish")->render(getMemDC(), 10, 640);
	

}

void playScene::mapSetting(int stageNum)
{
	char str[100];
	sprintf_s(str, "stage%d.txt", stageNum + 1);

	_vBuildings.clear();

	COCDB->loadMap(str, _offsetX, _offsetY);
	
	for (int i = 0; i < COCDB->getVMap().size(); i++)
	{
		_vBuildings.push_back(COCDB->getVMap()[i]);
	}
}

void playScene::offsetSetting()
{
	if (_offsetX != _tile->getOffsetX() || _offsetY != _tile->getOffsetY())
	{
		int x = _tile->getOffsetX() - _offsetX;
		int y = _tile->getOffsetY() - _offsetY;

		for (unsigned int i = 0; i < _vBuildings.size(); i++)
		{
			_vBuildings[i]->rc = { _vBuildings[i]->rc.left - x, _vBuildings[i]->rc.top - y, _vBuildings[i]->rc.right - x, _vBuildings[i]->rc.bottom - y };
			_vBuildings[i]->collisionRc = { _vBuildings[i]->collisionRc.left - x, _vBuildings[i]->collisionRc.top - y, _vBuildings[i]->collisionRc.right - x, _vBuildings[i]->collisionRc.bottom - y };

			_vBuildings[i]->topPoint = pointMake((_vBuildings[i]->rc.left + _vBuildings[i]->rc.right) / 2, _vBuildings[i]->rc.top);
			_vBuildings[i]->leftPoint = pointMake(_vBuildings[i]->rc.left, (_vBuildings[i]->rc.top + _vBuildings[i]->rc.bottom) / 2);
			_vBuildings[i]->rightPoint = pointMake(_vBuildings[i]->rc.right, (_vBuildings[i]->rc.top + _vBuildings[i]->rc.bottom) / 2);
			_vBuildings[i]->bottomPoint = pointMake((_vBuildings[i]->rc.left + _vBuildings[i]->rc.right) / 2, _vBuildings[i]->rc.bottom);
		}

		for (unsigned int i = 0; i < _unitManager->getUnits().size(); i++)
		{
			_unitManager->getUnits()[i]->setOffset(x, y);
		}

		_offsetX = _tile->getOffsetX();
		_offsetY = _tile->getOffsetY();
	}

	setTileState();
}

void playScene::createUnit()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_btnFinish, _ptMouse))
		{
			SCENEMANAGER->changeScene("mainScene");
		}

		for (int i = 0; i < UNITTYPEMAX; i++)
		{
			if (PtInRect(&_unitRect[i], _ptMouse))
			{
				_selectUnitType = i;
				break;
			}
		
		}

		if (_tile->ptInDiamond() &&
			!PtInRect(&_unitRect[0], _ptMouse) &&
			!PtInRect(&_unitRect[1], _ptMouse) &&
			!PtInRect(&_unitRect[2], _ptMouse) &&
			!PtInRect(&_unitRect[3], _ptMouse))
		{
			switch (_selectUnitType)
			{
			case 0:
				_unitManager->fire("barbarian", 1.5, 3, BARBARIAN, pointMake(_tile->mapTile[_tile->getTouchX()][_tile->getTouchY()].p1.x, _tile->mapTile[_tile->getTouchX()][_tile->getTouchY()].p2.y),
					pointMake(_tile->getTouchX(), _tile->getTouchY()));
				break;
			case 1:
				_unitManager->fire("giant", 1.5, 5, GIANT, pointMake(_tile->mapTile[_tile->getTouchX()][_tile->getTouchY()].p1.x, _tile->mapTile[_tile->getTouchX()][_tile->getTouchY()].p2.y),
					pointMake(_tile->getTouchX(), _tile->getTouchY()));
				break;
			case 2:
				_unitManager->fire("barbarian", 1.5, 3, WALL_BRAKER, pointMake(_tile->mapTile[_tile->getTouchX()][_tile->getTouchY()].p1.x, _tile->mapTile[_tile->getTouchX()][_tile->getTouchY()].p2.y),
					pointMake(_tile->getTouchX(), _tile->getTouchY()));
				break;
			case 3:
				_unitManager->fire("archer", 1.5, 3, ARCHER, pointMake(_tile->mapTile[_tile->getTouchX()][_tile->getTouchY()].p1.x, _tile->mapTile[_tile->getTouchX()][_tile->getTouchY()].p2.y),
					pointMake(_tile->getTouchX(), _tile->getTouchY()));
				break;
			}
		}
	
	}
}

void playScene::setTileState()
{
	for (unsigned int i = 0; i < _vBuildings.size(); i++)
	{
		if(_vBuildings[i]->type != 0)
			_tile->mapTile[_vBuildings[i]->x][_vBuildings[i]->y].state = START_NODE;
		if (_vBuildings[i]->type == 8)
			_tile->mapTile[_vBuildings[i]->x][_vBuildings[i]->y].state = WALL_NODE;
	}
}