#include "stdafx.h"
#include "selectPlayScene.h"


selectPlayScene::selectPlayScene()
{
}


selectPlayScene::~selectPlayScene()
{
}

int selectPlayScene::sceneNum = 0;

HRESULT selectPlayScene::init()
{
	loadDB();
	
	_offsetY = _startY = 0;
	_offsetMoveY = false;
	return S_OK;
}

void selectPlayScene::release()
{
}

void selectPlayScene::update()
{
	btnClick();
	setOffset();
}

void selectPlayScene::render()
{
//	IMAGEMANAGER->findImage("selectSceneBackground")->render(getMemDC());
	IMAGEMANAGER->loopRender("selectSceneBackground", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), 0, _offsetY);
	
	char str[100];
	HFONT myFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Supercell-Magic");
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);
	for (int i = 0; i < 10; i++)
	{
		sprintf_s(str, _stage[i]->name.c_str());
		TextOut(getMemDC(), _stage[i]->rc.left - 15, _stage[i]->rc.top - 20, str, strlen(str));
	}
	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);

	IMAGEMANAGER->findImage("btn_attack_finish")->render(getMemDC(), 10, 760);

}

void selectPlayScene::loadDB()
{
	vector<string> vTemp;
	vTemp = TXTDATA->txtLoad("stageInfo.txt");

	int j = 0;

	for (unsigned int i = 0; i < vTemp.size(); i = i + 2)
	{
		stage* temp = new stage;

		temp->name = vTemp[i];
		temp->star = atoi(vTemp[i + 1].c_str());
		if (j % 4 == 3)
		{
			temp->rc = RectMake(620, 100 + 100 * j, 50, 50);
		}
		else
		{
			temp->rc = RectMake(290 + (j % 4 * 330), 100 + 100 * j, 50, 50);
		}
		
		_stage[j] = temp;

		j++;
	}

}

void selectPlayScene::setOffset()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		_offsetMoveY = true;
		_startY = _ptMouse.y;
	}
	
	if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))
	{
		_offsetMoveY = false;
	}

	if (_offsetMoveY)
	{
		if (_offsetY < 0)
		{
			_offsetY = 0;
			_offsetMoveY = false;
		}
		else if (_offsetY > IMAGEMANAGER->findImage("selectSceneBackground")->getHeight() - WINSIZEY)
		{
			_offsetY = IMAGEMANAGER->findImage("selectSceneBackground")->getHeight() - WINSIZEY;
			_offsetMoveY = false;
		}
		else if (_offsetY >= 0 && _offsetY <= IMAGEMANAGER->findImage("selectSceneBackground")->getHeight() - WINSIZEY)
		{
			_offsetMoveY = true;
			_offsetY = _offsetY + _startY - _ptMouse.y;
			_startY = _ptMouse.y;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (i % 4 == 3)
		{
			_stage[i]->rc = RectMake(620, 100 + 100 * i - _offsetY, 50, 50);
		}
		else
		{
			_stage[i]->rc = RectMake(290 + (i % 4 * 330), 100 + 100 * i - _offsetY, 50, 50);
		}
	}

}

void selectPlayScene::btnClick()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 10; i++)
		{
			if (PtInRect(&_stage[i]->rc, _ptMouse))
			{
				selectPlayScene::sceneNum = i;
				SCENEMANAGER->changeScene("playScene");
				break;
			}
		}

		if (PtInRect(&RectMake(10, 760, 115, 42), _ptMouse))
		{
			SCENEMANAGER->changeScene("mainScene");
		}
	}
}
