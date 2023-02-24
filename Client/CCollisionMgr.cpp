#include "pch.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"




CCollisionMgr::CCollisionMgr()
	: m_arrCheck{}
{
}

CCollisionMgr::~CCollisionMgr()
{
}


void CCollisionMgr::update()
{
	// 체크 된 애들끼리 충돌 하는지 확인하기
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow) // 행 전체 확인해야지
	{
		m_arrCheck[iRow];
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol) 
			// 각 행의 비트 확인해야지, 대신 iRow부터 확인해야 중복된 곳 체크 안한다
		{
			if (m_arrCheck[iRow] & (1 << iCol)) // 비트가 체크가 되었나?
			{
				// 물체 충돌 파악 (각 씬에 있겠지?)
				CollisionUpdateGroup((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}



}

void CCollisionMgr::CollisionUpdateGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	
	// vector<CObject*> vecLeft = pCurScene->GetGroupObject(_eLeft);
	// vector<CObject*> vecRight = pCurScene->GetGroupObject(_eRight);
	// 원본 참조를 받았지만 vecLeft는..? 지역 변수야
	// 그래서 아래처럼 똑같이 받아줘야해
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);

	map<ULONGLONG, bool>::iterator iter; // 반복문 도는 내내 잡힐거니까 바깥에 선언해두자

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// 만약에 충돌체가 활성화 안 되어 있는 애면 넘어가야지
		if (nullptr == vecLeft[i]->GetCollider())
		{
			continue;
		}

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// 자기 자신인 경우에도 넘어가야지
			if (nullptr == vecRight[j]->GetCollider()
				|| vecLeft[i] == vecRight[j])
			{
				continue;
			}

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();

			// 두 충돌체 조합 아이디 생성
			COLLIDER_ID ID;
			ID.iLeft_id = pLeftCol->GetID();
			ID.iRight_id = pRightCol->GetID();
			
			iter = m_mapColInfo.find(ID.ID);
			// 그 조합으로 find 해보는거지. 만약에 뭔가 있으면 이전 프레임에 뭔가가 있던거지

			// 뭐가 아예 없어 == 검색 자체가 처음이야 => 키 값을 저장해줘야해 아직 충돌 안한걸로
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			// 이제 진짜 충돌하는지 검사
			if (IsCollision(pLeftCol, pRightCol))
			{
				/* 이전에 충돌했는지 아닌지를 알아야 하는데 그러려면 충돌체조합마다 고유한 키값이 필요해
				   그러면 아예 충돌체 생성시에 고유 키값을 만들고 그 키값의 조합으로 만들면 되잖아 -> 충돌체 ID 생성하자 */
				
				// 현재 충돌중이다.
			
				if (iter->second)
					// 이전에도 충돌중이다.
				{
					pLeftCol->OnCollision(pRightCol);
					pRightCol->OnCollision(pLeftCol);
				}
				else
					// 이전에는 충돌 안했다
				{
					pLeftCol->OnCollisionEnter(pRightCol);
					pRightCol->OnCollisionEnter(pLeftCol);
					iter->second = true;
				}
			}
			else
			{
				// 현재 충돌하고있지 않다
				if (iter->second)
					// 하지만 이전에 충돌했었다.
				{
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	// 충돌의 판정을 어떻게 알까
	// -> 각 x축 좌표의 차이(길이)가 사이즈가 보다 작고, y도 그러한 경우에 '겹친다' 라고 할 수 있지
	Vec2 vLeftPos = _pLeftCol->GetFinalPos();
	Vec2 vLeftScale = _pLeftCol->GetScale();
	
	Vec2 vRightPos = _pRightCol->GetFinalPos();
	Vec2 vRightScale = _pRightCol->GetScale();

	if (abs(vRightPos.x - vLeftPos.x) < (vLeftScale.x + vRightScale.x) / 2.f
		&& abs(vRightPos.y - vLeftPos.y) < (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;	
	}
	return false;
}


void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// 더 작은 값의 그룹 타입을 행으로, 큰 값의 그룹을 열(비트)로 사용.

	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol)) // 만약에 이미 채워져있다면
	{
		m_arrCheck[iRow] &= ~(1 << iCol); // 있는거 체크 해제하고
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol); // 아니면 체크한다.
	}

}
