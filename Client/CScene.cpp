#include "pch.h"
#include "CScene.h"

#include "CObject.h"

CScene::CScene()
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j = m_arrObj[i].size(); ++j)
		{
			delete m_arrObj[i][j];

			/* 지금 vector 자체가 32개가 있고, 그 vector 안에 필요한 만큼의 Object들이
			   자식 클래스 안에서 넣어졌을거야. 전부 동적 할당으로 만들어졌으니 지워줘야
			   하는데, 그걸 자식 클래스에서 일일이 만들 필요는 없으니까
			   
			   부모 클래스에서 이중 for문을 돌아서 32개의 벡터 안에 있는, 각각의 벡터에 쌓인
			   오브젝트들을 지워버리는거지*/

			/* 벡터 자체는 어차피 CScene 클래스의 일원이라 안보이지만 소멸자에서 알아서 없애줘 
			   그럼 그 안의 개체들은 왜 없애?
			   
			   왜냐면 지금 이 벡터 안에는 뭐가 들어있는게 아니라 주소값이 들어있고, 그 주소로 가보면
			   각각의 Object들이 있는 구조라서 벡터를 지운다 = Object들의 주소를 지운다 가 되서
			   진짜 Object들이 지워지는게 아니란말야 그래서 지워주는거야*/
		}
	}
}

void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->update();
		}
	}
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->render(_dc);
		}
	}
}

void CScene::Enter()
{
}
