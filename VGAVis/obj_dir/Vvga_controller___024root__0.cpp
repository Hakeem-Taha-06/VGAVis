// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vvga_controller.h for the primary calling header

#include "Vvga_controller__pch.h"

void Vvga_controller___024root___eval_sample(Vvga_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___eval_sample\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vvga_controller___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 2> &triggers, const std::string &tag);
#endif  // VL_DEBUG
bool Vvga_controller___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 2> &in);
void Vvga_controller_graphics_engine___ico_sequent__TOP__vga_controller__gfx_inst__0(Vvga_controller_graphics_engine* vlSelf);

bool Vvga_controller___024root___eval_ico(Vvga_controller___024root* vlSelf, CData/*0:0*/ firstIteration) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___eval_ico\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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
                                                        ((((IData)(vlSelfRef.rst) 
                                                           != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__rst__0)) 
                                                          << 1U) 
                                                         | ((IData)(vlSelfRef.clk) 
                                                            != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0)))));
        vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
        vlSelfRef.__Vtrigprevexpr___TOP__rst__0 = vlSelfRef.rst;
        if (VL_UNLIKELY(((1U & (~ (IData)(vlSelfRef.__VicoDidInit)))))) {
            vlSelfRef.__VicoDidInit = 1U;
            vlSelfRef.__VicoTriggered[0U] = (1ULL | vlSelfRef.__VicoTriggered[0U]);
            vlSelfRef.__VicoTriggered[0U] = (2ULL | vlSelfRef.__VicoTriggered[0U]);
        }
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vvga_controller___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
    __VicoExecute = Vvga_controller___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        {
            // Inlined CFunc: _eval_body__ico
            if ((1ULL & vlSelfRef.__VicoTriggered[1U])) {
                Vvga_controller_graphics_engine___ico_sequent__TOP__vga_controller__gfx_inst__0((&vlSymsp->TOP__vga_controller__gfx_inst));
            }
        }
    }
    return (__VicoExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vvga_controller___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
void Vvga_controller___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in);

bool Vvga_controller___024root___eval_act(Vvga_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___eval_act\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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
        Vvga_controller___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vvga_controller___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

bool Vvga_controller___024root___eval_inact(Vvga_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___eval_inact\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    return (0U);
}

bool Vvga_controller___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);
void Vvga_controller_vga_controller___nba_sequent__TOP__vga_controller__0(Vvga_controller_vga_controller* vlSelf);
void Vvga_controller_graphics_engine___nba_sequent__TOP__vga_controller__gfx_inst__0(Vvga_controller_graphics_engine* vlSelf);
void Vvga_controller_vga_controller___nba_sequent__TOP__vga_controller__1(Vvga_controller_vga_controller* vlSelf);
void Vvga_controller___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out);

bool Vvga_controller___024root___eval_nba(Vvga_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___eval_nba\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vvga_controller___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        {
            // Inlined CFunc: _eval_body__nba
            if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
                Vvga_controller_vga_controller___nba_sequent__TOP__vga_controller__0((&vlSymsp->TOP__vga_controller));
                Vvga_controller_graphics_engine___nba_sequent__TOP__vga_controller__gfx_inst__0((&vlSymsp->TOP__vga_controller__gfx_inst));
                {
                    // Inlined CFunc: _nba_sequent__TOP__0
                    vlSelfRef.vsync = (1U & (~ ((0x01eaU 
                                                 <= (IData)(vlSymsp->TOP__vga_controller.__PVT__sync_inst__DOT__v_count)) 
                                                & (0x01ecU 
                                                   > (IData)(vlSymsp->TOP__vga_controller.__PVT__sync_inst__DOT__v_count)))));
                    vlSelfRef.hsync = (1U & (~ ((0x0290U 
                                                 <= (IData)(vlSymsp->TOP__vga_controller.__PVT__sync_inst__DOT__h_count)) 
                                                & (0x02f0U 
                                                   > (IData)(vlSymsp->TOP__vga_controller.__PVT__sync_inst__DOT__h_count)))));
                    vlSelfRef.rgb = vlSymsp->TOP__vga_controller__gfx_inst.__PVT__rgb;
                }
                Vvga_controller_vga_controller___nba_sequent__TOP__vga_controller__1((&vlSymsp->TOP__vga_controller));
                Vvga_controller_graphics_engine___ico_sequent__TOP__vga_controller__gfx_inst__0((&vlSymsp->TOP__vga_controller__gfx_inst));
            }
        }
        Vvga_controller___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

bool Vvga_controller___024root___eval_obs(Vvga_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___eval_obs\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    return (0U);
}

bool Vvga_controller___024root___eval_react(Vvga_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___eval_react\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    return (0U);
}

void Vvga_controller___024root___eval_postponed(Vvga_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___eval_postponed\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

bool Vvga_controller___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 2> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___trigger_anySet__ico\n"); );
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

bool Vvga_controller___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___trigger_anySet__act\n"); );
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

void Vvga_controller___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

void Vvga_controller___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___trigger_clear__act\n"); );
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
void Vvga_controller___024root___eval_debug_assertions(Vvga_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvga_controller___024root___eval_debug_assertions\n"); );
    Vvga_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.rst & 0xfeU)))) {
        Verilated::overWidthError("rst");
    }
}
#endif  // VL_DEBUG
