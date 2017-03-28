#pragma once

#include "singletonBase.h"

#include <vector>
#include <map>

//struct elements //아래와 같다
//{
//	const char* name;
//	float increaseSpeed;
//	float maxSpeed;
//	float angle;
//	int currentHP;
//	int maxHP;
//};

class elements
{
public:
	const char* name;
	int level;
	int count;
	int maxHp;
	int type;
	int size;
	int x;
	int y;

	elements() {}
	~elements() {}
};

class database : public singletonBase<database>
{
private:
	typedef vector<string> arrElements;
	typedef vector<string>::iterator iterElements;
	typedef map<string, elements*> arrElement;
	typedef map<string, elements*>::iterator iterElement;

private:
	arrElement _mTotalElement;

public:
	database();
	~database();

	HRESULT init();
	void release();

	void loadDatabase( string name );
	void saveDatabase();

	elements* getElementData( string str ) { return _mTotalElement.find( str )->second; } 

	void setElementDataLevel(string str, int level);
	void setElementDataCount(string str, int count);
	void setElementDataMaxHp(string str, int maxHp);
	void setElementDataType(string str, int type);
	void setElementDataSize(string str, int size);
	void setElementDataX(string str, int x);
	void setElementDataY(string str, int y);

	/*void setElementDataIncreaseSpeed( string str, float is );
	void setElementDataMaxSpeed( string str, float ms );
	void setElementDataAngle( string str, float a );
	void setElementDataCurrentHP( string str, int ch );
	void setElementDataMaxHP( string str, int mh );*/
};

