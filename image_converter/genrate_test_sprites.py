def generate_test_files():
    # 1. Palette: 8 entries (3-bit RGB)
    # Palette 0: Black(0), Red(4), Green(2), Blue(1)
    # Palette 1: Black(0), Cyan(3), Magenta(5), White(7)
    with open("palette.hex", "w") as f:
        palettes = [0, 4, 2, 1, 0, 3, 5, 7]
        for p in palettes:
            f.write(f"{p:01X}\n")

    # 2. Pattern Table: 128 tiles * 8 rows = 1024 lines (16-bit)
    # Tile 0: Solid Color 1
    # Tile 1: Checkerboard (Colors 2 and 3)
    with open("pattern_table.hex", "w") as f:
        for tile_id in range(128):
            for row in range(8):
                if tile_id == 0:
                    val = 0x5555  # 01010101... -> Color index 1
                elif tile_id == 1:
                    val = 0xAAAA if row % 2 == 0 else 0xFFFF # Alternating 10(2) and 11(3)
                else:
                    val = 0x0000  # Blank for unused tiles
                f.write(f"{val:04X}\n")

    # 3. Nametable: 1200 tiles (40x30 screen)
    # Alternates between Tile 0 (Palette 0) and Tile 1 (Palette 1)
    with open("nametable.hex", "w") as f:
        for y in range(30):
            for x in range(40):
                if (x + y) % 2 == 0:
                    tile_id = 0
                    palette = 0
                else:
                    tile_id = 1
                    palette = 1
                
                # Combine 1-bit palette and 7-bit tile_id
                entry = (palette << 7) | tile_id
                f.write(f"{entry:02X}\n")

    print("Test HEX files generated successfully.")

if __name__ == "__main__":
    generate_test_files()