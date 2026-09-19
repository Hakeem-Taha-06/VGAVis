// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vgraphics_engine.h for the primary calling header

#ifndef VERILATED_VGRAPHICS_ENGINE_GRAPHICS_ENGINE_H_
#define VERILATED_VGRAPHICS_ENGINE_GRAPHICS_ENGINE_H_  // guard

#include "verilated.h"


class Vgraphics_engine__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vgraphics_engine_graphics_engine final {
  public:

    // DESIGN-SPECIFIC STATE
    CData/*0:0*/ video_on;
    CData/*0:0*/ clk;
    CData/*2:0*/ rgb;
    SData/*9:0*/ pixel_x;
    SData/*9:0*/ pixel_y;
    IData/*16:0*/ __PVT__addr;
    VlUnpacked<CData/*2:0*/, 76800> framebuffer;

    // INTERNAL VARIABLES
    Vgraphics_engine__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vgraphics_engine_graphics_engine();
    ~Vgraphics_engine_graphics_engine();
    void ctor(Vgraphics_engine__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vgraphics_engine_graphics_engine);

    // INTERNAL METHODS
};


#endif  // guard
