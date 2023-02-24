#pragma once

class CCollider;

// ȭ�鿡 �����ϴ� �ϳ��ϳ��� ��ü
class CObject
{
private:
	/*
	POINT		m_ptPos;
	POINT		m_ptScale;
	*/
	/* 1�ȼ��� ���������� ��ǻ�Ͱ� �ʹ� ���� 1�ʿ� ���� ��Ʈ�����ε� 2.7������ �����̴µ� ������ ��06��
	 �׷��� �Ǽ� ������ �����ϰž�
	 �׷���, �Ǽ� ������ �ȼ��� �ɰ� �� �ֳ�? �Ұ�����
	 �����ΰ�, �Ǽ� ������ �����͵� ĳ���� �� ���� ������ �ٲ㼭 ������ �׷��� ������ ��ü��
	 �Ǽ��� ������ ���� �� �־� */
	Vec2			m_vPos;
	Vec2			m_vScale;

	CCollider*		m_pCollider;
	 /* �浹�� Object �鳢�� �Ͼ -> Object���� �浹�� �˼� �ִ� ��Ҹ� �߰�
	    �ٵ� �浹�� �ʿ��� �ֵ鵵 �ְ� ���� �ֵ鵵 �־�
	    �׷��ϰ� Object�� �� �ٱ�� ������ �浹 �ִ� ���� �ֵ�� ���� �� ����
	    �ٵ� ���߿� �ٱ⸦ �������� �͵��� �����ؾ��� ���� ���� ��� �ɱ�?
	    �̰� ���߿� ��ġ�� ������ �� �־�. �׷��� �ʹ� ��� �ٱ⸦ ��� �صθ� ���߿� ���� ���� ���ɼ��� �ִ�.
	    �׷��� ����ϴ°� Component ��� ������ 
		
		�׳� ���� ���� ���� �ְ�, ���� ���� �ִ� '��ǰ' ��Ҹ� ������ �ִٰ�
		�ʿ��� �ֵ��� Ȱ��ȭ �ϰ�, �ƴ� �ֵ��� ��Ȱ��ȭ ��Ű�°ž� ��ǰó��
		
		Ŭ������ ��� �ִٰ� �ʿ� ������ nullptr�� �صθ� �ǰ�, �ʿ��ϸ� �ּ� �־��ָ� ��*/

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
	/* Collider �� �ϳ� �־�.�׸��� Collider�� ����, �浹�� ������ ������Ʈ���� Collider�� �ּҸ� ������ ����.
	   �׷��� Collider�� �浹��� ���� ������Ʈ�鸶�� �� ���ε��� �����������? �ƴ���
	   �ٸ� ������Ʈ�鵵 Collider�� ������ �ִ°� �Ƴ�. CreateCollider��  ������ �ִ°���*/
	virtual void render(HDC _dc);

	void component_render(HDC _dc);


	// ������Ʈ�鵵 �������� ������ �־�. ��Ǯ�� �׳� �ð� ���� ���Ÿ��Ű�,
	// �������� ���� ��ȭ�� ���� ������ ������ �����Ű� �÷��̾�� �����϶����� ���ϰ�
	// �׷��� ������ virtual�� ���� �Լ��� ���� update�� render�� �����
	// ������ �ٸ� ������Ʈ�� ������ �ٸ� update�� render�� �� �� �ִ�.


public:
	CObject();
	virtual ~CObject();
};

