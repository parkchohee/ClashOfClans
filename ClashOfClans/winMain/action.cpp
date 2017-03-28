#include "stdafx.h"
#include "action.h"


action::action()
{
}


action::~action()
{
}

HRESULT action::init()
{
	_callbackFunction = NULL;
	_worldTimeCount = 0.f;
	_isMoving = false;

	return S_OK;
}

void action::release()
{
}

void action::update()
{
	moving();
}

void action::render()
{
}

void action::moveTo( image * image, float endX, float endY, float time )
{
	if ( !_isMoving )
	{
		_callbackFunction = NULL;

		//이미지 주소값 넣어주자
		_image = image;

		//이동 시작점
		_startX = _image->getX();
		_startY = _image->getY();

		//도착점 저장
		_endX = endX;
		_endY = endY;

		//이동 거리 구한다
		_travelRange = MY_UTIL::getDistance( _startX, _startY, _endX, _endY );

		//각도 구하자
		_angle = MY_UTIL::getAngle( _startX, _startY, _endX, _endY );

		//월드 타임 저장
		_worldTimeCount = TIMEMANAGER->getWorldTime();

		//이동 시간도 저장하자
		_time = time;

		_isMoving = true;
	}
}

void action::moveTo( image * image, float endX, float endY, float time, CALLBACK_FUNCTION cbFunction )
{
	if ( !_isMoving )
	{
		_callbackFunction = cbFunction;

		//이미지 주소값 넣어주자
		_image = image;

		//이동 시작점
		_startX = _image->getX();
		_startY = _image->getY();

		//도착점 저장
		_endX = endX;
		_endY = endY;

		//이동 거리 구한다
		_travelRange = MY_UTIL::getDistance( _startX, _startY, _endX, _endY );

		//각도 구하자
		_angle = MY_UTIL::getAngle( _startX, _startY, _endX, _endY );

		//월드 타임 저장
		_worldTimeCount = TIMEMANAGER->getWorldTime();

		//이동 시간도 저장하자
		_time = time;

		_isMoving = true;
	}
}

void action::moving()
{
	if ( !_isMoving ) return;

	float elapsedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeed = ( elapsedTime / _time ) * _travelRange;

	//이동
	_image->setX( _image->getX() + cosf( _angle ) * moveSpeed );
	_image->setY( _image->getY() + -sinf( _angle ) * moveSpeed );

	//타임매니져를 이용한 애니메이션
	if ( _time + _worldTimeCount <= TIMEMANAGER->getWorldTime() )
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		_image->setX( _endX );
		_image->setY( _endY );
		_isMoving = false;
		if ( _callbackFunction != NULL )
		{
			_callbackFunction();
		}
	}
}
