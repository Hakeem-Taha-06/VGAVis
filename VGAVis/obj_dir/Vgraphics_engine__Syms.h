// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VGRAPHICS_ENGINE__SYMS_H_
#define VERILATED_VGRAPHICS_ENGINE__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vgraphics_engine.h"

// INCLUDE MODULE CLASSES
#include "Vgraphics_engine___024root.h"
#include "Vgraphics_engine_graphics_engine.h"

// DPI TYPES for DPI Export callbacks (Internal use)

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vgraphics_engine__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vgraphics_engine* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool& __Vm_didInit;

    // MODULE INSTANCE STATE
    Vgraphics_engine___024root     TOP;
    Vgraphics_engine_graphics_engine TOP__graphics_engine;

    // SCOPE NAMES
    VerilatedScope* __Vscopep_graphics_engine;

    // CONSTRUCTORS
    Vgraphics_engine__Syms(VerilatedContext* contextp, const char* namep, Vgraphics_engine* modelp);
    ~Vgraphics_engine__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
