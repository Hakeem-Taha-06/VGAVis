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
    CData/*0:0*/ __PVT__clk;
    CData/*0:0*/ __PVT__rst;
    CData/*0:0*/ __PVT__mode_select;
    CData/*0:0*/ __PVT__video_on;
    CData/*2:0*/ __PVT__rgb;
    CData/*0:0*/ __PVT__video_on_d1;
    CData/*0:0*/ __PVT__video_on_d2;
    CData/*0:0*/ __PVT__mode_select_d1;
    CData/*0:0*/ __PVT__mode_select_d2;
    CData/*2:0*/ __PVT__image_rgb_stage1;
    CData/*2:0*/ __PVT__image_rgb_stage2;
    CData/*7:0*/ __PVT__nametable_out;
    CData/*2:0*/ __PVT__ntile_x_d1;
    CData/*2:0*/ __PVT__ntile_x_d2;
    CData/*2:0*/ __PVT__ntile_y_d1;
    CData/*0:0*/ __PVT__palette_sel_d1;
    SData/*9:0*/ __PVT__pixel_x;
    SData/*9:0*/ __PVT__pixel_y;
    SData/*10:0*/ __PVT__nametable_addr;
    SData/*15:0*/ __PVT__pattern_row;
    IData/*16:0*/ __PVT__img_addr;
    VlUnpacked<CData/*2:0*/, 76800> framebuffer;
    VlUnpacked<CData/*7:0*/, 1200> nametable;
    VlUnpacked<SData/*15:0*/, 1024> pattern_table;
    VlUnpacked<CData/*2:0*/, 8> palette_mem;

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
