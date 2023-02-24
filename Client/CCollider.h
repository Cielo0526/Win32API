#pragma once


// 충돌체인 콜라이더는 오브젝트를 따라가면서 충돌했는지 아닌지 알아야 함

class CObject;

class CCollider
{
private:
	static UINT	 g_iNextID;		// m_iID 값을 절대 겹치지 않게 하게끔 해줄 정적 변수

	CObject*	 m_pOwner;		// collider를 소유하고 있는 오브젝트
	Vec2		 m_vOffsetPos;	// 오프셋 == 기준 위치(지금은 object)에서부터의 상대적인 차이값
	Vec2		 m_vFinalPos;	// 충돌체의 최종 위치 (finalupdate에서 매 프레임마다 계산
	Vec2		 m_vScale;		// 충돌체의 크기

	UINT		 m_iID;			// 충돌체의 고유한 ID 값
	int		 m_iCol;

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

	Vec2 GetFinalPos() { return m_vFinalPos; }

	UINT GetID() { return m_iID; }

public:
	void finalupdate();
	void render(HDC _dc);

public:
	// 충돌 시점 함수
	void OnCollision(CCollider* _pOther); // 충돌 중인 경우 호출
	void OnCollisionEnter(CCollider* _pOther); // 충돌 진입 시
	void OnCollisionExit(CCollider* _pOther); // 충돌 해제 시

	CCollider& operator = (CCollider& _origin) = delete;
	// 대입이 되면 ID값이 중복되는데, 애초에 출돌체끼리 대입할 일이.. 없을거라고 생각해
	// 그러면 아예 실수 방지를 위해 대입을 막아버리면 되잖아. 그럼 이렇게 막아버려

public:
	CCollider();
	CCollider(const CCollider& _origin);
	// 만약에 복사가 되버리면 고유 ID값도 복사되버리잖아?? 그걸 방지하기 위해 복사 생성자도 내가 만든다
	~CCollider();

	friend class CObject;
};

