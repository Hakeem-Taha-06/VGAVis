#pragma once
#include "Window.h"
#include "Simulator.h"

class Application
{

public:
	Application(int width, int height);
	~Application();

	void run();

private:
	Simulator sim;
	Window window;

	int pixel_x = 0;
	int pixel_y = 0;
	bool video_on = 1;
};

