// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vvga_controller.h for the primary calling header

#include "Vvga_controller__pch.h"

void Vvga_controller___024root___ctor_var_reset(Vvga_controller___024root* vlSelf);

Vvga_controller___024root::Vvga_controller___024root(Vvga_controller__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vvga_controller___024root___ctor_var_reset(this);
}

Vvga_controller___024root::~Vvga_controller___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
