#define OLC_PGE_APPLICATION

#include "olcPGE/olcPixelGameEngine.h"

class Engine : public olc::PixelGameEngine
{
public:
	Engine()
	{
		sAppName = "Evolution Simul8r";
	}


	bool OnUserCreate()
	{
		return true;
	}

	bool OnUserUpdate(float fElapsedTime)
	{
		return true;
	}
};

int main()
{
	const int width = 800;
	const int height = 600;
	Engine engine;
	engine.Construct(width, height, 1, 1, false);
	engine.Start();
	return 0;
}


