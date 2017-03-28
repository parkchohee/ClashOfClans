#include "stdafx.h"
#include "cocDB.h"


cocDB::cocDB()
{
}


cocDB::~cocDB()
{
}

HRESULT cocDB::init()
{
	return S_OK;
}

void cocDB::release()
{
}

tagSlot * cocDB::getElementData(string str)
{	
	if (_mTotalElement.find(str) == _mTotalElement.end())
	{
		tagSlot* temp = new tagSlot;
		temp->count = 0;
		return temp;
	}
	else
	{
		return _mTotalElement.find(str)->second; 
	}
}

void cocDB::loadAllBuildings(string name)
{
	vector<string> vTemp;
	vTemp = TXTDATA->txtLoad(name.c_str());
	
	string str;

	for (unsigned int i = 0; i < vTemp.size(); i = i + 9)
	{
		tagSlot* temp = new tagSlot;

		str = vTemp[i] + "_" + vTemp[i + 1];
		_mTotalElement.insert(pair<string, tagSlot*>(str, temp));

		iterElement mIter = _mTotalElement.find(str);

		mIter->second->img = IMAGEMANAGER->findImage(str);
		mIter->second->name = vTemp[i];
		mIter->second->level = atoi(vTemp[i + 1].c_str());
		mIter->second->maxLevel = atoi(vTemp[i + 2].c_str());
		mIter->second->size = atoi(vTemp[i + 3].c_str());
		mIter->second->type = atoi(vTemp[i + 4].c_str());
		mIter->second->maxHp = atoi(vTemp[i + 5].c_str());
		mIter->second->maxUpdateTime = atoi(vTemp[i + 6].c_str());
		mIter->second->maxCountTime = atoi(vTemp[i + 7].c_str());
		mIter->second->count = atoi(vTemp[i + 8].c_str());

	}
}

void cocDB::saveAllBuildings(string name, vector<tagSlot*> mapItems)
{
	vector<string> vStr;

	for (unsigned int i = 0; i < mapItems.size(); i++)
	{
		vStr.push_back(mapItems[i]->name);
		vStr.push_back(to_string(mapItems[i]->level));
		vStr.push_back(to_string(mapItems[i]->maxLevel));
		vStr.push_back(to_string(mapItems[i]->size));
		vStr.push_back(to_string(mapItems[i]->type));
		vStr.push_back(to_string(mapItems[i]->maxHp));
		vStr.push_back(to_string(mapItems[i]->maxUpdateTime));
		vStr.push_back(to_string(mapItems[i]->maxCountTime));
		vStr.push_back(to_string(mapItems[i]->count));
	}

	TXTDATA->txtSave("playerBuildingsInfo.txt", vStr);
}

