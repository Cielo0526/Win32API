#pragma once

/* 우리 프로그램의 코어! 핵심!
   제대로 생성 안되면 프로그램도 진행이 안 되게끔*/

   // ## 싱글톤 패턴 ##
   // 객체의 생성을 1개로 제한
   // 너무 중요하니까 언제 어디서든 접근 가능해야해
   // 근데 extern 으로 선언해버리면 1개만 만들 수 있는 제한을 못 걸어

   // 방법 1. 생산자 숨기기 - 이러면 생성 못해
   //                       - 근데 이러면 extern 선언도 못해
   // 방법 1-1. 생산자를 숨기고 생성 함수를 만들기 (멤버 함수에서는 private 접근 가능하니까)
   //                       - 근데 애초에 멤버 함수를 호출하려면 객체가 필요한데..?
   // 방법 1-2. 생산자를 숨기고 static 정적 멤버함수를 만들면 됨.
   //                       - 객체 없이도 호출 가능 But, this 키워드가 없으니 멤버에 접근이 안돼
   //						 - 대신 정적 변수에는 접근이 됨!



   //class CCore
   //{
   //private:
   //	static CCore* g_pInst;
   //
   //public:
   //	static CCore* GetInstance()
   //	{
   //		// 한 번만 만들어야 하기 때문에 이 함수를 다시 호출하더라도 원래 있던 걸 줘야해
   //		// 그걸 알려면 함수가 끝나서 다시 호출되어 초기화 되더라도 만들었었다는걸 알고 있어야해
   //		// 그렇기 때문에 반환해줄 Core의 주소를 담고 있을 포인터 변수도 정적변수로 해주면 됨
   //
   //		// 최초 호출된 경우
   //		// static CCore* pCore = nullptr;
   //		// static 변수는 초기화가 한 번만 되기 떄문에 이렇게 해둬도 호출될떄마다 이걸 하진 않아
   //		
   //		if (nullptr == g_pInst)
   //		{
   //			g_pInst = new CCore;
   //		}
   //
   //
   //      	// 두 번 이상 호출된 경우에는 그냥 원래 있던걸 반환
   // 		return g_pInst;
   // 	}
   //
   //	//pCore의 주소를 해제해줄 멤버 함수도 만들어줘야해
   //    static void Release()
   //	{
   //		if (nullptr != g_pInst)
   //		{
   //			delete g_pInst;
   //			g_pInst = nullptr;
   //		}
   //		
   //		 // CCore* p = GetInstance();
   //		 // delete p;
   //		 // 만약 이렇게 지웠는데 다시 GetInstance 하면 pCore에는 무슨 주소가 있지?
   //		 // 삭제된 곳의 주소를 들고 있겠지 그럼 지우고 GetInstance를 해버리면 그냥 그 주소를 준단말야
   //		 // 그러니까 차라리 정적 멤버 변수로 빼서 쓰자.
   //
   //		 // 그리고 위와같이 바꾸면 지울떄 nullptr로 줘서 혹시나 다시 부르면 깔끔하게 다시 할 수 있게끔
   //
   //	}
   //
   //private:
   //	CCore();
   //	~CCore();
   //};


   // 방법 2. 클래스의 객체를 데이터 영역으로 보내고 가져다 쓰기


   //class CCore
   //{
   //public:
   //	// 객체 없이 받아와야하니 이거까지는 동일
   //	static CCore* GetInst()
   //	{
   //		static CCore core;
   //		// GetInst도 멤버함수니까 생성자 호출이 가능함 (바깥에서 초기화할 필요 없음)
   //		// 정적 변수니까 데이터 영역을 쓰게 됨
   //		// 정적 변수라서 다시 호출해도 초기화 이미 된 상태라 반환도 그냥 이걸 다시 반환함 -> 편함!
   //
   //		return &core;
   //		// 심지어 core의 주소를 준거라서 정적 변수고 클래스고 뭐고 주소로 들어가서 접근할 수 있지
   //		// 소멸자도 당연히 될거라서 해제에 신경 쓰지 않아도 됨
   //		// But 원할 때 해제할 수 없음
   //	}
   //
   //
   //private:
   //	CCore();
   //	~CCore();
   //
   //
   //};

   // 상황에 따라서 어느 쪽을 쓸 지는 모른다
   // 1번은 귀찮은 대신에 해제할 수 있고
   // 2번은 편한 대신에 해제나 짜잘한 설정이 가능하지

   // 보통 싱글톤으로 쓰는 객체는 매니저의 역할을 하기 때문에 굳이 지울 일이 없기도 하긴 해

#include "define.h"

class CCore
{
	SINGLE(CCore);

private:
	HWND	 m_hWnd;			 // 메인 윈도우 핸들
	POINT	 m_ptResolution;	 // 메인 윈도우 해상도
	HDC		 m_hDC;				 // 메인 윈도우에 Draw 할 DC

	HBITMAP	m_hBit;				 // 해상도만큼의 픽셀 데이터 뭉탱이를 '비트맵' 이라 함
	HDC		m_memDC;


	// 자주 사용하는 GDI Object
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();
	
private:
	void CreateBrushPen();



public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	POINT GetResolution() { return m_ptResolution; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }

};