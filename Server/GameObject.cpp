#include "pch.h"
#include "GameObject.h"
#include "Player.h"
#include "Monster.h"
#include "GameRoom.h"

atomic<uint64> GameObject::s_idGenerator = 1;

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