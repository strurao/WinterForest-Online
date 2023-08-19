#pragma once
#include "Tilemap.h"

struct PQNode
{
	PQNode(int32 cost, Vec2Int pos) : cost(cost), pos(pos) { }

	bool operator<(const PQNode& other) const { return cost < other.cost; }
	bool operator>(const PQNode& other) const { return cost > other.cost; }

	int32 cost;
	Vec2Int pos;
};

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
	// PacketHandler
	void Handle_C_Move(Protocol::C_Move& pkt);

public:
	void AddObject(GameObjectRef gameObject);
	void RemoveObject(uint64 id);
	void BroadCast(SendBufferRef& sendBuffer);

public:
	PlayerRef FindClosestPlayer(Vec2Int pos);
	bool FindPath(Vec2Int src, Vec2Int dest, vector<Vec2Int>& path, int32 maxDepth = 10);
	bool CanGo(Vec2Int cellPos);
	Vec2Int GetRandomEmptyCellPos();
	GameObjectRef GetGameObjectAt(Vec2Int cellPos);

private:
	map<uint64, PlayerRef> _players;
	map<uint64, MonsterRef> _monsters;
	Tilemap _tilemap;
};

extern GameRoomRef GRoom; // 전역으로 접근 가능