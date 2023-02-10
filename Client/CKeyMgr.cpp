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

  //LAST �� �׳� ���� �˸��� ���� �װſ����ϱ� �߰��� �ʿ� ����,
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
	// ������ ��Ŀ�� Ȯ�� �� ��Ŀ���� �ƴ϶�� �ȴ��� ���·� �����ص���
	// Ȥ���� HOLD ���ٸ� �ڿ������� HOLD->AWAY->NONE ������ ���� ������
	
	// HWND hMainWnd = CCore::GetInst()->GetMainHwnd(); ���� �����쿡 ���� ���� �����̰� �ҰŸ� �̰Ŷ� ���̶� ���ϸ� �ǰ�
	//													�׳� ���� �츮 ���α׷��� ��Ŀ�� ���ִ��� ������ �ؿ��� null���� �ƴ���
	HWND hWnd = GetFocus(); // ���� ��Ŀ�� �Ǿ��ִ� ������ ���� ��ȯ����, �ƿ� ������ 0.

	// �����찡 ��Ŀ���� ��
	if(nullptr != hWnd)
	{
	// ������ ���ȴ��� ��� Ȯ���� ������ϴϱ�, GetAsyncKeyState�� ���ǵ�,
	// �� �ȿ� ���ڷ� VK_��¼������ ����ϴµ� �ű�� 16���� �̻��� ���ڰ�,
	// �츮���� �׳� 0���� enum class�� �ذǵ� ��� ��?

	// -> �� �ش��ϴ� int �迭�� ���� ��Ī��Ű�� ���� enum ����
	// �̰� enum�� ���̴�!

		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			// Ű�� �����ִ�.
			if( GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				// �������� �����־���.
				if (m_vecKey[i].bPrevPush)
				{
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				// ������ �������� �ʾҴ�.
				else
				{
					m_vecKey[i].eState = KEY_STATE::TAP;
				}
				// Ű �������� ó��
				m_vecKey[i].bPrevPush = true;
			}
			// Ű�� �ȴ����ִ�.
			else
			{
				// ������ �����־���.
				if (m_vecKey[i].bPrevPush)
				{
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				// �������� �������� �ʾҴ�
				else
				{
					m_vecKey[i].eState = KEY_STATE::NONE;
				}
				m_vecKey[i].bPrevPush = false;
			}
		}
	}
	
	// ������ ��Ŀ�� �ȵǾ�����
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
