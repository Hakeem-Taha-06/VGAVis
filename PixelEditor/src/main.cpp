#include "Application.h"

int main(int argc, char** argv) {

	Application* a = new Application(1600, 1200);

	a->run();

	delete a;

	return 0;
}
