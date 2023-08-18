#include "pch.h"
#include "Tilemap.h"
#include <fstream>
#include <iostream>

Tilemap::Tilemap()
{
}

Tilemap::~Tilemap()
{
}

void Tilemap::LoadFile(const wstring& path)
{
	// C 스타일
	if (false)
	{
		FILE* file = nullptr;
		::_wfopen_s(&file, path.c_str(), L"rb"); // read binary
		assert(file != nullptr);

		::fread(&_mapSize.x, sizeof(_mapSize.x), 1, file);
		::fread(&_mapSize.y, sizeof(_mapSize.y), 1, file);

		SetMapSize(_mapSize);

		for (int32 y = 0; y < _mapSize.y; y++)
		{
			for (int32 x = 0; x < _mapSize.x; x++)
			{
				int32 value = -1;
				::fread(&value, sizeof(value), 1, file);
				_tiles[y][x].value = value;
			}
		}
		::fclose(file);
		return;
	}

	// C++ 스타일
	{
		wifstream ifs;

		ifs.open(path);

		ifs >> _mapSize.x;
		ifs >> _mapSize.y;

		SetMapSize(_mapSize);

		for (int32 y = 0; y < _mapSize.y; y++)
		{
			wstring line;
			ifs >> line;

			for (int32 x = 0; x < _mapSize.x; x++)
			{
				_tiles[y][x].value = line[x] - L'0';
			}
		}

		ifs.close();
	}
}

void Tilemap::SaveFile(const wstring& path)
{
	// C 스타일
	if(false)
	{
		FILE* file = nullptr;
		::_wfopen_s(&file, path.c_str(), L"wb"); // write binary // binary 와 text 의 차이?
		assert(file != nullptr);

		::fwrite(&_mapSize.x, sizeof(_mapSize.x), 1, file);
		::fwrite(&_mapSize.x, sizeof(_mapSize.y), 1, file);

		for (int32 y = 0; y < _mapSize.y; y++)
		{
			for (int32 x = 0; x < _mapSize.x; x++)
			{
				int32 value = _tiles[y][x].value;
				::fwrite(&value, sizeof(value), 1, file);
			}
		}
		::fclose(file);
		return;
	}

	// C++ 스타일
	{
		wofstream ofs;
		ofs.open(path);
		ofs << _mapSize.x << endl;
		ofs << _mapSize.y << endl;

		for (int32 y = 0; y < _mapSize.y; y++)
		{
			for (int32 x = 0; x < _mapSize.x; x++)
			{
				ofs << _tiles[y][x].value;
			}

			ofs << endl;
		}

		ofs.close();
	}
}

Tile* Tilemap::GetTileAt(Vec2Int pos)
{
	if (pos.x < 0 || pos.x >= _mapSize.x || pos.y < 0 || pos.y >= _mapSize.y)
		return nullptr;

	return &_tiles[pos.y][pos.x];
}

void Tilemap::SetMapSize(Vec2Int size)
{
	_mapSize = size;

	_tiles = vector<vector<Tile>>(size.y, vector<Tile>(size.x));

	for (int32 y = 0; y < size.y; y++)
	{
		for (int32 x = 0; x < size.x; x++)
		{
			_tiles[y][x] = Tile{ 0 };
		}
	}
}

void Tilemap::SetTileSize(int32 size)
{
	_tileSize = size;
}
