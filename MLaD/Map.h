#pragma once
#include "olcPixelGameEngine.h"
#include <deque>

struct Tile
{
	int x;
	int y;
	int idx;
	int sx;
	int sy;
	std::deque<Tile*> neighbours;
	bool isSolid;
	float Local;
	float Global;
	bool Visited = false;
	Tile* parent;
};

class Map
{
public:
	Map();
	~Map();

public:

	

	int mWidth;
	int mHeight;

	const int TileWidth = 32;
	const int TileHeight = 32;


	std::string sName;
	olc::Sprite* mapsprite;

	bool Create(std::string FileData, olc::Sprite* sprite, std::string name);

	int GetIndex(int x, int y);
	bool GetSolid(int x, int y);
	void genNeighbours();

	void AddTiles(std::deque<Tile>& tiles, Map* map);

	std::deque<Tile> tiles;
	

private:
	int *m_indices = nullptr;
	bool *m_solids = nullptr;
};

class mMap1 : public Map
{
public:
	mMap1();

};

