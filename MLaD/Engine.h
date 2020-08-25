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
	
	//Draw Funcs
	void DrawTileMap(Map* m_CurrentMap, std::vector<Tile> tiles);
	void DisplayTime(int Day, int Hour);
	void DisplayNumAdvent(std::vector<Adventurers> advent);
	void DrawHead(olc::Sprite& adhead, std::vector<Adventurers> advent);

	//Time Funcs
	void EndofDay(int& Day, int& Hour);
	void GameTime(float& Tick, float fElapsedTime, float TickTime, int& Hour);
	

	//Name Funcs
	std::string RandNameMale();
	std::string RandNameFemale();

	//Adventurer Funcs
	void addAdventurer(std::vector<Adventurers>& advent, std::string& tempName, Map* m_CurrentMap);
	void MoveAdventurer(std::vector<Adventurers> advent, std::vector<std::vector<int>> Next, int SelectedTile);
	void Input(std::vector<Adventurers>& advent);
	
	//Engine Funcs
	bool OnUserCreate();
	bool OnUserUpdate(float fElapsedTime);
	
private:
	Map* m_CurrentMap = nullptr;
	olc::Sprite* adhead = nullptr;
	olc::Decal* head = nullptr;
	std::string tempName;
	std::vector<Adventurers> advent;
	float Tick = 0;
	float TickTime = 20.f;
	int Day = 1;
	int Hour = 7;
};