#include "pch.h"
#include "CCore.h"

#include "CObject.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"
//CCore* CCore::g_pInst = nullptr;


CObject g_obj;

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
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst(); init();

	g_obj.SetPos(Vec2(m_ptResolution.x / 2, m_ptResolution.y / 2));
	g_obj.SetScale(Vec2(100, 100));


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


	CSceneMgr::GetInst()->render();
	// 위에서 Scene을 업데이트 하고, 여기서 그려내고 아래에서 윈도우로 출력시켜주고

	// 복사용 비트맵에서 윈도우용 비트맵으로 복사
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_memDC, 0, 0, SRCCOPY);

}

void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	// Message 방식이 아니기 때문에 포커싱 되어있는지 아닌지 모르고, 코드가 계속 돌고 있다는 걸 신경써야함
	// if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		// GetAsyncKeyState 는 단순히 눌렸는가를 리턴하지 않고 이것저것 상태를 같이 비트로 줘. 최상위 비트가 눌렸는지 여부임
	if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)
	{
		vPos.x -= 200.f * fDT;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD)
	{
		vPos.x += 200.f * fDT;
	}
	// 근데 이렇게 해버리면 성능 좋은 애들은 더 빨리 움직일거아냐
	// 그러면 필요한게 '시간 동기화'가 필요하지 (1초당 몇 픽셀 움직이게끔)

	g_obj.SetPos(vPos);
	g_obj.SetScale(vScale);
	
}

void CCore::render()
{
	
	
	
	// 이중 버퍼링할 Bit에 그리기


	//Vec2 vPos = g_obj.GetPos();
	//Vec2 vScale = g_obj.GetScale();
	//Rectangle(m_memDC, int(vPos.x - vScale.x / 2.f)
	//	, int(vPos.y - vScale.y / 2.f)
	//	, int(vPos.x + vScale.x / 2.f)
	//	, int(vPos.y + vScale.y / 2.f));

	//// 복사용 비트맵에서 윈도우용 비트맵으로 복사
	//BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
	//		,m_memDC, 0, 0, SRCCOPY);

	// => 벌써 FPS 개떨어짐. 왜냐면 아직 CPU만을 이용하니까.
	// => Direct 쪽으로 가면 GPU를 씀.
	// => 대신 BitBlt은 고정비용이야. 얼마나 대단한 작업을 해도 픽셀 수는 달라지지 않으니까.

	
	// 원래 하던 짓거리

	// 화면 Clear
	// Rectangle(m_hDC,  -1, -1, m_ptResolution.x + 1, m_ptResolution.y +1);

	/* 픽셀만 1280 x 7680 이라고만 해도 거의 백만개야 
	   심지어 이러면 지우고, 그리고 반복인데 우리가 '사각형이 있는' 시점을 본다는 확신도 없어
	   그냥 빈칸을 볼 수도 있음*/
	/* 지금 render 안에 Rectangle이 두개니까 두개의 작업이 따따 이뤄지고 있는거잖아. 
	   그러니까 그리는 과정을 다른 곳에서 전부 수행 한 후에
	   그 전체만 한 번에 그리게끔 하면 '완성본' 만을 보지 않을까 -> 2중 버퍼링*/

	// 그리기
	// Vec2 vPos = g_obj.GetPos();
	// Vec2 vScale = g_obj.GetScale();

    // Rectangle(m_hDC, int(vPos.x - vScale.x / 2.f)
	//				,int(vPos.y - vScale.y / 2.f)
	//				,int(vPos.x + vScale.x / 2.f)
	//				,int(vPos.y + vScale.y / 2.f));
	

}


