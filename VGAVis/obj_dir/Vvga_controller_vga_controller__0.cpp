// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vvga_controller.h for the primary calling header

#include "Vvga_controller__pch.h"

void Vvga_controller_vga_controller___nba_sequent__TOP__vga_controller__0(Vvga_controller_vga_controller* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vvga_controller_vga_controller___nba_sequent__TOP__vga_controller__0\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __Vdly__sync_inst__DOT__pixel_clk;
    __Vdly__sync_inst__DOT__pixel_clk = 0;
    SData/*9:0*/ __Vdly__sync_inst__DOT__h_count;
    __Vdly__sync_inst__DOT__h_count = 0;
    SData/*9:0*/ __Vdly__sync_inst__DOT__v_count;
    __Vdly__sync_inst__DOT__v_count = 0;
    // Body
    __Vdly__sync_inst__DOT__pixel_clk = vlSelfRef.__PVT__sync_inst__DOT__pixel_clk;
    __Vdly__sync_inst__DOT__h_count = vlSelfRef.__PVT__sync_inst__DOT__h_count;
    __Vdly__sync_inst__DOT__v_count = vlSelfRef.__PVT__sync_inst__DOT__v_count;
    __Vdly__sync_inst__DOT__pixel_clk = (1U & ((~ (IData)(vlSymsp->TOP.rst)) 
                                               & (~ (IData)(vlSelfRef.__PVT__sync_inst__DOT__pixel_clk))));
    if (vlSymsp->TOP.rst) {
        __Vdly__sync_inst__DOT__h_count = 0U;
        __Vdly__sync_inst__DOT__v_count = 0U;
    } else if (vlSelfRef.__PVT__sync_inst__DOT__pixel_clk) {
        if ((0x031fU == (IData)(vlSelfRef.__PVT__sync_inst__DOT__h_count))) {
            __Vdly__sync_inst__DOT__h_count = 0U;
            __Vdly__sync_inst__DOT__v_count = ((0x020cU 
                                                == (IData)(vlSelfRef.__PVT__sync_inst__DOT__v_count))
                                                ? 0U
                                                : (0x000003ffU 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlSelfRef.__PVT__sync_inst__DOT__v_count))));
        } else {
            __Vdly__sync_inst__DOT__h_count = (0x000003ffU 
                                               & ((IData)(1U) 
                                                  + (IData)(vlSelfRef.__PVT__sync_inst__DOT__h_count)));
        }
    }
    vlSelfRef.__PVT__sync_inst__DOT__pixel_clk = __Vdly__sync_inst__DOT__pixel_clk;
    vlSelfRef.__PVT__sync_inst__DOT__v_count = __Vdly__sync_inst__DOT__v_count;
    vlSelfRef.__PVT__sync_inst__DOT__h_count = __Vdly__sync_inst__DOT__h_count;
}

void Vvga_controller_vga_controller___nba_sequent__TOP__vga_controller__1(Vvga_controller_vga_controller* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vvga_controller_vga_controller___nba_sequent__TOP__vga_controller__1\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.video_on = ((0x0280U > (IData)(vlSelfRef.__PVT__sync_inst__DOT__h_count)) 
                          & (0x01e0U > (IData)(vlSelfRef.__PVT__sync_inst__DOT__v_count)));
    vlSelfRef.pixel_x = vlSelfRef.__PVT__sync_inst__DOT__h_count;
    vlSelfRef.pixel_y = vlSelfRef.__PVT__sync_inst__DOT__v_count;
}
