#include "stdafx.h"
#include "mainScene.h"


mainScene::mainScene()
{
}


mainScene::~mainScene()
{
}

HRESULT mainScene::init()
{
	SOUNDMANAGER->play("bgm", 0.05);

	// BackgroundSetting
	backgroundImg = IMAGEMANAGER->findImage("background");

	// btnSetting
	_btnAttack = RectMake(10, 685, 105, 105);
	_btnArmy = RectMake(10, 623, 57, 57);
	_btnMapSetting = RectMake(1235, 510, 55, 55);
	_btnMission = RectMake(1235, 570, 55, 55);
	_btnSetting = RectMake(1235, 630, 55, 55);
	_btnShop = RectMake(1190, 690, 100, 100);

	_vBuildings.clear();
	_makedUnits.clear();
	_makingUnits.clear();

	//tile
	_tile = new TileMapSetting;
	_tile->init();

	_offsetX = _tile->getOffsetX();
	_offsetY = _tile->getOffsetY();

	mapSetting();
	_playerMoney = 0;
	_playerElixir = 0;

	_unitListShow = false;
	_lakeElixir = false;
	_lakeElixirTextCount = 0.f;
	
	ZeroMemory(_unitCount, sizeof(_unitCount));

	_selectType = 0;
	_selectBuildingNum = 0;




	unitSetting();

	return S_OK;
}

void mainScene::release()
{
	_tile->release();
	SAFE_DELETE(_tile);
}

void mainScene::update()
{
	_tile->update();

	offsetSetting();
	buttonClickCheck();
	buildingCount();
}

