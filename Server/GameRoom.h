#pragma once

class GameRoom : public enable_shared_from_this<GameRoom>
{
public:
	GameRoom();
	virtual ~GameRoom();

	void Init();
	void Update();

	void EnterRoom(GameSessionRef session);
	void LeaveRoom(GameSessionRef session);
	GameObjectRef FindObject(uint64 id);

	GameRoomRef GetRoomRef() { return shared_from_this(); }

public:
	void AddObject(GameObjectRef gameObject);
	void RemoveObject(uint64 id);

private:
	map<uint64, PlayerRef> _players;
	map<uint64, MonsterRef> _monsters;
};

extern GameRoomRef GRoom; // 전역으로 접근 가능