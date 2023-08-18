#pragma once

class Player;
class Monster;

class GameObject
{
public:
	GameObject() {}
	virtual ~GameObject() {}
	
	static PlayerRef CreatePlayer();
	static MonsterRef CreateMonster();

public:
	Protocol::ObjectInfo info;
	GameRoomRef room;

private:
	static atomic<uint64> s_idGenerator;
};

