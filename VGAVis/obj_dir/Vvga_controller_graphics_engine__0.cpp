// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vvga_controller.h for the primary calling header

#include "Vvga_controller__pch.h"

void Vvga_controller_graphics_engine___ico_sequent__TOP__vga_controller__gfx_inst__0(Vvga_controller_graphics_engine* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vvga_controller_graphics_engine___ico_sequent__TOP__vga_controller__gfx_inst__0\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__img_addr = (0x0001ffffU & (((IData)(0x00000140U) 
                                                 * 
                                                 (0x000001ffU 
                                                  & ((IData)(vlSymsp->TOP__vga_controller.pixel_y) 
                                                     >> 1U))) 
                                                + (0x000001ffU 
                                                   & ((IData)(vlSymsp->TOP__vga_controller.pixel_x) 
                                                      >> 1U))));
    vlSelfRef.__PVT__nametable_addr = (0x000007ffU 
                                       & (((IData)(0x00000028U) 
                                           * (0x0000001fU 
                                              & ((IData)(vlSymsp->TOP__vga_controller.pixel_y) 
                                                 >> 4U))) 
                                          + (0x0000003fU 
                                             & ((IData)(vlSymsp->TOP__vga_controller.pixel_x) 
                                                >> 4U))));
}

void Vvga_controller_graphics_engine___nba_sequent__TOP__vga_controller__gfx_inst__0(Vvga_controller_graphics_engine* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vvga_controller_graphics_engine___nba_sequent__TOP__vga_controller__gfx_inst__0\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__palette_sel_d1 = (1U & ((IData)(vlSelfRef.__PVT__nametable_out) 
                                             >> 7U));
    vlSelfRef.__PVT__ntile_x_d2 = vlSelfRef.__PVT__ntile_x_d1;
    vlSelfRef.__PVT__mode_select_d2 = ((1U & (~ (IData)(vlSymsp->TOP.rst))) 
                                       && (IData)(vlSelfRef.__PVT__mode_select_d1));
    vlSelfRef.__PVT__video_on_d2 = ((1U & (~ (IData)(vlSymsp->TOP.rst))) 
                                    && (IData)(vlSelfRef.__PVT__video_on_d1));
    vlSelfRef.__PVT__pattern_row = vlSelfRef.pattern_table
        [((0x000003f8U & ((IData)(vlSelfRef.__PVT__nametable_out) 
                          << 3U)) | (IData)(vlSelfRef.__PVT__ntile_y_d1))];
    if (vlSymsp->TOP.rst) {
        vlSelfRef.__PVT__image_rgb_stage2 = 0U;
        vlSelfRef.__PVT__image_rgb_stage1 = 0U;
    } else {
        vlSelfRef.__PVT__image_rgb_stage2 = vlSelfRef.__PVT__image_rgb_stage1;
        vlSelfRef.__PVT__image_rgb_stage1 = (((0x0280U 
                                               > (IData)(vlSymsp->TOP__vga_controller.pixel_x)) 
                                              & (0x01e0U 
                                                 > (IData)(vlSymsp->TOP__vga_controller.pixel_y)))
                                              ? ((0x00012bffU 
                                                  >= vlSelfRef.__PVT__img_addr)
                                                  ? vlSelfRef.framebuffer
                                                 [vlSelfRef.__PVT__img_addr]
                                                  : 0U)
                                              : 0U);
    }
    vlSelfRef.__PVT__ntile_x_d1 = (7U & ((IData)(vlSymsp->TOP__vga_controller.pixel_x) 
                                         >> 1U));
    vlSelfRef.__PVT__mode_select_d1 = ((1U & (~ (IData)(vlSymsp->TOP.rst))) 
                                       && (IData)(vlSymsp->TOP.mode_select));
    vlSelfRef.__PVT__video_on_d1 = ((1U & (~ (IData)(vlSymsp->TOP.rst))) 
                                    && (IData)(vlSymsp->TOP__vga_controller.video_on));
    vlSelfRef.__PVT__nametable_out = ((0x04afU >= (IData)(vlSelfRef.__PVT__nametable_addr))
                                       ? vlSelfRef.nametable
                                      [vlSelfRef.__PVT__nametable_addr]
                                       : 0U);
    vlSelfRef.__PVT__ntile_y_d1 = (7U & ((IData)(vlSymsp->TOP__vga_controller.pixel_y) 
                                         >> 1U));
}
