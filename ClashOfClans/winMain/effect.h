#pragma once

#include "gameNode.h"

class animation;

class effect : public gameNode
{
protected:
	int _x;							//이펙트 좌표 위치X
	int _y;							//이펙트 좌료 위치Y

	image* _effectImage;			//이펙트 이미지
	animation* _effectAnimation;	//이펙트 애니메이션
	BOOL _isRunning;				//이펙트 활성화 여부
	float _elapsedTime;				//이펙트 경과 시간

public:
	effect();
	~effect();
	
	HRESULT init( image *effectImage, int frameW, int frameH, int fps, float elapsedTime );
	void update();
	void release();
	void render();

	void startEffect( int x, int y );
	void killEffect();

	BOOL getIsRunning() { return _isRunning; }
};

