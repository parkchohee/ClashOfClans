#pragma once

#include "gameNode.h"
#include "TileMapSetting.h"
#include <vector>

class mapMakeScene : public gameNode
{
	image* backgroundImg;
	TileMapSetting* _tile;
	
	vector<tagSlot*> _buildingSlot;
	vector<tagSlot*> _vRect;
	
	RECT btnDelete;
	RECT btnDeleteAll;
	RECT btnSave;
	RECT btnCancel;

	int _totalBuildingCount;
	int _totalBuildingSlotCount;
	int _offsetX, _offsetY;
	int _x, _y;

	int _selectSlotNum;
	bool _buildingSelect;
	bool _buildingCollision;
	bool _deleteMode;

public:
	mapMakeScene();
	~mapMakeScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void offsetSetting();

	void makeBuilding();
	void buildingCollision();
	void buildingListSwap();
	void btnClickListener();

	
	//bool diaCollisionCheck(POINT point, float m, POINT topPoint, POINT leftPoint, POINT bottomPoint, POINT rightPoint);
};

