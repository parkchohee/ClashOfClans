#pragma once

#include "gameNode.h"
#include "TileMapSetting.h"

struct unit
{
	string name;
	image* img;
	int type;
	float makeTime;
};


class mainScene : public gameNode
{
	image* backgroundImg;

	vector<tagSlot*> _vBuildings;
	vector<tagSlot*>::iterator _viBuildings;

	vector<unit*> _makedUnits;
	vector<unit*> _makingUnits;

	RECT _btnAttack;
	RECT _btnArmy;
	RECT _btnMapSetting;
	RECT _btnMission;
	RECT _btnSetting;
	RECT _btnShop;

	int _offsetX;
	int _offsetY;

	TileMapSetting* _tile;

	int _playerMoney;
	int _playerElixir;
	int _elixirMax;
	int _goldMax;

	bool _unitListShow;

	bool _lakeElixir;
	float _lakeElixirTextCount;

	int _unitCount[4];

	int _selectType, _selectBuildingNum;

	RECT rc;


	bool _showPop;
	bool _work;
	int _workNum;

public:
	mainScene();
	~mainScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void mapSetting();
	void unitSetting();
	void offsetSetting();
	void buttonClickCheck();
	void buildingClick(int type, int buildingNum);
	void buildingCount();

	void buildingUpgrade();
	void saveUnit();

	void btnClick();
	void unitMake();
	void elixirCollect();
	void goldCollect();
	void storage();
};

