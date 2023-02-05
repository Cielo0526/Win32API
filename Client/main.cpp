// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Client.h"
#include "CCore.h"
#include "pch.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND      g_hWnd;                               /* 메인 윈도우 핸들 */

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// 정적 변수 사용법 ( 데이터 영역을 씀 )
// 1. 함수 안에
// 2. 파일(일반 cpp같은 곳에) - 같은 이름의 다른 변수가 있어도 상관 없음. 영역을 달리 사니까
// 3. 클래스 안에

class CClass
{
private:
    int m_i;

    static int m_iStatic;
    // 정적 멤버 (데이터 영역) -> 클래스 사이즈에 포함 안 됨
    // 물론 public으로 쓰면 밖에서도 접근할 수 있음

public:
    void func()
    {
        m_i = 0;
        m_iStatic = 0;
    }

    // 정적 멤버함수, 객체없이 호출 가능
    static void FUNC()
    {
        m_iStatic = 0;
        // this->m_iStatic; 정적변수는 지금 클래스 안에 선언되어 있긴 하지만 데이터 영역을 쓰기 떄문에 this로 받지 않음
        // 정적멤버 함수는 this가 없지만, 정적변수는 어차피 데이터 영역에 있으니까.
        // 클래스 내 정적 멤버함수는 정적변수밖에 넣을 게 없어
    }
};

int CClass::m_iStatic = 0;
// 클래스 내 정적 멤버는 클래스 밖에서 초기화를 해줘야함.

    //APIENTRY 이런것도 STL 주석임. 근데 보통 주석언어는 무시해도 돼
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, /*실행 된 프로세스의 시작 주소*/
    _In_opt_ HINSTANCE hPrevInstance,
    /*같은 프로그램인데, 여러개를 띄웠을 경우 그 이전의 프로세스 시작 주소. 근데 이게 옛날 OS의 잔재임. 지금은 여러 창을 띄워도 전부 프로세스 시작 주소가 같음*/
    /*지금은 가상 메모리를 사용하기 때문에, 물리적인 메모리 공간은 다르더라도 프로세스 상대적인 공간으로써는 같게끔 취급함*/
    /*결국 윈도우 안에서 프로그램들은 자신의 '진짜 물리적 주소'를 알진 못함*/
    /*옛날에는 실제 물리적 공간을 할당받기 떄문에 이전 주소도 알고 있는거지*/
    _In_ LPWSTR    lpCmdLine,
    /*프로그램의 추가적인 명령어를 짧은 단어나 변수명 등으로 받아올 수 있게끔 해주는 것
      cmd shutdown -t -s 3600 이런게 있다 치면 -t -s 이런거 같으 느낌*/
    _In_ int       nCmdShow)
    /* _In_ _In_opt_ 이게 모냐->SAL 주석임.
       컴파일러적인 의미는 없고, 해당 변수의 용도를 알려주는 것임
       모든 것에 주절주절 주석을 달 순 없잖아
       _In_ -> 데이터가 이 함수에 입력된다
       _In_opt_ (optional) -> 뭔가 부가적으로 입력(들어오는)되는 변수가*/
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    // (아무런 의미 없다고 알려줌)

// TODO: 여기에 코드를 입력합니다.

