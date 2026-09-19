// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vgraphics_engine__pch.h"

//============================================================
// Constructors

Vgraphics_engine::Vgraphics_engine(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vgraphics_engine__Syms(contextp(), _vcname__, this)}
    , m_evalLoop{*this, /*convergeLimit:*/ 10000}
    , clk{vlSymsp->TOP.clk}
    , video_on{vlSymsp->TOP.video_on}
    , rgb{vlSymsp->TOP.rgb}
    , pixel_x{vlSymsp->TOP.pixel_x}
    , pixel_y{vlSymsp->TOP.pixel_y}
    , graphics_engine{vlSymsp->TOP.graphics_engine}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vgraphics_engine::Vgraphics_engine(const char* _vcname__)
    : Vgraphics_engine(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vgraphics_engine::~Vgraphics_engine() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vgraphics_engine___024root___eval_debug_assertions(Vgraphics_engine___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD void Vgraphics_engine___024root___eval_static(Vgraphics_engine___024root* vlSelf);
VL_ATTR_COLD void Vgraphics_engine___024root___eval_initial(Vgraphics_engine___024root* vlSelf);
VL_ATTR_COLD bool Vgraphics_engine___024root___eval_stl(Vgraphics_engine___024root* vlSelf, CData/*0:0*/ firstIteration);
void Vgraphics_engine___024root___eval_sample(Vgraphics_engine___024root* vlSelf);
bool Vgraphics_engine___024root___eval_ico(Vgraphics_engine___024root* vlSelf, CData/*0:0*/ firstIteration);
bool Vgraphics_engine___024root___eval_act(Vgraphics_engine___024root* vlSelf);
bool Vgraphics_engine___024root___eval_inact(Vgraphics_engine___024root* vlSelf);
bool Vgraphics_engine___024root___eval_nba(Vgraphics_engine___024root* vlSelf);
bool Vgraphics_engine___024root___eval_obs(Vgraphics_engine___024root* vlSelf);
bool Vgraphics_engine___024root___eval_react(Vgraphics_engine___024root* vlSelf);
void Vgraphics_engine___024root___eval_postponed(Vgraphics_engine___024root* vlSelf);
VL_ATTR_COLD void Vgraphics_engine___024root___eval_final(Vgraphics_engine___024root* vlSelf);
VL_ATTR_COLD void Vgraphics_engine___024root___eval_dump_triggers__stl(Vgraphics_engine___024root* vlSelf);
VL_ATTR_COLD void Vgraphics_engine___024root___eval_dump_triggers__ico(Vgraphics_engine___024root* vlSelf);
VL_ATTR_COLD void Vgraphics_engine___024root___eval_dump_triggers__act(Vgraphics_engine___024root* vlSelf);
VL_ATTR_COLD void Vgraphics_engine___024root___eval_dump_triggers__nba(Vgraphics_engine___024root* vlSelf);
VL_ATTR_COLD void Vgraphics_engine___024root___eval_dump_triggers__obs(Vgraphics_engine___024root* vlSelf);
VL_ATTR_COLD void Vgraphics_engine___024root___eval_dump_triggers__react(Vgraphics_engine___024root* vlSelf);

void Vgraphics_engine::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vgraphics_engine::eval_step\n"); );
    m_evalLoop.eval();
}

void Vgraphics_engine::evalBegin() {
#ifdef VL_DEBUG
    // Debug assertions
    Vgraphics_engine___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
}

void Vgraphics_engine::evalEnd() {
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

void Vgraphics_engine::evalStatic() {
    Vgraphics_engine___024root___eval_static(&(vlSymsp->TOP));
}

void Vgraphics_engine::evalInitial() {
    Vgraphics_engine___024root___eval_initial(&(vlSymsp->TOP));
}

bool Vgraphics_engine::evalStl(bool firstIteration) {
    return Vgraphics_engine___024root___eval_stl(&(vlSymsp->TOP), firstIteration);
}

void Vgraphics_engine::evalSample() {
    Vgraphics_engine___024root___eval_sample(&(vlSymsp->TOP));
}

bool Vgraphics_engine::evalIco(bool firstIteration) {
    return Vgraphics_engine___024root___eval_ico(&(vlSymsp->TOP), firstIteration);
}

bool Vgraphics_engine::evalAct() {
    return Vgraphics_engine___024root___eval_act(&(vlSymsp->TOP));
}

bool Vgraphics_engine::evalInact() {
    return Vgraphics_engine___024root___eval_inact(&(vlSymsp->TOP));
}

bool Vgraphics_engine::evalNba() {
    return Vgraphics_engine___024root___eval_nba(&(vlSymsp->TOP));
}

bool Vgraphics_engine::evalObs() {
    return Vgraphics_engine___024root___eval_obs(&(vlSymsp->TOP));
}

bool Vgraphics_engine::evalReact() {
    return Vgraphics_engine___024root___eval_react(&(vlSymsp->TOP));
}

void Vgraphics_engine::evalPostponed() {
    Vgraphics_engine___024root___eval_postponed(&(vlSymsp->TOP));
}

void Vgraphics_engine::evalFinal() {
    Vgraphics_engine___024root___eval_final(&(vlSymsp->TOP));
}

VL_ATTR_COLD void Vgraphics_engine::dumpTriggersStl() {
    Vgraphics_engine___024root___eval_dump_triggers__stl(&(vlSymsp->TOP));
}

VL_ATTR_COLD void Vgraphics_engine::dumpTriggersIco() {
    Vgraphics_engine___024root___eval_dump_triggers__ico(&(vlSymsp->TOP));
}

VL_ATTR_COLD void Vgraphics_engine::dumpTriggersAct() {
    Vgraphics_engine___024root___eval_dump_triggers__act(&(vlSymsp->TOP));
}

VL_ATTR_COLD void Vgraphics_engine::dumpTriggersNba() {
    Vgraphics_engine___024root___eval_dump_triggers__nba(&(vlSymsp->TOP));
}

VL_ATTR_COLD void Vgraphics_engine::dumpTriggersObs() {
    Vgraphics_engine___024root___eval_dump_triggers__obs(&(vlSymsp->TOP));
}

VL_ATTR_COLD void Vgraphics_engine::dumpTriggersReact() {
    Vgraphics_engine___024root___eval_dump_triggers__react(&(vlSymsp->TOP));
}

//============================================================
// Events and timing
bool Vgraphics_engine::eventsPending() { return false; }

uint64_t Vgraphics_engine::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vgraphics_engine::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

VL_ATTR_COLD void Vgraphics_engine::final() {
    contextp()->executingFinal(true);
    evalFinal();
    contextp()->executingFinal(false);
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vgraphics_engine::hierName() const { return vlSymsp->name(); }
const char* Vgraphics_engine::modelName() const { return "Vgraphics_engine"; }
unsigned Vgraphics_engine::threads() const { return 1; }
void Vgraphics_engine::prepareClone() const { contextp()->prepareClone(); }
void Vgraphics_engine::atClone() const {
    contextp()->threadPoolpOnClone();
}
