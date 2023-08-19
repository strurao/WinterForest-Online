#pragma once

struct Tile
{
	// TODO
	int32 value = 0;
};

class Tilemap
{
public:
	Tilemap();
	virtual ~Tilemap();

	virtual void LoadFile(const wstring& path);

	Vec2Int GetMapSize() { return _mapSize; }
	int32 GetTileSize() { return _tileSize; }
	Tile* GetTileAt(Vec2Int pos);
	vector<vector<Tile>>& GetTiles() { return _tiles; };

	void SetMapSize(Vec2Int size);
	void SetTileSize(int32 size);

private:
	Vec2Int _mapSize = {};
	int32 _tileSize = {};
	vector<vector<Tile>> _tiles;
};

