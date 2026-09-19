// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vgraphics_engine.h for the primary calling header

#include "Vgraphics_engine__pch.h"

void Vgraphics_engine_graphics_engine___ctor_var_reset(Vgraphics_engine_graphics_engine* vlSelf);

Vgraphics_engine_graphics_engine::Vgraphics_engine_graphics_engine() = default;
Vgraphics_engine_graphics_engine::~Vgraphics_engine_graphics_engine() = default;

void Vgraphics_engine_graphics_engine::ctor(Vgraphics_engine__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vgraphics_engine_graphics_engine___ctor_var_reset(this);
}

void Vgraphics_engine_graphics_engine::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
