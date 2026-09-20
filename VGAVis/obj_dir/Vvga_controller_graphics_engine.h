// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vvga_controller.h for the primary calling header

#ifndef VERILATED_VVGA_CONTROLLER_GRAPHICS_ENGINE_H_
#define VERILATED_VVGA_CONTROLLER_GRAPHICS_ENGINE_H_  // guard

#include "verilated.h"


class Vvga_controller__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vvga_controller_graphics_engine final {
  public:

    // DESIGN-SPECIFIC STATE
    CData/*0:0*/ __PVT__video_on;
    CData/*0:0*/ __PVT__clk;
    CData/*0:0*/ __PVT__rst;
    CData/*2:0*/ __PVT__rgb;
    SData/*9:0*/ __PVT__pixel_x;
    SData/*9:0*/ __PVT__pixel_y;
    IData/*16:0*/ __PVT__addr;
    VlUnpacked<CData/*2:0*/, 76800> framebuffer;

    // INTERNAL VARIABLES
    Vvga_controller__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vvga_controller_graphics_engine();
    ~Vvga_controller_graphics_engine();
    void ctor(Vvga_controller__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vvga_controller_graphics_engine);

    // INTERNAL METHODS
};


#endif  // guard
