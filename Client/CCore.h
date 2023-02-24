#pragma once

/* �츮 ���α׷��� �ھ�! �ٽ�!
   ����� ���� �ȵǸ� ���α׷��� ������ �� �ǰԲ�*/

   // ## �̱��� ���� ##
   // ��ü�� ������ 1���� ����
   // �ʹ� �߿��ϴϱ� ���� ��𼭵� ���� �����ؾ���
   // �ٵ� extern ���� �����ع����� 1���� ���� �� �ִ� ������ �� �ɾ�

   // ��� 1. ������ ����� - �̷��� ���� ����
   //                       - �ٵ� �̷��� extern ���� ����
   // ��� 1-1. �����ڸ� ����� ���� �Լ��� ����� (��� �Լ������� private ���� �����ϴϱ�)
   //                       - �ٵ� ���ʿ� ��� �Լ��� ȣ���Ϸ��� ��ü�� �ʿ��ѵ�..?
   // ��� 1-2. �����ڸ� ����� static ���� ����Լ��� ����� ��.
   //                       - ��ü ���̵� ȣ�� ���� But, this Ű���尡 ������ ����� ������ �ȵ�
   //						 - ��� ���� �������� ������ ��!



   //class CCore
   //{
   //private:
   //	static CCore* g_pInst;
   //
   //public:
   //	static CCore* GetInstance()
   //	{
   //		// �� ���� ������ �ϱ� ������ �� �Լ��� �ٽ� ȣ���ϴ��� ���� �ִ� �� �����
   //		// �װ� �˷��� �Լ��� ������ �ٽ� ȣ��Ǿ� �ʱ�ȭ �Ǵ��� ��������ٴ°� �˰� �־����
   //		// �׷��� ������ ��ȯ���� Core�� �ּҸ� ��� ���� ������ ������ ���������� ���ָ� ��
   //
   //		// ���� ȣ��� ���
   //		// static CCore* pCore = nullptr;
   //		// static ������ �ʱ�ȭ�� �� ���� �Ǳ� ������ �̷��� �صֵ� ȣ��ɋ����� �̰� ���� �ʾ�
   //		
   //		if (nullptr == g_pInst)
   //		{
   //			g_pInst = new CCore;
   //		}
   //
   //
   //      	// �� �� �̻� ȣ��� ��쿡�� �׳� ���� �ִ��� ��ȯ
   // 		return g_pInst;
   // 	}
   //
   //	//pCore�� �ּҸ� �������� ��� �Լ��� ����������
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
   //		 // ���� �̷��� �����µ� �ٽ� GetInstance �ϸ� pCore���� ���� �ּҰ� ����?
   //		 // ������ ���� �ּҸ� ��� �ְ��� �׷� ����� GetInstance�� �ع����� �׳� �� �ּҸ� �شܸ���
   //		 // �׷��ϱ� ���� ���� ��� ������ ���� ����.
   //
   //		 // �׸��� ���Ͱ��� �ٲٸ� ��� nullptr�� �༭ Ȥ�ó� �ٽ� �θ��� ����ϰ� �ٽ� �� �� �ְԲ�
   //
   //	}
   //
   //private:
   //	CCore();
   //	~CCore();
   //};


   // ��� 2. Ŭ������ ��ü�� ������ �������� ������ ������ ����


   //class CCore
   //{
   //public:
   //	// ��ü ���� �޾ƿ;��ϴ� �̰ű����� ����
   //	static CCore* GetInst()
   //	{
   //		static CCore core;
   //		// GetInst�� ����Լ��ϱ� ������ ȣ���� ������ (�ٱ����� �ʱ�ȭ�� �ʿ� ����)
   //		// ���� �����ϱ� ������ ������ ���� ��
   //		// ���� ������ �ٽ� ȣ���ص� �ʱ�ȭ �̹� �� ���¶� ��ȯ�� �׳� �̰� �ٽ� ��ȯ�� -> ����!
   //
   //		return &core;
   //		// ������ core�� �ּҸ� �ذŶ� ���� ������ Ŭ������ ���� �ּҷ� ���� ������ �� ����
   //		// �Ҹ��ڵ� �翬�� �ɰŶ� ������ �Ű� ���� �ʾƵ� ��
   //		// But ���� �� ������ �� ����
   //	}
   //
   //
   //private:
   //	CCore();
   //	~CCore();
   //
   //
   //};

   // ��Ȳ�� ���� ��� ���� �� ���� �𸥴�
   // 1���� ������ ��ſ� ������ �� �ְ�
   // 2���� ���� ��ſ� ������ ¥���� ������ ��������

   // ���� �̱������� ���� ��ü�� �Ŵ����� ������ �ϱ� ������ ���� ���� ���� ���⵵ �ϱ� ��

#include "define.h"

class CCore
{
	SINGLE(CCore);

private:
	HWND	 m_hWnd;			 // ���� ������ �ڵ�
	POINT	 m_ptResolution;	 // ���� ������ �ػ�
	HDC		 m_hDC;				 // ���� �����쿡 Draw �� DC

	HBITMAP	m_hBit;				 // �ػ󵵸�ŭ�� �ȼ� ������ �����̸� '��Ʈ��' �̶� ��
	HDC		m_memDC;


	// ���� ����ϴ� GDI Object
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