// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vgraphics_engine.h for the primary calling header

#include "Vgraphics_engine__pch.h"

void Vgraphics_engine___024root___eval_sample(Vgraphics_engine___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___eval_sample\n"); );
    Vgraphics_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vgraphics_engine___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 2> &triggers, const std::string &tag);
#endif  // VL_DEBUG
bool Vgraphics_engine___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 2> &in);
void Vgraphics_engine_graphics_engine___ico_comb__TOP__graphics_engine__0(Vgraphics_engine_graphics_engine* vlSelf);

bool Vgraphics_engine___024root___eval_ico(Vgraphics_engine___024root* vlSelf, CData/*0:0*/ firstIteration) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___eval_ico\n"); );
    Vgraphics_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VicoExecute;
    // Body
    vlSelfRef.__VicoTriggered[1U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VicoTriggered[1U]) 
                                     | (IData)((IData)(firstIteration)));
    {
        // Inlined CFunc: _eval_triggers_vec__ico
        vlSelfRef.__VicoTriggered[0U] = (QData)((IData)(
                                                        (((((IData)(vlSelfRef.clk) 
                                                            != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0)) 
                                                           << 3U) 
                                                          | (((IData)(vlSelfRef.video_on) 
                                                              != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__video_on__0)) 
                                                             << 2U)) 
                                                         | ((((IData)(vlSelfRef.pixel_y) 
                                                              != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__pixel_y__0)) 
                                                             << 1U) 
                                                            | ((IData)(vlSelfRef.pixel_x) 
                                                               != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__pixel_x__0))))));
        vlSelfRef.__Vtrigprevexpr___TOP__pixel_x__0 
            = vlSelfRef.pixel_x;
        vlSelfRef.__Vtrigprevexpr___TOP__pixel_y__0 
            = vlSelfRef.pixel_y;
        vlSelfRef.__Vtrigprevexpr___TOP__video_on__0 
            = vlSelfRef.video_on;
        vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
        if (VL_UNLIKELY(((1U & (~ (IData)(vlSelfRef.__VicoDidInit)))))) {
            vlSelfRef.__VicoDidInit = 1U;
            vlSelfRef.__VicoTriggered[0U] = (1ULL | vlSelfRef.__VicoTriggered[0U]);
            vlSelfRef.__VicoTriggered[0U] = (2ULL | vlSelfRef.__VicoTriggered[0U]);
            vlSelfRef.__VicoTriggered[0U] = (4ULL | vlSelfRef.__VicoTriggered[0U]);
            vlSelfRef.__VicoTriggered[0U] = (8ULL | vlSelfRef.__VicoTriggered[0U]);
        }
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vgraphics_engine___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
    __VicoExecute = Vgraphics_engine___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        {
            // Inlined CFunc: _eval_body__ico
            if ((3ULL & vlSelfRef.__VicoTriggered[0U])) {
                Vgraphics_engine_graphics_engine___ico_comb__TOP__graphics_engine__0((&vlSymsp->TOP__graphics_engine));
            }
        }
    }
    return (__VicoExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vgraphics_engine___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
void Vgraphics_engine___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in);

bool Vgraphics_engine___024root___eval_act(Vgraphics_engine___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___eval_act\n"); );
    Vgraphics_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    {
        // Inlined CFunc: _eval_triggers_vec__act
        vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                        ((IData)(vlSelfRef.clk) 
                                                         & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__1)))));
        vlSelfRef.__Vtrigprevexpr___TOP__clk__1 = vlSelfRef.clk;
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vgraphics_engine___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vgraphics_engine___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

bool Vgraphics_engine___024root___eval_inact(Vgraphics_engine___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___eval_inact\n"); );
    Vgraphics_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    return (0U);
}

bool Vgraphics_engine___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);
void Vgraphics_engine_graphics_engine___nba_sequent__TOP__graphics_engine__0(Vgraphics_engine_graphics_engine* vlSelf);
void Vgraphics_engine___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out);

bool Vgraphics_engine___024root___eval_nba(Vgraphics_engine___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___eval_nba\n"); );
    Vgraphics_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vgraphics_engine___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        {
            // Inlined CFunc: _eval_body__nba
            if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
                Vgraphics_engine_graphics_engine___nba_sequent__TOP__graphics_engine__0((&vlSymsp->TOP__graphics_engine));
                {
                    // Inlined CFunc: _nba_sequent__TOP__0
                    vlSelfRef.rgb = vlSymsp->TOP__graphics_engine.rgb;
                }
            }
        }
        Vgraphics_engine___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

bool Vgraphics_engine___024root___eval_obs(Vgraphics_engine___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___eval_obs\n"); );
    Vgraphics_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    return (0U);
}

bool Vgraphics_engine___024root___eval_react(Vgraphics_engine___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___eval_react\n"); );
    Vgraphics_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    return (0U);
}

void Vgraphics_engine___024root___eval_postponed(Vgraphics_engine___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___eval_postponed\n"); );
    Vgraphics_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

bool Vgraphics_engine___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 2> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___trigger_anySet__ico\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((2U > n));
    return (0U);
}

bool Vgraphics_engine___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___trigger_anySet__act\n"); );
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

void Vgraphics_engine___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

void Vgraphics_engine___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

#ifdef VL_DEBUG
void Vgraphics_engine___024root___eval_debug_assertions(Vgraphics_engine___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgraphics_engine___024root___eval_debug_assertions\n"); );
    Vgraphics_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.pixel_x & 0xfc00U)))) {
        Verilated::overWidthError("pixel_x");
    }
    if (VL_UNLIKELY(((vlSelfRef.pixel_y & 0xfc00U)))) {
        Verilated::overWidthError("pixel_y");
    }
    if (VL_UNLIKELY(((vlSelfRef.video_on & 0xfeU)))) {
        Verilated::overWidthError("video_on");
    }
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
}
#endif  // VL_DEBUG
