#pragma once
#include "SingletonBase.h"
//게임 노드 전방 선언
class GameNode;

class SceneManager : public SingletonBase<SceneManager>
{
	//씬 == 게임노드(게임노드를 상속 받는 전부가 Scene이 될 수 있음)
private:
	typedef map<string, GameNode*> m_sceneList;
	typedef map<string, GameNode*>::iterator m_sceneListIter;

	GameNode*			currentScene = nullptr;		//현재 Scene
	m_sceneList			sceneList;					//Scene 목록

public:
	SceneManager() {};
	~SceneManager() {};

	//전체 Scene 삭제
	void ReleaseAll();
	//현재 Scene 호출
	void CurrentSceneUpdate();
	void CurrentSceneRender();


	//Scene 추가
	GameNode* AddScene(string name, GameNode* scene);
	//Scene 변경
	HRESULT ChangeScene(string name);

	//현재 Scene 받아오기
	MAKEGET(GameNode*, currentScene);


};

