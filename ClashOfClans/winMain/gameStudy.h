#pragma once

#include "gameNode.h"
#include "mainScene.h"
#include "mapMakeScene.h"
#include "playScene.h"
#include "selectPlayScene.h"
#include "stageMake.h"

class gameStudy : public gameNode
{
private:

public:
	gameStudy();
	virtual ~gameStudy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

