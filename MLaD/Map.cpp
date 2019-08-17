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


