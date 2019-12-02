#include "time.h"

static float startTime;
static float oldTime;
static float oldFPSTime;

unsigned Time::frameCount = 0;
float Time::time = 0.0f;
float Time::deltaTime = 0.0f;
float Time::fps = 0.0f;


void Time::Start()
{
	startTime = static_cast<float>(clock())/1000.0;
	oldTime = startTime;
	oldFPSTime = 0.0f;
}

void Time::Update()
{
	float now = static_cast<float>(clock())/1000.0;
	time = now - startTime;

	frameCount++;
	if (time - oldTime >= 1.0f) 
	{
		fps = frameCount;
		std::cout << fps << std::endl;
		oldTime = time;
		frameCount = 0;
	}
}