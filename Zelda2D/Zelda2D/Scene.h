#pragma once
class Actor;
class Creature;
class UI;

class Scene
{
public:
	Scene();
	virtual ~Scene();
	
	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	
	virtual void AddActor(Actor* actor);
	virtual void RemoveActor(Actor* actor);

	Creature* GetCreatureAt(Vec2Int cellPos);

public:
	vector<Actor*> _actors[LAYER_MAXCOUNT];
	vector<UI*> _uis;
};

