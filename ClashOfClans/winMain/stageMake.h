#pragma once
#include "gameNode.h"
#include "TileMapSetting.h"
#include <vector>

#define STAGEMAX 10

class stageMake : public gameNode
{
	image* backgroundImg;
	TileMapSetting* _tile;

	vector<tagSlot*> _vRect;
	vector<tagSlot*>::iterator _viRect;
	vector<tagSlot*> _vBuildings;

	string _stageName;
	string _stageNames[STAGEMAX];
	int _selectStageNum;


	int _selectBuildingNum;
	int _selectBuildingType;


	RECT _prev, _next, _save, _cancel, _remove, _allRemove;
	int _offsetX, _offsetY;

	RECT _bulidingRc;
	RECT _bulidingColiisionRc;

	int _x, _y;
	bool _isCollision;

public:
	stageMake();
	~stageMake();

	HRESULT init();
	void release();
	void update();
	void render();

	void btnClick();
	void buildingSlotSetting();
	void offsetSetting();

	void loadMap();
};

