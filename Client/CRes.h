#pragma once





class CRes
{
private:
	wstring m_strKey;				// ���ҽ� Ű (��Ī�� �̸�)
	wstring m_strRelativePath;		// ���ҽ� �����
									// ���α׷��� ��ġ�ϸ�, �������� C, D ����̺� ���� ��ġ�� �޶�����
									// ����ִ� ���� ���� data, resourse �� �̷� ������ �ִٸ�
									// �׷��� ������� ��ġ�� �ٲ��� ���� ��

public:
	void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	void SetRelativePath(const wstring& _strPath) { m_strRelativePath = _strPath; }

	const wstring& GetKey() { return m_strKey; }
	const wstring& GetRelativePath() { return m_strRelativePath; }

public:
	CRes();
	~CRes();

};

