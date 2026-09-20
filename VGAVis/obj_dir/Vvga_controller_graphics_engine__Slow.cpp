// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vvga_controller.h for the primary calling header

#include "Vvga_controller__pch.h"

void Vvga_controller_graphics_engine___ctor_var_reset(Vvga_controller_graphics_engine* vlSelf);

Vvga_controller_graphics_engine::Vvga_controller_graphics_engine() = default;
Vvga_controller_graphics_engine::~Vvga_controller_graphics_engine() = default;

void Vvga_controller_graphics_engine::ctor(Vvga_controller__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vvga_controller_graphics_engine___ctor_var_reset(this);
}

void Vvga_controller_graphics_engine::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