void mainScene::render()
{
	// 기본 백그라운드
	_tile->render();


	char str[100];
	//sprintf_s(str, "%d %d %d", _selectType, _selectBuildingNum, _makedUnits.size());
	

	HFONT myFont = CreateFont(10, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Supercell-Magic");
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);
	//TextOut(getMemDC(), 0, 100, str, strlen(str));
	//SelectObject(getMemDC(), oldFont);
	//DeleteObject(myFont);

	for (unsigned int i = 0; i < _vBuildings.size(); i++)
	{
		if (_vBuildings[i]->size == 1) {
			_vBuildings[i]->img->render(getMemDC(), _vBuildings[i]->rc.left - 13, _vBuildings[i]->rc.top - 27);
		}
		else if (_vBuildings[i]->size == 2) {
			IMAGEMANAGER->findImage("building_bottom_2_2")->render(getMemDC(), _vBuildings[i]->rc.left, _vBuildings[i]->rc.top);
			_vBuildings[i]->img->render(getMemDC(), _vBuildings[i]->rc.left, _vBuildings[i]->rc.top - 34);
		}
		else if (_vBuildings[i]->size == 3) {
			IMAGEMANAGER->findImage("building_bottom_3_3")->render(getMemDC(), _vBuildings[i]->rc.left, _vBuildings[i]->rc.top);
			_vBuildings[i]->img->render(getMemDC(), _vBuildings[i]->rc.left, _vBuildings[i]->rc.top - 45);
		}
		else if (_vBuildings[i]->size == 4) {
			IMAGEMANAGER->findImage("building_bottom_4_4")->render(getMemDC(), _vBuildings[i]->rc.left, _vBuildings[i]->rc.top);
			_vBuildings[i]->img->render(getMemDC(), _vBuildings[i]->rc.left, _vBuildings[i]->rc.top - 120);
		}

	//	sprintf_s(str, "%f, %d", _vBuildings[i]->updateTime, _vBuildings[i]->maxUpdateTime);
//		TextOut(getMemDC(), _vBuildings[i]->rc.left, _vBuildings[i]->rc.top, str, strlen(str));

		if (_vBuildings[i]->countTime > 10)
		{
			if (_vBuildings[i]->type == ELIXIR_COLLECTOR)
			{
				IMAGEMANAGER->findImage("elixir_pop")->render(getMemDC(), _vBuildings[i]->rc.left + 50, _vBuildings[i]->rc.top - 40);
			}
			else if (_vBuildings[i]->type == GOLD_COLLECTOR)
			{
				IMAGEMANAGER->findImage("money_pop")->render(getMemDC(), _vBuildings[i]->rc.left + 50, _vBuildings[i]->rc.top - 40);
			}
		}

	}

	if (_work)
	{
		if (_vBuildings[_workNum]->size == 3) {
			IMAGEMANAGER->findImage("upgrade")->render(getMemDC(), _vBuildings[_workNum]->rc.left, _vBuildings[_workNum]->rc.top);
			//sprintf_s(str, "%f, %f", (float)_vBuildings[_workNum]->updateTime, (float)_vBuildings[_workNum]->maxUpdateTime);
			//TextOut(getMemDC(), 0, 150, str, strlen(str));
			IMAGEMANAGER->findImage("hpBarBottom")->render(getMemDC(), _vBuildings[_workNum]->rc.left + 40, _vBuildings[_workNum]->rc.top - 20);
			IMAGEMANAGER->findImage("hpBarTop")->render(getMemDC(), _vBuildings[_workNum]->rc.left + 40, _vBuildings[_workNum]->rc.top - 20, 0, 0, 62 - (((float)_vBuildings[_workNum]->updateTime / (float)_vBuildings[_workNum]->maxUpdateTime) * 62), 12);
		}
		else if (_vBuildings[_workNum]->size == 4) {
			IMAGEMANAGER->findImage("upgrade")->render(getMemDC(), _vBuildings[_workNum]->rc.left + 25, _vBuildings[_workNum]->rc.top + 34);
		}
	}



	if (_selectType != BUILDING_TYPE_NULL &&
		_showPop != true &&
		_selectType != BUILDER)
	{
		IMAGEMANAGER->findImage("upgrade_btn")->render(getMemDC(), 660, 685);
	}

	if (_selectType == TOWN_HALL)
	{
		if (_showPop)
		{
			IMAGEMANAGER->findImage("town_hall_pop")->render(getMemDC(), 300, 150); 
		
			IMAGEMANAGER->findImage("progress_pop")->render(getMemDC(), 637, 246, 0, 0, ((float)_playerMoney / (float)_goldMax) * 346, 25);
			IMAGEMANAGER->findImage("progress_pop")->render(getMemDC(), 637, 288, 0, 0, ((float)_playerElixir / (float)_elixirMax) * 346, 25);

			myFont = CreateFont(13, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Supercell-Magic");
			oldFont = (HFONT)SelectObject(getMemDC(), myFont);
			sprintf_s(str, "저장 용량 : %d / %d", _playerMoney, _goldMax);
			TextOut(getMemDC(), 645, 244, str, strlen(str));
			sprintf_s(str, "저장 용량 : %d / %d", _playerElixir, _elixirMax);
			TextOut(getMemDC(), 645, 286, str, strlen(str));
			sprintf_s(str, "HP : 100 / 100");
			TextOut(getMemDC(), 645, 328, str, strlen(str));
			SelectObject(getMemDC(), oldFont);
			DeleteObject(myFont);
		}
		else
		{
			IMAGEMANAGER->findImage("info_btn")->render(getMemDC(), 550, 685);
		}
	}

	if (_selectType == UNIT_MAKE)
	{
		if (_showPop)
		{
			IMAGEMANAGER->findImage("unit_make_pop")->render(getMemDC(), 300, 150);

			float unitMakeTime = 0.f;

			for (unsigned int i = 0; i < _makingUnits.size(); i++)
			{
				_makingUnits[i]->img->render(getMemDC(), 735 - (i * 75), 240);
				unitMakeTime += _makingUnits[i]->makeTime;
			}
			myFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Supercell-Magic");
			oldFont = (HFONT)SelectObject(getMemDC(), myFont);
			sprintf_s(str, "남은시간", unitMakeTime);
			TextOut(getMemDC(), 870, 240, str, strlen(str));
			sprintf_s(str, "%.2f 초", unitMakeTime);
			TextOut(getMemDC(), 870, 265, str, strlen(str));
			SelectObject(getMemDC(), oldFont);
			DeleteObject(myFont);

			if (_lakeElixir)
			{
				myFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Supercell-Magic");
				oldFont = (HFONT)SelectObject(getMemDC(), myFont);
				sprintf_s(str, "엘릭서가 부족합니다.");
				TextOut(getMemDC(), 600, 350, str, strlen(str));
				SelectObject(getMemDC(), oldFont);
				DeleteObject(myFont);

			}
		}
		else
		{
			IMAGEMANAGER->findImage("unit_make_btn")->render(getMemDC(), 550, 685);
		}
	}
	
	if (_selectType == ELIXIR_STORAGE)
	{
		if (_showPop)
		{
			IMAGEMANAGER->findImage("elixir_collector_pop")->render(getMemDC(), 300, 150);
			IMAGEMANAGER->findImage("progress_pop")->render(getMemDC(), 637, 246, 0, 0, ((float)_playerElixir / (float)_elixirMax) * 346, 25);

			myFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Supercell-Magic");
			oldFont = (HFONT)SelectObject(getMemDC(), myFont);
			sprintf_s(str, "엘릭서 저장소 (레벨 %d)", _vBuildings[_selectBuildingNum]->level);
			TextOut(getMemDC(), 580, 175, str, strlen(str));
			SelectObject(getMemDC(), oldFont);
			DeleteObject(myFont);

			myFont = CreateFont(13, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Supercell-Magic");
			oldFont = (HFONT)SelectObject(getMemDC(), myFont);
			sprintf_s(str, "저장 용량 : %d / %d", _playerElixir, _elixirMax);
			TextOut(getMemDC(), 645, 244, str, strlen(str));
			sprintf_s(str, "HP : 100 / 100");
			TextOut(getMemDC(), 645, 286, str, strlen(str));
			SelectObject(getMemDC(), oldFont);
			DeleteObject(myFont);
		}
		else
		{
			IMAGEMANAGER->findImage("info_btn")->render(getMemDC(), 550, 685);
		}
	}

	if (_selectType == GOLD_STORAGE)
	{
		if (_showPop)
		{
			IMAGEMANAGER->findImage("gold_collector_pop")->render(getMemDC(), 300, 150);
			IMAGEMANAGER->findImage("progress_pop")->render(getMemDC(), 637, 246, 0, 0, ((float)_playerMoney / (float)_goldMax) * 346, 25);

			myFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Supercell-Magic");
			oldFont = (HFONT)SelectObject(getMemDC(), myFont);
			sprintf_s(str, "골드 저장소 (레벨 %d)", _vBuildings[_selectBuildingNum]->level);
			TextOut(getMemDC(), 580, 175, str, strlen(str));
			SelectObject(getMemDC(), oldFont);
			DeleteObject(myFont);

			myFont = CreateFont(13, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Supercell-Magic");
			oldFont = (HFONT)SelectObject(getMemDC(), myFont);
			sprintf_s(str, "저장 용량 : %d / %d", _playerMoney, _goldMax);
			TextOut(getMemDC(), 645, 244, str, strlen(str));
			sprintf_s(str, "HP : 100 / 100");
			TextOut(getMemDC(), 645, 286, str, strlen(str));
			SelectObject(getMemDC(), oldFont);
			DeleteObject(myFont);
		}
		else
		{
			IMAGEMANAGER->findImage("info_btn")->render(getMemDC(), 550, 685);
		}
	}


	// 기본 버튼들 이미지 그려준다.
	IMAGEMANAGER->findImage("btn_attack")->render(getMemDC(), _btnAttack.left, _btnAttack.top);
	IMAGEMANAGER->findImage("btn_army")->render(getMemDC(), _btnArmy.left, _btnArmy.top);
	IMAGEMANAGER->findImage("btn_map_setting")->render(getMemDC(), _btnMapSetting.left, _btnMapSetting.top);
	IMAGEMANAGER->findImage("btn_mission")->render(getMemDC(), _btnMission.left, _btnMission.top);
	IMAGEMANAGER->findImage("btn_setting")->render(getMemDC(), _btnSetting.left, _btnSetting.top);
	IMAGEMANAGER->findImage("btn_shop")->render(getMemDC(), _btnShop.left, _btnShop.top);
	IMAGEMANAGER->findImage("worker_slot")->render(getMemDC(), 500, 10);
	
	
	IMAGEMANAGER->findImage("progress_gold")->render(getMemDC(), 1090 + (175 - ((float)_playerMoney / (float)_goldMax) * 175), 27, 0,0, ((float)_playerMoney / (float)_goldMax) * 175,30);
	IMAGEMANAGER->findImage("progress_elixir")->render(getMemDC(), 1090 + (175 - ((float)_playerElixir / (float)_elixirMax) * 175), 78, 0, 0, ((float)_playerElixir / (float)_elixirMax) * 175, 30);
	IMAGEMANAGER->findImage("money_slot")->render(getMemDC(), 1090, 10);


	if (_unitListShow)
	{
		IMAGEMANAGER->findImage("unit_list_slot")->render(getMemDC(), 0,200);

		myFont = CreateFont(13, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Supercell-Magic");
		oldFont = (HFONT)SelectObject(getMemDC(), myFont);
		sprintf_s(str, "%d", _unitCount[0]);
		TextOut(getMemDC(), 10, 220, str, strlen(str));
		sprintf_s(str, "%d", _unitCount[1]);
		TextOut(getMemDC(), 10, 295, str, strlen(str));
		sprintf_s(str, "%d", _unitCount[2]);
		TextOut(getMemDC(), 10, 370, str, strlen(str));
		sprintf_s(str, "%d", _unitCount[3]);
		TextOut(getMemDC(), 10, 445, str, strlen(str));
		SelectObject(getMemDC(), oldFont);
		DeleteObject(myFont);
	}

	myFont = CreateFont(13, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Supercell-Magic");
	oldFont = (HFONT)SelectObject(getMemDC(), myFont);
	sprintf_s(str, "%d", _playerMoney);
	TextOut(getMemDC(), 1150, 34, str, strlen(str));
	sprintf_s(str, "%d", _playerElixir);
	TextOut(getMemDC(), 1150, 84, str, strlen(str));
	sprintf_s(str, "%d / 1", !_work);
	TextOut(getMemDC(), 580, 37, str, strlen(str));
	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);





}


void mainScene::mapSetting()
{
	_vBuildings.clear();

	COCDB->loadMap("playerMapInfo.txt", _offsetX, _offsetY);
	
	for (int i = 0; i < COCDB->getVMap().size(); i++)
	{
		_vBuildings.push_back(COCDB->getVMap()[i]);
	}

	_elixirMax = COCDB->getMaxElixir();
	_goldMax = COCDB->getMaxGold();
}

void mainScene::unitSetting()
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

void mainScene::offsetSetting()
{
	if (_offsetX != _tile->getOffsetX() || _offsetY != _tile->getOffsetY())
	{
		int x = _tile->getOffsetX() - _offsetX;
		int y = _tile->getOffsetY() - _offsetY;

		for (unsigned int i = 0; i < _vBuildings.size(); i++)
		{
			_vBuildings[i]->rc = { _vBuildings[i]->rc.left - x, _vBuildings[i]->rc.top - y, _vBuildings[i]->rc.right - x, _vBuildings[i]->rc.bottom - y };
			_vBuildings[i]->topPoint = pointMake((_vBuildings[i]->rc.left + _vBuildings[i]->rc.right)/2, _vBuildings[i]->rc.top);
			_vBuildings[i]->leftPoint = pointMake(_vBuildings[i]->rc.left, (_vBuildings[i]->rc.top + _vBuildings[i]->rc.bottom) / 2);
			_vBuildings[i]->rightPoint = pointMake(_vBuildings[i]->rc.right, (_vBuildings[i]->rc.top + _vBuildings[i]->rc.bottom) / 2);
			_vBuildings[i]->bottomPoint = pointMake((_vBuildings[i]->rc.left + _vBuildings[i]->rc.right) / 2, _vBuildings[i]->rc.bottom);
		}

		_offsetX = _tile->getOffsetX();
		_offsetY = _tile->getOffsetY();
	}
}

void mainScene::buttonClickCheck()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//_selectType = BUILDING_TYPE_NULL;
	
		if (!_showPop)
		{
			btnClick();
		}

		switch (_selectType)
		{
		case ELIXIR_COLLECTOR:
			elixirCollect();
			break;
		case TOWN_HALL:
		case ELIXIR_STORAGE:
		case GOLD_STORAGE:
			storage(); 
			break;
		case UNIT_MAKE:
			unitMake();
			break;
		case GOLD_COLLECTOR:
			goldCollect();
			break;
		case BUILDER:
			break;
		case WALL:
			break;
		default:
			break;
		}
		
	}
}

void mainScene::buildingClick(int type, int buildingNum)
{
	_selectType = type;
	_selectBuildingNum = buildingNum;
}

void mainScene::buildingCount()
{
	for (unsigned int i = 0; i < _vBuildings.size(); i++)
	{
		if (_vBuildings[i]->type == ELIXIR_COLLECTOR || _vBuildings[i]->type == GOLD_COLLECTOR)
		{
			if (_work)
			{
				if (i != _workNum)
				{
					if (_vBuildings[i]->maxCountTime > _vBuildings[i]->countTime)
						_vBuildings[i]->countTime += TIMEMANAGER->getElapsedTime();
					else
						_vBuildings[i]->countTime = _vBuildings[i]->maxCountTime;
				}
			}
			else
			{
				if (_vBuildings[i]->maxCountTime > _vBuildings[i]->countTime)
					_vBuildings[i]->countTime += TIMEMANAGER->getElapsedTime();
				else
					_vBuildings[i]->countTime = _vBuildings[i]->maxCountTime;
			}
		}

	}

	if (_lakeElixir)
	{
		_lakeElixirTextCount -= TIMEMANAGER->getElapsedTime();

		if (_lakeElixirTextCount < 0)
			_lakeElixir = false;
	}

	if (_work)
	{
		if (_vBuildings[_workNum]->updateTime < _vBuildings[_workNum]->maxUpdateTime)
		{
			_vBuildings[_workNum]->updateTime += TIMEMANAGER->getElapsedTime();
		}
		else
		{
			buildingUpgrade();
			_vBuildings[_workNum]->updateTime = 0;
			_work = false;
		}
			
	}

	if (_makingUnits.size() > 0)
	{

		_makingUnits[0]->makeTime -= TIMEMANAGER->getElapsedTime();
		if (_makingUnits[0]->makeTime < 0)
		{
			_makedUnits.push_back(_makingUnits[0]);
			
			if (_makingUnits[0]->type == BARBARIAN)
				_unitCount[0]++;
			else if (_makingUnits[0]->type == GIANT)
				_unitCount[1]++;
			else if (_makingUnits[0]->type == WALL_BRAKER)
				_unitCount[2]++;
			else if (_makingUnits[0]->type == ARCHER)
				_unitCount[3]++;

			saveUnit();

			_makingUnits.erase(_makingUnits.begin());
		}
	}
}

void mainScene::buildingUpgrade()
{
	// 맵에서 업그레이드
	_vBuildings[_workNum]->level++;
	_vBuildings[_workNum]->maxCountTime = 10000 * _vBuildings[_workNum]->level;
	COCDB->saveMap("playerMapInfo.txt", _vBuildings, _offsetX, _offsetY);

	// 가지고있는 건물목록에서 업그레이드
	vector<tagSlot*> mapItems;

	mapItems.clear();
	mapItems.push_back(_vBuildings[0]);

	bool find;

	for (int i = 0; i < _vBuildings.size(); i++)
	{
		find = false;

		for (int j = 0; j < mapItems.size(); j++)
		{
			if (_vBuildings[i]->name == mapItems[j]->name &&
				_vBuildings[i]->level == mapItems[j]->level)
			{
				mapItems[j]->count++;
				find = true;
			}
		}

		if (!find)
		{
			_vBuildings[i]->count++;
			mapItems.push_back(_vBuildings[i]);
		}
	}

	COCDB->saveAllBuildings("playerBuildingsInfo.txt", mapItems);

	_selectType = BUILDING_TYPE_NULL;

	mapSetting();
}

void mainScene::saveUnit()
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
	
	vStr.push_back("goldMax");
	vStr.push_back(to_string(_goldMax));

	vStr.push_back("elixirMax");
	vStr.push_back(to_string(_elixirMax));


	TXTDATA->txtSave("playerUnitInfo.txt", vStr);
}

void mainScene::btnClick()
{
	if (PtInRect(&_btnMapSetting, _ptMouse))
	{
		SCENEMANAGER->changeScene("mapMakeScene");
	}
	else if (PtInRect(&_btnArmy, _ptMouse))
	{
		_unitListShow = !_unitListShow;
	}
	else if (PtInRect(&_btnAttack, _ptMouse))
	{
		// 만들어진 유닛들을 저장
		saveUnit();

		SCENEMANAGER->changeScene("selectPlayScene");
	}
	else if (PtInRect(&_btnMission, _ptMouse))
	{
		SCENEMANAGER->changeScene("stageMake");
	}

	for (unsigned int i = 0; i < _vBuildings.size(); i++)
	{
		float m = (float)(_vBuildings[i]->rc.bottom - _vBuildings[i]->rc.top) / (float)(_vBuildings[i]->rc.right - _vBuildings[i]->rc.left);

		if (_tile->diaCollisionCheck(_ptMouse, m, _vBuildings[i]->topPoint, _vBuildings[i]->leftPoint, _vBuildings[i]->bottomPoint, _vBuildings[i]->rightPoint))
			buildingClick(_vBuildings[i]->type, i);
	}

	if (!_work)
	{
		if (PtInRect(&RectMake(660, 685, 100, 100), _ptMouse))
		{
			if (_vBuildings[_selectBuildingNum]->maxLevel > _vBuildings[_selectBuildingNum]->level)
			{
				if (_playerMoney > 1000)
				{
					_playerMoney -= 1000;
					_work = true;
					_workNum = _selectBuildingNum;
				}
			}
		}
	}
}

void mainScene::unitMake()
{
	RECT rcUnitPopBarbarian = RectMake(325, 375, 320, 100);;
	RECT rcUnitPopArcher = RectMake(655, 485, 320, 100);
	RECT rcUnitPopGiant = RectMake(325, 485, 320, 100);
	RECT rcUnitPopWallBreaker = RectMake(655, 375, 320, 100);
	RECT rcUnitPopExit = RectMake(950, 165, 40, 40);


	if (PtInRect(&rcUnitPopExit, _ptMouse))
	{
		_selectType = BUILDING_TYPE_NULL;
		_showPop = false;
	}
	else
	{
		if (_showPop == false)
		{
			if (PtInRect(&RectMake(550, 685, 100, 100), _ptMouse))
			{
				_showPop = true;
			}
		}
		else
		{
			if (_makingUnits.size() < 6)
			{

				if (PtInRect(&rcUnitPopBarbarian, _ptMouse))
				{
					if (_playerElixir >= 100)
					{
						unit* temp = new unit;

						temp->name = "barbarian";
						temp->img = IMAGEMANAGER->findImage("barbarian_slot");
						temp->makeTime = 1.5f;
						temp->type = BARBARIAN;

						_playerElixir -= 100;
						_makingUnits.push_back(temp);
					}
					else
					{
						_lakeElixir = true;
						_lakeElixirTextCount = 1.5f;
					}
				}
				else if (PtInRect(&rcUnitPopArcher, _ptMouse))
				{
					if (_playerElixir >= 200)
					{
						unit* temp = new unit;

						temp->name = "archer";
						temp->img = IMAGEMANAGER->findImage("archer_slot");
						temp->makeTime = 2.0f;
						temp->type = ARCHER;

						_playerElixir -= 200;
						_makingUnits.push_back(temp);
					}
					else
					{
						_lakeElixir = true;
						_lakeElixirTextCount = 1.5f;
					}
				}
				else if (PtInRect(&rcUnitPopGiant, _ptMouse))
				{
					if (_playerElixir >= 500)
					{
						unit* temp = new unit;

						temp->name = "giant";
						temp->img = IMAGEMANAGER->findImage("giant_slot");
						temp->makeTime = 5.0f;
						temp->type = GIANT;

						_playerElixir -= 500;
						_makingUnits.push_back(temp);
					}
					else
					{
						_lakeElixir = true;
						_lakeElixirTextCount = 1.5f;
					}
				}
				else if (PtInRect(&rcUnitPopWallBreaker, _ptMouse))
				{
					if (_playerElixir >= 300)
					{
						unit* temp = new unit;

						temp->name = "wallBraker";
						temp->img = IMAGEMANAGER->findImage("wall_breaker_slot");
						temp->makeTime = 3.0f;
						temp->type = WALL_BRAKER;

						_playerElixir -= 300;
						_makingUnits.push_back(temp);
					}
					else
					{
						_lakeElixir = true;
						_lakeElixirTextCount = 1.5f;
					}
				}


			}
		}
	}
}

void mainScene::elixirCollect()
{
	

	if (_vBuildings[_selectBuildingNum]->countTime > 10)
	{
		
		_playerElixir += (int)_vBuildings[_selectBuildingNum]->countTime * 10 * _vBuildings[_selectBuildingNum]->level;


		for (unsigned int i = 0; i < _vBuildings.size(); i++)
		{
			if (_vBuildings[i]->type == ELIXIR_STORAGE)
			{
				if (_vBuildings[i]->maxCountTime > _playerElixir)
				{
					_vBuildings[_selectBuildingNum]->countTime = 0.f;
					_vBuildings[i]->countTime = (float)_playerElixir;
					SOUNDMANAGER->play("gold", 0.05f);
				}
				else
				{
					// 저장소과 꽉 참 메세지 띄우기..

					_vBuildings[i]->countTime = _vBuildings[i]->maxCountTime;
					_playerElixir = _vBuildings[i]->maxCountTime;
				}
				break;
			}
		}

		saveUnit();
	}

	//_selectType = BUILDING_TYPE_NULL;
}

void mainScene::goldCollect()
{
	if (_vBuildings[_selectBuildingNum]->countTime > 10)
	{
		_playerMoney += (int)_vBuildings[_selectBuildingNum]->countTime * 10 * _vBuildings[_selectBuildingNum]->level;

		for (unsigned int i = 0; i < _vBuildings.size(); i++)
		{
			if (_vBuildings[i]->type == GOLD_STORAGE)
			{
				if (_vBuildings[i]->maxCountTime > _playerMoney)
				{
					_vBuildings[_selectBuildingNum]->countTime = 0.f;
					SOUNDMANAGER->play("gold", 0.05f);
					_vBuildings[i]->countTime = (float)_playerMoney;
				}
				else
				{
					_vBuildings[i]->countTime = _vBuildings[i]->maxCountTime;
					_playerMoney = _vBuildings[i]->maxCountTime;
				}
				break;
			}
		}

		saveUnit();
	}
	//_selectType = BUILDING_TYPE_NULL;
}

void mainScene::storage()
{
	RECT rcPopExit = RectMake(950, 165, 40, 40);

	
	if (_showPop == false)
	{
		if (PtInRect(&RectMake(550, 685, 100, 100), _ptMouse))
		{
			_showPop = true;
		}
	}
	else
	{
		if (PtInRect(&rcPopExit, _ptMouse))
		{
			_selectType = BUILDING_TYPE_NULL;
			_showPop = false;
		}

	}
}
