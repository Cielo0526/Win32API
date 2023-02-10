#pragma once


/* 간단한 함수가 너무 자주 반복된다면 함수 호출 비용이 아까우니까
   그걸 define으로 매크로를 만들어서 마치 함수 처럼 해버리는거지

   근데 주의해야할 게 있어
   10 * Add(10, 20) 이면 300이 될거야.
   근데 매크로로 (Add 10, 20) 을 10 + 20 으로 매크로 해뒀다면
   10 * 10 + 20 일거야 그러면 120이 되겠지

   매크로는 전처리기니까. 함수처럼 처리하는게 아니라 바꿔주는 것 뿐이야.
   이걸 유의하자 */

   // Singleton 매크로
#define SINGLE(type) public:\
                        static type* GetInst()\
						{\
							static type mgr;\
							return &mgr;\
						 }\
					private:\
						type();\
						~type();
// 싱글톤을 만들때 type에 이름만 넣어주면 되겠지?
// \(역슬래시)를 끝에 넣어주면 다음 줄도 define에 속한다는 의미


#define fDT CTimeMgr::GetInst()->GetfDT()
// float 형 초당 움직이는 픽셀
#define DT CTimeMgr::GetInst()->GetDT()
// doubld 형 초당 움직이는 픽셀


// Scene 안에 존재하는 Object 들을 나눔
enum class GROUP_TYPE
{
	DEFAULT,			// 0
	PLAYER,				// 1
	MISSILE,			// 2
	MONSTER,			// 3




	END = 32,			// 32
};

// Scene들의 종류를 나눔
enum class SCENE_TYPE
{
	TOOL,		//0, 내가 Scene을 만들 때 필요한 것들의 모음
	START,

	STAGE_01,
	STAGE_02,



	END,
};