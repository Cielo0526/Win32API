#pragma once
#include "CRes.h"



class CTexture :
    public CRes
{
private:
    HDC          m_dc;
    HBITMAP      m_hBit;
    // 이미지 해상도에 맞는 픽셀로 DC랑 연결해서 메모리상에 그려두고
    // 우리가 작업하고 있는 비트맵에 옮겨줘야되니까
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
    // 생성 자체를 ResMgr에서 하게 하려고 private으로 막아둔 것

};

