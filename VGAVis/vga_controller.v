module vga_controller(
	input wire clk,
	input wire rst,
	output wire vsync,
	output wire hsync,
	output wire [2:0] rgb
);

	wire video_on /*verilator public*/;
	wire [9:0] pixel_x /*verilator public*/;
	wire [9:0] pixel_y /*verilator public*/;
	vga_sync sync_inst(
		.clk(clk),
		.rst(rst),
		.vsync(vsync),
		.hsync(hsync),
		.pixel_x(pixel_x),
		.pixel_y(pixel_y),
		.video_on(video_on)
	);

	graphics_engine gfx_inst(
		.pixel_x(pixel_x),
		.pixel_y(pixel_y),
		.video_on(video_on),
		.clk(clk),
		.rst(rst),
		.rgb(rgb)
	);

endmodule