#pragma once


#include "Map.h"

struct Adventurers
{
	enum Gender
	{
		Male,
		Female
	};

	float px = 40;
	float py = 40;

	std::string name;
	int Gender = Male;
	int Level = 1;
	int Health = 0;
	int Strength = 1;
	int Endurance = 1;
	int Dexterity = 1;
	int Agility = 1;
	int Exhaustion = 0;
};

class Engine : public olc::PixelGameEngine
{
public:
	Engine();

	//Algorithm Funcs
	bool aStar(Map* m_CurrentMap, Tile* Start, Tile* End);
	
	//Draw Funcs
	void DrawTileMap(Map* m_CurrentMap, std::deque<Tile> tiles);
	void DisplayTime(int Day, int Hour);
	void DisplayNumAdvent();
	void DrawHead(olc::Sprite& adhead);

	//Time Funcs
	void EndofDay(int& Day, int& Hour);
	void GameTime(float& Tick, float fElapsedTime, float TickTime, int& Hour);

	void DrawMousePos();
	//void test();


	//Name Funcs
	std::string RandNameMale();
	std::string RandNameFemale();

	//Adventurer Funcs
	void addAdventurer(std::string& tempName, Map* m_CurrentMap);
	void MoveAdventurer();
	void Input();

	//olc::vi2d ScreentoWorld(int x, int y);

	
	//Engine Funcs
	bool OnUserCreate();
	bool OnUserUpdate(float fElapsedTime);
	
	//Variables
	Map* currentMap = nullptr;
	olc::Sprite* adhead = nullptr;
	olc::Decal* head = nullptr;
	std::string tempName;
	std::deque<Adventurers> advent;
	Tile* t = nullptr;
	Tile* destination = nullptr;

	int TileX = 0;
	int TileY = 0;
	float Tick = 0;
	float TickTime = 20.f;
	int Day = 1;
	int Hour = 7;

	bool pathComplete = false;
	bool testcomplete = false;
};