void cocDB::loadMap(string name, int offsetX, int offsetY)
{
	vMap.clear();

	vector<string> vTemp;
	vTemp = TXTDATA->txtLoad(name.c_str());

	string str;

	for (unsigned int i = 0; i < vTemp.size(); i = i + 23)
	{
		tagSlot* temp = new tagSlot;

		str = vTemp[i] + "_" + vTemp[i+1];
		
		temp->name = vTemp[i].c_str();
		temp->level = atoi(vTemp[i + 1].c_str());
		temp->img = IMAGEMANAGER->findImage(str);
		temp->maxLevel = atoi(vTemp[i + 2].c_str());
		temp->size = atoi(vTemp[i + 3].c_str());
		temp->type = atoi(vTemp[i + 4].c_str());
		temp->currentHp = atoi(vTemp[i + 5].c_str());
		temp->maxHp = atoi(vTemp[i + 5].c_str());
		temp->updateTime = atof(vTemp[i + 6].c_str());
		temp->maxUpdateTime = atof(vTemp[i + 7].c_str());
		temp->countTime = atof(vTemp[i + 8].c_str());
		temp->maxCountTime = atof(vTemp[i + 9].c_str());
		temp->count = atof(vTemp[i + 10].c_str());
		temp->x = atoi(vTemp[i + 11].c_str());
		temp->y = atoi(vTemp[i + 12].c_str());
		
		if (temp->size == 1)
		{
			temp->rc = RectMake(atoi(vTemp[i + 13].c_str()) - offsetX, atoi(vTemp[i + 14].c_str()) - offsetY, 50, 34);
			temp->collisionRc = RectMake(temp->rc.left + 13, temp->rc.top + 8, 25, 17);
		}
		else if (temp->size == 2)
		{
			temp->rc = RectMake(atoi(vTemp[i + 13].c_str()) - offsetX, atoi(vTemp[i + 14].c_str()) - offsetY, 100, 68);
			temp->collisionRc = RectMake(temp->rc.left + 25, temp->rc.top + 17, 50, 34);
		}
		else if (temp->size == 3)
		{
			temp->rc = RectMake(atoi(vTemp[i + 13].c_str()) - offsetX, atoi(vTemp[i + 14].c_str()) - offsetY, 150, 102);
			temp->collisionRc = RectMake(temp->rc.left + 37, temp->rc.top + 25, 75, 51);
		}
		else if (temp->size == 4)
		{
			temp->rc = RectMake(atoi(vTemp[i + 13].c_str()) - offsetX, atoi(vTemp[i + 14].c_str()) - offsetY, 200, 136);
			temp->collisionRc = RectMake(temp->rc.left + 50, temp->rc.top + 34, 100, 68);
		}

		temp->topPoint = pointMake(atoi(vTemp[i + 15].c_str()), atoi(vTemp[i + 16].c_str()));
		temp->leftPoint = pointMake(atoi(vTemp[i + 17].c_str()), atoi(vTemp[i + 18].c_str()));
		temp->bottomPoint = pointMake(atoi(vTemp[i + 19].c_str()), atoi(vTemp[i + 20].c_str()));
		temp->rightPoint = pointMake(atoi(vTemp[i + 21].c_str()), atoi(vTemp[i + 22].c_str()));

		if (temp->type == ELIXIR_STORAGE)
			maxElixir = temp->maxCountTime;
		if (temp->type == GOLD_STORAGE)
			maxGold = temp->maxCountTime;

		temp->destroyed = false;

		vMap.push_back(temp);
	}

}

void cocDB::saveMap(string name, vector<tagSlot*> mapItems, int offsetX, int offsetY)
{
	vector<string> vStr;

	for (unsigned int i = 0; i < mapItems.size(); i++)
	{
		vStr.push_back(mapItems[i]->name);
		vStr.push_back(to_string(mapItems[i]->level));
		vStr.push_back(to_string(mapItems[i]->maxLevel));
		vStr.push_back(to_string(mapItems[i]->size));
		vStr.push_back(to_string(mapItems[i]->type));
		vStr.push_back(to_string(mapItems[i]->maxHp));
		//vStr.push_back(to_string(mapItems[i]->updateTime));
		vStr.push_back(to_string(0));
		vStr.push_back(to_string(mapItems[i]->maxUpdateTime));
		//vStr.push_back(to_string(mapItems[i]->countTime));
		vStr.push_back(to_string(0));
		vStr.push_back(to_string(mapItems[i]->maxCountTime));
		vStr.push_back(to_string(0));
		vStr.push_back(to_string(mapItems[i]->x));
		vStr.push_back(to_string(mapItems[i]->y));
		vStr.push_back(to_string(mapItems[i]->rc.left + offsetX));
		vStr.push_back(to_string(mapItems[i]->rc.top + offsetY));
		vStr.push_back(to_string(mapItems[i]->topPoint.x + offsetX));
		vStr.push_back(to_string(mapItems[i]->topPoint.y + offsetY));
		vStr.push_back(to_string(mapItems[i]->leftPoint.x + offsetX));
		vStr.push_back(to_string(mapItems[i]->leftPoint.y + offsetY));
		vStr.push_back(to_string(mapItems[i]->bottomPoint.x + offsetX));
		vStr.push_back(to_string(mapItems[i]->bottomPoint.y + offsetY));
		vStr.push_back(to_string(mapItems[i]->rightPoint.x + offsetX));
		vStr.push_back(to_string(mapItems[i]->rightPoint.y + offsetY));
	}

	TXTDATA->txtSave(name.c_str(), vStr);
}
