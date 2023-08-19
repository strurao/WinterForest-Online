#include "pch.h"
#include "DevScene.h"
#include "Utils.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Actor.h"
#include "SpriteActor.h"
#include "Player.h"
#include "Flipbook.h"
#include "UI.h"
#include "Button.h"
#include "TestPanel.h"
#include "TilemapActor.h"
#include "Tilemap.h"
#include "SoundManager.h"
#include "Sound.h"
#include "Monster.h"
#include "MyPlayer.h"
#include "SceneManager.h"

DevScene::DevScene()
{

}

DevScene::~DevScene()
{
}

void DevScene::Init()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"Stage01", L"Sprite\\Map\\Stage01.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Tile", L"Sprite\\Map\\Tile.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Sword", L"Sprite\\Item\\Sword.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Arrow", L"Sprite\\Item\\Arrow.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Potion", L"Sprite\\UI\\Mp.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerDown", L"Sprite\\Player\\PlayerDown.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerUp", L"Sprite\\Player\\PlayerUp.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerLeft", L"Sprite\\Player\\PlayerLeft.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerRight", L"Sprite\\Player\\PlayerRight.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Snake", L"Sprite\\Monster\\Snake.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Hit", L"Sprite\\Effect\\Hit.bmp", RGB(0, 0, 0));

	GET_SINGLE(ResourceManager)->LoadTexture(L"Start", L"Sprite\\UI\\Start.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Edit", L"Sprite\\UI\\Edit.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Exit", L"Sprite\\UI\\Exit.bmp");

	GET_SINGLE(ResourceManager)->CreateSprite(L"Stage01", GET_SINGLE(ResourceManager)->GetTexture(L"Stage01"));
	GET_SINGLE(ResourceManager)->CreateSprite(L"TileO", GET_SINGLE(ResourceManager)->GetTexture(L"Tile"), 0, 0, 48, 48);
	GET_SINGLE(ResourceManager)->CreateSprite(L"TileX", GET_SINGLE(ResourceManager)->GetTexture(L"Tile"), 48, 0, 48, 48);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Start_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Start"), 0, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Start_On", GET_SINGLE(ResourceManager)->GetTexture(L"Start"), 150, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Edit_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Edit"), 0, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Edit_On", GET_SINGLE(ResourceManager)->GetTexture(L"Edit"), 150, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Exit_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Exit"), 0, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Exit_On", GET_SINGLE(ResourceManager)->GetTexture(L"Exit"), 150, 0, 150, 150);

	LoadMap();
	LoadPlayer();
	LoadMonster();
	LoadProjectiles();
	LoadEffect();
	LoadTilemap();

	GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\BGM.wav");
	GET_SINGLE(ResourceManager)->LoadSound(L"Attack", L"Sound\\Sword.wav");

	//SpawnObjectAtRandomPos<MyPlayer>();
	//SpawnObjectAtRandomPos<Monster>();
	//SpawnObject<Monster>(Vec2Int{ 7, 7 });

	Super::Init();
}

void DevScene::Update()
{
	Super::Update();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	TickMonsterSpawn();
}

void DevScene::Render(HDC hdc)
{
	Super::Render(hdc);

}

void DevScene::AddActor(Actor* actor)
{
	Super::AddActor(actor);

	Monster* creature = dynamic_cast<Monster*>(actor);
	if (creature)
	{
		_monsterCount++;
	}
}

void DevScene::RemoveActor(Actor* actor)
{
	Super::RemoveActor(actor);

	Monster* creature = dynamic_cast<Monster*>(actor);
	if (creature)
	{
		_monsterCount--;
	}
}

void DevScene::LoadMap()
{
	Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Stage01");

	SpriteActor* background = new SpriteActor();
	background->SetSprite(sprite);
	background->SetLayer(LAYER_BACKGROUND);
	const Vec2Int size = sprite->GetSize();
	background->SetPos(Vec2(size.x / 2, size.y / 2));

	AddActor(background);
}

