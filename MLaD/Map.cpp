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
		return m_indices[y * mWidth + x];
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

void Map::genNeighbours()
{
	for (int x = 0; x < mWidth; x++)
	{
		for (int y = 0; y < mHeight; y++)
		{
			if (y > 0)
			{
				tiles[y * mWidth + x].neighbours.push_back(&tiles[(y - 1) * mWidth + (x + 0)]);
			}
			if (y < mHeight - 1)
			{
				tiles[y * mWidth + x].neighbours.push_back(&tiles[(y + 1) * mWidth + (x + 0)]);
			}
			if (x > 0)
			{
				tiles[y * mWidth + x].neighbours.push_back(&tiles[(y + 0) * mWidth + (x - 1)]);
			}
			if (x < mWidth - 1)
			{
				tiles[y * mWidth + x].neighbours.push_back(&tiles[(y + 0) * mWidth + (x + 1)]);
			}
		}
	}
}

void Map::AddTiles(std::deque<Tile>& tiles, Map* map)
{
	for (int i = 0; i < mWidth; i++)
	{
		for (int j = 0; j < mHeight; j++)
		{
			Tile t;
			t.idx = map->GetIndex(i, j);
			t.isSolid = map->GetSolid(i, j);
			t.sx = t.idx % 9;
			t.sy = t.idx / 9;
			t.x = i * TileWidth;
			t.y = j * TileHeight;
			t.Global = INFINITY;
			t.Local = INFINITY;

			tiles.emplace_back(t);

		}
	}
}


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




