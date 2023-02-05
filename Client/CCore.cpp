#include "pch.h"
#include "CCore.h"

//CCore* CCore::g_pInst = nullptr;


CCore::CCore()
{

}

CCore::~CCore()
{

}


int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// 해상도에 맞게 윈도우 크기 조절
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt /* 구조체 RECT의 주소값, 크기 설정 이거를 받아서 그 안에 적당한 값을 넣어줘. 그러니까 그냥 pointer로 받아가 const 말고. 보통 리턴값이 너무 큰 자료형이면 이런식으로 해. 리턴을 주려면 어디에 임시값을 줘야되니까*/
		, WS_OVERLAPPEDWINDOW /* 윈도우 기본 세팅임 들어가보면 비트 연산자로 이것저것 설정 가능*/
		, true/*메뉴바 있으니까 그거 감안해달라고 true*/); // 윈도우 버전마다 설정이 살짝 다른데 그거에 따라 맞춰주는거
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
	// x, y 는 전체 화면 기준으로 어디서부터냐 하는거

	_ptResolution.x;
	_ptResolution.y;

	return S_OK;
}

void CCore::progress()
// 이곳이 프로그램이 실행될 곳
{

}
