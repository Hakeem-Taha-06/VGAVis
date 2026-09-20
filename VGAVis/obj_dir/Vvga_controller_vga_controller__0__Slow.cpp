// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vvga_controller.h for the primary calling header

#include "Vvga_controller__pch.h"

VL_ATTR_COLD void Vvga_controller_vga_controller___eval_static__TOP__vga_controller(Vvga_controller_vga_controller* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vvga_controller_vga_controller___eval_static__TOP__vga_controller\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__sync_inst__DOT__h_count = 0U;
    vlSelfRef.__PVT__sync_inst__DOT__v_count = 0U;
    vlSelfRef.__PVT__sync_inst__DOT__pixel_clk = 0U;
}

VL_ATTR_COLD void Vvga_controller_vga_controller___ctor_var_reset(Vvga_controller_vga_controller* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vvga_controller_vga_controller___ctor_var_reset\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18209466448985614591ull);
    vlSelf->vsync = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18337175696363507471ull);
    vlSelf->hsync = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2999247747110030874ull);
    vlSelf->rgb = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 11277054808258870952ull);
    vlSelf->video_on = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2323527325512367260ull);
    vlSelf->pixel_x = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 13974469888022793920ull);
    vlSelf->pixel_y = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 2390262161722732155ull);
}
