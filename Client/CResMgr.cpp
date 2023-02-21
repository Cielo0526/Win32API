#include "pch.h"
#include "CResMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"

CResMgr::CResMgr()
{
}

CResMgr::~CResMgr()

{
	map<wstring, CTexture*>::iterator iter = m_mapTex.begin();
	for (; iter != m_mapTex.end(); ++iter)
	{
		delete iter->second;
	}
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	// 일단 그 키값으로 들어간게 있는지 확인
	CTexture* pTex = FindTexture(_strKey);
	if (nullptr != pTex)
	{
		return pTex;
	}

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pTex = new CTexture;
	pTex->Load(strFilePath);
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);
	// 리소스 자체도 자신의 키값과 상대 경로를 알아둬야한다~ 고 CRes때 정해뒀죠

	m_mapTex.insert(make_pair(_strKey, pTex));


	return pTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	// map의 find 는 iterator를 주니까 iterator로 받자.
	map<wstring,CTexture*>::iterator iter = m_mapTex.find(_strKey);
	if (iter == m_mapTex.end())
	{
		return nullptr;
	}

	// 만약에 빈칸(end iterator가 아니라면 페어로 받았을 테니까 map의 second인 pTex를 return하면 돼.
	return iter->second;
}
