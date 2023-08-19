#pragma once
#include "GameObject.h"

class Monster : public GameObject
{
	using Super = GameObject;

public:
	Monster();
	virtual ~Monster() override;

	virtual void Update();

private:
	virtual void UpdateIdle();
	virtual void UpdateMove();
	virtual void UpdateSkill();

private:
	uint64 _waitUntil = 0.f;
	weak_ptr<Player> _target;
};

