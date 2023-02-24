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
	// üũ �� �ֵ鳢�� �浹 �ϴ��� Ȯ���ϱ�
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow) // �� ��ü Ȯ���ؾ���
	{
		m_arrCheck[iRow];
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol) 
			// �� ���� ��Ʈ Ȯ���ؾ���, ��� iRow���� Ȯ���ؾ� �ߺ��� �� üũ ���Ѵ�
		{
			if (m_arrCheck[iRow] & (1 << iCol)) // ��Ʈ�� üũ�� �Ǿ���?
			{
				// ��ü �浹 �ľ� (�� ���� �ְ���?)
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
	// ���� ������ �޾����� vecLeft��..? ���� ������
	// �׷��� �Ʒ�ó�� �Ȱ��� �޾������
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);

	map<ULONGLONG, bool>::iterator iter; // �ݺ��� ���� ���� �����Ŵϱ� �ٱ��� �����ص���

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// ���࿡ �浹ü�� Ȱ��ȭ �� �Ǿ� �ִ� �ָ� �Ѿ����
		if (nullptr == vecLeft[i]->GetCollider())
		{
			continue;
		}

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// �ڱ� �ڽ��� ��쿡�� �Ѿ����
			if (nullptr == vecRight[j]->GetCollider()
				|| vecLeft[i] == vecRight[j])
			{
				continue;
			}

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();

			// �� �浹ü ���� ���̵� ����
			COLLIDER_ID ID;
			ID.iLeft_id = pLeftCol->GetID();
			ID.iRight_id = pRightCol->GetID();
			
			iter = m_mapColInfo.find(ID.ID);
			// �� �������� find �غ��°���. ���࿡ ���� ������ ���� �����ӿ� ������ �ִ�����

			// ���� �ƿ� ���� == �˻� ��ü�� ó���̾� => Ű ���� ����������� ���� �浹 ���Ѱɷ�
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			// ���� ��¥ �浹�ϴ��� �˻�
			if (IsCollision(pLeftCol, pRightCol))
			{
				/* ������ �浹�ߴ��� �ƴ����� �˾ƾ� �ϴµ� �׷����� �浹ü���ո��� ������ Ű���� �ʿ���
				   �׷��� �ƿ� �浹ü �����ÿ� ���� Ű���� ����� �� Ű���� �������� ����� ���ݾ� -> �浹ü ID �������� */
				
				// ���� �浹���̴�.
			
				if (iter->second)
					// �������� �浹���̴�.
				{
					pLeftCol->OnCollision(pRightCol);
					pRightCol->OnCollision(pLeftCol);
				}
				else
					// �������� �浹 ���ߴ�
				{
					pLeftCol->OnCollisionEnter(pRightCol);
					pRightCol->OnCollisionEnter(pLeftCol);
					iter->second = true;
				}
			}
			else
			{
				// ���� �浹�ϰ����� �ʴ�
				if (iter->second)
					// ������ ������ �浹�߾���.
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
	// �浹�� ������ ��� �˱�
	// -> �� x�� ��ǥ�� ����(����)�� ����� ���� �۰�, y�� �׷��� ��쿡 '��ģ��' ��� �� �� ����
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
	// �� ���� ���� �׷� Ÿ���� ������, ū ���� �׷��� ��(��Ʈ)�� ���.

	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol)) // ���࿡ �̹� ä�����ִٸ�
	{
		m_arrCheck[iRow] &= ~(1 << iCol); // �ִ°� üũ �����ϰ�
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol); // �ƴϸ� üũ�Ѵ�.
	}

}
