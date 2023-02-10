#pragma once


/* �ʴ� 100 �ȼ� ���� �;�.
   �ٵ� �� ��ǻ�ʹ� 200 ������ / second �� ����
   �׷��� �� ���� �� �ȼ� ���������ұ�?
   ���� ���� �ȼ� / �ð��� ������ �̰���?
   ���� ���� �ȼ� * 1������ �����̴µ� �ɸ��� �ð�*/

class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;


	double			m_dDT;			// ������ ���� �ð��� 
	double			m_dAcc;			// 1�� üũ�� ���� �ð� ������
	UINT            m_iCallCount;	// ȣ�� Ƚ�� üũ
	UINT			m_iFPS;			// 1�ʴ� ȣ�� Ƚ��
	// FPS�� �˾ƾ� ��
	// 1 �����Ӵ� �ɸ��� �ð� Delta Time

	// ������ UI�� �����̴� �������� �ð� ����ȭ�� ����Ǿ�� ��. ���� ������ ������ �ϱ� ���ؼ�
	// �ٵ� GetTickCount�δ� 1/1000 �� �����ۿ� �����µ� �� ��Ʈ�ϸ� �ص� �Ʊ� 1�ʿ� 2.4���� ���ư�
	// �׷� �װŷ� ����� �� ���� ����.

	// QueryPerformanceCounter();
	// ��� 1000������ 1�ʾ� �� �� �־�.

public:
	void init();
	// �ʱ�ȭ

	void update();
	// �� �����Ӹ���

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }

};

