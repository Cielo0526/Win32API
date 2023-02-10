#pragma once

// �������� ������Ʈ�� ����ϴ�. �׳� ��ü���� UI ��� ��� ��
// �� ȭ�鿡 �ִ� ��� ������Ʈ���� �����ϴ� �ϳ��� Scene�� �ֽ��ϴ�.
// Scene�� ���������� �ְ���? �� ��ӹ����ô�

class CObject;
	// ���� ����� CObject�� Ŭ���� �� Ÿ������ ������ �� ���� -> ���� ��Ȯ���� �𸣴ϱ�
	// ��� �����ͷδ� ��� ����. ������ �����ʹ� �԰� �����������ϱ�.
	// ���� �����ϴ� ������ ������ �ӵ� ������, ���� ����� �����ϸ� Object �ڵ� ����� Scene�� Ȯ�� ������ϴϱ� ���ŷο�
	// ���� �������� �ϸ� �׳� ���״ٰ� ���߿� ������⸸ �ϸ� �Ǵϱ�.
	// ��������� ���� ���� ���ϴ°� ����.

class CScene
{

private:
	vector<CObject*> m_arrVecObj[(UINT)GROUP_TYPE::END];
	// CObject*�� �ϴ� ������ �갡 ���� �θ���̴ϱ� �̰� �ϳ��� ���� ���� ����
	// ���� �츮�� ������Ʈ�� �׷����� �������� �� vector�� �׷� ����ŭ �־�� ��
	// �׷��� �̷� vector�� �迭�� ���������� enum ���� ���������.
	wstring			 m_strName;		// Scene �̸�

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

public:
	CScene();
	virtual ~CScene();

};

