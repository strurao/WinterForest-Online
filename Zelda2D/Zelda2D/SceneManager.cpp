#include "pch.h"
#include "SceneManager.h"
#include "DevScene.h"
#include "Resource.h"
#include "EditScene.h"

void SceneManager::Init()
{
}

void SceneManager::Update()
{
	if (_scene)
		_scene->Update();
}

void SceneManager::Render(HDC hdc)
{
	if (_scene)
		_scene->Render(hdc);
}

void SceneManager::Clear()
{
	SAFE_DELETE(_scene);
}

void SceneManager::ChangeScene(SceneType sceneType)
{
	if (_sceneType == sceneType) // 바꾸고자 하는 씬타입이 현재 씬타입과 같다면
		return;

	Scene* newScene = nullptr;

	switch (sceneType)
	{
		case SceneType::DevScene:
			newScene = new DevScene();
			break;
		case SceneType::EditScene:
			newScene = new EditScene();
			break;
	}

	SAFE_DELETE(_scene);

	_scene = newScene;
	_sceneType = sceneType;

	newScene->Init();
}
