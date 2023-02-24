#pragma once

class CCollider;

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
	Vec2			m_vPos;
	Vec2			m_vScale;

	CCollider*		m_pCollider;
	 /* 충돌은 Object 들끼리 일어남 -> Object에서 충돌을 알수 있는 요소를 추가
	    근데 충돌이 필요한 애들도 있고 없는 애들도 있어
	    그러니가 Object를 두 줄기로 나눠서 충돌 있는 없는 애들로 나눌 수 있지
	    근데 나중에 줄기를 나눠놓은 것들을 변경해야할 때가 오면 어떻게 될까?
	    이게 나중에 골치가 아파질 수 있어. 그래서 너무 상속 줄기를 깊게 해두면 나중에 일이 생길 가능성이 있다.
	    그래서 사용하는게 Component 기반 구조야 
		
		그냥 누군 있을 수도 있고, 없을 수도 있는 '부품' 요소를 가지고 있다가
		필요한 애들은 활성화 하고, 아닌 애들은 비활성화 시키는거야 부품처럼
		
		클래스로 들고 있다가 필요 없으면 nullptr로 해두면 되고, 필요하면 주소 넣어주면 돼*/

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	CCollider* GetCollider() { return m_pCollider; }

	void CreateCollider();
	

public:
	virtual void update() = 0;
	virtual void finalupdate() final;
	/* Collider 는 하나 있어.그리고 Collider를 가진, 충돌이 가능한 오브젝트들은 Collider의 주소를 가지고 있지.
	   그러면 Collider는 충돌기능 가진 오브젝트들마다 다 따로따로 실행해줘야해? 아니지
	   다른 오브젝트들도 Collider를 가지고 있는게 아냐. CreateCollider로  가지고 있는거지*/
	virtual void render(HDC _dc);

	void component_render(HDC _dc);


	// 오브젝트들도 여러가지 성격이 있어. 수풀은 그냥 시간 내내 흔들거릴거고,
	// 돌같은건 뭔가 변화가 있을 때까지 가만히 있을거고 플레이어는 움직일때마다 변하고
	// 그렇기 떄문에 virtual로 가상 함수로 만들어서 update와 render를 해줘야
	// 성격이 다른 오브젝트들 마다의 다른 update와 render를 할 수 있다.


public:
	CObject();
	virtual ~CObject();
};