// 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
    /*위에 선언한 전역 변수에 문자열 채워넣는거지
    그래서 위에꺼들은 뭘 하는거냐. 프로그램 실행했을 때 위에 뜨는 이름을 넣어주는 거야.
    IDS_APP_TITLE 이런걸 테이블에 가서 보면 지정된 숫자(배열의 번호?)가 있고, 그 안에 프로젝트 이름이 들어가있어
    그걸 #define 해서 지금 넣어주는거야 */

    // 윈도우(창) 정보 등록
    MyRegisterClass(hInstance);


    // 애플리케이션 초기화를 수행합니다:
    /* 윈도우 생성 */
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    // Core 초기화
    if (FAILED(CCore::GetInst()->init(g_hWnd, POINT{ 1280, 760 })))
    {
        MessageBox(nullptr, L"Core 객체 초기화 실패", L"ERROR", MB_OK);
        return FALSE;
        // 혹여나 무슨 문제로 코어 초기화가 안되면 프로그램도 안되도록
    }


    /* 사용자 - 인터페이스(윈도우) - 물리적 장치
       프로세스 != 윈도우
       윈도우(창)을 갖고 있지 않는 프로세스도 많아.
       보통 윈도우를 종료하면 프로세스를 종료하게끔 만들어 놓지만 그렇지 않은 경우도 많고, 애초에 창을 요구하지 않는
       프로세스도 있음*/

       /* 단축키 정보 테이블 로딩 */
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;


    // SetTimer(g_hWnd, 10/* 이건 ID값 정하는거라 암거나 */, 0/*1000당 1초, 0은 그냥 최대한 빠르게*/, nullptr);
    /* 이 프로그램 상에서는 새로운 메세지가 생기지 않는 한 뭔가 새로 프로그램이 돌지 않아. 멈춰있어
       하지만 실제 게임에서는 내가 움직이지 않아도 코드가 계속 돈단말야. AI든 뭐든
       그래서 이렇게 일정 시간마다 강제로 메세지를 만들게도 할 수 있지만, 암튼 지금 형태는 별로 효율적이지 않아 */

       /* 그리고 메세지 처리 방식이 애초에 그렇게 빠르지도 않아.
          그래서 되도록 메세지 처리를 써야만 하는 경우를 제외하고는 안쓸 예정 */

    msg.message;
    msg.lParam;
    msg.wParam;
    msg.pt;
    msg.time;
    /* 무슨 종류 메세지고, 파라미터는 뭘 가져왔고, 마우스 좌표는 어디고, 시간은 언제고~ */
    msg.hwnd;
    /* 이 메세지가 발생한 윈도우 (하나의 프로세스에 윈도우가 여러개일 수 있으니까.) */

    {
        /* GetMessage */
        /* 메세지 큐에서 메세지를 확인될 때까지 대기 */
        /* msg.message = WM_QUIT 인 경우에 false를 반환 -> 프로그램 종료 */
        /* WM_QUIT 이전에 열려있는 윈도우나 이것저것 다 닫아놓게 됨.
       WM_QUIT 자체가 이미 꺼지기 위한 전처리를 전부 다 했다는 마무리 메세지임*/

       // 기본 메시지 루프입니다:
   //    while (GetMessage(&msg, nullptr, 0, 0))
           /*윈도우에 있는 메세지 큐 - 뭔가 일어날만한 이벤트들이 정리되어있는데
             포커싱이 되어있는 프로세스에 그 메세지를 전달해준다.
             '마우스 클릭' 이라는 메세지가 큐에 들어갔다고 치자. visual studio에서는 클릭이 그냥 클릭이겠지만
             그림판에서는?? 클릭이 곧 색을 칠하는 일이 됨.
             '포커싱' 된 곳에 따라 메세지가 다른 역할을 할 수도 있다는 것.
             GetMessage는 해당 윈도우에 포커싱 된 상태로 뭔가 메세지가 온 게 있나 확인하는 함수임
             그렇게 받은 메세지를 저장하려고 메세지 구조체를 만들어서 &msg로 주소를 넘긴거임*/
             //   {
             //       if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
                        /*단축키가 눌렸나 확인하는 부분(안쓰면 필요 없음)*/
             //       {
             //           TranslateMessage(&msg);
             //           DispatchMessage(&msg);
                        /* 받아온 메세지를 처리하는 것
                           프로시즈(처리기) 함수 - 각 윈도우들은 자기에게 일어날 일을 해결해줄 함수를 같이 들고있음*/
                           //       }
                           //   }
    } // 원래 있던 메세지 받는 유형

    /* PeekMessage
       메세지 유무와 관계없이 반환
       GetMessage는 WM_QUIT을 받으면 false를 반환하기 때문에 while문의 조건으로 할 수 있었지만
       PeekMessage는? 언제나 반환하니까 뭐가 있으면 True 없으면 False
       */

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
            /* PM_REMOVE 를 해주면 본 메세지를 지워준다는 거 -> 그래야 큐에서 사라지겠지?*/
            /* 메세지가 있을 수도 있고 없을 수도 있으니까 if로. 있으면 걸려서 들어오겠지?*/
        {
            if (WM_QUIT == msg.message)
                break;
            /* 꺼지는 조건은 걸어놔야지 */

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        /* 메세지가 발생하지 않는 대부분의 시간
           메세지가 발생하지 않아도 돌아가야하는 부분들이 많고, 그게 더 유리한 프로그램도 있음.
           반대로 메세지와 포커싱이 있어야 동작하는 것들도 있고
           (그림판 같은게 최소화 되어있는데 맘대로 그려지면 안되지만 기반 프로그램같은건 메세지 없어도 돌아가야하듯이)*/

        else
        {
            /* 메세지가 없는 동안 호출되는 부분 */


            /* Game 코드 수행
               디자인 패턴(설계 유형)
                 - 요런 방식에는 요런 해결법으로 해결하더라. 언어마다 다를 일이 없음. 구현법이 다른거지
                 - 모든 패턴을 배울 필요는 없음. 어차피 이름 붙이기라 별별 것들이 다 있어서, 대표적인 것만 배우자

               #1. 싱글톤 패턴*/
            CCore::GetInst()->progress();
        }
    }

    // KillTimer(g_hWnd, 10);
    /* 타이머도 커널 오브젝트라 없애줘야함 */

    return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CLIENT);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
    // RegisterClassExW 같은 경우는 윈도우에서 제공해주는 함수임.
    // 이런 식으로 구현해놓은 함수를 잘 활용하는 습관을 가지자.
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
    // 윈도우 창 타이틀 바에 이름을 넣어주는 거야 지금
    // 만약에 바꾸고 싶으면 지금 위의 szTitle 을 바꿔주면 돼
    // 비워둘 순 없으니까 처음에 그냥 프로젝트 이름을 넣어준거

    if (!g_hWnd)
    {
        return FALSE;
    }

    ShowWindow(g_hWnd, nCmdShow);
    UpdateWindow(g_hWnd);

    return TRUE;
}

