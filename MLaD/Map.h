#pragma once
#include "olcPGE/olcPixelGameEngine.h"

class Map
{
public:
	Map();
	~Map();

public:
	int mWidth;
	int mHeight;

	std::string sName;
	olc::Sprite* mapsprite;

	bool Create(std::string FileData, olc::Sprite* sprite, std::string name);

	int GetIndex(int x, int y);
	bool GetSolid(int x, int y);

private:
	int *m_indices = nullptr;
	bool *m_solids = nullptr;
};

