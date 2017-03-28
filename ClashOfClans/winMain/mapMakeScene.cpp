#include "stdafx.h"
#include "mapMakeScene.h"


mapMakeScene::mapMakeScene()
{
}


mapMakeScene::~mapMakeScene()
{
}

HRESULT mapMakeScene::init()
{
	_tile = new TileMapSetting;
	_tile->init();

	
	string str[] = { 
		"town_hall_1", "town_hall_2", "town_hall_3", "town_hall_4", "town_hall_5", "town_hall_6", "town_hall_7",
		"elixir_collector_1","elixir_collector_2","elixir_collector_3","elixir_collector_4","elixir_collector_5",
		"elixir_storage_1", "elixir_storage_2","elixir_storage_3","elixir_storage_4","elixir_storage_5","elixir_storage_6",
		"gold_mine_1", "gold_mine_2","gold_mine_3","gold_mine_4","gold_mine_5",
		"gold_storage_1", "gold_storage_2","gold_storage_3","gold_storage_4","gold_storage_5","gold_storage_6",
		"barracks_1","barracks_2","barracks_3","barracks_4","barracks_5",
		"builder_hut_1", 
		"wall_1",
		"" };

	
	// 건물 수 파악..
	_totalBuildingSlotCount = 0;
	_totalBuildingCount = 0;

	_buildingSlot.clear();
	_vRect.clear();

	COCDB->loadAllBuildings("playerBuildingsInfo.txt");

	for (int j = 0; j < 37; j++)
	{
		if (COCDB->getElementData(str[j])->count > 0)
		{
			_totalBuildingSlotCount++;

			tagSlot* temp = new tagSlot;
			temp = COCDB->getElementData(str[j]);
			_totalBuildingCount += temp->count;

			_buildingSlot.push_back(temp);
		}
	}

	for (int i = 0; i < _totalBuildingSlotCount; i++)
	{
		_buildingSlot[i]->rc = RectMake(50 + 110 * i, 700, 100, 100);
	}

	_x = 0;
	_y = 0;

	_offsetX = 0; 
	_offsetY = 0;

	_buildingSelect = false;
	_buildingCollision = false;
	_deleteMode = false;

	btnDelete = RectMake(1135, 25, 150, 30);
	btnDeleteAll = RectMake(1135, 72, 150, 30);
	btnSave = RectMake(1135, 119, 150, 30);
	btnCancel = RectMake(1135, 168, 150, 30);

	return S_OK;
}

void mapMakeScene::release()
{
	_tile->release();
	SAFE_DELETE(_tile);
}

void mapMakeScene::update()
{
	_tile->update();

	offsetSetting();

	makeBuilding();
	buildingCollision();
	buildingListSwap();

	btnClickListener();
}

