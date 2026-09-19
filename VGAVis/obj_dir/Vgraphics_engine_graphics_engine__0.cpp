// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vgraphics_engine.h for the primary calling header

#include "Vgraphics_engine__pch.h"

void Vgraphics_engine_graphics_engine___ico_comb__TOP__graphics_engine__0(Vgraphics_engine_graphics_engine* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vgraphics_engine_graphics_engine___ico_comb__TOP__graphics_engine__0\n"); );
    Vgraphics_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__addr = (0x0001ffffU & (((IData)(0x00000140U) 
                                             * (0x000001ffU 
                                                & ((IData)(vlSymsp->TOP.pixel_y) 
                                                   >> 1U))) 
                                            + (0x000001ffU 
                                               & ((IData)(vlSymsp->TOP.pixel_x) 
                                                  >> 1U))));
}

void Vgraphics_engine_graphics_engine___nba_sequent__TOP__graphics_engine__0(Vgraphics_engine_graphics_engine* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vgraphics_engine_graphics_engine___nba_sequent__TOP__graphics_engine__0\n"); );
    Vgraphics_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.rgb = (((IData)(vlSymsp->TOP.video_on) 
                      & ((0x0280U > (IData)(vlSymsp->TOP.pixel_x)) 
                         & (0x01e0U > (IData)(vlSymsp->TOP.pixel_y))))
                      ? ((0x00012bffU >= vlSelfRef.__PVT__addr)
                          ? vlSelfRef.framebuffer[vlSelfRef.__PVT__addr]
                          : 0U) : 0U);
}
