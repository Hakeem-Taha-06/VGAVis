"""
Generates cool-looking pattern_table.hex / nametable.hex / palette.hex files
for the Tilemap Mode showcase, in the exact format the RTL's $readmemh
expects (matches the existing pattern_table.hex / nametable.hex / palette.hex
already in the project):

  pattern_table.hex : 1024 lines (128 tiles x 8 rows), one 4-hex-digit
                       16-bit word per line (2 bits/pixel x 8 pixels/row,
                       MSB-first: bits [15:14] = leftmost pixel).
  nametable.hex      : 1200 lines (40 x 30 screen tiles, row-major),
                       one 2-hex-digit byte per line = (palette_sel << 7) | tile_id.
  palette.hex        : 8 lines, one hex digit per line (address =
                       (palette_sel << 2) | color_index), value = one of
                       the 8 fixed 1-bit-per-channel VGA colors below.

Usage:
    python generate_patterns_2.py --pattern fractal
    python generate_patterns_2.py --pattern rings --out-dir ./demo1
    python generate_patterns_2.py --pattern all      # writes one folder per effect

Available --pattern effects: checkerboard, stripes, fractal, rings, scenery,
                              all_tiles, waves, spiral, noise, cityscape, 
                              maze, space, mega_image, all
"""

import argparse
import math
import os

# ---------------------------------------------------------------------------
# Fixed project constants
# ---------------------------------------------------------------------------
SCREEN_TILES_X = 40
SCREEN_TILES_Y = 30
TILE_SIZE      = 8
MAX_TILES      = 128
COLORS_PER_PAL = 4
PALETTE_COUNT  = 2

BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE = range(8)

# ---------------------------------------------------------------------------
# Tile building blocks
# ---------------------------------------------------------------------------

def tile_blank(): return [[0] * TILE_SIZE for _ in range(TILE_SIZE)]
def tile_solid(c): return [[c] * TILE_SIZE for _ in range(TILE_SIZE)]