int g_x = 0;
int g_y = 0;

/* 물체가 여러개라면? 다 다시 매번 그려야되나? 그렇다고 안그릴 수도 없고?
   그러면 그거에 따른 프레임과 최적화는..?*/

#include <vector>

using std::vector;

struct tObjInfo
{
    POINT g_ptObjPos;
    POINT g_ptObjScale;

};

vector<tObjInfo> g_vecInfo;

/* 좌 상단 */
POINT g_ptLT;
/* 우 하단 */
POINT g_ptRB;

/* 무작정 Ractangle을 실행시킬 수 없으니까 클릭 될 때만 하게끔 하자*/
bool bLbtDown = false;

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT: /* 무효화 영역(Invalidate Ract)이 발생한 경우에 WM_PAINT가 발생시킴 */
        /* 무효화 영역이란, 가려졌다 나올때 안보이던 부분이 챡 하고 나오는 그 때
           최소화 시켰다가 다시 올리면 발생함
           예전에는 부분적으로 가려져 있어도 그게 무효화 영역으로 취급되었는데, 윈도우 7 이후로
           부분적으로 가려지는 거는 무효화 영역으로 취급되지 않음 */
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        /*hdc도 핸들 값입니다.Device Context( 장치 그리기) 를 받아옴
          그걸 밑에 Rectangle에 넣어준거야 hdc도 찾아보면 결국 int 변수 하나 들고있는 구조체인데
          즉, BeginPaint라는 놈은 Device Context를 만들어서 그 ID값을 돌려주는 거지 */
          /* Device Context란?
             그리기 작업 수행에 필요한 Data들의 집합
             ex) 그림을 그리려면 펜, 붓, 색 등등이 필요하니까
             위의 인자를 통해 DC의 목적지는 hWnd, DC의 펜은 기본(black), DC의 브러쉬는 기본 브러쉬(White)
             인거로 정해진거임*/

             /* 직접 펜을 만들어서 DC에 넣으면 다른 색 펜이나 브러쉬 사용이 가능하겠지? */

        HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
        /* 펜 변경해서 ID값 받아옴 */
        HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
        //GetStockObject();
    /*자주 쓰느 것들을 미리 만들어둠. 그것들 가져오는 함수임*/


        HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen);
        HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);
        /* SelectObject는 범용적인 함수라서 void 타입을 반환해 그래서 반환 타입을 캐스팅 해줘야함*/
        /* 기본 펜 아이디 값을 받아둠*/

        HWND;
        HPEN;
        HBRUSH;

        /* 이런 비슷한 애들도 있어. 윈도우 아이디(무슨 윈도우인지) 값 받고,
           PEN이라는 커널 오브젝트 아아디 받고, BRUSH라는 커널 오브젝트 아이디 받고 */
           /* 커널 오브젝트이다보니, 우리는 ID값으로만 받아야 하고, ID값만 있으면 우리 입장에서는 구별이 어려우니
              이렇게 구조체를 통해 자료형을 만들어서 우리가 알아듣기 쉽게 해둔 것 */

              /* 윈도우 객체처럼, 운영체제에서 관리해서 내가 맘대로 다이렉트로 건들지 못하는걸 curnel object 라고 함
                 이런 경우 ID 값을 우리에게 줌 그걸 이용해서 제공하는 다른 함수들을 통해서 사용하게 됨
                 윈도우 핸들 (윈도우(창) 값, 어떤 윈도우인지)
                 윈도우 좌표
                 HDC?
                 작업 영역 (타이틀바와 메뉴바 아래의 창 내부) 0,0 은 맨 왼쪽 위. 단위는 픽셀 */

        if (bLbtDown)
        {
            Rectangle(hdc
                , g_ptLT.x, g_ptLT.y
                , g_ptRB.x, g_ptRB.y);
            /* 위에서 정한 dc의 값으로 사각형을 그리는거지*/
            /* 참고로 1 픽셀은 3byte로 되어서 RGB (각각 1byte씩 0~255) */
        }

        for (size_t i = 0; i < g_vecInfo.size(); ++i)
        {
            Rectangle(hdc
                , g_vecInfo[i].g_ptObjPos.x - g_vecInfo[i].g_ptObjScale.x / 2
                , g_vecInfo[i].g_ptObjPos.y - g_vecInfo[i].g_ptObjScale.y / 2
                , g_vecInfo[i].g_ptObjPos.x + g_vecInfo[i].g_ptObjScale.x / 2
                , g_vecInfo[i].g_ptObjPos.y + g_vecInfo[i].g_ptObjScale.y / 2);
        }
        /* 저장한 정보의 Rectangle을 만들어 놓은 상태로 유지하게 해줌
           근데 이걸 해보면 물체 늘어날수록 마우스 움직이면 겁나 깜빡거려

           왜냐면 마우스만 움직여도 전체 무효화 영역이 생기고, 그러면 벡터 순환 다 다시 하고 그러니까
           사람이 60~100 프레임을 느끼는데 그 60~100 프레임 안에 무효화 영역과 재순환이 걸리면
           깜빡거림을 보게 되는것

           해결하려면 우리가 데이터를 표시할 픽셀 데이터를 두가지를 관리하면 돼
           완성되어서 보여줄 픽셀 데이터와, 그리는 동안 저장될 픽셀 데이터*/

        SelectObject(hdc, hDefaultPen);
        SelectObject(hdc, hDefaultBrush);

        DeleteObject(hRedPen);
        DeleteObject(hBlueBrush);
        /* 할 일 끝났으면 다시 디폴트로 돌려주고 지울거 지우자*/


        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    /*swtich case 내부에서 변수를 만들고 싶을 때 중괄호를 다시 쳐줘야함*/
    break;
    case WM_KEYDOWN:
    {
        switch (wParam)
            /* wParam 이 키보드 눌린 정보, lParam 이 마우스 클릭 정보임*/
        {
        case VK_UP:
            // g_ptObjPos.y -= 10;
            InvalidateRect(hWnd, nullptr, true);
            /* nullptr 을 영역으로 하면 전체가 됨*/
            /* 세번째 True False는 무효화영역이 발생했을 때 한 번 싹 청소를 하냐 마냐 설정*/
            break;
        case VK_DOWN:
            // g_ptObjPos.y += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case VK_LEFT:
            // g_ptObjPos.x -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case VK_RIGHT:
            // g_ptObjPos.x += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

            /* 키 다운을 할 때 처음 1초 정도 막히는 부분이 있어. 그걸 또 해결해줘야해*/

        case 'W':
        {
            int a = 0;
        }
        break;
        }
    }
    break;

    case WM_KEYUP:
        /* 특정 키가 눌렀다가 떼질 때*/
    case WM_LBUTTONDOWN:
        /* 마우스가 눌릴 때*/
    {
        g_ptLT.x = LOWORD(lParam); /* X 좌표만 가져오는 비트 연산 함수ㅡ*/
        g_ptLT.y = HIWORD(lParam); /* Y 좌표만 자겨오는 비트 연산 함수 */
        lParam;
        bLbtDown = true;
        /* 4바이트 짜리. 2바이트(약 6.5만)씩 잘라서 X, Y 좌표를 담고 있다*/

    }
    break;

    /* 타이머 쓰면 따로 키를 누르지 않아도 여기 들어옴 */
    case WM_TIMER:
    {int a = 0; }
    break;

    case WM_MOUSEMOVE:
        g_ptRB.x = LOWORD(lParam);
        g_ptRB.y = HIWORD(lParam);
        // InvalidateRect(hWnd, nullptr, true);
        /* 메세지 처리 방식으로 안할꺼니까 이거 지우자. 리소스 잡아먹는다*/
        break;
        /* 위에서 클릭한 순간을 좌상단으로 보고, 마우스 움직이는걸 우 하단으로 보자는 거지 */

    case WM_LBUTTONUP:
    {
        tObjInfo info = {};
        info.g_ptObjPos.x = (g_ptLT.x + g_ptRB.x) / 2;
        info.g_ptObjPos.y = (g_ptLT.y + g_ptRB.y) / 2;

        info.g_ptObjScale.x = abs(g_ptLT.x - g_ptRB.x); // 절대값 함수
        info.g_ptObjScale.y = abs(g_ptLT.y - g_ptRB.y);

        g_vecInfo.push_back(info);
        bLbtDown = false;
        InvalidateRect(hWnd, nullptr, true);
    }

    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        /* 윈도우 메세지가 너무 많으니까. 따로 처리할 케이스는 위에 적어둔 거고,
           기본적인것들은 기본 제공하는 것 쪽으로 넘기겠다~ */
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
