from PIL import Image

def generate_hex(input_path, output_path):
    # 1. Open and resize to the pixel-doubled framebuffer dimensions (320x240)
    img = Image.open(input_path).convert("RGB")
    img = img.resize((320, 240), Image.Resampling.LANCZOS)
    
    pixels = img.load()

    with open(output_path, "w") as f:
        for y in range(img.height):
            for x in range(img.width):
                r, g, b = pixels[x, y]
                
                # 2. Quantize each channel to 1 bit (threshold at 128)
                r_bit = 1 if r >= 128 else 0
                g_bit = 1 if g >= 128 else 0
                b_bit = 1 if b >= 128 else 0
                
                # 3. Construct 3-bit color (R=bit2, G=bit1, B=bit0)
                color_val = (r_bit << 2) | (g_bit << 1) | b_bit
                
                # 4. Write as a single hex digit (0-7) followed by a newline
                f.write(f"{color_val:X}\n")

if __name__ == "__main__":
    generate_hex("L33-1.png", "image.hex")
    print("Successfully generated image.hex for 320x240 framebuffer.")