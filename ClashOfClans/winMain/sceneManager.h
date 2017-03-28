#pragma once

#include "singletonBase.h"
#include <map>
#include <string>

class gameNode;

using namespace std;

class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<string, gameNode*> mapSceneList;
	typedef map<string, gameNode*>::iterator mapSceneIter;

private:
	static gameNode *_currentScene; //현재 씬
	static gameNode *_loadingScene; //로딩 씬
	static gameNode *_readyScene;	//교체 대기 중인 씬

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;

	DWORD _loadThreadID;

public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//씬 추가
	gameNode* addScene( string sceneName, gameNode *scene );

	//로딩씬 추가
	gameNode* addLoadingScene( string loadingSceneName, gameNode *scene );

	//씬 체인지
	HRESULT	changeScene( string sceneName );
	HRESULT changeScene( string sceneName, string loadingSceneName );

	//로딩 쓰레드 함수 프렌드 선언
	friend DWORD CALLBACK loadingThead( LPVOID prc );
};