#pragma once

#include "gameNode.h"

//리턴형이 void 이고 매개변수가 void인 함수의 주소값을 받을 수 있는 포인터를
//CALLBACK_FUNCTION 의 이름으로 저장하겠다.
typedef void( *CALLBACK_FUNCTION )( void );
typedef void( *CALLBACK_FUNCTION_PARAMETER )( void* obj );

enum BUTTONDIRECTION
{
	BUTTONDIRECTION_NULL,
	BUTTONDIRECTION_UP,
	BUTTONDIRECTION_DOWN
};

class button : public gameNode
{
private:
	BUTTONDIRECTION _direction;
	const char * _imageName;
	image * _image;
	RECT _rc;
	float _x, _y;
	void* _obj;

	POINT _btnDownFramePoint;
	POINT _btnUpFramePoint;

	CALLBACK_FUNCTION _callbackFunction;
	CALLBACK_FUNCTION_PARAMETER _callbackFunctionParameter;

public:
	button();
	~button();

	HRESULT init( const char* imageName, int x, int y,
		POINT btnDownFramePoint, POINT btnUpFramePoint,
		CALLBACK_FUNCTION cbFunction );

	HRESULT init( const char* imageName, int x, int y,
		POINT btnDownFramePoint, POINT btnUpFramePoint,
		CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj );

	void release();
	void update();
	void render();
};

