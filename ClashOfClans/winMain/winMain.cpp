// winMain.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "gameStudy.h"

/* #### 전역변수 #### */
HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = {0, 0};
bool _leftButtonDown = false;
bool _rightButtonDown = false;

gameStudy _gs;

/* #### 함수 #### */
LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );
void setWindowSize( int x, int y, int width, int height );

/* #### 메인 #### */
int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow )
{
	_hInstance = hInstance;

	//MSG : 운영체제에서 발행하는 메시지 정보를 저장하기 위한 구조체
	MSG message;

	//WNDCLASS : 윈도우의 정보를 저장하기 위한 구조체
	WNDCLASS wndClass;

	wndClass.cbClsExtra = 0;             //클래스 여분 메모리
	wndClass.cbWndExtra = 0;             //윈도우 여분 메모리
	wndClass.hbrBackground = (HBRUSH) GetStockObject( WHITE_BRUSH ); //백그라운드
	wndClass.hCursor = LoadCursor( NULL, IDC_ARROW );  //커서
	wndClass.hIcon = LoadIcon( NULL, IDI_APPLICATION );//아이콘
	wndClass.hInstance = hInstance;              //인스턴스
	wndClass.lpfnWndProc = (WNDPROC) WndProc;    //윈도우 프로시져
	wndClass.lpszClassName = WINNAME;            //클래스이름
	wndClass.lpszMenuName = NULL;                //메뉴이름
	wndClass.style = CS_HREDRAW | CS_VREDRAW;    //윈도우 스타일

	//윈도우 클래스 등록
	RegisterClass( &wndClass );

	//윈도우 생성
	_hWnd = CreateWindow(
		WINNAME,     //윈도우 클래스의 이름
		WINNAME,     //윈도우 타이틀바 이름
		WINSTYLE,    //윈도우 스타일
		WINSTARTX,   //윈도우 화면좌표 x
		WINSTARTY,   //윈도우 화면좌표 y
		WINSIZEX,    //윈도우 화면좌표 width
		WINSIZEY,    //윈도우 화면좌표 height
		NULL,        //부모 윈도우
		(HMENU) NULL,//메뉴핸들
		hInstance,   //인스턴스 지정
		NULL );      //윈도우 및 자식 윈도우를 생성하면
					 //지정해주되 그렇지 않으면 NULL

	//화면 작업 사이즈 영역 계산
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	//화면에 윈도우 보여준다
	ShowWindow( _hWnd, nCmdShow );

	//게임 스터디의 초기화가 정상적으로 이뤄지지 않았다면 그냥 나가라
	if ( FAILED( _gs.init() ) )
	{
		return 0;
	}

	//메시지 루프~~

	//GetMessage : GetMessage는 메시지를 꺼내올 수 있을때까지 멈춰있는 함수이고,
	//PeekMessage : PeekMessage는 메시지가 없더라도 리턴되는 함수로서,
	//계속 루프되는 함수이다.


	while ( true ) //게임용
	{
		if ( PeekMessage( &message, NULL, 0, 0, PM_REMOVE ) )
		{
			if ( message.message == WM_QUIT ) break;
			TranslateMessage( &message );
			DispatchMessage( &message );
		}
		else
		{
			TIMEMANAGER->update( 70.f );
			_gs.update();
			_gs.render();
		}
	}

	//TranslateMessage : 키보드 입력메시지 처리를 담당한다.
	//입력된 키가 문자키인지 확인후 대문자 혹은 소문자, 한글, 영문,
	//인지에 대한 WM_CHAR메시지를 발생시킨다.

	//DispatchMessage : 윈도우 프로시져에서 전달된 메시지를 실제
	//윈도우로 전달해준다

	//메시지 큐에 메시지가 있으면 메시지 처리...
	//while ( GetMessage( &message, 0, 0, 0 ) ) //일반 프로그램용
	//{
	//	TranslateMessage( &message );
	//	DispatchMessage( &message );
	//}

	//스터디 해제
	_gs.release();

	//윈도우 클래스 등록 해제
	UnregisterClass( WINNAME, hInstance );

	return message.wParam;
}

//윈도우 프로시져 : 메시지를 운영체제에 전달
//강제로 운영체제가 호출해준다

//hWnd : 어느 윈도우에서 발생한 메시지인지 구분
//iMessage : 메시지 구분 번호
//wParam : unsigned int 마우스 버튼의 상태, 키보드 조합키의 상태를 전달
//lParam : unsigned long 마우스 클릭 좌표 전달
LRESULT CALLBACK WndProc( HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam )
{
	return _gs.MainProc( hWnd, iMessage, wParam, lParam );
}

//윈도우 사이즈 WINSIZEX, WINSIZEY 딱 맞게
void setWindowSize( int x, int y, int width, int height )
{
	RECT rc;

	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	AdjustWindowRect( &rc, WINSTYLE, false );

	SetWindowPos( _hWnd, NULL, x, y, ( rc.right - rc.left ),
		( rc.bottom - rc.top ), SWP_NOZORDER | SWP_NOMOVE );
}
