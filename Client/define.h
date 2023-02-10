#pragma once


/* ������ �Լ��� �ʹ� ���� �ݺ��ȴٸ� �Լ� ȣ�� ����� �Ʊ��ϱ�
   �װ� define���� ��ũ�θ� ���� ��ġ �Լ� ó�� �ع����°���

   �ٵ� �����ؾ��� �� �־�
   10 * Add(10, 20) �̸� 300�� �ɰž�.
   �ٵ� ��ũ�η� (Add 10, 20) �� 10 + 20 ���� ��ũ�� �ص״ٸ�
   10 * 10 + 20 �ϰž� �׷��� 120�� �ǰ���

   ��ũ�δ� ��ó����ϱ�. �Լ�ó�� ó���ϴ°� �ƴ϶� �ٲ��ִ� �� ���̾�.
   �̰� �������� */

   // Singleton ��ũ��
#define SINGLE(type) public:\
                        static type* GetInst()\
						{\
							static type mgr;\
							return &mgr;\
						 }\
					private:\
						type();\
						~type();
// �̱����� ���鶧 type�� �̸��� �־��ָ� �ǰ���?
// \(��������)�� ���� �־��ָ� ���� �ٵ� define�� ���Ѵٴ� �ǹ�


#define fDT CTimeMgr::GetInst()->GetfDT()
// float �� �ʴ� �����̴� �ȼ�
#define DT CTimeMgr::GetInst()->GetDT()
// doubld �� �ʴ� �����̴� �ȼ�


// Scene �ȿ� �����ϴ� Object ���� ����
enum class GROUP_TYPE
{
	DEFAULT,			// 0
	PLAYER,				// 1
	MISSILE,			// 2
	MONSTER,			// 3




	END = 32,			// 32
};

// Scene���� ������ ����
enum class SCENE_TYPE
{
	TOOL,		//0, ���� Scene�� ���� �� �ʿ��� �͵��� ����
	START,

	STAGE_01,
	STAGE_02,



	END,
};