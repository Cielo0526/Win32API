#include "pch.h"
#include "CPlayer.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CResMgr.h"


#include "CTexture.h"
#include "CMissile.h"



CPlayer::CPlayer()
	:m_pTex(nullptr)
{
	// CResMgr 이용해서 로딩
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");

	// Texture 로딩하기
	// m_pTex = new CTexture;

	// wstring strFilepath = CPathMgr::GetInst()->GetContentPath();
	// strFilepath += L"texture\\Player.bmp";
	// m_pTex->Load(strFilepath);

	/* 나중에 몬스터를 리소스에서 가져오려면 생성자에서 만들면 안돼.
	   플레이어야 하나 뿐이니까 상관이 없어보이지만, 몬스터 여러마리를 만든다고 하면
	   10마리 한다 치면 이미지를 10번 가져와서 쓰는건데? 그게 리소스가 맞나?
	   한 번 가져와서 그걸로 여러번 씌워야지
	   
	   그러기 위해 ResMgr을 써서 이미지가 이미 불러져왔다면 얻어다 쓰고, 없으면 로딩하는거지*/

}

CPlayer::~CPlayer()
{
	//	if (nullptr != m_pTex)
	//		delete m_pTex;
	
		// 리소스 매니저가 일을 하기 시작하면 여기서 지워줘야할 필요가 없지. 오히려 지우면 안 되지
}


void CPlayer::update()
{
	Vec2 vPos = GetPos();

	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 200.f * fDT;
	}

	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.f * fDT;
	}

	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 200.f * fDT;
	}

	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 200.f * fDT;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	SetPos(vPos);
}

void CPlayer::render(HDC _dc)
{
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();
	// 실제 이미지 크기는 음수일리가 없어서 UINT로 받았지만 화면에 넣을 때는 음수를 넣을 수도 있으니까 위치상

	Vec2 vPos = GetPos();

	

	/*BitBlt(_dc
		, int(vPos.x - (float)(iWidth / 2))
		, int(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0,0, SRCCOPY);*/

	TransparentBlt(_dc
		, int(vPos.x - (float)(iWidth / 2))
		, int(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255,0,255));
	// 특정 색을 무시하고 옮겨 그리는 함수, 
}

void CPlayer::CreateMissile()
{
 	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;
	
	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);
}
