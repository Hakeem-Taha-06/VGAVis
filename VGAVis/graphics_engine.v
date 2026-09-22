module graphics_engine #(
    parameter IMAGE_WIDTH  = 640,
			IMAGE_HEIGHT = 480,
			TILES_X      = 40,
			TILES_Y      = 30,
			NUM_TILES    = TILES_X * TILES_Y,   
			NUM_PATTERNS = 128            
)(
    input  wire  clk,  rst,  mode_select, video_on,
    input  wire [9:0]  pixel_x, pixel_y,
    output wire [2:0]  rgb
);

    wire [9:0] logical_x = pixel_x >> 1;
    wire [9:0] logical_y = pixel_y >> 1;

    reg video_on_d1, video_on_d2;
    reg mode_select_d1, mode_select_d2;

    always @(posedge clk)
        if (rst) begin
            video_on_d1    <= 1'b0;
            video_on_d2    <= 1'b0;
            mode_select_d1 <= 1'b0;
            mode_select_d2 <= 1'b0;
        end else begin
            video_on_d1    <= video_on;
            video_on_d2    <= video_on_d1;
            mode_select_d1 <= mode_select;
            mode_select_d2 <= mode_select_d1;
        end


    // Image Mode
    reg [2:0] framebuffer [0:76799] /*verilator public*/;

    initial begin
        $readmemh("initial_image.hex", framebuffer);
    end

    wire in_bounds = (pixel_x < IMAGE_WIDTH) && (pixel_y < IMAGE_HEIGHT);

    wire [16:0] img_addr;
    assign img_addr = ({7'b0, pixel_y} >> 1) * (IMAGE_WIDTH/2) + ({7'b0, pixel_x} >> 1);

    reg [2:0] image_rgb_stage1;   
    reg [2:0] image_rgb_stage2; 

    always @(posedge clk)
        if (rst) begin
            image_rgb_stage1 <= 3'b0;
            image_rgb_stage2 <= 3'b0;
        end else begin
            image_rgb_stage1 <= (in_bounds) ? framebuffer[img_addr] : 3'b0;
            image_rgb_stage2 <= image_rgb_stage1;
        end


    // Sprite Mode
    wire [5:0] tile_x  = logical_x[8:3];
    wire [4:0] tile_y  = logical_y[8:3];
    wire [2:0] ntile_x = logical_x[2:0];
    wire [2:0] ntile_y = logical_y[2:0];

    // nametable address
    wire [10:0] nametable_addr = tile_y * TILES_X + tile_x;

    reg [7:0] nametable [0:NUM_TILES-1] /*verilator public*/;
    initial begin
        $readmemh("nametable.hex", nametable);
    end

    // compute pattern address
    reg [7:0] nametable_out;
    reg [2:0] ntile_x_d1, ntile_x_d2;
    reg [2:0] ntile_y_d1;

    always @(posedge clk) begin
        nametable_out <= nametable[nametable_addr];
        ntile_x_d1    <= ntile_x;
        ntile_y_d1    <= ntile_y;
    end

    wire [6:0] tile_id     = nametable_out[6:0];
    wire       palette_sel = nametable_out[7];

    wire [9:0] pattern_addr = {tile_id, ntile_y_d1};

    reg [15:0] pattern_table [0:(NUM_PATTERNS*8)-1] /*verilator public*/;
    initial begin
        $readmemh("pattern_table.hex", pattern_table);
    end

    // extract color index
    reg [15:0] pattern_row;
    reg        palette_sel_d1;

    always @(posedge clk) begin
        pattern_row    <= pattern_table[pattern_addr];
        palette_sel_d1 <= palette_sel;
        ntile_x_d2     <= ntile_x_d1;
    end

    // 2 bits/pixel, MSB-first across the 8 pixels of the row
    wire [1:0] color_index = pattern_row[15 - 2*ntile_x_d2 -: 2];

    // palette memory
    reg [2:0] palette_mem [0:7] /*verilator public*/;
    initial begin
        $readmemh("palette.hex", palette_mem);
    end

    wire [2:0] sprite_rgb = palette_mem[{palette_sel_d1, color_index}];


    // output aligned after 2 cycles latency
    assign rgb = (!video_on_d2) ? 3'b000 :
                 (mode_select_d2 ? sprite_rgb : image_rgb_stage2);

endmodule