#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr);
private:
	CScene*		m_arrScene[(UINT)SCENE_TYPE::END];	// ¸ðµç ¾À
	CScene*		m_pCurScene;							// ÇöÀç ¾À

public:
	void init();

};

