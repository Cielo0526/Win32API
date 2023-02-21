#include "pch.h"
#include "CPathMgr.h"

#include "CCore.h"

CPathMgr::CPathMgr()
	: m_szContentPath{}
{
}

CPathMgr::~CPathMgr()
{
}

void CPathMgr::init()

{
	// 현재 주소 얻어오기
	GetCurrentDirectory(255, m_szContentPath);

	// 상위 폴더로 나가기
	int iLen = wcslen(m_szContentPath); // 전체 길이를 알아서 뒤에서부터 \\ 가 있는 곳을 찾아서 끊어두자
	for (int i = iLen - 1; 0 <= i; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}

	}

	// + bin\\content\\ 붙여주기
	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");


	// SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath);

}
