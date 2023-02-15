#pragma once
#include "CObject.h"


class CMissile :
    public CObject
{
private:
    float         m_fDir; // 위 아래 방향
    float         m_fxDir; // 좌 우 방향

public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    void SetDir(bool _bUp)
    {
        if (_bUp)
            m_fDir = -1.f;
        else
            m_fDir = 1.f;
    }
    void SetxDir(bool _bUp)
    {
        if (_bUp)
            m_fxDir = -1.f;
        else
            m_fxDir = 1.f;

    }

public:
    CMissile();
    ~CMissile();


};

