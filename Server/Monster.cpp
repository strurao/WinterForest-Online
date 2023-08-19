#include "pch.h"
#include "Monster.h"
#include "GameRoom.h"
#include "Player.h"

Monster::Monster()
{
	info.set_name("MonsterName");
	info.set_hp(50);
	info.set_maxhp(50);
	info.set_attack(5);
	info.set_defence(0);
}

Monster::~Monster()
{

}

void Monster::Update()
{
	// Super::Update();

	switch (info.state())
	{
	case IDLE:
		UpdateIdle();
		break;
	case MOVE:
		UpdateMove();
		break;
	case SKILL:
		UpdateSkill();
		break;
	}
}

void Monster::UpdateIdle()
{
	if (room == nullptr)
		return;

	// Find Player
	if (_target.lock() == nullptr)
		_target = room->FindClosestPlayer(GetCellPos());

	PlayerRef target = _target.lock();
	if (target)
	{
		Vec2Int dir = target->GetCellPos() - GetCellPos();
		int32 dist = abs(dir.x) + abs(dir.y);
		if (dist == 1)
		{
			SetDir(GetLookAtDir(target->GetCellPos()));
			SetState(SKILL, true);
			_waitUntil = GetTickCount64() + 1000;
		}
		else
		{
			vector<Vec2Int> path;
			if (room->FindPath(GetCellPos(), target->GetCellPos(), OUT path))
			{
				if (path.size() > 1)
				{
					Vec2Int nextPos = path[1];
					if (room->CanGo(nextPos))
					{
						SetDir(GetLookAtDir(nextPos));
						SetCellPos(nextPos);
						_waitUntil = GetTickCount64() + 1000;
						SetState(MOVE, true);
					}
				}
				else
					SetCellPos(path[0]);
			}
		}
	}
}

void Monster::UpdateMove()
{
	uint64 now = GetTickCount64();

	if (_waitUntil > now)
		return;

	SetState(IDLE);
}

void Monster::UpdateSkill()
{
	uint64 now = GetTickCount64();

	if (_waitUntil > now)
		return;

	SetState(IDLE);
}
