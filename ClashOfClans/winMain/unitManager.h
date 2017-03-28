#pragma once

#include "gameNode.h"
#include "units.h"
#include "TileMapSetting.h"


class unitManager : public gameNode
{
	vector<units*> _vUnit;
	vector<units*>::iterator _viUnit;

	TileMapSetting* _tile;
	
	int _unitCount[4];



	vector<tagSlot*> _vBuildings;

	POINT _startNodePoint;
	POINT _endNodePoint;
	POINT _searchPoint;

	bool _endSearch;
	int _searchValue;

	int _buildingCount, _attackBuildingCount;
	int _totalBuildingCount;

	float _destoryedPer;
	int _playerMoney;
	int	_playerElixir;
	bool _gamePlay;

	bool _search;

	RECT _finishBtn;

public:
	unitManager();
	~unitManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(string name, float speed, int pow, int type, POINT startPoint, POINT startPosition);

	void unitBuildingCollisionCheck();

	void buildingCount();



	vector<units*> getUnits() { return _vUnit; }

	void setTileMapMomeryLink(TileMapSetting* tile) { _tile = tile; }
	void setBuildingsMomeryLink(vector<tagSlot*> tagSlot) { 
		for (unsigned int i = 0; i < tagSlot.size(); i++)
			_vBuildings.push_back(tagSlot[i]);
	}



	vector<POINT> getWay(POINT position, int type);
	bool aStarFunc();


	void tileInit();

	void unitSetting();
	void saveUnit();
};

