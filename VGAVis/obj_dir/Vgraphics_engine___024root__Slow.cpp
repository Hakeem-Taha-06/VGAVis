// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vgraphics_engine.h for the primary calling header

#include "Vgraphics_engine__pch.h"

void Vgraphics_engine___024root___ctor_var_reset(Vgraphics_engine___024root* vlSelf);

Vgraphics_engine___024root::Vgraphics_engine___024root(Vgraphics_engine__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vgraphics_engine___024root___ctor_var_reset(this);
}

Vgraphics_engine___024root::~Vgraphics_engine___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
