`timescale 1ns / 1ps

module tb_vga;

    reg clk;
    reg rst;
    reg mode_select;
    
    wire vsync;
    wire hsync;
    wire [2:0] rgb;

    vga_controller uut (
        .clk(clk),
        .rst(rst),
        .mode_select(mode_select),
        .vsync(vsync),
        .hsync(hsync),
        .rgb(rgb)
    );

    initial begin
        clk = 0;
        forever #10 clk = ~clk;
    end

    integer fd;
    integer pixel_count = 0;

    // 2-Stage Shift Registers to match the 2-cycle RTL latency
    reg [1:0] video_on_shift = 2'b00;
    reg [1:0] p_clk_shift = 2'b00;

    always @(posedge clk) begin
        video_on_shift <= {video_on_shift[0], uut.sync_inst.video_on};
        p_clk_shift    <= {p_clk_shift[0], uut.sync_inst.pixel_clk};
    end

    wire [7:0] r = rgb[2] ? 8'd255 : 8'd0;
    wire [7:0] g = rgb[1] ? 8'd255 : 8'd0;
    wire [7:0] b = rgb[0] ? 8'd255 : 8'd0;

    initial begin
        fd = $fopen("vga_output.ppm", "w");
        if (fd == 0) begin
            $display("Error: Could not open output file.");
            $finish;
        end
        
        $fwrite(fd, "P3\n640 480\n255\n");

        rst = 1;
        mode_select = 1; // 1 = tilemap Mode, 0 = image Mode
        #100;
        rst = 0;

        $display("Simulation started. Rendering frame...");
        wait(pixel_count == 307200);
        
        $display("Frame completely rendered. Closing file.");
        $fclose(fd);
        $finish;
    end

    // Write to file using the 2-cycle delayed signals
    always @(posedge clk) begin
        if (video_on_shift[1] && !rst && p_clk_shift[1]) begin
            $fwrite(fd, "%0d %0d %0d\n", r, g, b);
            pixel_count = pixel_count + 1;
            
            if (pixel_count % 30720 == 0) begin
                $display("Rendering Progress: %0d%%", (pixel_count / 3072));
            end
        end
    end
    
    initial begin
        #30_000_000; 
        $display("Timeout reached! Something is wrong with the timing.");
        $fclose(fd);
        $finish;
    end
endmodule