# VGAVis

VGAVis is a real-time VGA controller visualizer for Windows. It takes a Verilog VGA controller design, compiles it into C++ using Verilator, and simulates it cycle-by-cycle while rendering the 640x480 output to a window using OpenGL and Dear ImGui. It supports both a direct Image rendering mode and a Sprite-based Tilemap rendering mode. The simulated memory (framebuffer, nametable, pattern table, and palette) can be directly inspected and edited in real-time, and tile data can be loaded through the UI.

https://github.com/user-attachments/assets/1fc5c8d0-54b9-4369-84d6-9fe91fd3eb21

The project is intended for debugging and visualizing FPGA-based VGA controller designs without needing physical hardware.

---

## Prerequisites

- **Windows 10 or later** (x64)
- **Visual Studio 2022** with the "Desktop development with C++" workload
- **MSYS2** with Verilator installed under the MINGW64 environment
- **Premake5** (bundled in the repository under `premake/`)

---

## Installing MSYS2 and Verilator

### 1. Install MSYS2

Download and run the installer from [https://www.msys2.org](https://www.msys2.org). Use the default installation path (`C:\msys64`). If you install to a different path, update the `MSYS2_PATH` variable in `VGAVis/RegenerateModule.bat` accordingly:

```bat
:: Path to your MSYS2 root installation
set "MSYS2_PATH=C:\msys64" :: <-- Edit this line if you installed MSYS2 elsewhere
```

After installation, open the **MSYS2 MINGW64** terminal and update the package database:

```bash
pacman -Syu
```

Close and reopen the terminal if prompted, then run the update again to finish:

```bash
pacman -Syu
```

### 2. Install Verilator

In the **MSYS2 MINGW64** terminal, install Verilator via the package manager:

```bash
pacman -S mingw-w64-x86_64-verilator
```

Verify the installation:

```bash
verilator --version
```

If you need a specific version or want to build from source instead, follow the official Verilator installation guide:
[https://verilator.org/guide/latest/install.html](https://verilator.org/guide/latest/install.html)

The build-from-source steps are Linux-oriented but work under the MSYS2 MINGW64 shell. You will need additional packages:

```bash
pacman -S --needed base-devel mingw-w64-x86_64-toolchain git flex bison perl autoconf
```

Then clone, configure, and build as described in the official guide.

---

## Verilog Module Naming Conventions

The C++ simulator expects a specific module hierarchy and naming scheme. If these conventions are not followed, the Verilator-generated C++ classes will not match what the simulator code includes, and the build will fail.

Feel free to tinker with the C++ side of things to change it to match what you need tho.

### Top Module: `vga_controller`

The top-level module must be named `vga_controller`. Its port interface must be exactly:

```verilog
module vga_controller(
    input wire clk,
    input wire rst,
    input wire mode_select,
    output wire vsync,
    output wire hsync,
    output wire [2:0] rgb
);
```

Any internal wires that the simulator needs to read (specifically `pixel_x`, `pixel_y`, and `video_on`) must be marked with `/*verilator public*/`. This annotation tells Verilator to expose the signal as a public C++ member instead of making it private. Place the marker between the signal name and the semicolon:

```verilog
wire video_on /*verilator public*/;
wire [9:0] pixel_x /*verilator public*/;
wire [9:0] pixel_y /*verilator public*/;
```

### Sub-Module: `graphics_engine`

The top module must instantiate a `graphics_engine` module with the instance name `gfx_inst`. The graphics engine must contain memory arrays marked with `/*verilator public*/` so the simulator can read from and write to them at runtime. Place the marker between the array declaration and the semicolon:

```verilog
reg [2:0] framebuffer [0:76799] /*verilator public*/;
reg [7:0] nametable [0:1199] /*verilator public*/;
reg [15:0] pattern_table [0:1023] /*verilator public*/;
reg [2:0] palette_mem [0:7] /*verilator public*/;
```

The `framebuffer` is used in Image mode (320x240 pixels). The `nametable`, `pattern_table`, and `palette_mem` are used in Tilemap mode for sprite-based rendering.

### Why These Names Matter

When Verilator processes `vga_controller.v`, it generates C++ classes using the module and instance names:

| Verilog Name | Generated C++ Class | Accessed Via |
|---|---|---|
| `vga_controller` (top) | `Vvga_controller` | `m_top` |
| `vga_controller` (internals) | `Vvga_controller_vga_controller` | `m_top->vga_controller` |
| `graphics_engine gfx_inst` | `Vvga_controller_graphics_engine` | `m_top->vga_controller->gfx_inst` |

The simulator includes and uses these exact class names. Renaming any module or instance in the Verilog will cause unresolved include errors or member access failures during compilation.

---

## Verilating the Design

The Verilog source files (`vga_controller.v`, `vga_sync.v`, `graphics_engine.v`) must be placed in the `VGAVis/` directory.

To regenerate the Verilator C++ output, run the batch script from within the `VGAVis/` directory:

```
RegenerateModule.bat
```

This invokes Verilator through the MSYS2 MINGW64 bash shell:

```bash
verilator -Wall --cc vga_controller.v
```

The generated C++ files are written to `VGAVis/obj_dir/`. These files are compiled alongside the application source by the Visual Studio project.

If Verilator reports warnings about `EOFNEWLINE` or `PROCASSINIT`, these can be safely ignored. To suppress them, add `-Wno-fatal` to the verilator command. Actual errors (such as missing ports or undeclared signals) must be resolved before proceeding.

---

## Building the Project

### 1. Generate the Visual Studio Solution

From the repository root, run:

```
premake\premake5.exe vs2022
```

This creates `VGAVis.sln` and the `.vcxproj` file under `VGAVis/`.

### 2. Build

Open `VGAVis.sln` in Visual Studio 2022 and build the solution (Debug or Release, x64).

Alternatively, build from the command line using the Developer Command Prompt or PowerShell:

```powershell
& 'C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe' VGAVis.sln /p:Configuration=Debug /p:Platform=x64
```

The output executable is placed in `bin/Debug-windows-x86_64/VGAVis/VGAVis.exe` (or the equivalent Release path).

---

## Usage

Run the built executable. The application opens a window with multiple panels:

- **Control Window** -- Select the render mode (Image or Tilemap). Load an image file into the framebuffer, or load a directory of hex files for the tilemap memories. Adjust simulation speed.
- **Screen** -- Displays the live 640x480 VGA output as rendered by the simulated controller.
- **Framebuffer** -- Displays the raw 320x240 framebuffer contents (used in Image mode).
- **Nametable & Pattern Table** -- View and edit the raw memory bytes used for tilemap rendering.
- **Pattern Pixels & Palette** -- Edit individual tiles pixel-by-pixel and adjust the 8-color palette in real-time.
- **Pattern & Nametable Textures** -- Visual representations of the loaded tile patterns and the composed tilemap screen.

The simulation runs the Verilog design cycle-by-cycle. The `vga_sync` module generates the timing signals, and the `graphics_engine` uses either the framebuffer or the tilemap memories (based on `mode_select`) to produce the pixel output.

---

## Project Structure

```
VGAControllerVisualizer/
    premake5.lua              -- Build configuration
    premake/                  -- Premake5 binary
    VGAVis/
        vga_controller.v      -- Top-level Verilog module
        vga_sync.v            -- VGA timing generator
        graphics_engine.v     -- Framebuffer and pixel output logic
        initial_image.hex     -- Default framebuffer contents loaded at startup
        RegenerateModule.bat  -- Runs Verilator to regenerate obj_dir/
        obj_dir/              -- Verilator-generated C++ (do not edit manually)
        src/
            main.cpp          -- Entry point
            Application.cpp   -- Main loop, drives simulation and rendering
            Simulator.cpp     -- Wraps the Verilated model
            Window.cpp        -- OpenGL/ImGui window and rendering
        include/
            Application.h
            Simulator.h
            Window.h
            Shader.h
            InputManager.h
        dependencies/         -- Third-party libraries (GLFW, glad, ImGui, stb, Verilator runtime headers)
```
