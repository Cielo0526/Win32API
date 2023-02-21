#pragma once


class CPathMgr
{
	SINGLE(CPathMgr);
private:
	wchar_t		 m_szContentPath[255];	 // 윈도우에서도 경로가 255글자로 제한이 걸려있음

public:
	void init();
	const wchar_t* GetContentPath() { return m_szContentPath; }

};

