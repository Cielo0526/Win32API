#pragma once
#include "CScene.h"

class CScene_Start :
    public CScene
{

public:
    virtual void Enter();
    // �� Scene���� ���� ���ݾ� �ٸ� �⺻ ���� �۾��� �ʿ���
    // => �ٵ� �ڽĿ� �����ϸ� �θ� �����ͷ� ���� -> �θ��ʿ� ���� �Լ��� �������Ѵ�
    virtual void Exit();
    // �ڽ� Ŭ���������� virtual�� ���� �ʾƵ� ���� �Լ��� �ν�������, �Ⱦ��� �򰥸��ϱ� ������ھ�


public:
    CScene_Start();
    ~CScene_Start();
};

