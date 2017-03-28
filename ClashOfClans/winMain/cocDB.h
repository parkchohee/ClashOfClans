#pragma once

#include "singletonBase.h"


enum STATE
{
	NORMAL_NODE,
	START_NODE,
	END_NODE,
	WALL_NODE,
	OPEN_LIST,
	CLOSE_LIST
};

enum BUILDINGTYPE {
	BUILDING_TYPE_NULL,
	TOWN_HALL,
	ELIXIR_COLLECTOR,
	ELIXIR_STORAGE,
	UNIT_MAKE,
	GOLD_COLLECTOR,
	GOLD_STORAGE,
	BUILDER,
	WALL,
	MORTER
};

enum UNITTYPE {
	BARBARIAN,
	GIANT,
	WALL_BRAKER,
	ARCHER
};


struct tagTile {
	RECT rc;	// Ÿ�� 1ĭ

	POINT p1;
	POINT p2;
	POINT p3;
	POINT p4;

	int x, y;
	tagTile* parent;
	int F, G, H;
	STATE state;

};

struct tagSlot {
	string name;
	image* img;	// �ǹ��̹���
	RECT rc;	// �̹��� �׸���� ��Ʈ
	RECT collisionRc; // �浹üũ�� ��Ʈ

	int size;	// 2x2, 3x3, 4x4���� �˷��ִ� ����
	float updateTime;
	int maxUpdateTime;
	float countTime;
	int maxCountTime;
	float count;	
	int maxCount;
	int x, y;	// _tile���� x, y��ǥ 
	int type;
	int level;
	int maxLevel;
	int maxHp;
	int currentHp;

	bool destroyed;

	POINT topPoint;
	POINT bottomPoint;
	POINT leftPoint;
	POINT rightPoint;

	void attack(int pow);
};
 
class cocDB : public singletonBase<cocDB>
{
	typedef map<string, tagSlot*> arrElement;
	typedef map<string, tagSlot*>::iterator iterElement;

	arrElement _mTotalElement;
	
	vector<tagSlot*> vMap;

	int maxElixir;
	int maxGold;

public:
	cocDB();
	~cocDB();

	HRESULT init();
	void release();

	tagSlot* getElementData(string str);

	void loadAllBuildings(string name);
	void saveAllBuildings(string name, vector<tagSlot*> mapItems);
	
	void loadMap(string name, int offsetX, int offsetY);
	void saveMap(string name, vector<tagSlot*> mapItems, int offsetX, int offsetY);

	int getMaxElixir() { return maxElixir; }
	int getMaxGold() { return maxGold; }

	vector<tagSlot*> getVMap() { return vMap; }

};