void DevScene::LoadPlayer()
{
	// IDLE
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerUp");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_IdleUp");
		fb->SetInfo({ texture, L"FB_MoveUp", {200, 200}, 0, 9, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerDown");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_IdleDown");
		fb->SetInfo({ texture, L"FB_MoveDown", {200, 200}, 0, 9, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerLeft");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_IdleLeft");
		fb->SetInfo({ texture, L"FB_MoveLeft", {200, 200}, 0, 9, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerRight");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_IdleRight");
		fb->SetInfo({ texture, L"FB_MoveRight", {200, 200}, 0, 9, 0, 0.5f });
	}
	// MOVE
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerUp");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveUp");
		fb->SetInfo({ texture, L"FB_MoveUp", {200, 200}, 0, 9, 1, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerDown");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveDown");
		fb->SetInfo({ texture, L"FB_MoveDown", {200, 200}, 0, 9, 1, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerLeft");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveLeft");
		fb->SetInfo({ texture, L"FB_MoveLeft", {200, 200}, 0, 9, 1, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerRight");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveRight");
		fb->SetInfo({ texture, L"FB_MoveRight", {200, 200}, 0, 9, 1, 0.5f });
	}
	// SKILL
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerUp");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackUp");
		fb->SetInfo({ texture, L"FB_MoveUp", {200, 200}, 0, 7, 3, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerDown");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackDown");
		fb->SetInfo({ texture, L"FB_MoveDown", {200, 200}, 0, 7, 3, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerLeft");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackLeft");
		fb->SetInfo({ texture, L"FB_MoveLeft", {200, 200}, 0, 7, 3, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerRight");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackRight");
		fb->SetInfo({ texture, L"FB_MoveRight", {200, 200}, 0, 7, 3, 0.5f, false });
	}
	// BOW
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerUp");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BowUp");
		fb->SetInfo({ texture, L"FB_BowUp", {200, 200}, 0, 7, 5, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerDown");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BowDown");
		fb->SetInfo({ texture, L"FB_BowDown", {200, 200}, 0, 7, 5, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerLeft");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BowLeft");
		fb->SetInfo({ texture, L"FB_BowLeft", {200, 200}, 0, 7, 5, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerRight");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BowRight");
		fb->SetInfo({ texture, L"FB_BowRight", {200, 200}, 0, 7, 5, 0.5f, false });
	}
	// STAFF
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerUp");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_StaffUp");
		fb->SetInfo({ texture, L"FB_StaffUp", {200, 200}, 0, 10, 6, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerDown");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_StaffDown");
		fb->SetInfo({ texture, L"FB_StaffDown", {200, 200}, 0, 10, 6, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerLeft");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_StaffLeft");
		fb->SetInfo({ texture, L"FB_StaffLeft", {200, 200}, 0, 10, 6, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerRight");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_StaffRight");
		fb->SetInfo({ texture, L"FB_StaffRight", {200, 200}, 0, 10, 6, 0.5f, false });
	}

}

void DevScene::LoadMonster()
{
	// MOVE
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Snake");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_SnakeUp");
		fb->SetInfo({ texture, L"FB_SnakeUp", {100, 100}, 0, 3, 3, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Snake");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_SnakeDown");
		fb->SetInfo({ texture, L"FB_SnakeDown", {100, 100}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Snake");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_SnakeLeft");
		fb->SetInfo({ texture, L"FB_SnakeLeft", {100, 100}, 0, 3, 2, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Snake");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_SnakeRight");
		fb->SetInfo({ texture, L"FB_SnakeRight", {100, 100}, 0, 3, 1, 0.5f });
	}
}

void DevScene::LoadProjectiles()
{
	// MOVE
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Arrow");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_ArrowUp");
		fb->SetInfo({ texture, L"FB_ArrowUp", {100, 100}, 0, 0, 3, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Arrow");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_ArrowDown");
		fb->SetInfo({ texture, L"FB_ArrowDown", {100, 100}, 0, 0, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Arrow");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_ArrowLeft");
		fb->SetInfo({ texture, L"FB_ArrowLeft", {100, 100}, 0, 0, 1, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Arrow");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_ArrowRight");
		fb->SetInfo({ texture, L"FB_ArrowRight", {100, 100}, 0, 0, 2, 0.5f });
	}
}

void DevScene::LoadEffect()
{
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Hit");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Hit");
		fb->SetInfo({ texture, L"FB_Hit", {50, 47}, 0, 5, 0, 0.5f, false });
	}
}

void DevScene::LoadTilemap()
{
	TilemapActor* actor = new TilemapActor();
	AddActor(actor);

	_tilemapActor = actor;
	{
		auto* tm = GET_SINGLE(ResourceManager)->CreateTilemap(L"Tilemap_02");
		tm->SetMapSize({ 63, 43 });
		tm->SetTileSize(48);

		GET_SINGLE(ResourceManager)->LoadTilemap(L"Tilemap_02", L"Tilemap\\Tilemap_02.txt");

		_tilemapActor->SetTilemap(tm);
		_tilemapActor->SetShowDebug(false);
	}
}

void DevScene::Handle_S_AddObject(Protocol::S_AddObject& pkt)
{
	uint64 myPlayerId = GET_SINGLE(SceneManager)->GetMyPlayerId();
	const int32 size = pkt.object_size();
	for (int32 i = 0; i < size; i++)
	{
		const Protocol::ObjectInfo& info = pkt.object(i);
		if (myPlayerId == info.objectid())
			continue;
		if (info.objecttype() == Protocol::OBJECT_TYPE_PLAYER)
		{
			Player* player = SpawnObject<Player>(Vec2Int{ info.posx(), info.posy() });
			player->SetDir(info.dir());
			player->SetState(info.state());
			player->info = info;
		}
		else if (info.objecttype() == Protocol::OBJECT_TYPE_MONSTER)
		{
			Monster* monster = SpawnObject<Monster>(Vec2Int{ info.posx(), info.posy() });
			monster->SetDir(info.dir());
			monster->SetState(info.state());
			monster->info = info;
		}
	}
}

void DevScene::Handle_S_RemoveObject(Protocol::S_RemoveObject& pkt)
{
	const int32 size = pkt.ids_size();
	for (int32 i = 0; i < size; i++)
	{
		int32 id = pkt.ids(i);
	
		GameObject* object = Get_Object(id);
		if (object)
			RemoveActor(object);
	}
}

GameObject* DevScene::Get_Object(uint64 id)
{
	for (Actor* actor : _actors[LAYER_OBJECT])
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(actor);
		if (gameObject && gameObject->info.objectid() == id)
			return gameObject;
	}

	return nullptr;
}

Player* DevScene::FindClosestPlayer(Vec2Int pos)
{
	float best = FLT_MAX;
	Player* ret = nullptr;

	for (Actor* actor : _actors[LAYER_OBJECT])
	{
		Player* player = dynamic_cast<Player*>(actor);
		if (player)
		{
			Vec2Int dir = pos - player->GetCellPos();
			float dist = dir.LengthSquared();
			if (dist < best)
			{
				dist = best;
				ret = player;
			}
		}
	}

	return ret;
}

// A* -> Dijikstra -> BFS -> Graph
// PQ
bool DevScene::FindPath(Vec2Int src, Vec2Int dest, vector<Vec2Int>& path, int32 maxDepth)
{
	// F = G + H
	// F = 최종 점수(작을 수록 좋음)
	// G = 시작점에서 해당 좌표까지 이동하는데 드는 비용
	// H = 목적지에서 해당 좌표까지 이동하는데 드는 비용
	int32 depth = abs(src.y - dest.y) + abs(src.x - dest.x);
	if (depth >= maxDepth)
		return false;

	priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;
	map<Vec2Int, int32> best;
	map<Vec2Int, Vec2Int> parent;

	// 초기값
	{
		int32 cost = abs(dest.y - src.y) + abs(dest.x - src.x);

		pq.push(PQNode(cost, src));
		best[src] = cost;
		parent[src] = src;
	}

	Vec2Int front[4] =
	{
		{0, -1},
		{0, 1},
		{-1, 0},
		{1, 0},
	};

	bool found = false;

	while (pq.empty() == false)
	{
		// 제일 좋은 후보를 찾는다
		PQNode node = pq.top();
		pq.pop();

		// 더 짧은 경로를 뒤늦게 찾았다면 스킵
		if (best[node.pos] < node.cost)
			continue;

		// 목적지에 도착했으면 바로 종료
		if (node.pos == dest)
		{
			found = true;
			break;
		}

		// 방문
		for (int32 dir = 0; dir < 4; dir++)
		{
			Vec2Int nextPos = node.pos + front[dir];

			if (CanGo(nextPos) == false)
				continue;

			int32 depth = abs(src.y - nextPos.y) + abs(src.x - nextPos.x);
			if (depth >= maxDepth)
				continue;

			int32 cost = abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x);
			int32 bestValue = best[nextPos];
			if (bestValue != 0)
			{
				// 다른 경로에서 더 빠른 길을 찾았으면 스킵
				if (bestValue <= cost)
					continue;
			}

			// 예약 진행
			best[nextPos] = cost;
			pq.push(PQNode(cost, nextPos));
			parent[nextPos] = node.pos;
		}
	}

	if (found == false)
	{
		float bestScore = FLT_MAX;

		for (auto& item : best)
		{
			Vec2Int pos = item.first;
			int32 score = item.second;

			// 동점이라면, 최초 위치에서 가장 덜 이동하는 쪽으로
			if (bestScore == score)
			{
				int32 dist1 = abs(dest.x - src.x) + abs(dest.y - src.y);
				int32 dist2 = abs(pos.x - src.x) + abs(pos.y - src.y);
				if (dist1 > dist2)
					dest = pos;
			}
			else if (bestScore > score)
			{
				dest = pos;
				bestScore = score;
			}
		}
	}

	path.clear();
	Vec2Int pos = dest;

	while (true)
	{
		path.push_back(pos);

		// 시작점
		if (pos == parent[pos])
			break;

		pos = parent[pos];
	}

	std::reverse(path.begin(), path.end());
	return true;
}

bool DevScene::CanGo(Vec2Int cellPos)
{
	if (_tilemapActor == nullptr)
		return false;

	Tilemap* tm = _tilemapActor->GetTilemap();
	if (tm == nullptr)
		return false;

	Tile* tile = tm->GetTileAt(cellPos);
	if (tile == nullptr)
		return false;

	// 몬스터 충돌?
	if (GetCreatureAt(cellPos) != nullptr)
		return false;

	return tile->value != 1;
}

Vec2 DevScene::ConvertPos(Vec2Int cellPos)
{
	Vec2 ret = {};

	if (_tilemapActor == nullptr)
		return ret;

	Tilemap* tm = _tilemapActor->GetTilemap();
	if (tm == nullptr)
		return ret;

	int32 size = tm->GetTileSize();
	Vec2 pos = _tilemapActor->GetPos();

	ret.x = pos.x + cellPos.x * size + (size / 2);
	ret.y = pos.y + cellPos.y * size + (size / 2);

	return ret;
}

Vec2Int DevScene::GetRandomEmptyCellPos()
{
	Vec2Int ret = { -1, -1 };

	if (_tilemapActor == nullptr)
		return ret;

	Tilemap* tm = _tilemapActor->GetTilemap();
	if (tm == nullptr)
		return ret;

	Vec2Int size = tm->GetMapSize();

	// 몇 번 시도?
	while (true)
	{
		int32 x = rand() % size.x;
		int32 y = rand() % size.y;
		Vec2Int cellPos{ x, y };

		if (CanGo(cellPos))
			return cellPos;
	}
}

void DevScene::TickMonsterSpawn()
{
	return;

	if (_monsterCount < DESIRED_COUNT)
		SpawnObjectAtRandomPos<Monster>();
}