def tile_checker(c1, c2, block=1):
    return [[c1 if ((x // block + y // block) % 2 == 0) else c2
             for x in range(TILE_SIZE)] for y in range(TILE_SIZE)]

def tile_diag_stripes(c1, c2, width=2, backslash=False):
    grid = []
    for y in range(TILE_SIZE):
        row = []
        for x in range(TILE_SIZE):
            d = (x - y) if backslash else (x + y)
            row.append(c1 if (d // width) % 2 == 0 else c2)
        grid.append(row)
    return grid

def tile_h_stripes(c1, c2, width=2):
    return [[c1 if (y // width) % 2 == 0 else c2 for x in range(TILE_SIZE)] for y in range(TILE_SIZE)]

def tile_v_stripes(c1, c2, width=2):
    return [[c1 if (x // width) % 2 == 0 else c2 for x in range(TILE_SIZE)] for y in range(TILE_SIZE)]

def tile_border(c_edge, c_fill):
    grid = [[c_fill] * TILE_SIZE for _ in range(TILE_SIZE)]
    for x in range(TILE_SIZE):
        grid[0][x] = grid[TILE_SIZE - 1][x] = c_edge
    for y in range(TILE_SIZE):
        grid[y][0] = grid[y][TILE_SIZE - 1] = c_edge
    return grid

def tile_diamond(c_fg, c_bg):
    cx = cy = (TILE_SIZE - 1) / 2
    return [[c_fg if abs(x - cx) + abs(y - cy) <= cx else c_bg
             for x in range(TILE_SIZE)] for y in range(TILE_SIZE)]

def tile_dot(c_fg, c_bg, radius=3.0):
    cx = cy = (TILE_SIZE - 1) / 2
    return [[c_fg if (x - cx) ** 2 + (y - cy) ** 2 <= radius ** 2 else c_bg
             for x in range(TILE_SIZE)] for y in range(TILE_SIZE)]

def tile_cross(c_fg, c_bg, thickness=2):
    cx = cy = (TILE_SIZE - 1) / 2
    grid = [[c_bg] * TILE_SIZE for _ in range(TILE_SIZE)]
    for y in range(TILE_SIZE):
        for x in range(TILE_SIZE):
            if abs(x - cx) < thickness / 2 or abs(y - cy) < thickness / 2:
                grid[y][x] = c_fg
    return grid

def tile_x(c_fg, c_bg, thickness=2):
    grid = [[c_bg] * TILE_SIZE for _ in range(TILE_SIZE)]
    for y in range(TILE_SIZE):
        for x in range(TILE_SIZE):
            if abs(x - y) < thickness or abs(x + y - (TILE_SIZE - 1)) < thickness:
                grid[y][x] = c_fg
    return grid

def tile_dither(levels):
    bayer4 = [[0, 8, 2, 10], [12, 4, 14, 6], [3, 11, 1, 9], [15, 7, 13, 5]]
    grid = []
    for y in range(TILE_SIZE):
        row = []
        for x in range(TILE_SIZE):
            v = bayer4[y % 4][x % 4]
            idx = min(3, v * 4 // 16)
            row.append(levels[idx])
        grid.append(row)
    return grid

def tile_from_mask(mask, colors, bg=0):
    return [[colors.get(ch, bg) for ch in row] for row in mask]

def tile_heart(c_fg, c_bg):
    return tile_from_mask(["01100110", "11111111", "11111111", "11111111", 
                           "01111110", "00111100", "00011000", "00000000"], {"1": c_fg}, c_bg)

def tile_star(c_fg, c_bg):
    return tile_from_mask(["00011000", "00011000", "11111111", "01111110",
                           "01111110", "11111111", "00100100", "01000010"], {"1": c_fg}, c_bg)

def tile_triangle_up(c_fg, c_bg=0):
    cx = (TILE_SIZE - 1) / 2
    grid = []
    for y in range(TILE_SIZE):
        half = y * (TILE_SIZE / 2) / (TILE_SIZE - 1)
        grid.append([c_fg if abs(x - cx) <= half else c_bg for x in range(TILE_SIZE)])
    return grid

def tile_slope_rise(c_fg, c_bg=0):
    return [[c_fg if x >= TILE_SIZE - 1 - y else c_bg for x in range(TILE_SIZE)] for y in range(TILE_SIZE)]

def tile_slope_fall(c_fg, c_bg=0):
    return [[c_fg if x <= y else c_bg for x in range(TILE_SIZE)] for y in range(TILE_SIZE)]

def tile_wave(c_fg, c_bg=0, amplitude=1.5, cycles=1):
    grid = []
    for y in range(TILE_SIZE):
        row = []
        for x in range(TILE_SIZE):
            wave_y = TILE_SIZE / 2 + amplitude * math.sin(2 * math.pi * cycles * x / TILE_SIZE)
            row.append(c_fg if y > wave_y else c_bg)
        grid.append(row)
    return grid

def tile_brick(c_mortar, c_brick):
    grid = [[c_brick] * TILE_SIZE for _ in range(TILE_SIZE)]
    for y in range(TILE_SIZE):
        if y % 4 == 0:
            grid[y] = [c_mortar] * TILE_SIZE
    for y in range(TILE_SIZE):
        if y % 4 != 0:
            joint = 0 if (y // 4) % 2 == 0 else TILE_SIZE // 2
            grid[y][joint] = c_mortar
    return grid

def tile_tree(c_leaves, c_trunk, c_bg=0):
    mask = ["00011000", "00111100", "01111110", "00111100", 
            "01111110", "00011000", "00022000", "00022000"]
    return tile_from_mask(mask, {"1": c_leaves, "2": c_trunk}, c_bg)

def tile_cloud(c_fg, c_bg=0):
    mask = ["00111000", "01111110", "11111111", "11111111", 
            "01111110", "00000000", "00000000", "00000000"]
    return tile_from_mask(mask, {"1": c_fg}, c_bg)

def tile_grass(c_fg, c_bg=0):
    mask = ["00000000", "00000000", "00000000", "00000000", 
            "00000000", "01000100", "11101110", "11111111"]
    return tile_from_mask(mask, {"1": c_fg}, c_bg)

def tile_arrow(c_fg, c_bg=0):
    mask = ["00010000", "00111000", "01111100", "11111110", 
            "00111000", "00111000", "00111000", "00111000"]
    return tile_from_mask(mask, {"1": c_fg}, c_bg)

def tile_smiley(c_fg, c_bg=0):
    mask = ["00111100", "01000010", "10100101", "10000001", 
            "10100101", "10011001", "01000010", "00111100"]
    return tile_from_mask(mask, {"1": c_fg}, c_bg)

def tile_window(c_fg, c_bg=0):
    mask = ["00000000", "01100110", "01100110", "00000000", 
            "01100110", "01100110", "00000000", "00000000"]
    return tile_from_mask(mask, {"1": c_fg}, c_bg)

def tile_procedural(tile_id):
    state = (tile_id * 2654435761 + 1) & 0xFFFFFFFF
    grid = []
    for _ in range(TILE_SIZE):
        row = []
        for _ in range(TILE_SIZE):
            state = (state * 1103515245 + 12345) & 0xFFFFFFFF
            row.append((state >> 30) & 0b11)
        grid.append(row)
    return grid

# Generates a massive 16x8 tile (128x64 pixel) image split into all 128 slots
def build_mega_image_tiles():
    tiles = {}
    for ty in range(8):
        for tx in range(16):
            grid = []
            for y in range(TILE_SIZE):
                row = []
                for x in range(TILE_SIZE):
                    gx, gy = tx * 8 + x, ty * 8 + y
                    if gy < 32:
                        # Sun and Sky
                        dist_sun = ((gx - 64)**2 + (gy - 24)**2)**0.5
                        row.append(3 if dist_sun < 12 else min(2, gy // 10))
                    else:
                        # Ocean with waves
                        wave = math.sin(gx * 0.2 + gy * 0.5)
                        row.append(1 if wave > 0 else 2)
                grid.append(row)
            tiles[ty * 16 + tx] = grid
    return tiles

def build_tile_set(pattern_name=""):
    if pattern_name == "mega_image":
        return build_mega_image_tiles()

    tiles = {
        0:  tile_blank(),
        1:  tile_solid(1),
        2:  tile_solid(2),
        3:  tile_solid(3),
        4:  tile_checker(1, 2, block=1),
        5:  tile_checker(1, 3, block=2),
        6:  tile_diag_stripes(1, 2, width=2, backslash=False),
        7:  tile_diag_stripes(1, 2, width=2, backslash=True),
        8:  tile_h_stripes(1, 3, width=2),
        9:  tile_v_stripes(1, 3, width=2),
        10: tile_border(1, 0),
        11: tile_diamond(2, 0),
        12: tile_dot(3, 0),
        13: tile_cross(1, 0, thickness=2),
        14: tile_x(2, 0, thickness=2),
        15: tile_dither((0, 1, 2, 3)),
        16: tile_heart(1, 0),
        17: tile_star(3, 0),
        18: tile_triangle_up(1, 0),        
        19: tile_slope_rise(1, 0),         
        20: tile_slope_fall(1, 0),         
        21: tile_cloud(3, 0),
        22: tile_tree(2, 1, 0),            
        23: tile_grass(2, 0),              
        24: tile_wave(3, 0),               
        25: tile_brick(0, 1),
        26: tile_arrow(3, 0),
        27: tile_dither((3, 2, 1, 0)),     
        28: tile_dot(3, 0, radius=3.5),    
        29: tile_dot(1, 0, radius=1.5),    
        30: tile_checker(2, 3, block=1),
        31: tile_h_stripes(2, 3, width=1),
        32: tile_v_stripes(2, 3, width=1),
        33: tile_diag_stripes(2, 3, width=1, backslash=False),
        34: tile_diag_stripes(2, 3, width=1, backslash=True),
        35: tile_border(3, 2),
        36: tile_cross(3, 0, thickness=3),
        37: tile_x(1, 0, thickness=3),
        38: tile_smiley(3, 0),
        39: tile_window(2, 1),             # For cityscape
        40: tile_border(1, 1),             # Solid building block
        41: tile_dot(3, 0, radius=2.5),    # Moon
    }
    return tiles

# ---------------------------------------------------------------------------
# Packing & I/O
# ---------------------------------------------------------------------------

def pack_tile_rows(grid):
    words = []
    for row in grid:
        word = 0
        for px in row:
            word = (word << 2) | (px & 0b11)
        words.append(word)
    return words

def write_pattern_table(path, tiles):
    with open(path, "w", newline="") as f:
        for tile_id in range(MAX_TILES):
            grid = tiles[tile_id] if tile_id in tiles else tile_procedural(tile_id)
            for word in pack_tile_rows(grid):
                f.write(f"{word:04x}\r\n")

def write_palette(path, palettes):
    with open(path, "w", newline="") as f:
        for pal in palettes:
            for c in pal:
                f.write(f"{c:01x}\r\n")

def write_nametable(path, entries):
    with open(path, "w", newline="") as f:
        for tile_id, pal_sel in entries:
            byte = ((pal_sel & 1) << 7) | (tile_id & 0x7F)
            f.write(f"{byte:02x}\r\n")

# ---------------------------------------------------------------------------
# Nametable effects
# ---------------------------------------------------------------------------

def effect_checkerboard():
    return [((4 if ((tx // 4) + (ty // 4)) % 2 == 0 else 5), ((tx // 4) + (ty // 4)) % PALETTE_COUNT)
            for ty in range(SCREEN_TILES_Y) for tx in range(SCREEN_TILES_X)]

def effect_stripes():
    pool = (6, 7, 8, 9)
    return [(pool[(tx + ty) % len(pool)], (tx + ty) % PALETTE_COUNT)
            for ty in range(SCREEN_TILES_Y) for tx in range(SCREEN_TILES_X)]

def effect_fractal():
    pool = (1, 2, 3, 11, 12, 14, 15)
    return [(pool[(tx ^ ty) % len(pool)], (tx ^ ty) % PALETTE_COUNT)
            for ty in range(SCREEN_TILES_Y) for tx in range(SCREEN_TILES_X)]

def effect_rings():
    pool = (1, 4, 2, 5, 3, 10)
    cx, cy = (SCREEN_TILES_X - 1) / 2, (SCREEN_TILES_Y - 1) / 2
    return [(pool[int(((tx - cx)**2 + (ty - cy)**2)**0.5) % len(pool)],
             int(((tx - cx)**2 + (ty - cy)**2)**0.5) % PALETTE_COUNT)
            for ty in range(SCREEN_TILES_Y) for tx in range(SCREEN_TILES_X)]

def effect_scenery():
    FLAT, GND, PEAK, SL_L, SL_R, CLOUD, TREE, GRASS, SUN = 1, 2, 18, 19, 20, 21, 22, 23, 28
    horizon = 20
    peaks, pk_h, rdg_h = [8, 20, 32], 6, 7
    out = []
    for ty in range(SCREEN_TILES_Y):
        for tx in range(SCREEN_TILES_X):
            h, side = 0, 0
            for c in peaks:
                d, ad = tx - c, abs(tx - c)
                if ad <= rdg_h and pk_h - int(pk_h * ad / rdg_h) > h:
                    h, side = pk_h - int(pk_h * ad / rdg_h), 0 if d == 0 else (-1 if d < 0 else 1)
            mtn = horizon - h
            if (tx, ty) == (33, 3): out.append((SUN, 1))
            elif (tx, ty) in {(5, 3), (6, 3), (5, 4), (23, 5), (24, 5)}: out.append((CLOUD, 0))
            elif (tx, ty) in {(2, horizon), (12, horizon), (37, horizon)}: out.append((TREE, 0))
            elif h > 0 and ty == mtn: out.append((PEAK if side == 0 else (SL_L if side < 0 else SL_R), 1))
            elif h > 0 and mtn < ty < horizon: out.append((FLAT, 1))
            elif ty < horizon: out.append((FLAT, 0))
            elif ty == horizon: out.append((GRASS if tx % 4 == 0 else GND, 0))
            else: out.append((GND, 0))
    return out

def effect_all_tiles():
    return [(i % MAX_TILES, (i // MAX_TILES) % PALETTE_COUNT) for i in range(SCREEN_TILES_X * SCREEN_TILES_Y)]

def effect_waves():
    pool = (1, 2, 3, 15, 27)
    return [(pool[int((math.sin(tx * 0.3) + math.sin(ty * 0.4) + math.sin((tx + ty) * 0.15) + 3) * len(pool) / 6) % len(pool)],
             int((math.sin(tx * 0.3) + math.sin(ty * 0.4) + math.sin((tx + ty) * 0.15) + 3) * len(pool) / 6) % PALETTE_COUNT)
            for ty in range(SCREEN_TILES_Y) for tx in range(SCREEN_TILES_X)]

def effect_spiral():
    pool = (1, 4, 2, 5, 3, 10, 15)
    cx, cy = (SCREEN_TILES_X - 1) / 2, (SCREEN_TILES_Y - 1) / 2
    return [(pool[int(((tx - cx)**2 + (ty - cy)**2)**0.5 - math.atan2(ty - cy, tx - cx) * 3) % len(pool)],
             int(((tx - cx)**2 + (ty - cy)**2)**0.5 - math.atan2(ty - cy, tx - cx) * 3) % PALETTE_COUNT)
            for ty in range(SCREEN_TILES_Y) for tx in range(SCREEN_TILES_X)]

def effect_noise():
    pool, out, state = (0, 1, 2, 3, 4, 5, 15, 30), [], 12345
    for _ in range(SCREEN_TILES_X * SCREEN_TILES_Y):
        state = (state * 1103515245 + 12345) & 0xFFFFFFFF
        out.append((pool[(state >> 28) % len(pool)], (state >> 26) & 1))
    return out

def effect_cityscape():
    BLD_WIN, BLD_SOL, MOON, STAR, SKY = 39, 40, 41, 29, 0
    out = []
    skyline = [15, 12, 18, 10, 14, 20, 13, 16, 9, 11]
    for ty in range(SCREEN_TILES_Y):
        for tx in range(SCREEN_TILES_X):
            h = skyline[tx // 4]
            if ty > h:
                out.append((BLD_WIN, 1) if tx % 2 == 1 and ty % 2 == 0 and ty > h + 1 else (BLD_SOL, 1))
            elif ty == h:
                out.append((BLD_SOL, 1))
            else:
                if (tx, ty) == (30, 5): out.append((MOON, 0))
                elif (tx * 17 + ty * 23) % 47 == 0: out.append((STAR, 0))
                else: out.append((SKY, 0))
    return out

def effect_maze():
    WALL, PATH = 25, 0
    grid = [[WALL] * SCREEN_TILES_X for _ in range(SCREEN_TILES_Y)]
    for ty in range(1, SCREEN_TILES_Y - 1, 2):
        for tx in range(1, SCREEN_TILES_X - 1, 2):
            grid[ty][tx] = PATH
            if tx == 1 and ty == 1: pass
            elif tx == 1: grid[ty - 1][tx] = PATH
            elif ty == 1: grid[ty][tx - 1] = PATH
            else:
                if (tx * 13 + ty * 17) % 2 == 0: grid[ty - 1][tx] = PATH
                else: grid[ty][tx - 1] = PATH
    return [(grid[ty][tx], 1 if grid[ty][tx] == WALL else 0) 
            for ty in range(SCREEN_TILES_Y) for tx in range(SCREEN_TILES_X)]

def effect_space():
    STAR1, STAR2, SKY = 12, 29, 0
    out = []
    for ty in range(SCREEN_TILES_Y):
        for tx in range(SCREEN_TILES_X):
            # Center a large 8x8 procedural tile block as a planet
            if 16 <= tx < 24 and 11 <= ty < 19:
                out.append((64 + (ty - 11) * 8 + (tx - 16), 1))
            else:
                rand = (tx * 101 + ty * 197) % 100
                out.append((STAR1, 0) if rand == 0 else ((STAR2, 0) if rand < 4 else (SKY, 0)))
    return out

def effect_mega_image():
    # Places all 128 uniquely generated tiles as a 16x8 massive composite
    out = []
    for ty in range(SCREEN_TILES_Y):
        for tx in range(SCREEN_TILES_X):
            if 12 <= tx < 28 and 11 <= ty < 19:
                out.append(((ty - 11) * 16 + (tx - 12), 0))
            else:
                out.append((0, 1))
    return out

EFFECTS = {
    "checkerboard": effect_checkerboard,
    "stripes":      effect_stripes,
    "fractal":      effect_fractal,
    "rings":        effect_rings,
    "scenery":      effect_scenery,
    "all_tiles":    effect_all_tiles,
    "waves":        effect_waves,
    "spiral":       effect_spiral,
    "noise":        effect_noise,
    "cityscape":    effect_cityscape,
    "maze":         effect_maze,
    "space":        effect_space,
    "mega_image":   effect_mega_image,
}

DEFAULT_PALETTES = [
    [BLACK, RED,     GREEN,  BLUE], 
    [BLACK, MAGENTA, YELLOW, CYAN], 
]

PATTERN_PALETTES = {
    "scenery":    [[BLACK, BLUE, GREEN, WHITE], [BLACK, CYAN, MAGENTA, YELLOW]],
    "cityscape":  [[BLACK, BLUE, CYAN, WHITE], [BLACK, BLUE, YELLOW, RED]],
    "maze":       [[BLACK, GREEN, CYAN, WHITE], [BLACK, RED, YELLOW, WHITE]],
    "space":      [[BLACK, WHITE, CYAN, YELLOW], [BLACK, MAGENTA, BLUE, RED]],
    "mega_image": [[BLACK, BLUE, CYAN, YELLOW], [BLACK, WHITE, RED, MAGENTA]],
}

def generate(pattern_name, out_dir):
    os.makedirs(out_dir, exist_ok=True)
    tiles = build_tile_set(pattern_name)
    entries = EFFECTS[pattern_name]()
    palettes = PATTERN_PALETTES.get(pattern_name, DEFAULT_PALETTES)

    write_pattern_table(os.path.join(out_dir, "pattern_table.hex"), tiles)
    write_palette(os.path.join(out_dir, "palette.hex"), palettes)
    write_nametable(os.path.join(out_dir, "nametable.hex"), entries)

    print(f"[{pattern_name}] wrote pattern_table.hex, palette.hex, nametable.hex -> {out_dir}")

def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--pattern", choices=list(EFFECTS) + ["all"], default="fractal")
    ap.add_argument("--out-dir", default=".")
    args = ap.parse_args()

    if args.pattern == "all":
        for name in EFFECTS:
            generate(name, os.path.join(args.out_dir, name))
    else:
        generate(args.pattern, args.out_dir)

if __name__ == "__main__":
    main()