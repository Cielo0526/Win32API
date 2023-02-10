#include "pch.h"
#include "CSceneMgr.h"



#include "CScene_Start.h"


CSceneMgr::CSceneMgr()
	: m_arrScene{}
	, m_pCurScene(nullptr)
{


}

CSceneMgr::~CSceneMgr()
{
	// 씬을 전부 삭제 해야하는데, 씬 매니저는 가지고 있는게 부모 타입 포인터야.
	// 그러면 자식 클래스들 소멸은 어떻게 해? => 이래서 맨 부모격 클래스 소멸자를 virtual 함수로 했어야해

	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}

	}

}

void CSceneMgr::init()
{
	// Scene 생성

	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	// m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	// m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_Stage01;
	// m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Stage02;

	// 현재 씬 지정
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];


}