void mapMakeScene::render()
{
	_tile->render();



	char str[100];
	//sprintf_s(str, "%d, %d", _x, _y);
	//TextOut(getMemDC(), 0, 100, str, strlen(str));

	//sprintf_s(str, "%d %d", _totalBuildingSlotCount, _totalBuildingCount);
	//TextOut(getMemDC(), 0, 120, str, strlen(str));
	
	// 벽 그림 맞게 설정하기....




	for (unsigned int i = 0; i < _vRect.size(); i++)
	{
		//Rectangle(getMemDC(), _vRect[i]->rc.left, _vRect[i]->rc.top, _vRect[i]->rc.right, _vRect[i]->rc.bottom);

		if (_vRect[i]->size == 1)
		{
			if (_buildingCollision && i == _vRect.size() - 1)
				IMAGEMANAGER->findImage("building_bottom_1_1_error")->render(getMemDC(), _vRect[i]->rc.left, _vRect[i]->rc.top);

			_vRect[i]->img->render(getMemDC(), _vRect[i]->rc.left- 13, _vRect[i]->rc.top - 27);

	//		sprintf_s(str, "%d, %d", _vRect[i]->x, _vRect[i]->y);
	//		TextOut(getMemDC(), _vRect[i]->rc.left, _vRect[i]->rc.top, str, strlen(str));

		}
		else if (_vRect[i]->size == 2)
		{
			if (_buildingCollision && i == _vRect.size() - 1)
				IMAGEMANAGER->findImage("building_bottom_2_2_error")->render(getMemDC(), _vRect[i]->rc.left, _vRect[i]->rc.top);
			else
				IMAGEMANAGER->findImage("building_bottom_2_2")->render(getMemDC(), _vRect[i]->rc.left, _vRect[i]->rc.top);
			
			_vRect[i]->img->render(getMemDC(), _vRect[i]->rc.left, _vRect[i]->rc.top - 34);
			
		}
		else if (_vRect[i]->size == 3)
		{
			if(_buildingCollision && i == _vRect.size() - 1)
				IMAGEMANAGER->findImage("building_bottom_3_3_error")->render(getMemDC(), _vRect[i]->rc.left, _vRect[i]->rc.top);
			else
				IMAGEMANAGER->findImage("building_bottom_3_3")->render(getMemDC(), _vRect[i]->rc.left, _vRect[i]->rc.top);
			
			_vRect[i]->img->render(getMemDC(), _vRect[i]->rc.left, _vRect[i]->rc.top - 45);
			
		}
		else if (_vRect[i]->size == 4)
		{
			if (_buildingCollision && i == _vRect.size() - 1)
				IMAGEMANAGER->findImage("building_bottom_4_4_error")->render(getMemDC(), _vRect[i]->rc.left, _vRect[i]->rc.top);
			else
				IMAGEMANAGER->findImage("building_bottom_4_4")->render(getMemDC(), _vRect[i]->rc.left, _vRect[i]->rc.top);
			
			_vRect[i]->img->render(getMemDC(), _vRect[i]->rc.left, _vRect[i]->rc.top - 120);
		}	

	//	sprintf_s(str, "%d, %d", _vRect[i]->x, _vRect[i]->y);
	//	TextOut(getMemDC(), _vRect[i]->rc.left, _vRect[i]->rc.top, str, strlen(str));

	}

	IMAGEMANAGER->findImage("title_map_setting_mode")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("slot_background_bottom")->render(getMemDC(), 0, 660);
	IMAGEMANAGER->findImage("save_btn_map_setting_mode")->render(getMemDC(), 1069, 0);

	for (unsigned int i = 0; i < _buildingSlot.size(); i++)
	{
		IMAGEMANAGER->findImage("slot_background")->render(getMemDC(), _buildingSlot[i]->rc.left, _buildingSlot[i]->rc.top);
		if(_buildingSlot[i]->size == 3)
			_buildingSlot[i]->img->render(getMemDC(),_buildingSlot[i]->rc.left - 20, _buildingSlot[i]->rc.top - 20);
		else if(_buildingSlot[i]->size == 4)
			_buildingSlot[i]->img->render(getMemDC(), _buildingSlot[i]->rc.left - 40, _buildingSlot[i]->rc.top - 100);
		else
			_buildingSlot[i]->img->render(getMemDC(), _buildingSlot[i]->rc.left, _buildingSlot[i]->rc.top);
	}


}

void mapMakeScene::offsetSetting()
{
	if (_offsetX != _tile->getOffsetX() || _offsetY != _tile->getOffsetY())
	{
		int x = _tile->getOffsetX() - _offsetX;
		int y = _tile->getOffsetY() - _offsetY;

		for (unsigned int i = 0; i < _vRect.size(); i++)
		{
			_vRect[i]->rc = { _vRect[i]->rc.left - x, _vRect[i]->rc.top - y, _vRect[i]->rc.right - x, _vRect[i]->rc.bottom - y };

			_vRect[i]->topPoint = pointMake((_vRect[i]->rc.left + _vRect[i]->rc.right) / 2, _vRect[i]->rc.top);
			_vRect[i]->leftPoint = pointMake(_vRect[i]->rc.left, (_vRect[i]->rc.top + _vRect[i]->rc.bottom) / 2);
			_vRect[i]->rightPoint = pointMake(_vRect[i]->rc.right, (_vRect[i]->rc.top + _vRect[i]->rc.bottom) / 2);
			_vRect[i]->bottomPoint = pointMake((_vRect[i]->rc.left + _vRect[i]->rc.right) / 2, _vRect[i]->rc.bottom);

		}

		_offsetX = _tile->getOffsetX();
		_offsetY = _tile->getOffsetY();
	}

}

