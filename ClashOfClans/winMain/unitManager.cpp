#include "stdafx.h"
#include "unitManager.h"


unitManager::unitManager()
{
}


unitManager::~unitManager()
{
}

HRESULT unitManager::init()
{
	_gamePlay = true;
	_search = true;
	_finishBtn = RectMake(0,0,0,0);

	unitSetting();

	return S_OK;
}

void unitManager::release()
{
}

void unitManager::update()
{
	if (_gamePlay)
	{
		for (int i = 0; i < _vUnit.size(); i++)
		{
			_vUnit[i]->update();
		}

		buildingCount();
		unitBuildingCollisionCheck();
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (PtInRect(&_finishBtn, _ptMouse))
			{
				SCENEMANAGER->changeScene("mainScene");
			}
		}
	}
}

void unitManager::render()
{
	for (int i = 0; i < _vUnit.size(); i++)
	{
		_vUnit[i]->render();
	}

	char str[100];
	/*sprintf_s(str, "%d %d %d %d %f", _vUnit.size(), _buildingCount, _attackBuildingCount, _totalBuildingCount, _destoryedPer);
	TextOut(getMemDC(), 0,150, str, strlen(str));
	sprintf_s(str, "%d %d %d %d", _unitCount[0], _unitCount[1], _unitCount[2], _unitCount[3]);
	TextOut(getMemDC(), 0, 170, str, strlen(str));*/

	IMAGEMANAGER->findImage("star_slot")->render(getMemDC(), 1133, 630);
	IMAGEMANAGER->findImage("unit_slot_bottom")->render(getMemDC(), 0, 689);


	HFONT myFont = CreateFont(17, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Supercell-Magic");
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);
	sprintf_s(str, "%.0f %%", _destoryedPer * 100);		
	TextOut(getMemDC(), 1175, 640, str, strlen(str));
	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);

	myFont = CreateFont(23, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Supercell-Magic");
	oldFont = (HFONT)SelectObject(getMemDC(), myFont);
	sprintf_s(str, "x %d", _unitCount[0]);
	TextOut(getMemDC(), 90, 720, str, strlen(str));
	sprintf_s(str, "x %d", _unitCount[1]);
	TextOut(getMemDC(), 380, 720, str, strlen(str));
	sprintf_s(str, "x %d", _unitCount[2]);
	TextOut(getMemDC(), 670, 720, str, strlen(str));
	sprintf_s(str, "x %d", _unitCount[3]);
	TextOut(getMemDC(), 960, 720, str, strlen(str));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);


	if (!_gamePlay)
	{
		saveUnit();

		if (_destoryedPer < 0.2f)
			IMAGEMANAGER->findImage("playScene_finish_pop_0")->render(getMemDC(), 190, 150);
		else if(_destoryedPer < 0.5f)
			IMAGEMANAGER->findImage("playScene_finish_pop_1")->render(getMemDC(), 190, 150);
		else if (_destoryedPer < 0.99f)
			IMAGEMANAGER->findImage("playScene_finish_pop_2")->render(getMemDC(), 190, 150);
		else 
			IMAGEMANAGER->findImage("playScene_finish_pop_3")->render(getMemDC(), 190, 150);

		HFONT myFont = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Supercell-Magic");
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);
		sprintf_s(str, "%.0f%%", _destoryedPer * 100);
		TextOut(getMemDC(), 580, 210, str, strlen(str));
		SelectObject(getMemDC(), oldFont);
		DeleteObject(myFont);

	//	Rectangle(getMemDC(), _finishBtn.left, _finishBtn.top, _finishBtn.right, _finishBtn.bottom);

	}
}

void unitManager::fire(string name, float speed, int pow, int type, POINT startPoint, POINT startPosition)
{
	if (_unitCount[type] > 0)
	{
		units* tempUnit = new units;
		tempUnit->init(startPoint.x, startPoint.y, 0, speed, pow, type, startPosition, name);

		tileInit();
		_tile->mapTile[startPosition.x][startPosition.y].state = END_NODE;

		tempUnit->setAStarWay(getWay(startPosition, type));
		tempUnit->setSearch(_search);
		_vUnit.push_back(tempUnit);

		_unitCount[type]--;
	}

}

