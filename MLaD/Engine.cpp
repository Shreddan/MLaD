#include "Engine.h"

Engine::Engine()
{
	sAppName = "MLaD";
}

void Engine::EndofDay(int& Day, int& Hour)
{
	Day++;
	Hour = 7;
}

void Engine::GameTime(float& Tick, float fElapsedTime, float TickTime, int& Hour)
{
	Tick += fElapsedTime;
	if (Tick >= TickTime)
	{
		Hour++;
		if (Hour == 19)
		{
			EndofDay(Day, Hour);
		}
		Tick = 0;
	}
}

void Engine::DisplayTime(int Day, int Hour)
{
	DrawString(50, ScreenHeight() - 80, "Day : " + std::to_string(Day), olc::GREEN, 2U);
	DrawString(50, ScreenHeight() - 40, "Time : " + std::to_string(Hour) + ":00", olc::GREEN, 2U);
}

void Engine::DisplayNumAdvent(std::vector<Adventurers> advent)
{
	DrawString(ScreenWidth() - 280, ScreenHeight() - 680, "Adventurers : " + std::to_string(advent.size()), olc::GREEN, 2U);
}

std::string Engine::RandNameMale()
{
	tempName = std::vector<std::string>{ "Tom", "Dick", "Harry", "Jeff", "David", "Sebastien", "Murdoc", "Judd", "Phil", "Mike" } [rand() % 10] ;
	return tempName;
}

std::string Engine::RandNameFemale()
{
	tempName = std::vector<std::string>{ "Maureen", "Delilah", "Florence", "Isabelle", "Tamatha", "Susan", "Geraldine", "Rose", "Christine", "Holly" } [rand() % 10] ;
	return tempName;
}

void Engine::addAdventurer(std::vector<Adventurers>& advent, std::string& tempName, Map* m_CurrentMap)
{
	if (advent.size() < 20)
	{
		Adventurers ad;
		int GenderDec;
		GenderDec = rand() % 10;
		if (GenderDec < 5)
		{
			ad.Gender = ad.Male;
			ad.name = RandNameMale();
		}
		else if (GenderDec > 5)
		{
			ad.Gender = ad.Female;
			ad.name = RandNameFemale();
		}
		ad.px = rand() % m_CurrentMap->mWidth * m_CurrentMap->TileWidth;
		ad.py = rand() % m_CurrentMap->mHeight * m_CurrentMap->TileHeight;
		ad.Health = rand() % 50 + 15;
		ad.Strength = rand() % 10;
		ad.Endurance = rand() % 10;
		ad.Dexterity = rand() % 10;
		ad.Endurance = rand() % 10;
		ad.Exhaustion = 0;

		advent.emplace_back(ad);
	}
	else
	{
		return;
	}
}

void Engine::MoveAdventurer(std::vector<Adventurers> advent, std::vector<std::vector<int>> Next, int SelectedTile)
{
	if (advent.size() > 0 && SelectedTile != NULL)
	{
		int destination = SelectedTile;

		Next[m_CurrentMap->GetIndex(advent[0].px, advent[0].py)][destination];
	}
}

void Engine::Input(std::vector<Adventurers>& advent)
{
	if (GetKey(olc::SPACE).bPressed)
	{
		addAdventurer(advent, tempName, m_CurrentMap);
	}
}

void Engine::DrawHead(olc::Sprite& adhead, std::vector<Adventurers> advent)
{
	for (size_t i = 0; i < advent.size(); i++)
	{
		DrawPartialDecal(olc::vf2d(advent[i].px, advent[i].py), head, olc::vf2d(0, 0), olc::vf2d(32, 30), olc::vf2d(1.f, 1.f), olc::WHITE);
	}
}


bool Engine::OnUserCreate()
{
	srand(time(NULL));
	adhead = new olc::Sprite("AdventurerHead.png");
	head = new olc::Decal(adhead);
	m_CurrentMap = new mMap1();
	m_CurrentMap->AddTiles(m_CurrentMap->tiles, m_CurrentMap);

	return true;
}

bool Engine::OnUserUpdate(float fElapsedTime)
{
	{
		int TileX = GetMouseX() / m_CurrentMap->TileWidth;
		int TileY = GetMouseY() / m_CurrentMap->TileHeight;


		Clear(olc::Pixel(154, 43, 7));
		DrawTileMap(m_CurrentMap, m_CurrentMap->tiles);
		GameTime(Tick, fElapsedTime, TickTime, Hour);
		Input(advent);
		SetPixelMode(olc::Pixel::ALPHA);
		DrawHead(*adhead, advent);

		//MoveAdventurer(advent, Next, SelectedTileX, SelectedTileY);
		SetPixelMode(olc::Pixel::NORMAL);
		DisplayTime(Day, Hour);
		DisplayNumAdvent(advent);

		return true;
	}
}

void Engine::DrawTileMap(Map* m_CurrentMap, std::vector<Tile> tiles)
{
	for (size_t i = 0; i < tiles.size(); i++)
	{
		DrawPartialSprite(tiles[i].x, tiles[i].y, m_CurrentMap->mapsprite, tiles[i].sx * m_CurrentMap->TileWidth, tiles[i].sy * m_CurrentMap->TileHeight, m_CurrentMap->TileWidth, m_CurrentMap->TileHeight);
	}
}
