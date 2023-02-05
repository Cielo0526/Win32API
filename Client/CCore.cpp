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

	// �ػ󵵿� �°� ������ ũ�� ����
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt /* ����ü RECT�� �ּҰ�, ũ�� ���� �̰Ÿ� �޾Ƽ� �� �ȿ� ������ ���� �־���. �׷��ϱ� �׳� pointer�� �޾ư� const ����. ���� ���ϰ��� �ʹ� ū �ڷ����̸� �̷������� ��. ������ �ַ��� ��� �ӽð��� ��ߵǴϱ�*/
		, WS_OVERLAPPEDWINDOW /* ������ �⺻ ������ ������ ��Ʈ �����ڷ� �̰����� ���� ����*/
		, true/*�޴��� �����ϱ� �װ� �����ش޶�� true*/); // ������ �������� ������ ��¦ �ٸ��� �װſ� ���� �����ִ°�
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
	// x, y �� ��ü ȭ�� �������� ��𼭺��ͳ� �ϴ°�

	_ptResolution.x;
	_ptResolution.y;

	return S_OK;
}

void CCore::progress()
// �̰��� ���α׷��� ����� ��
{

}
