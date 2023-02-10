#pragma once

// DT -> 한 프레임이 걸린 시간
// DT 안에서 이런저런 일이 코드상으로 한 줄 한 줄 일어나지만
// 우리가 보기에는 동시에 일어나는 일이야. (다 완료된 걸 그려서 윈도우에 띄우니까)
// 그런데 정말 찰나의 타이밍으로 DT 안에서 A라는 키가 눌렸다가 떼질 수도 있고
// 그것 때문에 한 DT 안의 후반에 있던 키 입력 반응 코드에서 그게 반응하지 않으면?? 문제가 되겠지
// 그래서 키매니져는 프레임 동기화 (한 DT 안에서는 키 입력 상태를 동일하게 받게끔) 해줘야해

// 1. 프레임 동기화
//   - 동일 프레임 내에서 같은 키에 대해 동일한 이벤트를 가져간다. 

// 2. 키 입력 이벤트 처리
//   - tap, hold, away

enum class KEY_STATE
{
	NONE,	// 눌리지 않았고, 이전에도 눌리지 않은 상태
	TAP,	// 막 누른 시점
	HOLD,	// 누르고 있는 중
	AWAY,	// 막 뗀 시점
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,

	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	Z,
	X,
	C,
	V,
	B,

	ALT,
	CTRL,
	LSHIFT,
	SAPCE,
	ENTER,
	ESC,

	LAST,

};

struct tKeyInfo
{
	// 원래는 KEY 값도 struct의 저장값이었으나.
	// vector의 첫번째 index 값이 곧 enum의 숫자가 되니까 저장 안해도 될 듯
	KEY_STATE	eState;		// 키의 상태값
	bool		bPrevPush;		// 이전에 눌렸는지 여부
};

class CKeyMgr
{
	SINGLE(CKeyMgr);
private:
	vector<tKeyInfo> m_vecKey;

public:
	void init();
	void update();

public:
	KEY_STATE GetKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].eState; }
};

