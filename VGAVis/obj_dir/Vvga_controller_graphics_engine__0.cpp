// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vvga_controller.h for the primary calling header

#include "Vvga_controller__pch.h"

void Vvga_controller_graphics_engine___ico_sequent__TOP__vga_controller__gfx_inst__0(Vvga_controller_graphics_engine* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vvga_controller_graphics_engine___ico_sequent__TOP__vga_controller__gfx_inst__0\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__addr = (0x0001ffffU & (((IData)(0x00000140U) 
                                             * (0x000001ffU 
                                                & ((IData)(vlSymsp->TOP__vga_controller.pixel_y) 
                                                   >> 1U))) 
                                            + (0x000001ffU 
                                               & ((IData)(vlSymsp->TOP__vga_controller.pixel_x) 
                                                  >> 1U))));
}

void Vvga_controller_graphics_engine___nba_sequent__TOP__vga_controller__gfx_inst__0(Vvga_controller_graphics_engine* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vvga_controller_graphics_engine___nba_sequent__TOP__vga_controller__gfx_inst__0\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__rgb = ((IData)(vlSymsp->TOP.rst)
                             ? 0U : (((IData)(vlSymsp->TOP__vga_controller.video_on) 
                                      & ((0x0280U > (IData)(vlSymsp->TOP__vga_controller.pixel_x)) 
                                         & (0x01e0U 
                                            > (IData)(vlSymsp->TOP__vga_controller.pixel_y))))
                                      ? ((0x00012bffU 
                                          >= vlSelfRef.__PVT__addr)
                                          ? vlSelfRef.framebuffer
                                         [vlSelfRef.__PVT__addr]
                                          : 0U) : 0U));
}
