#define OLC_PGE_APPLICATION

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
	Engine()
	{
		sAppName = "MLaD";
	}

	Map *m_CurrentMap = nullptr;

	std::vector<int> Path;
	

	olc::Sprite* adhead = nullptr;
	std::string tempName;

	std::vector<Adventurers> advent;

	float Tick = 0;
	float TickTime = 20.f;
	int Day = 1;
	int Hour = 7;

	void DrawTileMap(Map* m_CurrentMap, std::vector<Tile> tiles)
	{
		for (size_t i = 0; i < tiles.size(); i++)
		{
			DrawPartialSprite(tiles[i].x, tiles[i].y, m_CurrentMap->mapsprite, tiles[i].sx * m_CurrentMap->TileWidth, tiles[i].sy * m_CurrentMap->TileHeight, m_CurrentMap->TileWidth, m_CurrentMap->TileHeight);
		}
	}
	
	/*void PopulateNext(Map* m_CurrentMap)
	{
		for (int x = 0; x < m_CurrentMap->mWidth; x++)
		{
			for (int y = 0; y < m_CurrentMap->mHeight; y++)
			{
				if (m_CurrentMap->tiles[y * m_CurrentMap->mWidth + x].y > 0)
				{
					m_CurrentMap->tiles[y * m_CurrentMap->mWidth + x].Next[(y - 1) * m_CurrentMap->mWidth + x] = (y - 1) * m_CurrentMap->mWidth + x;
				}
				if (m_CurrentMap->tiles[y * m_CurrentMap->mWidth + x].y < m_CurrentMap->mHeight - 1)
				{
					m_CurrentMap->tiles[y * m_CurrentMap->mWidth + x].Next[(y + 1) * m_CurrentMap->mWidth + x] = (y + 1) * m_CurrentMap->mWidth + x;
				}
				if (m_CurrentMap->tiles[y * m_CurrentMap->mWidth + x].x > 0)
				{
					m_CurrentMap->tiles[y * m_CurrentMap->mWidth + x].Next[y * m_CurrentMap->mWidth + (x - 1)] = y * m_CurrentMap->mWidth + (x - 1);
				}
				if (m_CurrentMap->tiles[y * m_CurrentMap->mWidth + x].x < m_CurrentMap->mWidth - 1)
				{
					m_CurrentMap->tiles[y * m_CurrentMap->mWidth + x].Next[y * m_CurrentMap->mWidth + (x + 1)] = y * m_CurrentMap->mWidth + (x + 1);
				}
			}
		}
	}*/
	
	/*void PopulateDist(Map* m_CurrentMap)
	{
		for (int x = 0; x < m_CurrentMap->mWidth; x++)
		{
			for (int y = 0; y < m_CurrentMap->mHeight; y++)
			{
				if (m_CurrentMap->tiles[y * m_CurrentMap->mWidth + x].y > 0)
				{
					m_CurrentMap->tiles[y * m_CurrentMap->mWidth + x].Dist[(y - 1) * m_CurrentMap->mWidth + x] = 1;
				}
				if (m_CurrentMap->tiles[y * m_CurrentMap->mWidth + x].y < m_CurrentMap->mHeight - 1)
				{
					m_CurrentMap->tiles[y * m_CurrentMap->mWidth + x].Dist[(y + 1) * m_CurrentMap->mWidth + x] = 1;
				}
				if (m_CurrentMap->tiles[y * m_CurrentMap->mWidth + x].x > 0)
				{
					m_CurrentMap->tiles[y * m_CurrentMap->mWidth + x].Dist[y * m_CurrentMap->mWidth + (x - 1)] = 1;
				}
				if (m_CurrentMap->tiles[y * m_CurrentMap->mWidth + x].x < m_CurrentMap->mWidth - 1)
				{
					m_CurrentMap->tiles[y * m_CurrentMap->mWidth + x].Dist[y * m_CurrentMap->mWidth + (x + 1)] = 1;
				}
			}
		}
	}*/

	/*void FWAlg(Map* m_CurrentMap)
	{
		for (size_t k = 0; k < m_CurrentMap->tiles.size(); k++)
		{
			for (size_t i = 0; i < m_CurrentMap->tiles.size(); i++)
			{
				for (size_t j = 0; j < m_CurrentMap->tiles.size(); j++)
				{
					if (m_CurrentMap->tiles[k].Dist[i][j] > m_CurrentMap->tiles[k].Dist[i][k] + m_CurrentMap->tiles[k].Dist[k][j])
					{
						m_CurrentMap->tiles[k].Dist[i][j] = Dist[i][k] + Dist[k][j];
						Next[i][j] = Next[i][k];
					}
				}
			}
		}
	}*/

	/*void Collision()
	{
		for (int i = 0; i < m_CurrentMap->mWidth; i++)
		{
			for (int j = 0; j < m_CurrentMap->mHeight; j++)
			{
				if ()
			}
		}
		
	}*/

	void EndofDay(int& Day, int& Hour)
	{
		Day++;
		Hour = 7;
	}

	void GameTime(float& Tick, float fElapsedTime, float TickTime, int& Hour)
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

	void DisplayTime(int Day, int Hour)
	{
		DrawString(50, ScreenHeight() - 80, "Day : " + std::to_string(Day), olc::GREEN, 2U);
		DrawString(50, ScreenHeight() - 40, "Time : " + std::to_string(Hour) + ":00", olc::GREEN, 2U);
	}

	void DisplayNumAdvent(std::vector<Adventurers> advent)
	{
		DrawString(ScreenWidth() - 280, ScreenHeight() - 680, "Adventurers : " + std::to_string(advent.size()), olc::GREEN, 2U);
	}

	std::string RandNameMale()
	{
		tempName = std::vector<std::string>{"Tom", "Dick", "Harry", "Jeff", "David", "Sebastien", "Murdoc", "Judd", "Phil", "Mike"}[rand()% 10];
		return tempName;
	}
	std::string RandNameFemale()
	{
		tempName = std::vector<std::string>{"Maureen", "Delilah", "Florence", "Isabelle", "Tamatha", "Susan", "Geraldine", "Rose", "Christine", "Holly"}[rand()% 10];
		return tempName;
	}

	void addAdventurer(std::vector<Adventurers>& advent, std::string& tempName, Map* m_CurrentMap)
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

	void MoveAdventurer(std::vector<Adventurers> advent, std::vector<std::vector<int>> Next, int SelectedTile)
	{
		if (advent.size() > 0 && SelectedTile != NULL)
		{
			int destination = SelectedTile;

			Next[m_CurrentMap->GetIndex(advent[0].px, advent[0].py)][destination];
		}
	}

	/*void testcharvect(std::vector<Adventurers> advent)
	{
		for (int i = 0; i < advent.size(); i++)
		{
			std::cout << "Name : " << advent[i].name << " " << "Health : " << advent[i].Health << std::endl;
			if (advent[i].Gender == 0)
			{
				std::cout << "Gender : " << " Male " << std::endl;
			}
			else if (advent[i].Gender == 1)
			{
				std::cout << "Gender : " << " Female " << std::endl;
			}
		}
	}*/

	void Input(std::vector<Adventurers>& advent)
	{
		if (GetKey(olc::SPACE).bPressed)
		{
			addAdventurer(advent, tempName, m_CurrentMap);
		}

	}


	void DrawHead(olc::Sprite& adhead, std::vector<Adventurers> advent)
	{
		for (size_t i = 0; i < advent.size(); i++)
		{
			DrawPartialSprite(advent[i].px, advent[i].py, &adhead, 0, 0, 32, 30, 1U);
		}
	}



	bool OnUserCreate()
	{
		srand(time(NULL));
		adhead = new olc::Sprite("AdventurerHead.png");
		m_CurrentMap = new mMap1();
		m_CurrentMap->AddTiles(m_CurrentMap->tiles, m_CurrentMap);
		//m_CurrentMap->initialiseDist(m_CurrentMap->tiles);
		//m_CurrentMap->initialiseNext(m_CurrentMap->tiles);
		//PopulateDist(m_CurrentMap);
		//PopulateNext(m_CurrentMap);
		

		return true;
	}

	

	bool OnUserUpdate(float fElapsedTime)
	{

		//int SelectedTileIndex = m_CurrentMap->GetIndex(SelectedTileX, SelectedTileY);

		
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
};

int main()
{
	const int width = 1200;
	const int height = 750;
	Engine engine;
	engine.Construct(width, height, 1, 1, false);
	engine.Start();
	return 0;
}


