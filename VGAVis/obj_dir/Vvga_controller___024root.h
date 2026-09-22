// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vvga_controller.h for the primary calling header

#ifndef VERILATED_VVGA_CONTROLLER___024ROOT_H_
#define VERILATED_VVGA_CONTROLLER___024ROOT_H_  // guard

#include "verilated.h"
class Vvga_controller_vga_controller;


class Vvga_controller__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vvga_controller___024root final {
  public:
    // CELLS
    Vvga_controller_vga_controller* vga_controller;

    // DESIGN-SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(mode_select,0,0);
    VL_OUT8(vsync,0,0);
    VL_OUT8(hsync,0,0);
    VL_OUT8(rgb,2,0);
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__rst__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__mode_select__0;
    CData/*0:0*/ __VicoDidInit;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__1;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 2> __VicoTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vvga_controller__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vvga_controller___024root(Vvga_controller__Syms* symsp, const char* namep);
    ~Vvga_controller___024root();
    VL_UNCOPYABLE(Vvga_controller___024root);

    // INTERNAL METHODS
};


#endif  // guard
