#include "pch.h"
#include "CCollider.h"

#include "CObject.h"
#include "CCore.h"
#include "SelectGDI.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++)
	, m_iCol(0)
{
}

CCollider::CCollider(const CCollider& _origin)
	: m_pOwner(nullptr) // 복사 한다고 하나에 충돌체가 두 가지 일린 없으니까 nullptr로
	, m_vOffsetPos(_origin.m_vOffsetPos)
	// finalPos는 어차피 매 프레임 계산 되니까 굳이 지정해서 생성할 필요 없고
	, m_vScale(_origin.m_vScale)
	, m_iID(g_iNextID++) // 이렇게 해줘야 이것도 고유 번호 가지지
	, m_iCol(0)
{
}

CCollider::~CCollider()
{
}


void CCollider::finalupdate()
{
	// update로 전부 만들어진 Object 중에 충돌판정이 있는 Object의 움직임을 따라간다
	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;

	assert(0 <= m_iCol);
}

void CCollider::render(HDC _dc)
{
	PEN_TYPE ePen = PEN_TYPE::GREEN;

	if (m_iCol)
		ePen = PEN_TYPE::RED;

	SelectGDI p(_dc, ePen);
	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);
	// 이러면 임시 객체 생성됨, render 끝나면 사라짐.
	// 매번 SelectObject 하고 뭐하고 끝나면 다시 바꾸고 없애고 이러는거보다 편할듯

	Rectangle(_dc
		, (int)(m_vFinalPos.x - m_vScale.x / 2.f)
		, (int)(m_vFinalPos.y - m_vScale.y / 2.f)
		, (int)(m_vFinalPos.x + m_vScale.x / 2.f)
		, (int)(m_vFinalPos.y + m_vScale.y / 2.f));
	
}

void CCollider::OnCollision(CCollider* _pOther)
{

}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
	++m_iCol;
	// 만약에 여러개랑 충돌중인데 그중 하나가 빠져나가도 계속 충돌로 남아있어야하니까
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
	--m_iCol;
}
