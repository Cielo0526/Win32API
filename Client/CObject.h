#pragma once


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


	// ������Ʈ�鵵 �������� ������ �־�. ��Ǯ�� �׳� �ð� ���� ���Ÿ��Ű�,
	// �������� ���� ��ȭ�� ���� ������ ������ �����Ű� �÷��̾�� �����϶����� ���ϰ�
	// �׷��� ������ virtual�� ���� �Լ��� ���� update�� render�� �����
	// ������ �ٸ� ������Ʈ�� ������ �ٸ� update�� render�� �� �� �ִ�.


public:
	CObject();
	virtual ~CObject();
};

