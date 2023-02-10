#pragma once


/* 초당 100 픽셀 가고 싶어.
   근데 내 컴퓨터는 200 프레임 / second 가 나와
   그러면 한 번에 몇 픽셀 움직여야할까?
   가고 싶은 픽셀 / 시간당 프레임 이겠지?
   가고 싶은 픽셀 * 1프레임 움직이는데 걸리는 시간*/

class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;


	double			m_dDT;			// 프레임 간의 시간값 
	double			m_dAcc;			// 1초 체크를 위한 시간 누적값
	UINT            m_iCallCount;	// 호출 횟수 체크
	UINT			m_iFPS;			// 1초당 호출 횟수
	// FPS를 알아야 해
	// 1 프레임당 걸리는 시간 Delta Time

	// 심지어 UI가 움직이는 것조차도 시간 동기화가 적용되어야 해. 같은 경험을 느끼게 하기 위해서
	// 근데 GetTickCount로는 1/1000 초 까지밖에 못세는데 이 노트북만 해도 아까 1초에 2.4만번 돌아가
	// 그럼 그거로 제대로 셀 수가 없어.

	// QueryPerformanceCounter();
	// 얘는 1000만분의 1초씩 셀 수 있어.

public:
	void init();
	// 초기화

	void update();
	// 매 프레임마다

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }

};

