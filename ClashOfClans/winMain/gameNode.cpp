#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}


HRESULT gameNode::init( void )
{
	_hdc = GetDC( _hWnd );
	_managerInit = false;

	return S_OK;
}

HRESULT gameNode::init( bool managerInit )
{
	_hdc = GetDC( _hWnd );
	_managerInit = managerInit;

	if ( _managerInit )
	{
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		TXTDATA->init();
		EFFECTMANAGER->init();
		SCENEMANAGER->init();
		DATABASE->init();
		SOUNDMANAGER->init();
		COCDB->init();
	}

	return S_OK;
}

void gameNode::release( void )
{
	if ( _managerInit )
	{
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();
		TXTDATA->release();
		TXTDATA->releaseSingleton();
		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		DATABASE->release();
		DATABASE->releaseSingleton();
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();
		COCDB->release();
		COCDB->releaseSingleton();
	}

	//DC도 해제 해주자
	ReleaseDC( _hWnd, _hdc );
}

void gameNode::update( void )
{
	InvalidateRect( _hWnd, NULL, false );
}

void gameNode::render(  )
{
}

LRESULT gameNode::MainProc( HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch ( iMessage )
	{
	case WM_MOUSEMOVE:
	{
		_ptMouse.x = LOWORD( lParam );
		_ptMouse.y = HIWORD( lParam );
	}
	break;

	case WM_LBUTTONDOWN:
		_leftButtonDown = true;
		break;

	case WM_LBUTTONUP:
		_leftButtonDown = false;
		break;

	case WM_KEYDOWN:
		switch ( wParam )
		{
		case VK_ESCAPE:
			PostMessage( hWnd, WM_DESTROY, 0, 0 );
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage( 0 );
		return 0;
	}

	//윈도우 프로시져에서 처리되지 않은 나머지 메시지를 처리해준다
	return ( DefWindowProc( hWnd, iMessage, wParam, lParam ) );
}
