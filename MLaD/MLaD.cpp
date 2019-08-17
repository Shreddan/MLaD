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

	const int width = 1200;
	const int height = 750;



	olc::Sprite* adhead;
	olc::Sprite* tilemap;
	Map map;

	std::string tempName;

	std::vector<Adventurers> advent;

	float Tick = 0;
	float TickTime = 20.f;
	int Day = 1;
	int Hour = 7;

	void DrawTileMap(olc::Sprite tileMap)
	{
		for (int i = )
	}
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
		DrawString(50, 650, "Day : " + std::to_string(Day), olc::GREEN, 2U);
		DrawString(50, 700, "Time : " + std::to_string(Hour) + ":00", olc::GREEN, 2U);
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

	void addAdventurer(std::vector<Adventurers>& advent, std::string& tempName)
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
			ad.px = rand() % width;
			ad.py = rand() % height;
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
			addAdventurer(advent, tempName);
		}
	}

	void DrawHead(olc::Sprite& adhead, std::vector<Adventurers> advent)
	{
		for (int i = 0; i < advent.size(); i++)
		{
			DrawPartialSprite(advent[i].px, advent[i].py, &adhead, 0, 0, 32, 30, 1U);
		}
	}

	bool OnUserCreate()
	{
		srand(time(NULL));
		adhead = new olc::Sprite("AdventurerHead.png");
		map.Create("Tileset1.png", tilemap, "Map1");
		return true;
	}

	bool OnUserUpdate(float fElapsedTime)
	{
		Clear(olc::BLACK);
		//DrawTileMap(*tileMap);
		GameTime(Tick, fElapsedTime, TickTime, Hour);
		Input(advent);
		SetPixelMode(olc::Pixel::ALPHA);
		DrawHead(*adhead, advent);
		SetPixelMode(olc::Pixel::NORMAL);
		DisplayTime(Day, Hour);
		return true;
	}
};

int main()
{
	Engine engine;
	engine.Construct(engine.width, engine.height, 1, 1, false);
	engine.Start();
	return 0;
}


