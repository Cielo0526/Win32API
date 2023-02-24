#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CCore.h"

#include "CPathMgr.h"
#include "CTexture.h"

#include "CCollisionMgr.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}


void CScene_Start::Enter()
{

	// Object �߰�
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);


	// Moster Object �߰�
	int iMonCount = 6;
	float fMoveDist = 25.f;
	float fMoveDist2 = 50.f;
	float fObjScale = 50.f;
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	// ���� ������ ���ÿ� �̷��� �ع����� ���� �����ڰ� ��. -> ������ �����ε����� �ذ�
	CMonster* pMonsterObj = nullptr;

	float fTerm = (vResolution.x - ((fMoveDist + fObjScale / 2.f) * 2)) / (float)(iMonCount - 1);
	float fTerm2 = (vResolution.x - ((fMoveDist + fObjScale / 2.f) * 2)) / (float)(iMonCount - 6 - 1);

	for (int i = 0; i < iMonCount; ++i)
	{
		pMonsterObj = new CMonster;
		pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + (float)i * fTerm, 50.f));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		pMonsterObj->SetMoveDistance(fMoveDist);
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);

	}

	for (int i = 0; i < iMonCount-6; ++i)
	{
		pMonsterObj = new CMonster;
		pMonsterObj->SetPos(Vec2((fMoveDist2 + fObjScale / 2.f) + (float)i * fTerm2, 120.f));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		pMonsterObj->SetMoveDistance(fMoveDist2);
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);

	}

	// �浹 ����
	// Player �׷�� Monster �׷� ���� �浹 üũ
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
}

void CScene_Start::Exit()
{
	// ���� ������ �ٸ� ������ �Ѿ �� �ٸ� �ֵ鳢�� �浹�ϰ� �� ���� �����ϱ� ���� �浹 üũ�Ѱ� �����ؾ���
	CCollisionMgr::GetInst()->Reset();

}