#include "pch.h"
#include "GameObject.h"
#include "Player.h"
#include "Monster.h"
#include "GameRoom.h"

atomic<uint64> GameObject::s_idGenerator = 1;

void GameObject::Update()
{

}

PlayerRef GameObject::CreatePlayer()
{
	PlayerRef player = make_shared<Player>();
	player->info.set_objectid(s_idGenerator++);
	player->info.set_objecttype(Protocol::OBJECT_TYPE_PLAYER);

	return player;
}

MonsterRef GameObject::CreateMonster()
{
	MonsterRef monster = make_shared<Monster>();
	monster->info.set_objectid(s_idGenerator++);
	monster->info.set_objecttype(Protocol::OBJECT_TYPE_MONSTER);

	return monster;
}

void GameObject::SetState(ObjectState state, bool broadcast)
{
	if (info.state() == state)
		return;

	info.set_state(state);

	if (broadcast)
		BroadcastMove();
}

void GameObject::SetDir(Dir dir, bool broadcast)
{
	info.set_dir(dir);

	if (broadcast)
		BroadcastMove();
}

bool GameObject::CanGo(Vec2Int cellPos)
{
	if (room == nullptr)
		return false;

	return room->CanGo(cellPos);
}

Dir GameObject::GetLookAtDir(Vec2Int cellPos)
{
	Vec2Int dir = cellPos - GetCellPos();
	if (dir.x > 0)
		return DIR_RIGHT;
	else if (dir.x < 0)
		return DIR_LEFT;
	else if (dir.y > 0)
		return DIR_DOWN;
	else
		return DIR_UP;
}

void GameObject::SetCellPos(Vec2Int cellPos, bool broadcast)
{
	info.set_posx(cellPos.x);
	info.set_posy(cellPos.y);

	if (broadcast)
		BroadcastMove();
}


Vec2Int GameObject::GetFrontCellPos()
{
	Vec2Int pos = GetCellPos();

	switch (info.dir())
	{
	case DIR_DOWN:
		return pos + Vec2Int{ 0, 1 };
	case DIR_LEFT:
		return pos + Vec2Int{ -1, 0 };
	case DIR_RIGHT:
		return pos + Vec2Int{ 1, 0 };
	case DIR_UP:
		return pos + Vec2Int{ 0, -1 };
	}

	return pos;
}


void GameObject::BroadcastMove()
{
	if (room)
	{
		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_Move(info);
		room->BroadCast(sendBuffer);
	}
}