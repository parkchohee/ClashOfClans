#pragma once
#include "gameNode.h"

struct stage {
	string name;
	RECT rc;

	int star;
	int stageNum;
};


class selectPlayScene : public gameNode
{
	stage* _stage[10];

	int _offsetY;
	int _startY;
	bool _offsetMoveY;


public:
	selectPlayScene();
	~selectPlayScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void loadDB();
	void setOffset();
	void btnClick();


	static int sceneNum;
};

