#include "Application.h"
#include "verilated.h"

int main(int argc, char** argv) {

	// Pass command line arguments to the Verilator runtime
	Verilated::commandArgs(argc, argv);

	Application* a = new Application(1600, 1200);

	a->run();

	delete a;

	return 0;
}
