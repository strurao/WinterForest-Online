#pragma once
class Scene;
class MyPlayer;

class SceneManager
{
	DECLARE_SINGLE(SceneManager)

public:
	void Init();
	void Update();
	void Render(HDC hdc);

	void Clear();

public:
	void ChangeScene(SceneType sceneType);
	Scene* GetCurrentScene() { return _scene; }

	class DevScene* GetDevScene();

	MyPlayer* GetMyPlayer() { return _myPlayer; }
	uint64 GetMyPlayerId();
	void SetMyPlayer(MyPlayer* myPlayer) { _myPlayer = myPlayer; }
private:
	Scene* _scene;
	SceneType _sceneType = SceneType::None;

	MyPlayer* _myPlayer = nullptr;

public:
	Vec2 GetCameraPos() { return _cameraPos; }
	void SetCameraPos(Vec2 pos) { _cameraPos = pos; }
	 
private:
	Vec2 _cameraPos = { 400,300 };
};

