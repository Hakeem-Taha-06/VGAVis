#pragma once
#include "Window.h"
#include "PixelData.h"

class Application
{

public:
	Application(int width, int height);
	~Application();

	void run();

private:
	PixelData data;
	Window window;
};
