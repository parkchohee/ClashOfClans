#include "stdafx.h"
#include "actionManager.h"

#include "action.h" //전방선언 했으니까


actionManager::actionManager()
{
}


actionManager::~actionManager()
{
}

HRESULT actionManager::init()
{
	return S_OK;
}

void actionManager::release()
{
	for ( _viAction = _vAction.begin(); _viAction != _vAction.end(); )
	{
		if ( _vAction.size() != 0 )
		{
			SAFE_DELETE( *_viAction );
			_viAction = _vAction.erase( _viAction );
		}
		else ++_viAction;
	}

	_vAction.clear();
}

void actionManager::update()
{
	for ( _viAction = _vAction.begin(); _viAction != _vAction.end(); ++_viAction )
	{
		(*_viAction)->update();

		if ( !( *_viAction )->getIsMoving() )
		{
			SAFE_DELETE( ( *_viAction ) );
			_viAction = _vAction.erase( _viAction );
			_viAction--;
		}
	}
}

void actionManager::render()
{
}

void actionManager::moveTo( image * image, float endX, float endY, float time )
{
	action* moveAction;
	moveAction = new action;
	moveAction->init();
	moveAction->moveTo( image, endX, endY, time );

	_vAction.push_back( moveAction );
}

void actionManager::moveTo( image * image, float endX, float endY, float time, void * cbFunction )
{
	action* moveAction;
	moveAction = new action;
	moveAction->init();
	//보이드 포인터는 모든 주소를 다 받을(옮길) 수 있지만 
	//실 사용할 때는 형태에 대한 정보가 없기 때문에 꼭 형변환 해야 한다.
	moveAction->moveTo( image, endX, endY, time, (CALLBACK_FUNCTION)cbFunction );

	_vAction.push_back( moveAction );
}
