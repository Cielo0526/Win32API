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
	// �ϴ� �� Ű������ ���� �ִ��� Ȯ��
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
	// ���ҽ� ��ü�� �ڽ��� Ű���� ��� ��θ� �˾Ƶ־��Ѵ�~ �� CRes�� ���ص���

	m_mapTex.insert(make_pair(_strKey, pTex));


	return pTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	// map�� find �� iterator�� �ִϱ� iterator�� ����.
	map<wstring,CTexture*>::iterator iter = m_mapTex.find(_strKey);
	if (iter == m_mapTex.end())
	{
		return nullptr;
	}

	// ���࿡ ��ĭ(end iterator�� �ƴ϶�� ���� �޾��� �״ϱ� map�� second�� pTex�� return�ϸ� ��.
	return iter->second;
}
