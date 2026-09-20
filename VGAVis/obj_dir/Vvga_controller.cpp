// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vvga_controller__pch.h"

//============================================================
// Constructors

Vvga_controller::Vvga_controller(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vvga_controller__Syms(contextp(), _vcname__, this)}
    , m_evalLoop{*this, /*convergeLimit:*/ 10000}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , vsync{vlSymsp->TOP.vsync}
    , hsync{vlSymsp->TOP.hsync}
    , rgb{vlSymsp->TOP.rgb}
    , vga_controller{vlSymsp->TOP.vga_controller}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vvga_controller::Vvga_controller(const char* _vcname__)
    : Vvga_controller(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vvga_controller::~Vvga_controller() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vvga_controller___024root___eval_debug_assertions(Vvga_controller___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD void Vvga_controller___024root___eval_static(Vvga_controller___024root* vlSelf);
VL_ATTR_COLD void Vvga_controller___024root___eval_initial(Vvga_controller___024root* vlSelf);
VL_ATTR_COLD bool Vvga_controller___024root___eval_stl(Vvga_controller___024root* vlSelf, CData/*0:0*/ firstIteration);
void Vvga_controller___024root___eval_sample(Vvga_controller___024root* vlSelf);
bool Vvga_controller___024root___eval_ico(Vvga_controller___024root* vlSelf, CData/*0:0*/ firstIteration);
bool Vvga_controller___024root___eval_act(Vvga_controller___024root* vlSelf);
bool Vvga_controller___024root___eval_inact(Vvga_controller___024root* vlSelf);
bool Vvga_controller___024root___eval_nba(Vvga_controller___024root* vlSelf);
bool Vvga_controller___024root___eval_obs(Vvga_controller___024root* vlSelf);
bool Vvga_controller___024root___eval_react(Vvga_controller___024root* vlSelf);
void Vvga_controller___024root___eval_postponed(Vvga_controller___024root* vlSelf);
VL_ATTR_COLD void Vvga_controller___024root___eval_final(Vvga_controller___024root* vlSelf);
VL_ATTR_COLD void Vvga_controller___024root___eval_dump_triggers__stl(Vvga_controller___024root* vlSelf);
VL_ATTR_COLD void Vvga_controller___024root___eval_dump_triggers__ico(Vvga_controller___024root* vlSelf);
VL_ATTR_COLD void Vvga_controller___024root___eval_dump_triggers__act(Vvga_controller___024root* vlSelf);
VL_ATTR_COLD void Vvga_controller___024root___eval_dump_triggers__nba(Vvga_controller___024root* vlSelf);
VL_ATTR_COLD void Vvga_controller___024root___eval_dump_triggers__obs(Vvga_controller___024root* vlSelf);
VL_ATTR_COLD void Vvga_controller___024root___eval_dump_triggers__react(Vvga_controller___024root* vlSelf);

void Vvga_controller::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vvga_controller::eval_step\n"); );
    m_evalLoop.eval();
}

void Vvga_controller::evalBegin() {
#ifdef VL_DEBUG
    // Debug assertions
    Vvga_controller___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
}

void Vvga_controller::evalEnd() {
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

void Vvga_controller::evalStatic() {
    Vvga_controller___024root___eval_static(&(vlSymsp->TOP));
}

void Vvga_controller::evalInitial() {
    Vvga_controller___024root___eval_initial(&(vlSymsp->TOP));
}

bool Vvga_controller::evalStl(bool firstIteration) {
    return Vvga_controller___024root___eval_stl(&(vlSymsp->TOP), firstIteration);
}

void Vvga_controller::evalSample() {
    Vvga_controller___024root___eval_sample(&(vlSymsp->TOP));
}

bool Vvga_controller::evalIco(bool firstIteration) {
    return Vvga_controller___024root___eval_ico(&(vlSymsp->TOP), firstIteration);
}

bool Vvga_controller::evalAct() {
    return Vvga_controller___024root___eval_act(&(vlSymsp->TOP));
}

bool Vvga_controller::evalInact() {
    return Vvga_controller___024root___eval_inact(&(vlSymsp->TOP));
}

bool Vvga_controller::evalNba() {
    return Vvga_controller___024root___eval_nba(&(vlSymsp->TOP));
}

bool Vvga_controller::evalObs() {
    return Vvga_controller___024root___eval_obs(&(vlSymsp->TOP));
}

bool Vvga_controller::evalReact() {
    return Vvga_controller___024root___eval_react(&(vlSymsp->TOP));
}

void Vvga_controller::evalPostponed() {
    Vvga_controller___024root___eval_postponed(&(vlSymsp->TOP));
}

void Vvga_controller::evalFinal() {
    Vvga_controller___024root___eval_final(&(vlSymsp->TOP));
}

VL_ATTR_COLD void Vvga_controller::dumpTriggersStl() {
    Vvga_controller___024root___eval_dump_triggers__stl(&(vlSymsp->TOP));
}

VL_ATTR_COLD void Vvga_controller::dumpTriggersIco() {
    Vvga_controller___024root___eval_dump_triggers__ico(&(vlSymsp->TOP));
}

VL_ATTR_COLD void Vvga_controller::dumpTriggersAct() {
    Vvga_controller___024root___eval_dump_triggers__act(&(vlSymsp->TOP));
}

VL_ATTR_COLD void Vvga_controller::dumpTriggersNba() {
    Vvga_controller___024root___eval_dump_triggers__nba(&(vlSymsp->TOP));
}

VL_ATTR_COLD void Vvga_controller::dumpTriggersObs() {
    Vvga_controller___024root___eval_dump_triggers__obs(&(vlSymsp->TOP));
}

VL_ATTR_COLD void Vvga_controller::dumpTriggersReact() {
    Vvga_controller___024root___eval_dump_triggers__react(&(vlSymsp->TOP));
}

//============================================================
// Events and timing
bool Vvga_controller::eventsPending() { return false; }

uint64_t Vvga_controller::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vvga_controller::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

VL_ATTR_COLD void Vvga_controller::final() {
    contextp()->executingFinal(true);
    evalFinal();
    contextp()->executingFinal(false);
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vvga_controller::hierName() const { return vlSymsp->name(); }
const char* Vvga_controller::modelName() const { return "Vvga_controller"; }
unsigned Vvga_controller::threads() const { return 1; }
void Vvga_controller::prepareClone() const { contextp()->prepareClone(); }
void Vvga_controller::atClone() const {
    contextp()->threadPoolpOnClone();
}
