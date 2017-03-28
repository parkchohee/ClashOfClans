#pragma once

#include "gameNode.h"
#include "TileMapSetting.h"
#include "unitManager.h"
#include "selectPlayScene.h"

#define UNITTYPEMAX 4

class playScene : public gameNode
{
	TileMapSetting* _tile;

	unitManager* _unitManager;
	vector<tagSlot*> _vBuildings;

	int _offsetX;
	int _offsetY;

	RECT _unitRect[UNITTYPEMAX];
	RECT _btnFinish;

	int _selectUnitType;



	int _gold;
	int _elixir;

public:
	playScene();
	~playScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void mapSetting(int stageNum);
	void offsetSetting();
	void createUnit();

	//vector<POINT> aStar(POINT end);

	void setTileState();
};

