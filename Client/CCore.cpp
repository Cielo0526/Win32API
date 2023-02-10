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
	// Ŀ�� ������Ʈ�ϱ� ���� �ؾ��ϴµ�, �޼��� �Լ��� �¹����°� �ƴ϶� ���� ���� �����ָ� ��.
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
	// -> ������� ����� DC�ʹ� �ٸ��� �̷��� ���� ���۸��� ���� DC�� ��Ʈ���� ����Ʈ�� ���������
	// ������ ���� ���۷������� �׷��� �Ϸ�
}


int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// �ػ󵵿� �°� ������ ũ�� ����
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt /* ����ü RECT�� �ּҰ�, ũ�� ���� �̰Ÿ� �޾Ƽ� �� �ȿ� ������ ���� �־���. �׷��ϱ� �׳� pointer�� �޾ư� const ����. ���� ���ϰ��� �ʹ� ū �ڷ����̸� �̷������� ��. ������ �ַ��� ��� �ӽð��� ��ߵǴϱ�*/
		, WS_OVERLAPPEDWINDOW /* ������ �⺻ ������ ������ ��Ʈ �����ڷ� �̰����� ���� ����*/
		, true/*�޴��� �����ϱ� �װ� �����ش޶�� true*/); // ������ �������� ������ ��¦ �ٸ��� �װſ� ���� �����ִ°�
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
	// x, y �� ��ü ȭ�� �������� ��𼭺��ͳ� �ϴ°�
	// 1288 768

	m_hDC = GetDC(m_hWnd);

	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� �����.
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);
	// Compatible -> ȣȯ�� ==> ������ ������ ������ ������ �ϴϱ�
	// �̰͵鵵 �ڵ鰪�� �ޱ� ������ �ڵ�� �޾Ƽ� ���߿� ���α׷� ������ Delete ����
	
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	// DC�� ����� �´� �⺻������ 1�ȼ�¥�� ��Ʈ���� �޾�. �׷��� �װ� hBit���� �������� �ٲ���
	DeleteObject(hOldBit);
	// �׸��� ȯ������ 1�ȼ�¥�� �⺻ ��Ʈ���� ����

	// Manager �ʱ�ȭ
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst(); init();

	g_obj.SetPos(Vec2(m_ptResolution.x / 2, m_ptResolution.y / 2));
	g_obj.SetScale(Vec2(100, 100));


	return S_OK;
}



void CCore::progress()
// �̰��� ���α׷��� ����� ��
{
	// �׸��� �۾�
	// BeginPaint�� �޼��� ��� ���μ��� �ȿ����� �۵���. �׷��� �ٸ� ����� �����

	// �������̶�°� �� �������� ��� ������ �ٽ� �׸� (�������� ��������)
	// �׸��� ������ ���ܵΰ� �� �׷��� �׸��� �����༭ �ڿ������� ���� ��

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
	// ��ü���� ������ üũ (��ǥ ���)
	

	// ===========
	//  Rendering
	// ===========

	// ȭ�� clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);


	CSceneMgr::GetInst()->render();
	// ������ Scene�� ������Ʈ �ϰ�, ���⼭ �׷����� �Ʒ����� ������� ��½����ְ�

	// ����� ��Ʈ�ʿ��� ������� ��Ʈ������ ����
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_memDC, 0, 0, SRCCOPY);

}

void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	// Message ����� �ƴϱ� ������ ��Ŀ�� �Ǿ��ִ��� �ƴ��� �𸣰�, �ڵ尡 ��� ���� �ִٴ� �� �Ű�����
	// if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		// GetAsyncKeyState �� �ܼ��� ���ȴ°��� �������� �ʰ� �̰����� ���¸� ���� ��Ʈ�� ��. �ֻ��� ��Ʈ�� ���ȴ��� ������
	if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)
	{
		vPos.x -= 200.f * fDT;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD)
	{
		vPos.x += 200.f * fDT;
	}
	// �ٵ� �̷��� �ع����� ���� ���� �ֵ��� �� ���� �����ϰžƳ�
	// �׷��� �ʿ��Ѱ� '�ð� ����ȭ'�� �ʿ����� (1�ʴ� �� �ȼ� �����̰Բ�)

	g_obj.SetPos(vPos);
	g_obj.SetScale(vScale);
	
}

void CCore::render()
{
	
	
	
	// ���� ���۸��� Bit�� �׸���


	//Vec2 vPos = g_obj.GetPos();
	//Vec2 vScale = g_obj.GetScale();
	//Rectangle(m_memDC, int(vPos.x - vScale.x / 2.f)
	//	, int(vPos.y - vScale.y / 2.f)
	//	, int(vPos.x + vScale.x / 2.f)
	//	, int(vPos.y + vScale.y / 2.f));

	//// ����� ��Ʈ�ʿ��� ������� ��Ʈ������ ����
	//BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
	//		,m_memDC, 0, 0, SRCCOPY);

	// => ���� FPS ��������. �ֳĸ� ���� CPU���� �̿��ϴϱ�.
	// => Direct ������ ���� GPU�� ��.
	// => ��� BitBlt�� ��������̾�. �󸶳� ����� �۾��� �ص� �ȼ� ���� �޶����� �����ϱ�.

	
	// ���� �ϴ� ���Ÿ�

	// ȭ�� Clear
	// Rectangle(m_hDC,  -1, -1, m_ptResolution.x + 1, m_ptResolution.y +1);

	/* �ȼ��� 1280 x 7680 �̶�� �ص� ���� �鸸���� 
	   ������ �̷��� �����, �׸��� �ݺ��ε� �츮�� '�簢���� �ִ�' ������ ���ٴ� Ȯ�ŵ� ����
	   �׳� ��ĭ�� �� ���� ����*/
	/* ���� render �ȿ� Rectangle�� �ΰ��ϱ� �ΰ��� �۾��� ���� �̷����� �ִ°��ݾ�. 
	   �׷��ϱ� �׸��� ������ �ٸ� ������ ���� ���� �� �Ŀ�
	   �� ��ü�� �� ���� �׸��Բ� �ϸ� '�ϼ���' ���� ���� ������ -> 2�� ���۸�*/

	// �׸���
	// Vec2 vPos = g_obj.GetPos();
	// Vec2 vScale = g_obj.GetScale();

    // Rectangle(m_hDC, int(vPos.x - vScale.x / 2.f)
	//				,int(vPos.y - vScale.y / 2.f)
	//				,int(vPos.x + vScale.x / 2.f)
	//				,int(vPos.y + vScale.y / 2.f));
	

}


