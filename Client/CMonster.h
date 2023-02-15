#pragma once
#include "CObject.h"



class CMonster :
    public CObject
{
private:
    Vec2            m_vCenterPos;
    // 몬스터가 좌우로 움직일 기준점
    float           m_fSpeed;
    float           m_fMaxDistance;
    // 좌우로 움직일 거리
    int             m_iDir; // 1, -1 진행방향 설정 (우, 좌)



public:
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _f) { m_fSpeed = _f; }
    void SetMoveDistance(float _f) { m_fMaxDistance = _f; }
    void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }



public:
    virtual void update();


public:
    CMonster();
    ~CMonster();
};

