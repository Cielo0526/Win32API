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
	// 현재 카운트

	QueryPerformanceFrequency(&m_llFrequency);
	// 1초당 카운트가 얼마나 발생하는지 알려주는 함수
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);

	// 이전 프레임의 카운팅과, 현재 프레임 카운팅 값의 차이를 나눈다.
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;
	// 업데이트는 매 프레임마다 들어오니까 초기화 때 처음 세놓은 시간 을 업데이트때 센 시간이랑 빼면
	// 한 프레임의 시간이 나옴 => 그걸 PrevCount에 다시 넣음 => 반복 => 프레임마다의 시간을 계산



	
	// 이전 카운트 값을 현재값으로 갱신(다음번의 계산을 위해서)
	m_llPrevCount = m_llCurCount;

	// = 1. / m_dDT; 이렇게 해도 FPS가 나오긴 하지만,  아무래도 계속 변동하기 때문에 좀 불안정해
	// 그래서 그냥 1초동안 세자
	++m_iCallCount;
	m_dAcc += m_dDT; // DT 누적 = 시간 누적

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
