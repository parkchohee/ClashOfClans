#include "stdafx.h"
#include "database.h"


database::database()
{
}


database::~database()
{
}

HRESULT database::init()
{
	loadDatabase( "database.txt" );

	return S_OK;
}

void database::release()
{
	iterElement mIter = _mTotalElement.begin();

	for ( ; mIter != _mTotalElement.end(); )
	{
		if ( mIter->second )
		{
			SAFE_DELETE( mIter->second );
			mIter = _mTotalElement.erase( mIter );
		}
		else
			++mIter;
	}

	_mTotalElement.clear();
}

void database::loadDatabase( string name )
{
	//데이터를 읽어오자
	arrElements vTemp;
	vTemp = TXTDATA->txtLoad( name.c_str() );

	string str;
	int count = 0;

	for ( unsigned int i = 0; i < vTemp.size(); i++ )
	{
		if ( vTemp[i] == "|" )
		{
			elements* em = new elements;
			str = vTemp[i + 1];
			_mTotalElement.insert( pair<string, elements*>( str, em ) );
			if ( i != 0 ) count += 9;
			continue;
		}

		iterElement mIter = _mTotalElement.find( str );
		if ( i == count + 1 ) mIter->second->name = vTemp[i].c_str();
		else if ( i == count + 2 ) mIter->second->level = atoi( vTemp[i].c_str() );
		else if ( i == count + 3 ) mIter->second->count = atoi( vTemp[i].c_str() );
		else if (i == count + 4) mIter->second->maxHp = atoi(vTemp[i].c_str());
		else if (i == count + 5) mIter->second->type = atoi(vTemp[i].c_str());
		else if (i == count + 6) mIter->second->size = atoi(vTemp[i].c_str());
		else if (i == count + 7) mIter->second->x = atoi(vTemp[i].c_str());
		else if (i == count + 8) mIter->second->y = atoi(vTemp[i].c_str());

	}

	vTemp.clear();
}

void database::saveDatabase()
{
	// mTotalElement 를 돌면서 저장하면 될것같음
	//vector<string> vStr;
	//vStr.push_back(to_string(this->getElementData()->level));
	//vStr.push_back(to_string(totalStar));
	iterElement mIter = _mTotalElement.begin();


	//TXTDATA->txtSave(_fileName, vStr);
}

void database::setElementDataLevel(string str, int level)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->level = level;
}

void database::setElementDataCount(string str, int count)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->count = count;
}

void database::setElementDataMaxHp(string str, int maxHp)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->maxHp = maxHp;
}

void database::setElementDataType(string str, int type)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->type = type;
}

void database::setElementDataSize(string str, int size)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->size = size;
}

void database::setElementDataX(string str, int x)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->x = x;
}

void database::setElementDataY(string str, int y)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->y = y;
}

//void database::setElementDataIncreaseSpeed( string str, float is )
//{
//	iterElement mIter = _mTotalElement.find( str );
//	mIter->second->increaseSpeed = is;
//}
//
//void database::setElementDataMaxSpeed( string str, float ms )
//{
//	iterElement mIter = _mTotalElement.find( str );
//	mIter->second->maxSpeed = ms;
//}
//
//void database::setElementDataAngle( string str, float a )
//{
//	iterElement mIter = _mTotalElement.find( str );
//	mIter->second->angle = a;
//}
//
//void database::setElementDataCurrentHP( string str, int ch )
//{
//	iterElement mIter = _mTotalElement.find( str );
//	mIter->second->currentHP = ch;
//}
//
//void database::setElementDataMaxHP( string str, int mh )
//{
//	iterElement mIter = _mTotalElement.find( str );
//	mIter->second->maxHP = mh;
//}
