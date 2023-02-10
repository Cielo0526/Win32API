#include "pch.h"
#include "CKeyMgr.h"

#include "CCore.h"


int g_arrVK[(int)KEY::LAST] =
{
  VK_LEFT,		// LEFT,
  VK_RIGHT,		// RIGHT,
  VK_UP,		// UP,
  VK_DOWN,		// DOWN,
				   
  'Q', 			// Q,
  'W',			// W,
  'E',			// E,
  'R',			// R,
  'T',			// T,
  'Y',			// Y,
  'U',			// U,
  'I',			// I,
  'O',			// O,
  'P',			// P,
  'A',			// A,
  'S',			// S,
  'D',			// D,
  'F',			// F,
  'G',			// G,
  'Z',			// Z,
  'X',			// X,
  'C',			// C,
  'V',			// V,
  'B',			// B,
				   
  VK_MENU,		// ALT,
  VK_CONTROL,	// CTRL,
  VK_LSHIFT,	// LSHIFT,
  VK_SPACE,		// SAPCE,
  VK_RETURN,	// ENTER,
  VK_ESCAPE,	// ESC,

  //LAST 는 그냥 끝을 알리기 위한 그거였으니까 추가할 필요 없지,
}
	;



CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}

}

void CKeyMgr::update()
{
	// 윈도우 포커싱 확인 후 포커싱이 아니라면 안눌린 상태로 고정해두자
	// 혹여나 HOLD 였다면 자연스럽게 HOLD->AWAY->NONE 순으로 가게 해주자
	
	// HWND hMainWnd = CCore::GetInst()->GetMainHwnd(); 메인 윈도우에 있을 때만 움직이게 할거면 이거랑 밑이랑 비교하면 되고
	//													그냥 뭐든 우리 프로그램이 포커싱 되있는지 보려면 밑에만 null인지 아닌지
	HWND hWnd = GetFocus(); // 현재 포커싱 되어있는 윈도우 값을 반환해줌, 아예 없으면 0.

	// 윈도우가 포커싱일 때
	if(nullptr != hWnd)
	{
	// 실제로 눌렸는지 계속 확인을 해줘야하니까, GetAsyncKeyState를 쓸건데,
	// 그 안에 인자로 VK_어쩌구들을 줘야하는데 거기는 16진수 이상한 숫자고,
	// 우리꺼는 그냥 0부터 enum class로 준건데 어떻게 해?

	// -> 각 해당하는 int 배열을 만들어서 대칭시키면 되지 enum 으로
	// 이게 enum의 힘이다!

		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			// 키가 눌려있다.
			if( GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				// 이전에도 눌려있었다.
				if (m_vecKey[i].bPrevPush)
				{
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				// 이전에 눌려있지 않았다.
				else
				{
					m_vecKey[i].eState = KEY_STATE::TAP;
				}
				// 키 눌려있음 처리
				m_vecKey[i].bPrevPush = true;
			}
			// 키가 안눌려있다.
			else
			{
				// 이전에 눌려있었다.
				if (m_vecKey[i].bPrevPush)
				{
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				// 이전에도 눌려있지 않았다
				else
				{
					m_vecKey[i].eState = KEY_STATE::NONE;
				}
				m_vecKey[i].bPrevPush = false;
			}
		}
	}
	
	// 윈도우 포커싱 안되어있음
	else
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			m_vecKey[i].bPrevPush = false;
			
			if (KEY_STATE::TAP == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::HOLD == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}

	}
}
