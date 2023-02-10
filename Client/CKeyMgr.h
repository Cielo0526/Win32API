#pragma once

// DT -> �� �������� �ɸ� �ð�
// DT �ȿ��� �̷����� ���� �ڵ������ �� �� �� �� �Ͼ����
// �츮�� ���⿡�� ���ÿ� �Ͼ�� ���̾�. (�� �Ϸ�� �� �׷��� �����쿡 ���ϱ�)
// �׷��� ���� ������ Ÿ�̹����� DT �ȿ��� A��� Ű�� ���ȴٰ� ���� ���� �ְ�
// �װ� ������ �� DT ���� �Ĺݿ� �ִ� Ű �Է� ���� �ڵ忡�� �װ� �������� ������?? ������ �ǰ���
// �׷��� Ű�Ŵ����� ������ ����ȭ (�� DT �ȿ����� Ű �Է� ���¸� �����ϰ� �ްԲ�) �������

// 1. ������ ����ȭ
//   - ���� ������ ������ ���� Ű�� ���� ������ �̺�Ʈ�� ��������. 

// 2. Ű �Է� �̺�Ʈ ó��
//   - tap, hold, away

enum class KEY_STATE
{
	NONE,	// ������ �ʾҰ�, �������� ������ ���� ����
	TAP,	// �� ���� ����
	HOLD,	// ������ �ִ� ��
	AWAY,	// �� �� ����
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
	// ������ KEY ���� struct�� ���尪�̾�����.
	// vector�� ù��° index ���� �� enum�� ���ڰ� �Ǵϱ� ���� ���ص� �� ��
	KEY_STATE	eState;		// Ű�� ���°�
	bool		bPrevPush;		// ������ ���ȴ��� ����
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

