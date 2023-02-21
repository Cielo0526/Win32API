#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
//CCore* CCore::g_pInst = nullptr;

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
{

}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);
	// 커널 오브젝트니까 해제 해야하는데, 메세지 함수랑 맞물리는게 아니라 끝날 때만 지워주면 돼.
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
	// -> 윈도우와 연결된 DC와는 다르게 이렇게 이중 버퍼링에 쓰는 DC랑 비트맵은 딜리트로 없애줘야함
	// 이유는 몰라 레퍼런스에서 그렇게 하래
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
	// 1288 768

	m_hDC = GetDC(m_hWnd);

	// 이중 버퍼링 용도의 비트맵과 DC를 만든다.
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);
	// Compatible -> 호환성 ==> 어차피 원본과 같은걸 만들어야 하니까
	// 이것들도 핸들값을 받기 때문에 핸들로 받아서 나중에 프로그램 끝날때 Delete 해줌
	
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	// DC를 만들면 걔는 기본적으로 1픽셀짜리 비트맵을 받아. 그래서 그걸 hBit으로 목적지를 바꿔줘
	DeleteObject(hOldBit);
	// 그리고 환원받은 1픽셀짜리 기본 비트맵을 버려

	// Manager 초기화
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();


	return S_OK;
}



void CCore::progress()
// 이곳이 프로그램이 실행될 곳
{
	// 그리기 작업
	// BeginPaint는 메세지 기반 프로세스 안에서만 작동해. 그래서 다른 방식을 써야함

	// 랜더링이라는게 매 순간순간 모든 장면들을 다시 그림 (변경점이 없을지라도)
	// 그리는 과정은 숨겨두고 다 그려진 그림만 보여줘서 자연스러워 보일 뿐

	/* static int callcount = 0;
	++callcount;
	
	static int iPrevCount = GetTickCount();
	int iCurCount = GetTickCount();
	if (iCurCount - iPrevCount > 1000)
	{
		iPrevCount = iCurCount;
		callcount = 0;
	}*/

	//Manager Update
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();

	CSceneMgr::GetInst()->update();
	// 물체들의 변경점 체크 (좌표 등등)
	

	// ===========
	//  Rendering
	// ===========

	// 화면 clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);


	CSceneMgr::GetInst()->render(m_memDC);
	// 위에서 Scene을 업데이트 하고, 여기서 그려내고 아래에서 윈도우로 출력시켜주고

	// 복사용 비트맵에서 윈도우용 비트맵으로 복사
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_memDC, 0, 0, SRCCOPY);

	//CTimeMgr::GetInst()->render();
}
