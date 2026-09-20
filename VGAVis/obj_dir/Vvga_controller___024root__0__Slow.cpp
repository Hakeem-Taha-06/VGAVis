// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vvga_controller.h for the primary calling header

#include "Vvga_controller__pch.h"

VL_ATTR_COLD void Vvga_controller_vga_controller___eval_static__TOP__vga_controller(Vvga_controller_vga_controller* vlSelf);

VL_ATTR_COLD void Vvga_controller___024root___eval_static(Vvga_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___eval_static\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vvga_controller_vga_controller___eval_static__TOP__vga_controller((&vlSymsp->TOP__vga_controller));
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst__0 = vlSelfRef.rst;
    vlSelfRef.__Vtrigprevexpr___TOP__clk__1 = vlSelfRef.clk;
}

VL_ATTR_COLD void Vvga_controller_graphics_engine___eval_initial__TOP__vga_controller__gfx_inst(Vvga_controller_graphics_engine* vlSelf);

VL_ATTR_COLD void Vvga_controller___024root___eval_initial(Vvga_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___eval_initial\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vvga_controller_graphics_engine___eval_initial__TOP__vga_controller__gfx_inst((&vlSymsp->TOP__vga_controller__gfx_inst));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vvga_controller___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vvga_controller___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);
void Vvga_controller_vga_controller___nba_sequent__TOP__vga_controller__1(Vvga_controller_vga_controller* vlSelf);
void Vvga_controller_graphics_engine___ico_sequent__TOP__vga_controller__gfx_inst__0(Vvga_controller_graphics_engine* vlSelf);

VL_ATTR_COLD bool Vvga_controller___024root___eval_stl(Vvga_controller___024root* vlSelf, CData/*0:0*/ firstIteration) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___eval_stl\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(firstIteration)));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vvga_controller___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vvga_controller___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        {
            // Inlined CFunc: _eval_body__stl
            if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
                {
                    // Inlined CFunc: _stl_sequent__TOP__0
                    vlSelfRef.rgb = vlSymsp->TOP__vga_controller__gfx_inst.__PVT__rgb;
                    vlSelfRef.hsync = (1U & (~ ((0x0290U 
                                                 <= (IData)(vlSymsp->TOP__vga_controller.__PVT__sync_inst__DOT__h_count)) 
                                                & (0x02f0U 
                                                   > (IData)(vlSymsp->TOP__vga_controller.__PVT__sync_inst__DOT__h_count)))));
                    vlSelfRef.vsync = (1U & (~ ((0x01eaU 
                                                 <= (IData)(vlSymsp->TOP__vga_controller.__PVT__sync_inst__DOT__v_count)) 
                                                & (0x01ecU 
                                                   > (IData)(vlSymsp->TOP__vga_controller.__PVT__sync_inst__DOT__v_count)))));
                }
                Vvga_controller_vga_controller___nba_sequent__TOP__vga_controller__1((&vlSymsp->TOP__vga_controller));
                Vvga_controller_graphics_engine___ico_sequent__TOP__vga_controller__gfx_inst__0((&vlSymsp->TOP__vga_controller__gfx_inst));
            }
        }
    }
    return (__VstlExecute);
}

VL_ATTR_COLD void Vvga_controller___024root___eval_dump_triggers__stl(Vvga_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___eval_dump_triggers__stl\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    Vvga_controller___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vvga_controller___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 2> &triggers, const std::string &tag);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vvga_controller___024root___eval_dump_triggers__ico(Vvga_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___eval_dump_triggers__ico\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    Vvga_controller___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vvga_controller___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vvga_controller___024root___eval_dump_triggers__act(Vvga_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___eval_dump_triggers__act\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    Vvga_controller___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
}

VL_ATTR_COLD void Vvga_controller___024root___eval_dump_triggers__nba(Vvga_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___eval_dump_triggers__nba\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    Vvga_controller___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
}

VL_ATTR_COLD void Vvga_controller___024root___eval_dump_triggers__obs(Vvga_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___eval_dump_triggers__obs\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vvga_controller___024root___eval_dump_triggers__react(Vvga_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___eval_dump_triggers__react\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vvga_controller___024root___eval_final(Vvga_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___eval_final\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vvga_controller___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vvga_controller___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vvga_controller___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___trigger_anySet__stl\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

bool Vvga_controller___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 2> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vvga_controller___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 2> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(Vvga_controller___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @( clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @( rst)\n");
    }
    if ((1U & (IData)(triggers[1U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 64 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

bool Vvga_controller___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vvga_controller___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vvga_controller___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vvga_controller___024root___ctor_var_reset(Vvga_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___ctor_var_reset\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18209466448985614591ull);
    vlSelf->vsync = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18337175696363507471ull);
    vlSelf->hsync = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2999247747110030874ull);
    vlSelf->rgb = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 11277054808258870952ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__VicoTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__rst__0 = 0;
    vlSelf->__VicoDidInit = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__1 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}
