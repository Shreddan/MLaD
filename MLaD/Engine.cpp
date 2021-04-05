#include "Engine.h"

Engine::Engine()
{
	sAppName = "MLaD";
}

bool Engine::aStar(Map* m_CurrentMap, Tile* Start, Tile* End)
{
	//aStarDone = false;
	std::cout << "Calculating A*" << std::endl;
	for (int x = 0; x < m_CurrentMap->mWidth; x++)
	{
		for (int y = 0; y < m_CurrentMap->mHeight; y++)
		{
			m_CurrentMap->tiles[y * m_CurrentMap->mWidth + x].Local = INFINITY;
			m_CurrentMap->tiles[y * m_CurrentMap->mWidth + x].Global = INFINITY;
			m_CurrentMap->tiles[y * m_CurrentMap->mWidth + x].Visited = false;
			m_CurrentMap->tiles[y * m_CurrentMap->mWidth + x].parent = nullptr;
		}
	}

	//std::cout << "Reset variables" << std::endl;

	auto distance = [](Tile* a, Tile* b)
	{
		return sqrtf((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
	};

	auto heuristic = [distance](Tile* a, Tile* b)
	{
		return distance(a, b);
	};

	

	Tile* currTile = Start;
	//std::cout << "CurrTile : " << currTile->x << " " << currTile->y << std::endl;
	//std::cout << "Adventurer 0 : " << advent[0].px << " " << advent[0].py << std::endl;
	if (currTile == nullptr)
	{
		std::cout << "Current tile is NULL" << std::endl;
	}
	currTile->Local = 0.0f;
	currTile->Global = heuristic(Start, End);
	std::cout << currTile->Global << std::endl;

	std::cout << "Setting Current Tile + Global Goal" << std::endl;

	std::list<Tile*> uTiles;
	uTiles.push_back(Start);

	std::cout << "Created Node List" << std::endl;

	while (!uTiles.empty() && currTile != End)
	{
		uTiles.sort([](const Tile* lhs, const Tile* rhs) {return lhs->Global < rhs->Global; });

		while (!uTiles.empty() && uTiles.front()->Visited)
		{
			uTiles.pop_front();
			//std::cout << "Untested Tiles : " << uTiles.size() << std::endl;
		}

		if (uTiles.empty())
		{
			std::cout << "Job done!" << std::endl;
			break;
		}

		currTile = uTiles.front();
		currTile->Visited = true;

		for (auto tNeighbour : currTile->neighbours)
		{
			if (!tNeighbour->Visited && tNeighbour->isSolid == 0)
			{
				uTiles.push_back(tNeighbour);
			}

			float pLowerGoal = currTile->Local + distance(currTile, tNeighbour);
			if (pLowerGoal < tNeighbour->Local)
			{
				tNeighbour->parent = currTile;
				tNeighbour->Local = pLowerGoal;
	
				tNeighbour->Global = tNeighbour->Local + heuristic(tNeighbour, End);
			}
		}
	}
	return true;
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

void Engine::DrawMousePos()
{
	DrawStringDecal(olc::vi2d(GetMouseX(), GetMouseY()), std::to_string(GetMouseX() / currentMap->TileWidth) + "  " + std::to_string(GetMouseY() / currentMap->TileHeight), olc::WHITE);
}

void Engine::DisplayTime(int Day, int Hour)
{
	DrawStringDecal(olc::vi2d(50, ScreenHeight() - 80), "Day : " + std::to_string(Day), olc::GREEN, olc::vf2d(2.f, 2.f));
	DrawStringDecal(olc::vi2d(50, ScreenHeight() - 40), "Time : " + std::to_string(Hour) + ":00", olc::GREEN, olc::vf2d(2.f, 2.f));
}

void Engine::DisplayNumAdvent()
{
	DrawStringDecal(olc::vi2d(ScreenWidth() - 280, ScreenHeight() - 680), "Adventurers : " + std::to_string(advent.size()), olc::GREEN, olc::vf2d(2.f, 2.f));
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

void Engine::addAdventurer(std::string& tempName, Map* m_CurrentMap)
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

void Engine::MoveAdventurer()
{
	if (advent.size() > 0 && destination != nullptr)
	{

		Tile* p = destination;
		std::cout << p->x << " " << p->y << std::endl;
		if (p != nullptr)
		{
			if (advent[0].px <= p->x + (currentMap->TileWidth / 2))
			{
				advent[0].px += 5;
			}
			else if (advent[0].px >= p->x)
			{
				advent[0].px -= 5;
			}
			else if (advent[0].py <= p->y)
			{
				advent[0].py += 5;

			}
			else if (advent[0].py >= p->y)
			{
				advent[0].py -= 5;
			}

			if (p->parent != nullptr && p->x == p->parent->x && p->y == p->parent->y)
			{
				p = p->parent;
			}
		}
		
	}
		
}

void Engine::Input()
{
	if (GetKey(olc::SPACE).bPressed)
	{
		addAdventurer(tempName, currentMap);
	}
	else if (GetMouse(0).bReleased)
	{
		TileX = GetMouseX() / currentMap->TileWidth;
		TileY = GetMouseY() / currentMap->TileHeight;
		if (TileX >= 0 && TileX < currentMap->mWidth)
		{
			if (TileY >= 0 && TileY <= (currentMap->mHeight * currentMap->TileHeight))
			{
				t = &currentMap->tiles[TileY * currentMap->mHeight + TileX];
				std::cout << "Start : " << t->x << " " << t->y << std::endl;
				if (advent.size() > 0)
				{
					
					destination = &currentMap->tiles[advent[0].py / currentMap->TileHeight * currentMap->mWidth + advent[0].px / currentMap->TileWidth];
					
				}
				//currentMap->genNeighbours();
				std::cout << "Destination : " << destination->x << "  " << destination->y << std::endl;
				aStar(currentMap, t, destination);
			}
		}
		//aStar(currentMap, t, destination);
		
	}
}



//olc::vi2d Engine::ScreentoWorld(int x, int y)
//{
//	
//}

void Engine::DrawHead(olc::Sprite& adhead)
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
	currentMap = new mMap1();
	currentMap->AddTiles(currentMap->tiles, currentMap);
	currentMap->genNeighbours();
	return true;
}

bool Engine::OnUserUpdate(float fElapsedTime)
{
	
	Clear(olc::Pixel(154, 43, 7));
	DrawTileMap(currentMap, currentMap->tiles);
	GameTime(Tick, fElapsedTime, TickTime, Hour);

	
	Input();
	DrawHead(*adhead);
	
	DisplayTime(Day, Hour);
	DisplayNumAdvent();
	DrawMousePos();

	if (TileX >= 0 && TileX < currentMap->TileWidth * currentMap->mWidth - 1)
	{
		DrawRect(olc::vi2d(TileX * currentMap->TileWidth, TileY * currentMap->TileHeight), olc::vi2d(currentMap->TileWidth, currentMap->TileHeight), olc::BLUE);
	}

	MoveAdventurer();
	return true;
}

void Engine::DrawTileMap(Map* m_CurrentMap, std::deque<Tile> tiles)
{
	for (size_t i = 0; i < tiles.size(); i++)
	{
		DrawPartialSprite(tiles[i].x, tiles[i].y, m_CurrentMap->mapsprite, tiles[i].sx * m_CurrentMap->TileWidth, tiles[i].sy * m_CurrentMap->TileHeight, m_CurrentMap->TileWidth, m_CurrentMap->TileHeight);
	}
}
