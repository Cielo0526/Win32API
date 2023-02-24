#pragma once

// 여러가지 오브젝트가 생깁니다. 그냥 물체부터 UI 등등 모든 것
// 그 화면에 있는 모든 오브젝트들을 관리하는 하나의 Scene이 있습니다.
// Scene도 여러가지가 있겠죠? 다 상속받읍시다

class CObject;
	// 전방 선언시 CObject를 클래스 내 타입으로 지정할 순 없음 -> 뭔지 정확히는 모르니까
	// 대신 포인터로는 사용 가능. 어차피 포인터는 규격 정해져있으니까.
	// 전방 선언하는 이유는 컴파일 속도 때문에, 직접 헤더를 참조하면 Object 코드 변경시 Scene도 확인 해줘야하니까 번거로워
	// 전방 선언으로 하면 그냥 놔뒀다가 나중에 대려오기만 하면 되니까.
	// 헤더끼리는 참조 많이 안하는게 좋아.

class CScene
{

	// 나중에 이제 Scene 안에 Object들을 넣어야 할 때 밑의 vector에 접근해서 넣어줘야 하는데 자식 클래스에 쓰니까
	// protected가 편하긴 한데, 결국 자식쪽에서도 멤버에 맘대로 접근이 가능하니까 나중에 디버그 하기 좀 힘들어
	// 그래서 그냥 private로 두고 밑에 vector에 넣어주는 함수를 만들어서 그걸 protected로 주면 관리가 편하지 않을까?
private:
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END];
	// CObject*로 하는 이유는 얘가 제일 부모격이니까 이거 하나로 전부 관리 가능
	// 물론 우리는 오브젝트를 그룹으로 나눌꺼라 이 vector가 그룹 수만큼 있어야 함
	// 그래서 이런 vector를 배열로 만들어버려서 enum 으로 묶어버리자.
	wstring			 m_strName;		// Scene 이름

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }


	void update();
	void finalupdate();
	void render(HDC _dc);

	virtual void Enter() = 0;
	// 각 Scene은 자기 구성 요소에 맞는 기본 시작 작업이 필요하고 이걸 부모 포인터로 호출하기 위해서
	// 부모는 구현할 필요 없는 Start 함수를 만들어야 함 -> 순수 가상 함수(부모가 실제 객체화는 못시키고 자식 쪽에 이런게 있다고 알리는 용도)가 되면 좋음
	// 자식 클래스들이 Start를 구현하지 않으면 객체를 만들 수 없어짐 또한 부모 클래스는 실수로 객체를 만들지 못함
	virtual void Exit() = 0;
	// 반대로 Scene간의 전환이 일어날 때 원래의 Scene에서 이탈해야 하니까 또 함수 하나 만들고


	// 이렇게 자료가 출입할 수 있는 통로를 제한해두는 것이 나중에 디버그나 데이터 관리하기 수월하다.
	// 당장은 불편하더라도 나중에 문제가 커지는 걸 잡아주는거지
public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}
	// 대신 이렇게 헤더에 바로 구현해서 inline 함수로 만들어서 호출 비용이 들지 않게끔 한다.
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }
	// 원본을 줘야 제대로 충돌 검사를 하지. 근데 값이 훼손되면 안되겠지?
	
	

public:
	CScene();
	virtual ~CScene();

};

// 순수 가상 함수가 있는 클래스 -> 추상 클래스 -> 부모로만 존재하는, 객체를 만들 수 없는 클래스 
// 함수명() = 0; 이렇게 선언하면 되고, 따로 cpp에 구현 안해둬도 됨.
// 자식이 상속받아서 자식 안에서 구현하면 됨. 대신 모든 자식이 다 구현해놔야만 함