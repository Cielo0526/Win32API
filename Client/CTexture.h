#pragma once
#include "CRes.h"



class CTexture :
    public CRes
{
private:
    HDC          m_dc;
    HBITMAP      m_hBit;
    // �̹��� �ػ󵵿� �´� �ȼ��� DC�� �����ؼ� �޸𸮻� �׷��ΰ�
    // �츮�� �۾��ϰ� �ִ� ��Ʈ�ʿ� �Ű���ߵǴϱ�
    BITMAP       m_bitInfo;

public:
    void Load(const wstring& _strFilePath);
    
    UINT Width() { return m_bitInfo.bmWidth; }
    UINT Height() { return m_bitInfo.bmHeight; }

    HDC GetDC() { return m_dc; }

private:
    CTexture();
    ~CTexture();

    friend class CResMgr;
    // ���� ��ü�� ResMgr���� �ϰ� �Ϸ��� private���� ���Ƶ� ��

};

