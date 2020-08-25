#define OLC_PGE_APPLICATION

#include "Engine.h"

const int width = 1200;
const int height = 750;

int main()
{
	Engine engine;
	engine.Construct(width, height, 1, 1, false);
	engine.Start();
	return 0;
}


