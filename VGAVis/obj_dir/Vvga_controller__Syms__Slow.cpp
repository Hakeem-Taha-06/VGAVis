// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vvga_controller__pch.h"

extern const VlVarTableEntry Vvga_controller_vga_controller__VpiVarTable0[];
extern const VlVarTableEntry Vvga_controller_graphics_engine__VpiVarTable1[];
extern const VlScopeTableEntry Vvga_controller__Syms__VpiScopeTable[];


// VPI VARIABLE/SCOPE TABLES
#if defined(__GNUC__)
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Winvalid-offsetof"
#endif
extern const VlVarTableEntry Vvga_controller_vga_controller__VpiVarTable0[] = {
    {"pixel_x", offsetof(Vvga_controller_vga_controller, pixel_x), VLVT_UINT16, (VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY|VLVF_NET), 0, 1, {9, 0, 0, 0, 0, 0}},
    {"pixel_y", offsetof(Vvga_controller_vga_controller, pixel_y), VLVT_UINT16, (VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY|VLVF_NET), 0, 1, {9, 0, 0, 0, 0, 0}},
    {"video_on", offsetof(Vvga_controller_vga_controller, video_on), VLVT_UINT8, (VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY|VLVF_NET), 0, 0, {0, 0, 0, 0, 0, 0}},
};
extern const VlVarTableEntry Vvga_controller_graphics_engine__VpiVarTable1[] = {
    {"framebuffer", offsetof(Vvga_controller_graphics_engine, framebuffer), VLVT_UINT8, (VLVD_NODIR|VLVF_PUB_RW), 1, 1, {0, 76799, 2, 0, 0, 0}},
};
extern const VlScopeTableEntry Vvga_controller__Syms__VpiScopeTable[] = {
    {offsetof(Vvga_controller__Syms, __Vscopep_vga_controller), "vga_controller", "vga_controller", "<null>", 0, VerilatedScope::SCOPE_OTHER},
    {offsetof(Vvga_controller__Syms, __Vscopep_vga_controller__gfx_inst), "vga_controller.gfx_inst", "gfx_inst", "<null>", 0, VerilatedScope::SCOPE_OTHER},
};
#if defined(__GNUC__)
# pragma GCC diagnostic pop
#endif
Vvga_controller__Syms::Vvga_controller__Syms(VerilatedContext* contextp, const char* namep, Vvga_controller* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    , __Vm_didInit{modelp->m_didInit}
    // Setup top module instance
    , TOP{this, namep}
{
    // Check resources
    Verilated::stackCheck(214);
    // Setup sub module instances
    TOP__vga_controller.ctor(this, "vga_controller");
    TOP__vga_controller__gfx_inst.ctor(this, "vga_controller.gfx_inst");
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-12);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    TOP.vga_controller = &TOP__vga_controller;
    TOP__vga_controller.gfx_inst = &TOP__vga_controller__gfx_inst;
    // Setup scopes
    VerilatedScope::scopesConstructFromTable(Vvga_controller__Syms__VpiScopeTable, 2, this);
    // Setup export functions - final: 0
    // Setup export functions - final: 1
    // Setup public variables
    __Vscopep_vga_controller->varsInsertFromTable(Vvga_controller_vga_controller__VpiVarTable0, 3, &(TOP__vga_controller));
    __Vscopep_vga_controller__gfx_inst->varsInsertFromTable(Vvga_controller_graphics_engine__VpiVarTable1, 1, &(TOP__vga_controller__gfx_inst));
}

Vvga_controller__Syms::~Vvga_controller__Syms() {
    // Tear down scopes
    VL_DO_CLEAR(delete __Vscopep_vga_controller, __Vscopep_vga_controller = nullptr);
    VL_DO_CLEAR(delete __Vscopep_vga_controller__gfx_inst, __Vscopep_vga_controller__gfx_inst = nullptr);
    // Tear down sub module instances
    TOP__vga_controller__gfx_inst.dtor();
    TOP__vga_controller.dtor();
}
