// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vgraphics_engine__pch.h"

extern const VlVarTableEntry Vgraphics_engine_graphics_engine__VpiVarTable0[];
extern const VlScopeTableEntry Vgraphics_engine__Syms__VpiScopeTable[];


// VPI VARIABLE/SCOPE TABLES
#if defined(__GNUC__)
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Winvalid-offsetof"
#endif
extern const VlVarTableEntry Vgraphics_engine_graphics_engine__VpiVarTable0[] = {
    {"framebuffer", offsetof(Vgraphics_engine_graphics_engine, framebuffer), VLVT_UINT8, (VLVD_NODIR|VLVF_PUB_RW), 1, 1, {0, 76799, 2, 0, 0, 0}},
};
extern const VlScopeTableEntry Vgraphics_engine__Syms__VpiScopeTable[] = {
    {offsetof(Vgraphics_engine__Syms, __Vscopep_graphics_engine), "graphics_engine", "graphics_engine", "<null>", 0, VerilatedScope::SCOPE_OTHER},
};
#if defined(__GNUC__)
# pragma GCC diagnostic pop
#endif
Vgraphics_engine__Syms::Vgraphics_engine__Syms(VerilatedContext* contextp, const char* namep, Vgraphics_engine* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    , __Vm_didInit{modelp->m_didInit}
    // Setup top module instance
    , TOP{this, namep}
{
    // Check resources
    Verilated::stackCheck(209);
    // Setup sub module instances
    TOP__graphics_engine.ctor(this, "graphics_engine");
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-12);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    TOP.graphics_engine = &TOP__graphics_engine;
    // Setup scopes
    VerilatedScope::scopesConstructFromTable(Vgraphics_engine__Syms__VpiScopeTable, 1, this);
    // Setup export functions - final: 0
    // Setup export functions - final: 1
    // Setup public variables
    __Vscopep_graphics_engine->varsInsertFromTable(Vgraphics_engine_graphics_engine__VpiVarTable0, 1, &(TOP__graphics_engine));
}

Vgraphics_engine__Syms::~Vgraphics_engine__Syms() {
    // Tear down scopes
    VL_DO_CLEAR(delete __Vscopep_graphics_engine, __Vscopep_graphics_engine = nullptr);
    // Tear down sub module instances
    TOP__graphics_engine.dtor();
}