void mapMakeScene::makeBuilding()
{
	if (!_buildingSelect)
	{
		for (unsigned int i = 0; i < _buildingSlot.size(); i++)
		{
			if (PtInRect(&_buildingSlot[i]->rc, _ptMouse))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					if (_buildingSlot[i]->count > 0)
					{
						_selectSlotNum = i;
						_buildingSlot[i]->count--;

						tagSlot* temp = new tagSlot;
						
						temp->name = _buildingSlot[i]->name;
						temp->img = _buildingSlot[i]->img;
						temp->size = _buildingSlot[i]->size;
						temp->type = _buildingSlot[i]->type;
						temp->level = _buildingSlot[i]->level;
						temp->maxLevel = _buildingSlot[i]->maxLevel;
						temp->maxUpdateTime = _buildingSlot[i]->maxUpdateTime;
						temp->maxCountTime = _buildingSlot[i]->maxCountTime;
						temp->count = 0.0f;
						temp->maxHp = _buildingSlot[i]->maxHp;
						temp->rc = RectMakeCenter(_ptMouse.x, _ptMouse.y, 25, 15);
						temp->topPoint = pointMake(0, 0);
						temp->bottomPoint = pointMake(0, 0);
						temp->rightPoint = pointMake(0, 0);
						temp->leftPoint = pointMake(0, 0);

						_vRect.push_back(temp);

						_buildingSelect = true;
					}					
				}
			}
		}
	}

	// 어떤 빌딩을 놓을지 선택함..
	if (_buildingSelect)
	{
		if (_tile->ptInDiamond())
		{
			_x = _tile->getTouchX();
			_y = _tile->getTouchY();

			// 놓을자리 선택 하면 빌딩을 움직이지 않음..
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (!_buildingCollision)
				{
					_buildingSelect = false;
					_buildingCollision = false;
					_totalBuildingCount--;
				}				
			}
			else // 마우스 움직이는중.. 위치에따라 렉트 셋팅...
			{
				if (_buildingSelect && _vRect.size() > 0)
				{
					if (_vRect[_vRect.size() - 1]->size == 1)
					{
						_vRect[_vRect.size() - 1]->rc = RectMakeCenter((_tile->mapTile[_x][_y].rc.left + _tile->mapTile[_x][_y].rc.right) / 2,
							(_tile->mapTile[_x][_y].rc.top + _tile->mapTile[_x][_y].rc.bottom) / 2, 50, 34);
					}
					else if (_vRect[_vRect.size() - 1]->size == 2)
					{
						
						_vRect[_vRect.size() - 1]->rc = RectMakeCenter((_tile->mapTile[_x][_y].rc.left + _tile->mapTile[_x][_y].rc.right) / 2,
							_tile->mapTile[_x][_y].rc.top, 100, 68);
					}
					else if (_vRect[_vRect.size() - 1]->size == 3)
					{

						_vRect[_vRect.size() - 1]->rc = RectMakeCenter((_tile->mapTile[_x][_y].rc.left + _tile->mapTile[_x][_y].rc.right) / 2,
							(_tile->mapTile[_x][_y].rc.top + _tile->mapTile[_x][_y].rc.bottom) / 2, 150, 102);

					}
					else if (_vRect[_vRect.size() - 1]->size == 4)
					{
						_vRect[_vRect.size() - 1]->rc = RectMakeCenter((_tile->mapTile[_x][_y].rc.left + _tile->mapTile[_x][_y].rc.right) / 2,
							_tile->mapTile[_x][_y].rc.top, 200, 136);
					}

					_vRect[_vRect.size() - 1]->x = _x;
					_vRect[_vRect.size() - 1]->y = _y;

					_vRect[_vRect.size() - 1]->topPoint = pointMake((_vRect[_vRect.size() - 1]->rc.left + _vRect[_vRect.size() - 1]->rc.right) / 2, _vRect[_vRect.size() - 1]->rc.top);
					_vRect[_vRect.size() - 1]->bottomPoint = pointMake((_vRect[_vRect.size() - 1]->rc.left + _vRect[_vRect.size() - 1]->rc.right) / 2, _vRect[_vRect.size() - 1]->rc.bottom);
					_vRect[_vRect.size() - 1]->rightPoint = pointMake(_vRect[_vRect.size() - 1]->rc.right, (_vRect[_vRect.size() - 1]->rc.top + _vRect[_vRect.size() - 1]->rc.bottom) / 2);
					_vRect[_vRect.size() - 1]->leftPoint = pointMake(_vRect[_vRect.size() - 1]->rc.left, (_vRect[_vRect.size() - 1]->rc.top + _vRect[_vRect.size() - 1]->rc.bottom) / 2);

				}
			}
		}
		else {
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_buildingSlot[_selectSlotNum]->count++;
				_vRect.erase(_vRect.begin() + _vRect.size() - 1);

				_buildingSelect = false;
				_buildingCollision = false;
			}
		}
	}

}

