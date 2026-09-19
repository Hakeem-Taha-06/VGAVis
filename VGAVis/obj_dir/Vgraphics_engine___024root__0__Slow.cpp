// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vgraphics_engine.h for the primary calling header

#include "Vgraphics_engine__pch.h"

VL_ATTR_COLD void Vgraphics_engine___024root___eval_static(Vgraphics_engine___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___eval_static\n"); );
    Vgraphics_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__pixel_x__0 = vlSelfRef.pixel_x;
    vlSelfRef.__Vtrigprevexpr___TOP__pixel_y__0 = vlSelfRef.pixel_y;
    vlSelfRef.__Vtrigprevexpr___TOP__video_on__0 = vlSelfRef.video_on;
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__clk__1 = vlSelfRef.clk;
}

VL_ATTR_COLD void Vgraphics_engine_graphics_engine___eval_initial__TOP__graphics_engine(Vgraphics_engine_graphics_engine* vlSelf);

VL_ATTR_COLD void Vgraphics_engine___024root___eval_initial(Vgraphics_engine___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___eval_initial\n"); );
    Vgraphics_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vgraphics_engine_graphics_engine___eval_initial__TOP__graphics_engine((&vlSymsp->TOP__graphics_engine));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vgraphics_engine___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vgraphics_engine___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);
void Vgraphics_engine_graphics_engine___ico_comb__TOP__graphics_engine__0(Vgraphics_engine_graphics_engine* vlSelf);

VL_ATTR_COLD bool Vgraphics_engine___024root___eval_stl(Vgraphics_engine___024root* vlSelf, CData/*0:0*/ firstIteration) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___eval_stl\n"); );
    Vgraphics_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(firstIteration)));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vgraphics_engine___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vgraphics_engine___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        {
            // Inlined CFunc: _eval_body__stl
            if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
                {
                    // Inlined CFunc: _nba_sequent__TOP__0
                    vlSelfRef.rgb = vlSymsp->TOP__graphics_engine.rgb;
                }
                Vgraphics_engine_graphics_engine___ico_comb__TOP__graphics_engine__0((&vlSymsp->TOP__graphics_engine));
            }
        }
    }
    return (__VstlExecute);
}

VL_ATTR_COLD void Vgraphics_engine___024root___eval_dump_triggers__stl(Vgraphics_engine___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___eval_dump_triggers__stl\n"); );
    Vgraphics_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    Vgraphics_engine___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vgraphics_engine___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 2> &triggers, const std::string &tag);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vgraphics_engine___024root___eval_dump_triggers__ico(Vgraphics_engine___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___eval_dump_triggers__ico\n"); );
    Vgraphics_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    Vgraphics_engine___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vgraphics_engine___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vgraphics_engine___024root___eval_dump_triggers__act(Vgraphics_engine___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___eval_dump_triggers__act\n"); );
    Vgraphics_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    Vgraphics_engine___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
}

VL_ATTR_COLD void Vgraphics_engine___024root___eval_dump_triggers__nba(Vgraphics_engine___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___eval_dump_triggers__nba\n"); );
    Vgraphics_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    Vgraphics_engine___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
}

VL_ATTR_COLD void Vgraphics_engine___024root___eval_dump_triggers__obs(Vgraphics_engine___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___eval_dump_triggers__obs\n"); );
    Vgraphics_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vgraphics_engine___024root___eval_dump_triggers__react(Vgraphics_engine___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___eval_dump_triggers__react\n"); );
    Vgraphics_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vgraphics_engine___024root___eval_final(Vgraphics_engine___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___eval_final\n"); );
    Vgraphics_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vgraphics_engine___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vgraphics_engine___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vgraphics_engine___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___trigger_anySet__stl\n"); );
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

bool Vgraphics_engine___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 2> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vgraphics_engine___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 2> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(Vgraphics_engine___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @( pixel_x)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @( pixel_y)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @( video_on)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 3U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 3 is active: @( clk)\n");
    }
    if ((1U & (IData)(triggers[1U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 64 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

bool Vgraphics_engine___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vgraphics_engine___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vgraphics_engine___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vgraphics_engine___024root___ctor_var_reset(Vgraphics_engine___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___ctor_var_reset\n"); );
    Vgraphics_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->pixel_x = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 13974469888022793920ull);
    vlSelf->pixel_y = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 2390262161722732155ull);
    vlSelf->video_on = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2323527325512367260ull);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rgb = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 11277054808258870952ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__VicoTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__pixel_x__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__pixel_y__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__video_on__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    vlSelf->__VicoDidInit = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__1 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}
