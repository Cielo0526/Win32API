#include "pch.h"
#include "CMissile.h"
#include "CTimeMgr.h"

#include <math.h>

CMissile::CMissile()
	: m_fDir(1)
	, m_fxDir(0)
{
}

CMissile::~CMissile()
{
}

void CMissile::update()
{
	Vec2 vPos = GetPos();
	vPos.y += 400.f * fDT * m_fDir;

	if (m_fxDir == 1||-1)
	vPos.x += 200.f * fDT * m_fxDir;

	SetPos(vPos);

}

void CMissile::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Ellipse(_dc, (int)(vPos.x - vScale.x / 2.f), (int)(vPos.y - vScale.y / 2.f)
		, (int)(vPos.x + vScale.x / 2.f), (int)(vPos.y + vScale.y / 2.f));
}
