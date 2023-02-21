#pragma once





class CRes
{
private:
	wstring m_strKey;				// 리소스 키 (지칭할 이름)
	wstring m_strRelativePath;		// 리소스 상대경로
									// 프로그램을 설치하면, 절대적인 C, D 드라이브 등의 위치는 달라져도
									// 깔려있는 폴더 안의 data, resourse 뭐 이런 폴더가 있다면
									// 그러한 상대적인 위치는 바뀌지 않을 것

public:
	void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	void SetRelativePath(const wstring& _strPath) { m_strRelativePath = _strPath; }

	const wstring& GetKey() { return m_strKey; }
	const wstring& GetRelativePath() { return m_strRelativePath; }

public:
	CRes();
	~CRes();

};

