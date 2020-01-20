#include "Map.h"



Map::Map()
{
	mapsprite = nullptr;
	mWidth = 0;
	mHeight = 0;
	m_solids = nullptr;
	m_indices = nullptr;
}


Map::~Map()
{
	delete[] m_solids;
	delete[] m_indices;
}

int Map::GetIndex(int x, int y)
{
	if (x >= 0 && x < mWidth && y >= 0 && y < mHeight)
	{
		return m_indices[y*mWidth + x];
	}
	else
	{
		return 0;
	}
}

bool Map::GetSolid(int x, int y)
{
	if (x >= 0 && x < mWidth && y >= 0 && y < mHeight)
	{
		return m_solids[y*mWidth + x];
	}
	else
	{
		return true;
	}
}

void Map::AddTiles(std::vector<Tile>& tiles, Map* map)
{
	for (int i = 0; i < mWidth; i++)
	{
		for (int j = 0; j < mHeight; j++)
		{
			Tile t;
			t.idx = map->GetIndex(i, j);
			t.sx = t.idx % 9;
			t.sy = t.idx / 9;
			t.x = i * TileWidth;
			t.y = j * TileHeight;

			tiles.emplace_back(t);

		}
	}
}

//void Map::initialiseDist(std::vector<Tile> &map)
//{
//	
//	for (size_t i = 0; i < map.size(); i++)
//	{	
//		map[i].Dist.reserve(map.size());
//		for (size_t j = 0; j < map.size(); j++)
//		{
//			map[i].Dist.push_back(INFINITY);
//		}
//	}
//}
//
//void Map::initialiseNext(std::vector<Tile> &map)
//{
//	for (size_t i = 0; i < map.size(); i++)
//	{
//		map[i].Next.reserve(map.size());
//		for (size_t j = 0; j < map.size(); j++)
//		{
//			map[i].Next.push_back(-1);
//		}
//	}
//}



bool Map::Create(std::string FileData, olc::Sprite* sprite, std::string name)
{
	sName = name;
	mapsprite = sprite;
	std::ifstream data(FileData, std::ios::in || std::ios::binary);
		if (data.is_open())
		{
			data >> mWidth >> mHeight;
			m_solids = new bool[mWidth * mHeight];
			m_indices = new int[mWidth * mHeight];
			for (int i = 0; i < mWidth * mHeight; i++)
			{
				data >> m_indices[i];
				data >> m_solids[i];
			}

			return true;
		}
		return false;
}

mMap1::mMap1()
{
	Create("MainMap.txt", new olc::Sprite("Tileset1.png"), "Main");
}




