#pragma once


// 화면에 존재하는 하나하나의 물체
class CObject
{
private:
	/*
	POINT		m_ptPos;
	POINT		m_ptScale;
	*/
	/* 1픽셀씩 움직여서는 컴퓨터가 너무 빨라서 1초에 지금 노트북으로도 2.7만번이 움직이는데 감당이 안06돼
	 그래서 실수 단위로 움직일거야
	 그런데, 실수 단위로 픽셀을 쪼갤 수 있나? 불가능해
	 다행인건, 실수 상태의 데이터도 캐스팅 할 때는 정수로 바꿔서 가져가 그래서 데이터 자체는
	 실수로 가지고 있을 수 있어 */
	Vec2		m_vPos;
	Vec2		m_vScale;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }
	

public:
	virtual void update() = 0;
	virtual void render(HDC _dc);


	// 오브젝트들도 여러가지 성격이 있어. 수풀은 그냥 시간 내내 흔들거릴거고,
	// 돌같은건 뭔가 변화가 있을 때까지 가만히 있을거고 플레이어는 움직일때마다 변하고
	// 그렇기 떄문에 virtual로 가상 함수로 만들어서 update와 render를 해줘야
	// 성격이 다른 오브젝트들 마다의 다른 update와 render를 할 수 있다.


public:
	CObject();
	virtual ~CObject();
};

