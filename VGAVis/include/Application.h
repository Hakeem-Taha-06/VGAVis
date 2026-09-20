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
};

