#pragma once

class CCollider;


// ���Ͽ�
// 1. ���Ͽ��� ũ�� ���� ��� -> �� �߿� ���� ū ���� ũ�⸸ŭ�� �����ؼ� �������� ��
// 2. �� �ϳ��� �������� ������� �ؼ��� �� �ְԲ� �ϴ°�
// 3. �׷��� ������ id�� �߶�־ COLLIDER_ID�� LONGLONG���� ���ڴ� �̰���

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
	// �浹ü���� ���� ������ �浹 ���� (�Ѹ��� �������� ���Ϲ����� Ű���� ����� �ǰ���?)
	map<ULONGLONG, bool>		 m_mapColInfo;

	UINT					 m_arrCheck[(UINT)GROUP_TYPE::END];
	// �׷��� �� 32 �����ϱ� 32��Ʈ(4����Ʈ)¥�� ��Ʈ �����ڷ� üũ�ڽ��� ������~
	// A�� B �׷��� �浹�� �˾ƺ��ּ��� -> ���� ���ڰ� ��, ū ���ڰ� ��(��Ʈ��)


public:
	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset() {	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END);
				  /*memeset�� �׳� ������ �ּҸ� ������ ������ ����Ʈ ������ �о����*/	}

private:
	void CollisionUpdateGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
};

