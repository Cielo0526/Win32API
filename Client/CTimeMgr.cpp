#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"



CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_dDT(0.)
	, m_dAcc(0)
	, m_iCallCount()
{
}

CTimeMgr::~CTimeMgr()
{


}

void CTimeMgr::init()
{
	QueryPerformanceCounter(&m_llPrevCount);
	// ���� ī��Ʈ

	QueryPerformanceFrequency(&m_llFrequency);
	// 1�ʴ� ī��Ʈ�� �󸶳� �߻��ϴ��� �˷��ִ� �Լ�
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);

	// ���� �������� ī���ð�, ���� ������ ī���� ���� ���̸� ������.
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;
	// ������Ʈ�� �� �����Ӹ��� �����ϱ� �ʱ�ȭ �� ó�� ������ �ð� �� ������Ʈ�� �� �ð��̶� ����
	// �� �������� �ð��� ���� => �װ� PrevCount�� �ٽ� ���� => �ݺ� => �����Ӹ����� �ð��� ���



	
	// ���� ī��Ʈ ���� ���簪���� ����(�������� ����� ���ؼ�)
	m_llPrevCount = m_llCurCount;

	// = 1. / m_dDT; �̷��� �ص� FPS�� ������ ������,  �ƹ����� ��� �����ϱ� ������ �� �Ҿ�����
	// �׷��� �׳� 1�ʵ��� ����
	++m_iCallCount;
	m_dAcc += m_dDT; // DT ���� = �ð� ����

	if (m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_dDT);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}

	


}
