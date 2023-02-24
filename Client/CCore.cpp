#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
//CCore* CCore::g_pInst = nullptr;

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
	, m_arrBrush{}
	, m_arrPen{}
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

	for (int i = 0; i < (UINT)PEN_TYPE::END; i++)
	{
		DeleteObject(m_arrPen[i]);
	}

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

	// ���� ��� �� �� �� �귯�� ����
	CreateBrushPen();

	// Manager �ʱ�ȭ
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();


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
	CCollisionMgr::GetInst()->update();
	// ��ü���� ������ üũ (��ǥ ���)
	// �� �� �浹 �˻�
	

	// ===========
	//  Rendering
	// ===========

	// ȭ�� clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);


	CSceneMgr::GetInst()->render(m_memDC);
	// ������ Scene�� ������Ʈ �ϰ�, ���⼭ �׷����� �Ʒ����� ������� ��½����ְ�

	// ����� ��Ʈ�ʿ��� ������� ��Ʈ������ ����
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_memDC, 0, 0, SRCCOPY);

	//CTimeMgr::GetInst()->render();
}

void CCore::CreateBrushPen()
{
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH); // ��� ���ʿ� Window ������ ����� �������� �����аŶ� �˾Ƽ� ������. �Ҹ� �Ű� �� �ʿ� x

	// red green blue pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

}
