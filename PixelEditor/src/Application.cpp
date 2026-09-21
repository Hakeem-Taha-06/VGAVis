#include "Application.h"

Application::Application(int width, int height) : window(width, height){

}

Application::~Application() {

}

void Application::run() {

	while (!window.shouldExit()) {
		window.startFrame();
		window.render(data);
		window.endFrame();
	}
}
