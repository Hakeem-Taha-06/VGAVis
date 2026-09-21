module vga_controller(
	input wire clk,
	input wire rst,
	input wire mode_select,
	output wire vsync,
	output wire hsync,
	output wire [2:0] rgb
);

	wire video_on /*verilator public*/;
	wire [9:0] pixel_x /*verilator public*/;
	wire [9:0] pixel_y /*verilator public*/;

	wire vsync_raw, hsync_raw;

	vga_sync sync_inst(
		.clk(clk),
		.rst(rst),
		.vsync(vsync_raw),
		.hsync(hsync_raw),
		.pixel_x(pixel_x),
		.pixel_y(pixel_y),
		.video_on(video_on)
	);

	graphics_engine gfx_inst(
		.pixel_x(pixel_x),
		.pixel_y(pixel_y),
		.video_on(video_on),
	 	.mode_select(mode_select),
		.clk(clk),
		.rst(rst),
		.rgb(rgb)
	);

	// making two clocks latency
	reg [1:0] vsync_shift = 2'b00;
	reg [1:0] hsync_shift = 2'b00;

	always @(posedge clk) begin
		vsync_shift <= {vsync_shift[0], vsync_raw};
		hsync_shift <= {hsync_shift[0], hsync_raw};
	end

	assign vsync = vsync_shift[1];
	assign hsync = hsync_shift[1];
endmodule