#include "Application.h"

Application::Application(int width, int height) : window(width, height){

}

Application::~Application() {

}

void Application::run() {
	while (!window.shouldExit()) {

		// Advance the Verilated model by one clock cycle for this frame
		sim.Update();

		window.startFrame();
		window.render(sim);
		window.endFrame();
	}
}
