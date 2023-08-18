#pragma once
#include "ResourceBase.h"

struct Tile
{
	//TODO
	int32 value = 0;
};

class Tilemap : public ResourceBase
{
public:
	Tilemap();
	virtual ~Tilemap() override;

	virtual void LoadFile(const wstring& path) override;
	virtual void SaveFile(const wstring& path) override;

	Vec2Int GetMapSize() { return _mapSize; }
	int32 GetTileSize() { return _tileSize; }
	Tile* GetTileAt(Vec2Int pos);
	vector<vector<Tile>>& GetTiles() { return _tiles; }

	void SetMapSize(Vec2Int size);
	void SetTileSize(int32 size); // 하나의 타일이 몇비트씩 차지하는지? 

private:
	Vec2Int _mapSize = {};
	int32 _tileSize = {};
	vector<vector<Tile>> _tiles; // _tiles[y][x]
};

