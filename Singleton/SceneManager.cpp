#include "stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"

void SceneManager::ReleaseAll()
{
	//�ݺ��ڸ� ���Ͽ� ���� ���鼭 �ϳ��� ����
	m_sceneListIter iter = sceneList.begin();
	for (iter; iter != sceneList.end();)
	{
		if (iter->second != nullptr)
		{
			//���� ���� �����ɶ��� ������ ȣ�� �� ����
			if (iter->second == currentScene) iter->second->release();
			SAFE_DELETE(iter->second);
			iter = sceneList.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	sceneList.clear();
}

void SceneManager::CurrentSceneUpdate()
{
	if (currentScene)currentScene->update();
}

void SceneManager::CurrentSceneRender()
{
	if (currentScene)currentScene->render();
}

GameNode * SceneManager::AddScene(string name, GameNode * scene)
{
	if(!scene) return nullptr;

	sceneList.insert(make_pair(name, scene));

	return scene;
}

HRESULT SceneManager::ChangeScene(string name)
{
	m_sceneListIter iter = sceneList.find(name);

	//��ã�� ���
	if (iter == sceneList.end()) return E_FAIL;

	//�ٲٷ��� ���� ���� ���� ���ٸ�
	if (iter->second == currentScene) return E_FAIL;

	//���� ���� ������ �ʰ� ã������ ���� ���� �Ѵٸ�
	if (SUCCEEDED(iter->second->init()))
	{
		//���� �ٲٱ� �� ���� ���� �Ѵٸ� ������ ȣ��
		if (currentScene) currentScene->release();
		currentScene = iter->second;
		return S_OK;

	}
	else
	{
		return E_FAIL;
	}

	return E_FAIL;
}
