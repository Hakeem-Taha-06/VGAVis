// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VVGA_CONTROLLER__SYMS_H_
#define VERILATED_VVGA_CONTROLLER__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vvga_controller.h"

// INCLUDE MODULE CLASSES
#include "Vvga_controller___024root.h"
#include "Vvga_controller_vga_controller.h"
#include "Vvga_controller_graphics_engine.h"

// DPI TYPES for DPI Export callbacks (Internal use)

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vvga_controller__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vvga_controller* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool& __Vm_didInit;

    // MODULE INSTANCE STATE
    Vvga_controller___024root      TOP;
    Vvga_controller_vga_controller TOP__vga_controller;
    Vvga_controller_graphics_engine TOP__vga_controller__gfx_inst;

    // SCOPE NAMES
    VerilatedScope* __Vscopep_vga_controller;
    VerilatedScope* __Vscopep_vga_controller__gfx_inst;

    // CONSTRUCTORS
    Vvga_controller__Syms(VerilatedContext* contextp, const char* namep, Vvga_controller* modelp);
    ~Vvga_controller__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
