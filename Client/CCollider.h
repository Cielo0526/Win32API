#pragma once


// �浹ü�� �ݶ��̴��� ������Ʈ�� ���󰡸鼭 �浹�ߴ��� �ƴ��� �˾ƾ� ��

class CObject;

class CCollider
{
private:
	static UINT	 g_iNextID;		// m_iID ���� ���� ��ġ�� �ʰ� �ϰԲ� ���� ���� ����

	CObject*	 m_pOwner;		// collider�� �����ϰ� �ִ� ������Ʈ
	Vec2		 m_vOffsetPos;	// ������ == ���� ��ġ(������ object)���������� ������� ���̰�
	Vec2		 m_vFinalPos;	// �浹ü�� ���� ��ġ (finalupdate���� �� �����Ӹ��� ���
	Vec2		 m_vScale;		// �浹ü�� ũ��

	UINT		 m_iID;			// �浹ü�� ������ ID ��
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
	// �浹 ���� �Լ�
	void OnCollision(CCollider* _pOther); // �浹 ���� ��� ȣ��
	void OnCollisionEnter(CCollider* _pOther); // �浹 ���� ��
	void OnCollisionExit(CCollider* _pOther); // �浹 ���� ��

	CCollider& operator = (CCollider& _origin) = delete;
	// ������ �Ǹ� ID���� �ߺ��Ǵµ�, ���ʿ� �⵹ü���� ������ ����.. �����Ŷ�� ������
	// �׷��� �ƿ� �Ǽ� ������ ���� ������ ���ƹ����� ���ݾ�. �׷� �̷��� ���ƹ���

public:
	CCollider();
	CCollider(const CCollider& _origin);
	// ���࿡ ���簡 �ǹ����� ���� ID���� ����ǹ����ݾ�?? �װ� �����ϱ� ���� ���� �����ڵ� ���� �����
	~CCollider();

	friend class CObject;
};

