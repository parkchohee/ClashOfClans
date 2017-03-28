#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

//로딩 쓰레드 함수 프렌드 선언
DWORD CALLBACK loadingThead( LPVOID prc )
{
	//교체될 init 함수를 실행한다.
	sceneManager::_readyScene->init();

	//현재 씬을 교체될 씬으로 바꾼다.
	sceneManager::_currentScene = sceneManager::_readyScene;

	//로딩씬을 해제한다
	sceneManager::_loadingScene->release();
	sceneManager::_loadingScene = NULL;
	sceneManager::_readyScene = NULL;

	return 0;
}

gameNode * sceneManager::_currentScene = NULL; //현재 씬
gameNode * sceneManager::_loadingScene = NULL; //로딩 씬
gameNode * sceneManager::_readyScene = NULL;   //교체 대기 중인 씬

sceneManager::sceneManager()
{
}


sceneManager::~sceneManager()
{
}


HRESULT sceneManager::init()
{
	_currentScene = NULL;
	_loadingScene = NULL;
	_readyScene = NULL;

	return S_OK;
}

void sceneManager::release()
{
	//맵 전체를 돌면서 지운다
	mapSceneIter miSceneList = _mSceneList.begin();

	for ( ; miSceneList != _mSceneList.end(); )
	{
		//지워지면 반복자를 증가하지 않는다.
		if ( miSceneList->second != NULL )
		{
			if ( miSceneList->second == _currentScene ) miSceneList->second->release();
			SAFE_DELETE( miSceneList->second );
			miSceneList = _mSceneList.erase( miSceneList );
		}
		else
		{
			++miSceneList;
		}
	}

	_mSceneList.clear();
}

void sceneManager::update()
{
	if ( _currentScene ) _currentScene->update();
}

void sceneManager::render()
{
	if ( _currentScene ) _currentScene->render();
}

//씬 추가
gameNode* sceneManager::addScene( string sceneName, gameNode *scene )
{
	if ( !scene ) return NULL;

	_mSceneList.insert( make_pair( sceneName, scene ) );

	return scene;
}

//로딩씬 추가
gameNode* sceneManager::addLoadingScene( string loadingSceneName, gameNode *scene )
{
	if ( !scene ) return NULL;

	_mLoadingSceneList.insert( make_pair( loadingSceneName, scene ) );

	return scene;
}

//씬 체인지
HRESULT	sceneManager::changeScene( string sceneName )
{
	//바꾸려는 씬을 찾는다.
	mapSceneIter find = _mSceneList.find( sceneName );

	//바꾸지 못하면 펄스리턴하자
	if ( find == _mSceneList.end() ) return E_FAIL;

	//바꾸려 하는 씬과 현재씬이 같으면 그냥 리턴
	if ( find->second == _currentScene ) return S_OK;

	//새롭게 변경되는 씬을 초기화하자
	if ( SUCCEEDED( find->second->init() ) )
	{
		//기존에 있던 씬을 릴리즈
		//if ( _currentScene ) _currentScene->release();
		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}

HRESULT sceneManager::changeScene( string sceneName, string loadingSceneName )
{
	//바꾸려는 씬을 찾는다.
	mapSceneIter find = _mSceneList.find( sceneName );

	//바꾸지 못하면 펄스 리턴
	if ( find == _mSceneList.end() ) return E_FAIL;

	//바꾸려 하는 씬과 현재 씬이 같으면
	if ( find->second == _currentScene ) return S_OK;

	//바꾸려하는 씬을 찾는다
	mapSceneIter findLoading = _mLoadingSceneList.find( loadingSceneName );

	//찾지 못하면 일반 로딩...
	if ( findLoading == _mLoadingSceneList.end() ) return changeScene( sceneName );

	//로딩씬 초기화
	if ( SUCCEEDED( findLoading->second->init() ) )
	{
		//씬이 있다면 릴리즈
		if ( _currentScene ) _currentScene->release();

		//로딩씬
		_loadingScene = findLoading->second;

		//로딩이 끝난 후 변경될 씬
		_readyScene = find->second;

		//로딩씬 호출
		CloseHandle( CreateThread( NULL, 0, loadingThead, NULL, 0, &_loadThreadID ) );

		return S_OK;
	}

	return E_FAIL;
}