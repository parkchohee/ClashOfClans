#pragma once

#include "singletonBase.h"
#include "image.h"
#include <map>

class imageManager : public singletonBase<imageManager>
{
public:
	typedef map<string, image*> mapImageList;
	typedef map<string, image*>::iterator mapImageIter;

private:
	mapImageList _mImageList;

public:
	imageManager();
	~imageManager();

	HRESULT init();
	void release();

	//키 값으로 설정해서 초기화
	image* addImage( string strKey, int width, int height );

	image* addImage( string strKey, const DWORD resID,
		int width, int height, bool trans, COLORREF transColor );

	image* addImage( string strKey, const char* fileName,
		int width, int height, bool trans, COLORREF transColor );

	image* addImage( string strKey, const char* fileName,
		float x, float y, int width, int height, bool trans, COLORREF transColor );

	//프레임?
	image* addFrameImage( string strKey, const char* fileName, float x, float y,
		int width, int height, int frameX, int frameY, bool trans, COLORREF transColor );

	image* addFrameImage( string strKey, const char* fileName, int width, int height, 
		int frameX, int frameY, bool trans, COLORREF transColor );

	//이미지 찾는 함수
	image* findImage( string strKey );

	//이미지 지운다
	BOOL deleteImage( string strKey );

	//전체 이미지 지운다
	BOOL deleteAll();

	//렌더 함수
	void render( string strKey, HDC hdc );
	void render( string strKey, HDC hdc, int destX, int destY );
	void render( string strKey, HDC hdc, int destX, int destY,
		int sourX, int sourY, int sourWidth, int sourHeight );

	//프레임 렌더
	void frameRender( string strKey, HDC hdc, int destX, int destY );
	void frameRender( string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY );

	//알파 렌더
	void alphaRender( string strKey, HDC hdc, int destX, int destY, BYTE alpha );
	void alphaRender( string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha );

	//루프 렌더
	void loopRender( string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY );

};