void unitManager::unitBuildingCollisionCheck()
{
	// 유닛들과 빌딩이 충돌하면 해당 유닛의 state를 변경해준다..
	for (int j = 0; j < _vUnit.size(); j++)
	{
		for (int i = 0; i < _vBuildings.size(); i++)
		{
			if (IntersectRect(&RectMake(0, 0, 0, 0), &_vBuildings[i]->collisionRc, &_vUnit[j]->getRect()))
			{
				if (_vUnit[j]->getSearch())
				{
					if (_vBuildings[i]->type == WALL && _vUnit[j]->getType() != WALL_BRAKER) continue;
					if (_vBuildings[i]->type != WALL && _vUnit[j]->getType() == WALL_BRAKER) continue;
					if (_vBuildings[i]->type != MORTER && _attackBuildingCount != 0 && _vUnit[j]->getType() == GIANT) continue;
				}

				if (_vBuildings[i]->destroyed)
				{
					_tile->pointInDiamond(_vUnit[j]->getX(), _vUnit[j]->getY());
					
					_vUnit[j]->setAStarWay(getWay(pointMake(_tile->getTouchX(), _tile->getTouchY()), _vUnit[j]->getType()));
					_vUnit[j]->setSearch(_search);
					_vUnit[j]->setUnitState(0);
				}
				else
				{
					_vUnit[j]->setUnitState(1);
					
					if(!_vUnit[j]->getAttacked())
						_vBuildings[i]->attack(_vUnit[j]->getPower());
				}
			}
		}
	}
}

void unitManager::buildingCount()
{
	_buildingCount = _attackBuildingCount = 0;
	_totalBuildingCount = 0;

	for (int i = 0; i < _vBuildings.size(); i++)
	{
		if (_vBuildings[i]->type == WALL) continue;

		_totalBuildingCount++;

		if (_vBuildings[i]->destroyed) continue;

		if (_vBuildings[i]->type == MORTER) _attackBuildingCount++;
		_buildingCount++;

		
	}

	_destoryedPer = 1.f - (float)_buildingCount / (float)_totalBuildingCount;

	if (_buildingCount == 0)
	{
		_gamePlay = false;
		_finishBtn = RectMake(550,550,130,50);
	}

	if (_vUnit.size() == 0 && _unitCount[0] == 0 && _unitCount[1] == 0 &&
		_unitCount[2] == 0 && _unitCount[3] == 0)
	{
		_gamePlay = false;
		_finishBtn = RectMake(550, 550, 130, 50);
	}

	

}

