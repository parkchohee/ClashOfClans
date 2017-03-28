#pragma once

#include "singletonBase.h"
#include <bitset>

using namespace std;

#define KEYMAX 256

class keyManager : public singletonBase<keyManager>
{
private:
	bitset<KEYMAX> _keyDown;
	bitset<KEYMAX> _keyUp;

public:
	keyManager();
	~keyManager();

	HRESULT init();
	void release();

	bool isOnceKeyDown( int key );
	bool isOnceKeyUp( int key );
	bool isStayKeyDown( int key );
	bool isToggleKey( int key );

	bitset<KEYMAX> getKeyDown() { return _keyDown; }
	bitset<KEYMAX> getKeyUp() { return _keyUp; }

	void setKeyDown( int key, bool state ) { _keyDown.set( key, state ); }
	void setKeyUp( int key, bool state ) { _keyUp.set( key, state ); }
};

