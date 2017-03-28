#pragma once

#include <cmath>

#define PI 3.141592654f // PI == 180도
#define PI2 (PI * 2)	// PI2 == 360도


#define PI3		float(PI / 3.f)
#define PI6		float(PI / 6.f)
#define PI8		float(PI / 8.f)
#define PI16	float(PI / 16.f)
#define PI32	float(PI / 32.f)
#define PI64	float(PI / 64.f)
#define PI128	float(PI / 128.f)

#define RAD_TO_DEG			(180.f / PI)
#define DEG_TO_RAD			(PI / 180.f)
#define FLOAT_EPSILON		0.0001f //이 정도 차이가 나면 같다고 봐도 무방하겠다 라는, 허용 오차범위
#define FLOAT_TO_INT(f1)	static_cast<int>(f1 + FLOAT_EPSILON)
#define FLOAT_EQUAL(f1, f2) (fabs(f1 - f2) <= FLOAT_EPSILON)

namespace MY_UTIL
{
	//거리 가져오는 함수
	float getDistance( float startX, float startY, float endX, float endY );

	//앵글 가져오는 함수
	float getAngle( float startX, float startY, float endX, float endY );

	//포인트 구조체
	typedef struct tagPoint
	{
		float x;
		float y;

		tagPoint() : x( 0.0f ), y( 0.0f ) {}
		tagPoint( float _x, float _y ) : x( _x ), y( _y ) {}

		void move( float dx, float dy )
		{
			x += dx;
			y += dy;
		}
	}MYPOINT, *LPMYPOINT;

	//원 구조체
	typedef struct tagCircle
	{
		float x, y; //중심 좌표
		float r;	//반지름

		tagCircle() : x( 0.f ), y( 0.f ), r( 0.f ) {}
		tagCircle( float _x, float _y, float _r ) : x( _x ), y( _y ), r( _r ) {}

		void move( float dx, float dy )
		{
			x += dx;
			y += dy;
		}

		void set( float centerX, float centerY, float radius )
		{
			x = centerX;
			y = centerY;
			r = radius;
		}

		void setCenterPos( float posX, float posY )
		{
			x = posX;
			y = posY;
		}

		void render( HDC hdc )
		{
			int x1 = FLOAT_TO_INT( x );
			int y1 = FLOAT_TO_INT( y );
			int r1 = FLOAT_TO_INT( r );

			Ellipse( hdc, x1 - r1, y1 - r1, x1 + r1, y1 + r1 );
		}
	}MYCIRCLE, *LPMYCIRCLE;

	//사각형 구조체
	typedef struct tagRECT
	{
		float left;
		float top;
		float right;
		float bottom;

		tagRECT() : left( 0.f ), top( 0.f ), right( 0.f ), bottom( 0.f ) {}
		tagRECT(float _left, float _top, float _right, float _bottom) : left( _left ), top( _top ), right( _right ), bottom( _bottom ) {}

		void move( float dx, float dy )
		{
			left += dx;
			right += dx;
			top += dy;
			bottom += dy;
		}

		void set( float _left, float _top, float _right, float _bottom )
		{
			left = _left;
			top = _top;
			right = _right;
			bottom = _bottom;
		}

		float getWidth() { return right - left; }
		float getHeight() { return bottom - top; }

		void setLeftTopPos( float _left, float _top )
		{
			float width = getWidth();
			float height = getHeight();

			left = _left;
			top = _top;
			right = left + width;
			bottom = top + height;
		}

		void setCenterPos( float centerX, float centerY )
		{
			float halfW = getWidth() * 0.5f;
			float halfH = getHeight() * 0.5f;

			left = centerX - halfW;
			top = centerY - halfH;
			right = centerX + halfW;
			bottom = centerY + halfH;
		}

		void render( HDC hdc )
		{
			Rectangle( hdc,
				FLOAT_TO_INT( left ),
				FLOAT_TO_INT( top ),
				FLOAT_TO_INT( right ),
				FLOAT_TO_INT( bottom ) );
		}
	}MYRECT, *LPMYRECT;


	//점이 사각형 안에 있니?
	bool checkPointInRect( const RECT& rc, const POINT& pt );
	bool checkPointInRect( const RECT& rc, int x, int y );
	bool checkPointInRect( const MYRECT& rc, float x, float y );
	bool checkPointInRect( const MYRECT& rc, const MYPOINT& pt );

	//점이 원 안에 있니?
	bool checkPointInCircle( float cX, float cY, float cR, const MYPOINT& pt );
	bool checkPointInCircle( float cX, float cY, float cR, float x, float y );
	bool checkPointInCircle( const MYCIRCLE& rc, float x, float y );
	bool checkPointInCircle( const MYCIRCLE& rc, const MYPOINT& pt );

	//사각형이 사각형이랑 충돌했니?
	bool isCollision( const MYRECT& rc1, const MYRECT& rc2 );
	bool isCollision( const RECT& rc1, const RECT& rc2 );

	//원과 원이 충돌했니?
	bool isCollision( const MYCIRCLE& cir1, const MYCIRCLE& cir2 );

	//원과 사각형이 충돌했니?
	bool isCollision( const MYCIRCLE& cir, const RECT& rc );
	bool isCollision( const MYCIRCLE& cir, const MYRECT& rc );

	//충돌후 리액션은??
	bool isCollisionReaction( const RECT& rcHold, RECT & rcMove );
	bool isCollisionReaction( const MYRECT& mrcHold, MYRECT & mrcMove );
	bool isCollisionReaction( const MYCIRCLE& cirHold, MYCIRCLE & cirMove );


}