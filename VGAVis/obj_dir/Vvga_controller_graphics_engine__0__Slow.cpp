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
    VL_READMEM_N(true, 8, 1200, 0, "nametable.hex"s
                 ,  &(vlSelfRef.nametable), 0, ~0ULL);
    VL_READMEM_N(true, 16, 1024, 0, "pattern_table.hex"s
                 ,  &(vlSelfRef.pattern_table), 0, ~0ULL);
    VL_READMEM_N(true, 3, 8, 0, "palette.hex"s,  &(vlSelfRef.palette_mem)
                 , 0, ~0ULL);
}

VL_ATTR_COLD void Vvga_controller_graphics_engine___ctor_var_reset(Vvga_controller_graphics_engine* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vvga_controller_graphics_engine___ctor_var_reset\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->__PVT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->__PVT__rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18209466448985614591ull);
    vlSelf->__PVT__mode_select = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13075617197383548380ull);
    vlSelf->__PVT__video_on = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2323527325512367260ull);
    vlSelf->__PVT__pixel_x = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 13974469888022793920ull);
    vlSelf->__PVT__pixel_y = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 2390262161722732155ull);
    vlSelf->__PVT__rgb = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 11277054808258870952ull);
    vlSelf->__PVT__video_on_d1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12512862987182476423ull);
    vlSelf->__PVT__video_on_d2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2965109128664278746ull);
    vlSelf->__PVT__mode_select_d1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2370191371615824941ull);
    vlSelf->__PVT__mode_select_d2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4201750258019206284ull);
    for (int __Vi0 = 0; __Vi0 < 76800; ++__Vi0) {
        vlSelf->framebuffer[__Vi0] = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 18211612983462365535ull);
    }
    vlSelf->__PVT__img_addr = VL_SCOPED_RAND_RESET_I(17, __VscopeHash, 18350948880704197851ull);
    vlSelf->__PVT__image_rgb_stage1 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 9122025079499072086ull);
    vlSelf->__PVT__image_rgb_stage2 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 8479593739366382736ull);
    vlSelf->__PVT__nametable_addr = VL_SCOPED_RAND_RESET_I(11, __VscopeHash, 97669035911118824ull);
    for (int __Vi0 = 0; __Vi0 < 1200; ++__Vi0) {
        vlSelf->nametable[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 6664583443845431641ull);
    }
    vlSelf->__PVT__nametable_out = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 276709766697098977ull);
    vlSelf->__PVT__ntile_x_d1 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 5650172839827901921ull);
    vlSelf->__PVT__ntile_x_d2 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 6770765007489861353ull);
    vlSelf->__PVT__ntile_y_d1 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 10322458569158566218ull);
    for (int __Vi0 = 0; __Vi0 < 1024; ++__Vi0) {
        vlSelf->pattern_table[__Vi0] = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 17502487159325143375ull);
    }
    vlSelf->__PVT__pattern_row = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 513703324920425340ull);
    vlSelf->__PVT__palette_sel_d1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14619489460492748729ull);
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->palette_mem[__Vi0] = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 14766850398440988104ull);
    }
}
