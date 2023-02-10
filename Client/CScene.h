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

private:
	vector<CObject*> m_arrVecObj[(UINT)GROUP_TYPE::END];
	// CObject*로 하는 이유는 얘가 제일 부모격이니까 이거 하나로 전부 관리 가능
	// 물론 우리는 오브젝트를 그룹으로 나눌꺼라 이 vector가 그룹 수만큼 있어야 함
	// 그래서 이런 vector를 배열로 만들어버려서 enum 으로 묶어버리자.
	wstring			 m_strName;		// Scene 이름

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

public:
	CScene();
	virtual ~CScene();

};

