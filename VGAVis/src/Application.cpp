#include "Application.h"

Application::Application(int width, int height) : window(width, height){

}

Application::~Application() {

}

void Application::run() {

	while (!window.shouldExit()) {

        for (int i = 0; i < 10000; i++) {
            // Emulate vga_sync outputs
            uint16_t final_x = (pixel_x < 640) ? pixel_x : 0;
            uint16_t final_y = (pixel_y < 480) ? pixel_y : 0;
            bool video_on = (pixel_x < 640 && pixel_y < 480) ? 1 : 0;

            sim.setPixel(final_x, final_y, video_on);

            sim.Update();

            if (pixel_x < 640) {
                pixel_x++;
            }
            else {
                pixel_x = 0;
                if (pixel_y < 480) {
                    pixel_y++;
                }
                else {
                    pixel_y = 0;
                }
            }
        }

		window.startFrame();
		window.render(sim);
		window.endFrame();
	}
}
