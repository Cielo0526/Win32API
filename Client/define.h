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
						 }
// �̱����� ���鶧 type�� �̸��� �־��ָ� �ǰ���?
// \(��������)�� ���� �־��ָ� ���� �ٵ� define�� ���Ѵٴ� �ǹ�
