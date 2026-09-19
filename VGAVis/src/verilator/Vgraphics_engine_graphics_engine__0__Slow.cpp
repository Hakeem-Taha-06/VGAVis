// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vgraphics_engine.h for the primary calling header

#include "Vgraphics_engine__pch.h"

VL_ATTR_COLD void Vgraphics_engine_graphics_engine___eval_initial__TOP__graphics_engine(Vgraphics_engine_graphics_engine* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vgraphics_engine_graphics_engine___eval_initial__TOP__graphics_engine\n"); );
    Vgraphics_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_READMEM_N(true, 3, 76800, 0, "initial_image.hex"s
                 ,  &(vlSelfRef.framebuffer), 0, ~0ULL);
}

VL_ATTR_COLD void Vgraphics_engine_graphics_engine___ctor_var_reset(Vgraphics_engine_graphics_engine* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vgraphics_engine_graphics_engine___ctor_var_reset\n"); );
    Vgraphics_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->pixel_x = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 13974469888022793920ull);
    vlSelf->pixel_y = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 2390262161722732155ull);
    vlSelf->video_on = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2323527325512367260ull);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rgb = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 11277054808258870952ull);
    for (int __Vi0 = 0; __Vi0 < 76800; ++__Vi0) {
        vlSelf->framebuffer[__Vi0] = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 18211612983462365535ull);
    }
    vlSelf->__PVT__addr = VL_SCOPED_RAND_RESET_I(17, __VscopeHash, 14934084843038794831ull);
}
