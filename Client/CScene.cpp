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

			/* ���� vector ��ü�� 32���� �ְ�, �� vector �ȿ� �ʿ��� ��ŭ�� Object����
			   �ڽ� Ŭ���� �ȿ��� �־������ž�. ���� ���� �Ҵ����� ����������� �������
			   �ϴµ�, �װ� �ڽ� Ŭ�������� ������ ���� �ʿ�� �����ϱ�
			   
			   �θ� Ŭ�������� ���� for���� ���Ƽ� 32���� ���� �ȿ� �ִ�, ������ ���Ϳ� ����
			   ������Ʈ���� ���������°���*/

			/* ���� ��ü�� ������ CScene Ŭ������ �Ͽ��̶� �Ⱥ������� �Ҹ��ڿ��� �˾Ƽ� ������ 
			   �׷� �� ���� ��ü���� �� ����?
			   
			   �ֳĸ� ���� �� ���� �ȿ��� ���� ����ִ°� �ƴ϶� �ּҰ��� ����ְ�, �� �ּҷ� ������
			   ������ Object���� �ִ� ������ ���͸� ����� = Object���� �ּҸ� ����� �� �Ǽ�
			   ��¥ Object���� �������°� �ƴ϶����� �׷��� �����ִ°ž�*/
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
