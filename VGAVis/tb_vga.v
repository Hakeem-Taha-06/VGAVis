`timescale 1ns / 1ps

module tb_vga;

    // inputs
    reg clk;
    reg rst;
    
    // outputs
    wire vsync;
    wire hsync;
    wire [2:0] rgb;

    // Instantiate the VGA controller
    vga_controller uut (
        .clk(clk),
        .rst(rst),
        .vsync(vsync),
        .hsync(hsync),
        .rgb(rgb)
    );

    // Clock generation
    initial begin
        clk = 0;
        forever #10 clk = ~clk;
    end

    integer fd;
    integer pixel_count = 0;

    // Delay the video_on signal by one clock cycle to ensure we capture the correct pixel data
    reg video_on_d = 0;
    always @(posedge clk) begin
        video_on_d <= uut.sync_inst.video_on;
    end

    // determine the RGB values based on the 3-bit rgb output
    wire [7:0] r = rgb[2] ? 8'd255 : 8'd0;
    wire [7:0] g = rgb[1] ? 8'd255 : 8'd0;
    wire [7:0] b = rgb[0] ? 8'd255 : 8'd0;

    initial begin
        // open the output file for writing
        fd = $fopen("vga_output.ppm", "w");
        if (fd == 0) begin
            $display("Error: Could not open output file.");
            $finish;
        end
        
        // writing PPM header
        // P3: RGB format
        // 640 480: screen resolution
        // 255: color depth
        $fwrite(fd, "P3\n640 480\n255\n");

        // Reset logic
        rst = 1;
        #100;
        rst = 0;

        $display("Simulation started. Rendering frame...");

        // الانتظار حتى يتم رسم إطار كامل (640 × 480 = 307200 بكسل)
        wait(pixel_count == 307200);
        
        $display("Frame completely rendered. Closing file.");
        $fclose(fd);
        $finish;
    end

    // getting the pixel clock from the uut's sync_inst
    wire p_clk = uut.sync_inst.pixel_clk;

    // writing to the ppm file
    always @(posedge clk) begin
        if (video_on_d && !rst && p_clk) begin
            $fwrite(fd, "%0d %0d %0d\n", r, g, b);
            pixel_count = pixel_count + 1;
            
            if (pixel_count % 30720 == 0) begin
                $display("Rendering Progress: %0d%%", (pixel_count / 3072));
            end
        end
    end
    

    initial begin
        #30_000_000; // ِAvoidin infinite simulation, set a timeout of 30ms (30,000,000 ns)
        $display("Timeout reached! Something is wrong with the timing.");
        $fclose(fd);
        $finish;
    end

endmodule