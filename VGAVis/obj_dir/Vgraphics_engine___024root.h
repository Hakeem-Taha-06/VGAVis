// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vgraphics_engine.h for the primary calling header

#ifndef VERILATED_VGRAPHICS_ENGINE___024ROOT_H_
#define VERILATED_VGRAPHICS_ENGINE___024ROOT_H_  // guard

#include "verilated.h"
class Vgraphics_engine_graphics_engine;


class Vgraphics_engine__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vgraphics_engine___024root final {
  public:
    // CELLS
    Vgraphics_engine_graphics_engine* graphics_engine;

    // DESIGN-SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(video_on,0,0);
    VL_OUT8(rgb,2,0);
    CData/*0:0*/ __Vtrigprevexpr___TOP__video_on__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __VicoDidInit;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__1;
    VL_IN16(pixel_x,9,0);
    VL_IN16(pixel_y,9,0);
    SData/*9:0*/ __Vtrigprevexpr___TOP__pixel_x__0;
    SData/*9:0*/ __Vtrigprevexpr___TOP__pixel_y__0;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 2> __VicoTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vgraphics_engine__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vgraphics_engine___024root(Vgraphics_engine__Syms* symsp, const char* namep);
    ~Vgraphics_engine___024root();
    VL_UNCOPYABLE(Vgraphics_engine___024root);

    // INTERNAL METHODS
};


#endif  // guard