void mapMakeScene::buildingCollision()
{
	if (_vRect.size() > 1)
	{
		POINT topPoint = pointMake(_vRect[_vRect.size() - 1]->topPoint.x, _vRect[_vRect.size() - 1]->topPoint.y + 10);
		POINT leftPoint = pointMake(_vRect[_vRect.size() - 1]->leftPoint.x + 10, _vRect[_vRect.size() - 1]->leftPoint.y);
		POINT bottomPoint = pointMake(_vRect[_vRect.size() - 1]->bottomPoint.x, _vRect[_vRect.size() - 1]->bottomPoint.y - 10);
		POINT rightPoint = pointMake(_vRect[_vRect.size() - 1]->rightPoint.x - 10, _vRect[_vRect.size() - 1]->rightPoint.y);
		POINT centerPoint = pointMake((_vRect[_vRect.size() - 1]->rc.left + _vRect[_vRect.size() - 1]->rc.right) / 2,
			(_vRect[_vRect.size() - 1]->rc.top + _vRect[_vRect.size() - 1]->rc.bottom) / 2);

		for (unsigned int i = 0; i < _vRect.size() - 1; i++)
		{
			_buildingCollision = false;

			// 마름모 기울기
			float m = (float)(_vRect[i]->rc.bottom - _vRect[i]->rc.top) / (float)(_vRect[i]->rc.right - _vRect[i]->rc.left);
		
			if (_tile->diaCollisionCheck(topPoint, m, _vRect[i]->topPoint, _vRect[i]->leftPoint, _vRect[i]->bottomPoint, _vRect[i]->rightPoint) ||
				_tile->diaCollisionCheck(leftPoint, m, _vRect[i]->topPoint, _vRect[i]->leftPoint, _vRect[i]->bottomPoint, _vRect[i]->rightPoint) ||
				_tile->diaCollisionCheck(bottomPoint, m, _vRect[i]->topPoint, _vRect[i]->leftPoint, _vRect[i]->bottomPoint, _vRect[i]->rightPoint) ||
				_tile->diaCollisionCheck(rightPoint, m, _vRect[i]->topPoint, _vRect[i]->leftPoint, _vRect[i]->bottomPoint, _vRect[i]->rightPoint) ||
				_tile->diaCollisionCheck(centerPoint, m, _vRect[i]->topPoint, _vRect[i]->leftPoint, _vRect[i]->bottomPoint, _vRect[i]->rightPoint))
			{
				//충돌했다.
				_buildingCollision = true;
				break;
			}
		}
	}
}

void mapMakeScene::buildingListSwap()
{
	// _vRect를 x가 작은것부터 출력하도록한다. 
	// x가 같은것들은 y가 작은것부터 출력하도록 한다.

	

}

void mapMakeScene::btnClickListener()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&btnDelete, _ptMouse))
		{
			_deleteMode = !_deleteMode;
		}
		else if (PtInRect(&btnDeleteAll, _ptMouse))
		{
			init();
		}
		else if (PtInRect(&btnSave, _ptMouse))
		{
			if (_totalBuildingCount < 1)
			{
				// 파일을 저장한다. 
				COCDB->saveMap("playerMapInfo.txt", _vRect, _offsetX, _offsetY);


				// main씬으로 이동한다. 
				SCENEMANAGER->changeScene("mainScene");
				
			}
			else
			{
				// 모든 건물을 배치해주세요 .  알림 메세지 보여주기..
			}
		}
		else if (PtInRect(&btnCancel, _ptMouse))
		{ 
			SCENEMANAGER->changeScene("mainScene");
		}

		if (_deleteMode)
		{
			for (int i = 0; i < _vRect.size(); i++)
			{
				// 마름모 기울기
				float m = (float)(_vRect[i]->rc.bottom - _vRect[i]->rc.top) / (float)(_vRect[i]->rc.right - _vRect[i]->rc.left);

				if (_tile->diaCollisionCheck(_ptMouse, m, _vRect[i]->topPoint, _vRect[i]->leftPoint, _vRect[i]->bottomPoint, _vRect[i]->rightPoint))
				{
					//충돌했다.
					// 삭제해준다.
					//_vRect.erase(_vRect.begin() + i);

					break;
				}
								
			}
		}
	}
}

