module vga_sync #(
    parameter
    // Horizontal Specs
    h_visible = 640, h_front_porch = 16,  h_sync_pulse = 96,  h_back_porch = 48,
            
            h_edge = (h_visible + h_front_porch + h_sync_pulse + h_back_porch),

    // Vertical Specs
    v_visible = 480, v_front_porch = 10, v_sync_pulse = 2, v_back_porch = 33,

            v_edge = (v_visible + v_front_porch + v_sync_pulse + v_back_porch)
) (
   input clk, rst,
   output [9:0] pixel_x, pixel_y,
   output video_on, hsync, vsync
);


// counters, x,y
reg [9:0] h_count = 0, v_count = 0;

// halfing frequency clock (لسه عايز أشوف الطريقة التانية)
reg pixel_clk = 0;
always @(posedge clk) begin
    if (rst) pixel_clk <= 0;
    else pixel_clk <= ~pixel_clk;
end


always @(posedge clk) 

    if (rst) begin
        h_count <= 0;
        v_count <= 0;
    end

    else if (pixel_clk) begin

        if (h_count==h_edge-1) begin 
            h_count <= 0;

            if (v_count==v_edge-1) v_count<=0;
            else v_count <= v_count+1;

        end

        else h_count <= h_count+1;

    end

assign pixel_x = h_count, pixel_y = v_count;

assign video_on = (h_count < h_visible) & (v_count < v_visible);

// sync signals (Active low)
assign hsync    = ~((h_count >= (h_visible + h_front_porch)) & (h_count < (h_visible + h_front_porch + h_sync_pulse)));
assign vsync    = ~((v_count >= (v_visible + v_front_porch)) & (v_count < (v_visible + v_front_porch + v_sync_pulse)));
    
endmodule