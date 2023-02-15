#pragma once
#include "CScene.h"

class CScene_Start :
    public CScene
{

public:
    virtual void Enter();
    // 각 Scene마다 뭔가 조금씩 다른 기본 수행 작업이 필요해
    // => 근데 자식에 구현하면 부모 포인터로 못해 -> 부모쪽에 가상 함수로 띄워줘야한다
    virtual void Exit();
    // 자식 클래스에서는 virtual을 적지 않아도 가상 함수로 인식하지만, 안쓰면 헷갈리니까 적어두자아


public:
    CScene_Start();
    ~CScene_Start();
};

