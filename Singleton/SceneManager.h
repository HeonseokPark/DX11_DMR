#pragma once
#include "SingletonBase.h"
//���� ��� ���� ����
class GameNode;

class SceneManager : public SingletonBase<SceneManager>
{
	//�� == ���ӳ��(���ӳ�带 ��� �޴� ���ΰ� Scene�� �� �� ����)
private:
	typedef map<string, GameNode*> m_sceneList;
	typedef map<string, GameNode*>::iterator m_sceneListIter;

	GameNode*			currentScene = nullptr;		//���� Scene
	m_sceneList			sceneList;					//Scene ���

public:
	SceneManager() {};
	~SceneManager() {};

	//��ü Scene ����
	void ReleaseAll();
	//���� Scene ȣ��
	void CurrentSceneUpdate();
	void CurrentSceneRender();


	//Scene �߰�
	GameNode* AddScene(string name, GameNode* scene);
	//Scene ����
	HRESULT ChangeScene(string name);

	//���� Scene �޾ƿ���
	MAKEGET(GameNode*, currentScene);


};

