#pragma once

class CCollider;


// 유니온
// 1. 유니온의 크기 측정 방식 -> 그 중에 가장 큰 변수 크기만큼만 차지해서 공용으로 씀
// 2. 그 하나를 여러개의 방식으로 해석할 수 있게끔 하는거
// 3. 그래서 각각의 id를 잘라넣어서 COLLIDER_ID의 LONGLONG으로 쓰겠다 이거지

union COLLIDER_ID
{
	struct {
		UINT iLeft_id;
		UINT iRight_id;
	};
	ULONGLONG ID;
};

class CCollisionMgr
{
	SINGLE(CCollisionMgr)

private:
	// 충돌체간의 이전 프레임 충돌 정보 (둘만의 조합으로 유일무이한 키값을 만들면 되겠지?)
	map<ULONGLONG, bool>		 m_mapColInfo;

	UINT					 m_arrCheck[(UINT)GROUP_TYPE::END];
	// 그룹은 총 32 가지니까 32비트(4바이트)짜리 비트 연산자로 체크박스를 만들자~
	// A와 B 그룹의 충돌을 알아봐주세요 -> 작은 숫자가 행, 큰 숫자가 열(비트값)


public:
	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset() {	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END);
				  /*memeset은 그냥 지정한 주소를 지정한 값으로 바이트 단위로 밀어버림*/	}

private:
	void CollisionUpdateGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
};

