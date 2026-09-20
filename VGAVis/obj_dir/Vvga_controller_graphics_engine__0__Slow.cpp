// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vvga_controller.h for the primary calling header

#include "Vvga_controller__pch.h"

VL_ATTR_COLD void Vvga_controller_graphics_engine___eval_initial__TOP__vga_controller__gfx_inst(Vvga_controller_graphics_engine* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vvga_controller_graphics_engine___eval_initial__TOP__vga_controller__gfx_inst\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_READMEM_N(true, 3, 76800, 0, "initial_image.hex"s
                 ,  &(vlSelfRef.framebuffer), 0, ~0ULL);
}

VL_ATTR_COLD void Vvga_controller_graphics_engine___ctor_var_reset(Vvga_controller_graphics_engine* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vvga_controller_graphics_engine___ctor_var_reset\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->__PVT__pixel_x = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 13974469888022793920ull);
    vlSelf->__PVT__pixel_y = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 2390262161722732155ull);
    vlSelf->__PVT__video_on = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2323527325512367260ull);
    vlSelf->__PVT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->__PVT__rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18209466448985614591ull);
    vlSelf->__PVT__rgb = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 11277054808258870952ull);
    for (int __Vi0 = 0; __Vi0 < 76800; ++__Vi0) {
        vlSelf->framebuffer[__Vi0] = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 18211612983462365535ull);
    }
    vlSelf->__PVT__addr = VL_SCOPED_RAND_RESET_I(17, __VscopeHash, 14934084843038794831ull);
}
