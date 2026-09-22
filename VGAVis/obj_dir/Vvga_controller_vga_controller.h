// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vvga_controller.h for the primary calling header

#ifndef VERILATED_VVGA_CONTROLLER_VGA_CONTROLLER_H_
#define VERILATED_VVGA_CONTROLLER_VGA_CONTROLLER_H_  // guard

#include "verilated.h"
class Vvga_controller_graphics_engine;


class Vvga_controller__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vvga_controller_vga_controller final {
  public:
    // CELLS
    Vvga_controller_graphics_engine* gfx_inst;

    // DESIGN-SPECIFIC STATE
    CData/*0:0*/ clk;
    CData/*0:0*/ rst;
    CData/*0:0*/ mode_select;
    CData/*0:0*/ vsync;
    CData/*0:0*/ hsync;
    CData/*2:0*/ rgb;
    CData/*0:0*/ video_on;
    CData/*1:0*/ __PVT__vsync_shift;
    CData/*1:0*/ __PVT__hsync_shift;
    CData/*0:0*/ __PVT__sync_inst__DOT__pixel_clk;
    SData/*9:0*/ pixel_x;
    SData/*9:0*/ pixel_y;
    SData/*9:0*/ __PVT__sync_inst__DOT__h_count;
    SData/*9:0*/ __PVT__sync_inst__DOT__v_count;

    // INTERNAL VARIABLES
    Vvga_controller__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vvga_controller_vga_controller();
    ~Vvga_controller_vga_controller();
    void ctor(Vvga_controller__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vvga_controller_vga_controller);

    // INTERNAL METHODS
};


#endif  // guard
