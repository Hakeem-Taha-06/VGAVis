module graphics_engine #(
	parameter IMAGE_WIDTH = 640,
	parameter IMAGE_HEIGHT = 480
)(
	input wire [9:0] pixel_x,
	input wire [9:0] pixel_y,
	input wire video_on,
	input wire clk,
	input wire rst,
	output reg [2:0] rgb
);
	
	// 320 * 240 memory (the cyclone iv wouldn't fit 640*480*3 bits)
	reg [2:0] framebuffer [0:76799] /*verilator public*/;

	initial
	begin
		$readmemh("initial_image.hex",framebuffer);
	end

	wire in_bounds = (pixel_x < IMAGE_WIDTH) && (pixel_y < IMAGE_HEIGHT);

	// enough bits for 320*240 addresses
	wire [16:0] addr;

	// by shifting the x and y values, every pixel is essentially doubled in size, to fit the whole 640*480 screen
	// we divide the image width by 2 because the framebuffer only holds 320*240 pixels
	assign addr = ({7'b0, pixel_y} >> 1)*(IMAGE_WIDTH/2) + ({7'b0, pixel_x} >> 1);

	always @(posedge clk)
	begin
		if (rst) 
		begin
			rgb <= 3'b0;
		end
		else if(video_on && in_bounds)
		begin
			rgb <= framebuffer[addr];
		end
		else 
		begin
			rgb <= 3'b0;
		end
	end


endmodule
