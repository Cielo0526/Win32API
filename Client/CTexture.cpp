#include "pch.h"
#include "CTexture.h"

#include "CCore.h"


CTexture::CTexture()
	: m_hBit(0)
	, m_dc(0)
	, m_bitInfo{}
{
}

CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}


void CTexture::Load(const wstring& _strFilePath)
{
	// 파일로부터 로딩한 데이터를 비트맵으로 생성
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	// 사이즈에 0, 0을 넣으면 그 이미지의 원본 사이즈로 나옴
	assert(m_hBit);
	// m_hBit이 nullptr이면 제대로 로딩 안 된거니까


	// 비트맵과 연결지어줄 DC
	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	//비트맵과 DC 연결
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);

	// 비트맵 정보 입력
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);


	
}