vector<POINT> unitManager::getWay(POINT position, int type)
{
	vector<POINT> bestWay;			
	vector<POINT> way;

	int minSize = 1000;
	_search = true;

	for (int i = 0; i < _vBuildings.size(); i++)
	{
		if (_vBuildings[i]->destroyed) continue;
		if (type == GIANT && _attackBuildingCount != 0 && _vBuildings[i]->type != MORTER) continue;
		
		if ((_vBuildings[i]->type != WALL && type != WALL_BRAKER) || 
			(_vBuildings[i]->type == WALL && type == WALL_BRAKER))
		{
			tileInit();

			_tile->mapTile[_vBuildings[i]->x][_vBuildings[i]->y].state = START_NODE;
			_tile->mapTile[position.x][position.y].state = END_NODE;

			_startNodePoint = pointMake(_vBuildings[i]->x, _vBuildings[i]->y);
			_endNodePoint = position;

			_searchPoint = _startNodePoint;

			// 경로구한다...
			int count = 0;
			while (true)
			{
				count++;
				if (count > TILEMAX * TILEMAX)
					break;

				if (aStarFunc())
					break;
			}

			if (_endSearch)
			{
				tagTile* temp;
				temp = &_tile->mapTile[_endNodePoint.x][_endNodePoint.y];

				while (true)
				{
					if (temp->parent != NULL)
					{
						if (temp->parent->x == _startNodePoint.x && temp->parent->y == _startNodePoint.y) break;

						way.push_back(pointMake(_tile->mapTile[temp->parent->x][temp->parent->y].p1.x, _tile->mapTile[temp->parent->x][temp->parent->y].p2.y));

						temp = temp->parent;
						continue;
					}

					break;
				}

				_endSearch = false;
			}

			// 최단거리로 셋팅
			if (_searchValue < minSize && way.size() != 0)
			{
				minSize = _searchValue;
				bestWay.clear();
				bestWay.assign(way.begin(), way.end());
			}

			way.clear();
		}

	}

	// 길이 없음.... 
	if (bestWay.size() == 0)
	{
		_search = false;

		for (int i = 0; i < _vBuildings.size(); i++)
		{
			if (_vBuildings[i]->destroyed) continue;
			if (type == GIANT && _attackBuildingCount != 0 && _vBuildings[i]->type != MORTER) continue;

			
				tileInit();

				_tile->mapTile[_vBuildings[i]->x][_vBuildings[i]->y].state = START_NODE;
				_tile->mapTile[position.x][position.y].state = END_NODE;

				_startNodePoint = pointMake(_vBuildings[i]->x, _vBuildings[i]->y);
				_endNodePoint = position;

				_searchPoint = _startNodePoint;

				// 경로구한다...
				int count = 0;
				while (true)
				{
					count++;
					if (count > TILEMAX * TILEMAX)
						break;

					if (aStarFunc())
						break;
				}

				if (_endSearch)
				{
					tagTile* temp;
					temp = &_tile->mapTile[_endNodePoint.x][_endNodePoint.y];

					while (true)
					{
						if (temp->parent != NULL)
						{
							if (temp->parent->x == _startNodePoint.x && temp->parent->y == _startNodePoint.y) break;

							way.push_back(pointMake(_tile->mapTile[temp->parent->x][temp->parent->y].p1.x, _tile->mapTile[temp->parent->x][temp->parent->y].p2.y));

							temp = temp->parent;
							continue;
						}

						break;
					}

					_endSearch = false;
				}

				// 최단거리로 셋팅
				if (_searchValue < minSize && way.size() != 0)
				{
					minSize = _searchValue;
					bestWay.clear();
					bestWay.assign(way.begin(), way.end());
				}

				way.clear();
			

		}
	}
	

	return bestWay;
}

bool unitManager::aStarFunc()
{
	int minNum = 10000;

	for (int i = 0; i < TILEMAX; i++)
	{
		for (int j = 0; j < TILEMAX; j++)
		{
			if (_tile->mapTile[j][i].state == OPEN_LIST || _tile->mapTile[j][i].state == END_NODE)
			{
				if (_tile->mapTile[j][i].F < minNum)
				{
					_searchPoint = pointMake(_tile->mapTile[j][i].x, _tile->mapTile[j][i].y);
					minNum = _tile->mapTile[j][i].F;
				}
			}
		}
	}

	if (_tile->mapTile[_searchPoint.x][_searchPoint.y].state == END_NODE)
	{
		_endSearch = true;
		_searchValue = _tile->mapTile[_endNodePoint.x][_endNodePoint.y].F;
		return _endSearch;
	}


	if (!(_searchPoint.x == _startNodePoint.x && _searchPoint.y == _startNodePoint.y))
	{
		_tile->mapTile[_searchPoint.x][_searchPoint.y].state = CLOSE_LIST;
	}

	for (int i = (_searchPoint.y - 1); i <= (_searchPoint.y + 1); i++)
	{
		if (i < 0 || i > TILEMAX - 1) continue;

		for (int j = _searchPoint.x - 1; j <= _searchPoint.x + 1; j++)
		{
			if (j < 0 || j > TILEMAX - 1) continue;

			if (_tile->mapTile[_searchPoint.x][i].state == WALL_NODE) continue;
			if (_tile->mapTile[j][_searchPoint.y].state == WALL_NODE) continue;

			if (j == _searchPoint.x && i == _searchPoint.y) continue;
			if (_tile->mapTile[j][i].state == START_NODE ||
				_tile->mapTile[j][i].state == WALL_NODE ||
				_tile->mapTile[j][i].state == CLOSE_LIST) continue;

			_tile->mapTile[j][i].G = (abs(_endNodePoint.x - j) + abs(_endNodePoint.y - i)) * (TILEMAX - 1);

			if (j == _searchPoint.x || i == _searchPoint.y)
			{
				if (_tile->mapTile[j][i].H > _tile->mapTile[_searchPoint.x][_searchPoint.y].H + (TILEMAX - 1) || _tile->mapTile[j][i].H == 0)
				{
					_tile->mapTile[j][i].H = _tile->mapTile[_searchPoint.x][_searchPoint.y].H + 10;
					_tile->mapTile[j][i].parent = &_tile->mapTile[_searchPoint.x][_searchPoint.y];
				}
			}
			else
			{
				if (_tile->mapTile[j][i].H > _tile->mapTile[_searchPoint.x][_searchPoint.y].H + (TILEMAX - 1) || _tile->mapTile[j][i].H == 0)
				{
					_tile->mapTile[j][i].H = _tile->mapTile[_searchPoint.x][_searchPoint.y].H + 14;
					_tile->mapTile[j][i].parent = &_tile->mapTile[_searchPoint.x][_searchPoint.y];
				}
			}

			if (_tile->mapTile[j][i].F > _tile->mapTile[j][i].G + _tile->mapTile[j][i].H)
				_tile->mapTile[j][i].F = _tile->mapTile[j][i].G + _tile->mapTile[j][i].H;

			if (_tile->mapTile[j][i].state != END_NODE)
				_tile->mapTile[j][i].state = OPEN_LIST;
		}
	}

	int count = 0;
	for (int i = 0; i < TILEMAX; i++)
	{
		for (int j = 0; j < TILEMAX; j++)
		{
			if (_tile->mapTile[j][i].state == NORMAL_NODE)
				count++;
		}
	}

	if (count == 0)
		return true;

	return _endSearch;
}

