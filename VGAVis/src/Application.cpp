#include "Application.h"

Application::Application(int width, int height) : window(width, height){

}

Application::~Application() {

}

void Application::run() {

	while (!window.shouldExit()) {

        for (int i = 0; i < window.sim_speed; i++) {
            sim.Update();
        }

		window.startFrame();
		window.render(sim);
		window.endFrame();
	}
}