void unitManager::tileInit()
{
	for (int i = 0; i < TILEMAX; i++)
	{
		for (int j = 0; j < TILEMAX; j++)
		{
			_tile->mapTile[j][i].parent = NULL;
			_tile->mapTile[j][i].F = 10000;
			_tile->mapTile[j][i].G = 0;
			_tile->mapTile[j][i].H = 0;
			_tile->mapTile[j][i].state = NORMAL_NODE;
		}
	}

	for (int i = 0; i < _vBuildings.size(); i++)
	{
		if (_vBuildings[i]->type != 0)
			_tile->mapTile[_vBuildings[i]->x][_vBuildings[i]->y].state = START_NODE;
		if (_search)
		{
			if (_vBuildings[i]->type == WALL)
				_tile->mapTile[_vBuildings[i]->x][_vBuildings[i]->y].state = WALL_NODE;
		}
		else
		{
			if (_vBuildings[i]->type == WALL)
				_tile->mapTile[_vBuildings[i]->x][_vBuildings[i]->y].state = NORMAL_NODE;
		}
		
		if(_vBuildings[i]->destroyed)
			_tile->mapTile[_vBuildings[i]->x][_vBuildings[i]->y].state = NORMAL_NODE;
	}
}

void unitManager::unitSetting()
{
	vector<string> vTemp;
	vTemp = TXTDATA->txtLoad("playerUnitInfo.txt");

	_unitCount[0] = atoi(vTemp[2].c_str());
	_unitCount[1] = atoi(vTemp[5].c_str());
	_unitCount[2] = atoi(vTemp[8].c_str());
	_unitCount[3] = atoi(vTemp[11].c_str());


	_playerMoney = atoi(vTemp[13].c_str());
	_playerElixir = atoi(vTemp[15].c_str());
}

void unitManager::saveUnit()
{
	vector<string> vStr;

	vStr.push_back("barbarian");
	vStr.push_back(to_string(BARBARIAN));
	vStr.push_back(to_string(_unitCount[0]));

	vStr.push_back("giant");
	vStr.push_back(to_string(GIANT));
	vStr.push_back(to_string(_unitCount[1]));

	vStr.push_back("wallBraker");
	vStr.push_back(to_string(WALL_BRAKER));
	vStr.push_back(to_string(_unitCount[2]));

	vStr.push_back("archer");
	vStr.push_back(to_string(ARCHER));
	vStr.push_back(to_string(_unitCount[3]));

	vStr.push_back("gold");
	vStr.push_back(to_string(_playerMoney));

	vStr.push_back("elixir");
	vStr.push_back(to_string(_playerElixir));


	TXTDATA->txtSave("playerUnitInfo.txt", vStr);
}
