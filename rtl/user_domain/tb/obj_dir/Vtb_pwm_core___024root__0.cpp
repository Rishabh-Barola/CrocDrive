// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_pwm_core.h for the primary calling header

#include "Vtb_pwm_core__pch.h"

VlCoroutine Vtb_pwm_core___024root___eval_initial__TOP__Vtiming__0(Vtb_pwm_core___024root* vlSelf);
VlCoroutine Vtb_pwm_core___024root___eval_initial__TOP__Vtiming__1(Vtb_pwm_core___024root* vlSelf);

void Vtb_pwm_core___024root___eval_initial(Vtb_pwm_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___eval_initial\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtb_pwm_core___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
    Vtb_pwm_core___024root___eval_initial__TOP__Vtiming__1(vlSelf);
}

VlCoroutine Vtb_pwm_core___024root___eval_initial__TOP__Vtiming__0(Vtb_pwm_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_pwm_core__DOT__clk_i = 0U;
    while (true) {
        co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                             nullptr, 
                                             "tb_pwm_core.sv", 
                                             45);
        vlSelfRef.tb_pwm_core__DOT__clk_i = (1U & (~ (IData)(vlSelfRef.tb_pwm_core__DOT__clk_i)));
    }
    co_return;
}

void Vtb_pwm_core___024root____VbeforeTrig_h9d9a0fdf__0(Vtb_pwm_core___024root* vlSelf, const char* __VeventDescription);

VlCoroutine Vtb_pwm_core___024root___eval_initial__TOP__Vtiming__1(Vtb_pwm_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ tb_pwm_core__DOT__unnamedblk1_1__DOT____Vrepeat0;
    tb_pwm_core__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__start_pwm__0__period;
    __Vtask_tb_pwm_core__DOT__start_pwm__0__period = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__start_pwm__0__duty;
    __Vtask_tb_pwm_core__DOT__start_pwm__0__duty = 0;
    CData/*0:0*/ __Vtask_tb_pwm_core__DOT__start_pwm__0__polarity;
    __Vtask_tb_pwm_core__DOT__start_pwm__0__polarity = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_cycles__1__period;
    __Vtask_tb_pwm_core__DOT__check_cycles__1__period = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_cycles__1__duty;
    __Vtask_tb_pwm_core__DOT__check_cycles__1__duty = 0;
    CData/*0:0*/ __Vtask_tb_pwm_core__DOT__check_cycles__1__polarity;
    __Vtask_tb_pwm_core__DOT__check_cycles__1__polarity = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_cycles__1__num_cycles;
    __Vtask_tb_pwm_core__DOT__check_cycles__1__num_cycles = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_cycles__1__unnamedblk1__DOT__i;
    __Vtask_tb_pwm_core__DOT__check_cycles__1__unnamedblk1__DOT__i = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_cycles__1__exp_counter;
    __Vtask_tb_pwm_core__DOT__check_cycles__1__exp_counter = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_current__2__exp_counter;
    __Vtask_tb_pwm_core__DOT__check_current__2__exp_counter = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_current__2__exp_period;
    __Vtask_tb_pwm_core__DOT__check_current__2__exp_period = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_current__2__exp_duty;
    __Vtask_tb_pwm_core__DOT__check_current__2__exp_duty = 0;
    CData/*0:0*/ __Vtask_tb_pwm_core__DOT__check_current__2__exp_polarity;
    __Vtask_tb_pwm_core__DOT__check_current__2__exp_polarity = 0;
    CData/*0:0*/ __Vtask_tb_pwm_core__DOT__check_current__2__exp_pwm;
    __Vtask_tb_pwm_core__DOT__check_current__2__exp_pwm = 0;
    CData/*0:0*/ __Vtask_tb_pwm_core__DOT__check_current__2__exp_done;
    __Vtask_tb_pwm_core__DOT__check_current__2__exp_done = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_current__2__exp_duty_clamped;
    __Vtask_tb_pwm_core__DOT__check_current__2__exp_duty_clamped = 0;
    CData/*0:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__3__Vfuncout;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__3__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__3__counter;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__3__counter = 0;
    IData/*31:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__3__period;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__3__period = 0;
    IData/*31:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__3__duty;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__3__duty = 0;
    CData/*0:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__3__polarity;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__3__polarity = 0;
    IData/*31:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__3__duty_clamped;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__3__duty_clamped = 0;
    CData/*0:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__3__raw;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__3__raw = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__start_pwm__4__period;
    __Vtask_tb_pwm_core__DOT__start_pwm__4__period = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__start_pwm__4__duty;
    __Vtask_tb_pwm_core__DOT__start_pwm__4__duty = 0;
    CData/*0:0*/ __Vtask_tb_pwm_core__DOT__start_pwm__4__polarity;
    __Vtask_tb_pwm_core__DOT__start_pwm__4__polarity = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_cycles__5__period;
    __Vtask_tb_pwm_core__DOT__check_cycles__5__period = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_cycles__5__duty;
    __Vtask_tb_pwm_core__DOT__check_cycles__5__duty = 0;
    CData/*0:0*/ __Vtask_tb_pwm_core__DOT__check_cycles__5__polarity;
    __Vtask_tb_pwm_core__DOT__check_cycles__5__polarity = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_cycles__5__num_cycles;
    __Vtask_tb_pwm_core__DOT__check_cycles__5__num_cycles = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_cycles__5__unnamedblk1__DOT__i;
    __Vtask_tb_pwm_core__DOT__check_cycles__5__unnamedblk1__DOT__i = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_cycles__5__exp_counter;
    __Vtask_tb_pwm_core__DOT__check_cycles__5__exp_counter = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_current__6__exp_counter;
    __Vtask_tb_pwm_core__DOT__check_current__6__exp_counter = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_current__6__exp_period;
    __Vtask_tb_pwm_core__DOT__check_current__6__exp_period = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_current__6__exp_duty;
    __Vtask_tb_pwm_core__DOT__check_current__6__exp_duty = 0;
    CData/*0:0*/ __Vtask_tb_pwm_core__DOT__check_current__6__exp_polarity;
    __Vtask_tb_pwm_core__DOT__check_current__6__exp_polarity = 0;
    CData/*0:0*/ __Vtask_tb_pwm_core__DOT__check_current__6__exp_pwm;
    __Vtask_tb_pwm_core__DOT__check_current__6__exp_pwm = 0;
    CData/*0:0*/ __Vtask_tb_pwm_core__DOT__check_current__6__exp_done;
    __Vtask_tb_pwm_core__DOT__check_current__6__exp_done = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_current__6__exp_duty_clamped;
    __Vtask_tb_pwm_core__DOT__check_current__6__exp_duty_clamped = 0;
    CData/*0:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__7__Vfuncout;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__7__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__7__counter;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__7__counter = 0;
    IData/*31:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__7__period;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__7__period = 0;
    IData/*31:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__7__duty;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__7__duty = 0;
    CData/*0:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__7__polarity;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__7__polarity = 0;
    IData/*31:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__7__duty_clamped;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__7__duty_clamped = 0;
    CData/*0:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__7__raw;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__7__raw = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__start_pwm__8__period;
    __Vtask_tb_pwm_core__DOT__start_pwm__8__period = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__start_pwm__8__duty;
    __Vtask_tb_pwm_core__DOT__start_pwm__8__duty = 0;
    CData/*0:0*/ __Vtask_tb_pwm_core__DOT__start_pwm__8__polarity;
    __Vtask_tb_pwm_core__DOT__start_pwm__8__polarity = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_cycles__9__period;
    __Vtask_tb_pwm_core__DOT__check_cycles__9__period = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_cycles__9__duty;
    __Vtask_tb_pwm_core__DOT__check_cycles__9__duty = 0;
    CData/*0:0*/ __Vtask_tb_pwm_core__DOT__check_cycles__9__polarity;
    __Vtask_tb_pwm_core__DOT__check_cycles__9__polarity = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_cycles__9__num_cycles;
    __Vtask_tb_pwm_core__DOT__check_cycles__9__num_cycles = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_cycles__9__unnamedblk1__DOT__i;
    __Vtask_tb_pwm_core__DOT__check_cycles__9__unnamedblk1__DOT__i = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_cycles__9__exp_counter;
    __Vtask_tb_pwm_core__DOT__check_cycles__9__exp_counter = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_current__10__exp_counter;
    __Vtask_tb_pwm_core__DOT__check_current__10__exp_counter = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_current__10__exp_period;
    __Vtask_tb_pwm_core__DOT__check_current__10__exp_period = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_current__10__exp_duty;
    __Vtask_tb_pwm_core__DOT__check_current__10__exp_duty = 0;
    CData/*0:0*/ __Vtask_tb_pwm_core__DOT__check_current__10__exp_polarity;
    __Vtask_tb_pwm_core__DOT__check_current__10__exp_polarity = 0;
    CData/*0:0*/ __Vtask_tb_pwm_core__DOT__check_current__10__exp_pwm;
    __Vtask_tb_pwm_core__DOT__check_current__10__exp_pwm = 0;
    CData/*0:0*/ __Vtask_tb_pwm_core__DOT__check_current__10__exp_done;
    __Vtask_tb_pwm_core__DOT__check_current__10__exp_done = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_current__10__exp_duty_clamped;
    __Vtask_tb_pwm_core__DOT__check_current__10__exp_duty_clamped = 0;
    CData/*0:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__11__Vfuncout;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__11__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__11__counter;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__11__counter = 0;
    IData/*31:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__11__period;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__11__period = 0;
    IData/*31:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__11__duty;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__11__duty = 0;
    CData/*0:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__11__polarity;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__11__polarity = 0;
    IData/*31:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__11__duty_clamped;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__11__duty_clamped = 0;
    CData/*0:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__11__raw;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__11__raw = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__start_pwm__12__period;
    __Vtask_tb_pwm_core__DOT__start_pwm__12__period = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__start_pwm__12__duty;
    __Vtask_tb_pwm_core__DOT__start_pwm__12__duty = 0;
    CData/*0:0*/ __Vtask_tb_pwm_core__DOT__start_pwm__12__polarity;
    __Vtask_tb_pwm_core__DOT__start_pwm__12__polarity = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_cycles__13__period;
    __Vtask_tb_pwm_core__DOT__check_cycles__13__period = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_cycles__13__duty;
    __Vtask_tb_pwm_core__DOT__check_cycles__13__duty = 0;
    CData/*0:0*/ __Vtask_tb_pwm_core__DOT__check_cycles__13__polarity;
    __Vtask_tb_pwm_core__DOT__check_cycles__13__polarity = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_cycles__13__num_cycles;
    __Vtask_tb_pwm_core__DOT__check_cycles__13__num_cycles = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_cycles__13__unnamedblk1__DOT__i;
    __Vtask_tb_pwm_core__DOT__check_cycles__13__unnamedblk1__DOT__i = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_cycles__13__exp_counter;
    __Vtask_tb_pwm_core__DOT__check_cycles__13__exp_counter = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_current__14__exp_counter;
    __Vtask_tb_pwm_core__DOT__check_current__14__exp_counter = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_current__14__exp_period;
    __Vtask_tb_pwm_core__DOT__check_current__14__exp_period = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_current__14__exp_duty;
    __Vtask_tb_pwm_core__DOT__check_current__14__exp_duty = 0;
    CData/*0:0*/ __Vtask_tb_pwm_core__DOT__check_current__14__exp_polarity;
    __Vtask_tb_pwm_core__DOT__check_current__14__exp_polarity = 0;
    CData/*0:0*/ __Vtask_tb_pwm_core__DOT__check_current__14__exp_pwm;
    __Vtask_tb_pwm_core__DOT__check_current__14__exp_pwm = 0;
    CData/*0:0*/ __Vtask_tb_pwm_core__DOT__check_current__14__exp_done;
    __Vtask_tb_pwm_core__DOT__check_current__14__exp_done = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__check_current__14__exp_duty_clamped;
    __Vtask_tb_pwm_core__DOT__check_current__14__exp_duty_clamped = 0;
    CData/*0:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__15__Vfuncout;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__15__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__15__counter;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__15__counter = 0;
    IData/*31:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__15__period;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__15__period = 0;
    IData/*31:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__15__duty;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__15__duty = 0;
    CData/*0:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__15__polarity;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__15__polarity = 0;
    IData/*31:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__15__duty_clamped;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__15__duty_clamped = 0;
    CData/*0:0*/ __Vfunc_tb_pwm_core__DOT__expected_pwm__15__raw;
    __Vfunc_tb_pwm_core__DOT__expected_pwm__15__raw = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__start_pwm__16__period;
    __Vtask_tb_pwm_core__DOT__start_pwm__16__period = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core__DOT__start_pwm__16__duty;
    __Vtask_tb_pwm_core__DOT__start_pwm__16__duty = 0;
    CData/*0:0*/ __Vtask_tb_pwm_core__DOT__start_pwm__16__polarity;
    __Vtask_tb_pwm_core__DOT__start_pwm__16__polarity = 0;
    // Body
    vlSymsp->_vm_contextp__->dumpfile("tb_pwm_core.fst"s);
    vlSymsp->_traceDumpOpen();
    vlSelfRef.tb_pwm_core__DOT__errors = 0U;
    vlSelfRef.tb_pwm_core__DOT__rst_ni = 0U;
    vlSelfRef.tb_pwm_core__DOT__enable_i = 0U;
    vlSelfRef.tb_pwm_core__DOT__polarity_i = 0U;
    vlSelfRef.tb_pwm_core__DOT__period_cfg_i = 0U;
    vlSelfRef.tb_pwm_core__DOT__duty_cfg_i = 0U;
    tb_pwm_core__DOT__unnamedblk1_1__DOT____Vrepeat0 = 3U;
    while (VL_LTS_III(32, 0U, tb_pwm_core__DOT__unnamedblk1_1__DOT____Vrepeat0)) {
        Vtb_pwm_core___024root____VbeforeTrig_h9d9a0fdf__0(vlSelf, 
                                                           "@(posedge tb_pwm_core.clk_i)");
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VtrigSched_h9d9a0fdf__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_pwm_core.clk_i)", 
                                                             "tb_pwm_core.sv", 
                                                             185);
        tb_pwm_core__DOT__unnamedblk1_1__DOT____Vrepeat0 
            = (tb_pwm_core__DOT__unnamedblk1_1__DOT____Vrepeat0 
               - (IData)(1U));
    }
    vlSelfRef.tb_pwm_core__DOT__rst_ni = 1U;
    Vtb_pwm_core___024root____VbeforeTrig_h9d9a0fdf__0(vlSelf, 
                                                       "@(posedge tb_pwm_core.clk_i)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_h9d9a0fdf__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_pwm_core.clk_i)", 
                                                         "tb_pwm_core.sv", 
                                                         187);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(1ULL, nullptr, 
                                         "tb_pwm_core.sv", 
                                         188);
    VL_WRITEF_NX("[TB] Test 1: period=10, duty=3, active-high\n",0);
    __Vtask_tb_pwm_core__DOT__start_pwm__0__polarity = 0U;
    __Vtask_tb_pwm_core__DOT__start_pwm__0__duty = 3U;
    __Vtask_tb_pwm_core__DOT__start_pwm__0__period = 0x0000000aU;
    vlSelfRef.tb_pwm_core__DOT__enable_i = 0U;
    vlSelfRef.tb_pwm_core__DOT__polarity_i = __Vtask_tb_pwm_core__DOT__start_pwm__0__polarity;
    vlSelfRef.tb_pwm_core__DOT__period_cfg_i = (0x0000ffffU 
                                                & __Vtask_tb_pwm_core__DOT__start_pwm__0__period);
    vlSelfRef.tb_pwm_core__DOT__duty_cfg_i = (0x0000ffffU 
                                              & __Vtask_tb_pwm_core__DOT__start_pwm__0__duty);
    Vtb_pwm_core___024root____VbeforeTrig_h9d9a0fdf__0(vlSelf, 
                                                       "@(posedge tb_pwm_core.clk_i)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_h9d9a0fdf__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_pwm_core.clk_i)", 
                                                         "tb_pwm_core.sv", 
                                                         137);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(1ULL, nullptr, 
                                         "tb_pwm_core.sv", 
                                         138);
    vlSelfRef.tb_pwm_core__DOT__enable_i = 1U;
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(1ULL, nullptr, 
                                         "tb_pwm_core.sv", 
                                         144);
    __Vtask_tb_pwm_core__DOT__check_cycles__1__num_cycles = 0x00000019U;
    __Vtask_tb_pwm_core__DOT__check_cycles__1__polarity = 0U;
    __Vtask_tb_pwm_core__DOT__check_cycles__1__duty = 3U;
    __Vtask_tb_pwm_core__DOT__check_cycles__1__period = 0x0000000aU;
    vlSelfRef.__Vtask_tb_pwm_core__DOT__check_cycles__1__name = "period10_duty3"s;
    __Vtask_tb_pwm_core__DOT__check_cycles__1__exp_counter = 0U;
    __Vtask_tb_pwm_core__DOT__check_cycles__1__unnamedblk1__DOT__i = 0U;
    __Vtask_tb_pwm_core__DOT__check_cycles__1__unnamedblk1__DOT__i = 0U;
    while ((__Vtask_tb_pwm_core__DOT__check_cycles__1__unnamedblk1__DOT__i 
            < __Vtask_tb_pwm_core__DOT__check_cycles__1__num_cycles)) {
        __Vtask_tb_pwm_core__DOT__check_cycles__1__exp_counter 
            = ((0U == __Vtask_tb_pwm_core__DOT__check_cycles__1__period)
                ? 0U : VL_MODDIV_III(32, __Vtask_tb_pwm_core__DOT__check_cycles__1__unnamedblk1__DOT__i, __Vtask_tb_pwm_core__DOT__check_cycles__1__period));
        __Vtask_tb_pwm_core__DOT__check_current__2__exp_polarity 
            = __Vtask_tb_pwm_core__DOT__check_cycles__1__polarity;
        __Vtask_tb_pwm_core__DOT__check_current__2__exp_duty 
            = __Vtask_tb_pwm_core__DOT__check_cycles__1__duty;
        __Vtask_tb_pwm_core__DOT__check_current__2__exp_period 
            = __Vtask_tb_pwm_core__DOT__check_cycles__1__period;
        __Vtask_tb_pwm_core__DOT__check_current__2__exp_counter 
            = __Vtask_tb_pwm_core__DOT__check_cycles__1__exp_counter;
        vlSelfRef.__Vtask_tb_pwm_core__DOT__check_current__2__name 
            = vlSelfRef.__Vtask_tb_pwm_core__DOT__check_cycles__1__name;
        __Vtask_tb_pwm_core__DOT__check_current__2__exp_pwm = 0;
        __Vtask_tb_pwm_core__DOT__check_current__2__exp_done = 0;
        __Vtask_tb_pwm_core__DOT__check_current__2__exp_duty_clamped = 0U;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__3__polarity 
            = __Vtask_tb_pwm_core__DOT__check_current__2__exp_polarity;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__3__duty 
            = __Vtask_tb_pwm_core__DOT__check_current__2__exp_duty;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__3__period 
            = __Vtask_tb_pwm_core__DOT__check_current__2__exp_period;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__3__counter 
            = __Vtask_tb_pwm_core__DOT__check_current__2__exp_counter;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__3__Vfuncout = 0;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__3__duty_clamped = 0U;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__3__raw = 0;
        if ((0U == __Vfunc_tb_pwm_core__DOT__expected_pwm__3__period)) {
            __Vfunc_tb_pwm_core__DOT__expected_pwm__3__Vfuncout = 0U;
        } else {
            __Vfunc_tb_pwm_core__DOT__expected_pwm__3__duty_clamped 
                = ((__Vfunc_tb_pwm_core__DOT__expected_pwm__3__duty 
                    >= __Vfunc_tb_pwm_core__DOT__expected_pwm__3__period)
                    ? __Vfunc_tb_pwm_core__DOT__expected_pwm__3__period
                    : __Vfunc_tb_pwm_core__DOT__expected_pwm__3__duty);
            __Vfunc_tb_pwm_core__DOT__expected_pwm__3__raw 
                = (__Vfunc_tb_pwm_core__DOT__expected_pwm__3__counter 
                   < __Vfunc_tb_pwm_core__DOT__expected_pwm__3__duty_clamped);
            __Vfunc_tb_pwm_core__DOT__expected_pwm__3__Vfuncout 
                = (1U & ((IData)(__Vfunc_tb_pwm_core__DOT__expected_pwm__3__polarity)
                          ? (~ (IData)(__Vfunc_tb_pwm_core__DOT__expected_pwm__3__raw))
                          : (IData)(__Vfunc_tb_pwm_core__DOT__expected_pwm__3__raw)));
        }
        __Vtask_tb_pwm_core__DOT__check_current__2__exp_pwm 
            = __Vfunc_tb_pwm_core__DOT__expected_pwm__3__Vfuncout;
        __Vtask_tb_pwm_core__DOT__check_current__2__exp_done 
            = ((0U != __Vtask_tb_pwm_core__DOT__check_current__2__exp_period) 
               & (__Vtask_tb_pwm_core__DOT__check_current__2__exp_counter 
                  == (__Vtask_tb_pwm_core__DOT__check_current__2__exp_period 
                      - (IData)(1U))));
        __Vtask_tb_pwm_core__DOT__check_current__2__exp_duty_clamped 
            = ((__Vtask_tb_pwm_core__DOT__check_current__2__exp_duty 
                >= __Vtask_tb_pwm_core__DOT__check_current__2__exp_period)
                ? __Vtask_tb_pwm_core__DOT__check_current__2__exp_period
                : __Vtask_tb_pwm_core__DOT__check_current__2__exp_duty);
        if (VL_UNLIKELY((((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q) 
                          != (0x0000ffffU & __Vtask_tb_pwm_core__DOT__check_current__2__exp_counter))))) {
            VL_WRITEF_NX("[ERROR] %@: counter expected %0#, got %0# at t=%0t\n",0,
                         -1,&(vlSelfRef.__Vtask_tb_pwm_core__DOT__check_current__2__name),
                         32,__Vtask_tb_pwm_core__DOT__check_current__2__exp_counter,
                         16,(IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q),
                         64,VL_TIME_UNITED_Q(1),-12);
            vlSelfRef.tb_pwm_core__DOT__errors = ((IData)(1U) 
                                                  + vlSelfRef.tb_pwm_core__DOT__errors);
        }
        if (VL_UNLIKELY((((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q) 
                          != (0x0000ffffU & __Vtask_tb_pwm_core__DOT__check_current__2__exp_period))))) {
            VL_WRITEF_NX("[ERROR] %@: period_active expected %0#, got %0# at t=%0t\n",0,
                         -1,&(vlSelfRef.__Vtask_tb_pwm_core__DOT__check_current__2__name),
                         32,__Vtask_tb_pwm_core__DOT__check_current__2__exp_period,
                         16,(IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q),
                         64,VL_TIME_UNITED_Q(1),-12);
            vlSelfRef.tb_pwm_core__DOT__errors = ((IData)(1U) 
                                                  + vlSelfRef.tb_pwm_core__DOT__errors);
        }
        if (VL_UNLIKELY((((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__duty_active_q) 
                          != (0x0000ffffU & __Vtask_tb_pwm_core__DOT__check_current__2__exp_duty_clamped))))) {
            VL_WRITEF_NX("[ERROR] %@: duty_active expected %0#, got %0# at t=%0t\n",0,
                         -1,&(vlSelfRef.__Vtask_tb_pwm_core__DOT__check_current__2__name),
                         32,__Vtask_tb_pwm_core__DOT__check_current__2__exp_duty_clamped,
                         16,(IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__duty_active_q),
                         64,VL_TIME_UNITED_Q(1),-12);
            vlSelfRef.tb_pwm_core__DOT__errors = ((IData)(1U) 
                                                  + vlSelfRef.tb_pwm_core__DOT__errors);
        }
        if (VL_UNLIKELY((((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__pwm_o) 
                          != (IData)(__Vtask_tb_pwm_core__DOT__check_current__2__exp_pwm))))) {
            VL_WRITEF_NX("[ERROR] %@: pwm_o expected %0b, got %0b at counter=%0# t=%0t\n",0,
                         -1,&(vlSelfRef.__Vtask_tb_pwm_core__DOT__check_current__2__name),
                         1,(IData)(__Vtask_tb_pwm_core__DOT__check_current__2__exp_pwm),
                         1,vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__pwm_o,
                         16,(IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q),
                         64,VL_TIME_UNITED_Q(1),-12);
            vlSelfRef.tb_pwm_core__DOT__errors = ((IData)(1U) 
                                                  + vlSelfRef.tb_pwm_core__DOT__errors);
        }
        if (VL_UNLIKELY(((((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0) 
                           & ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q) 
                              == (0x0000ffffU & ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q) 
                                                 - (IData)(1U))))) 
                          != (IData)(__Vtask_tb_pwm_core__DOT__check_current__2__exp_done))))) {
            VL_WRITEF_NX("[ERROR] %@: period_done expected %0b, got %0b at counter=%0# t=%0t\n",0,
                         -1,&(vlSelfRef.__Vtask_tb_pwm_core__DOT__check_current__2__name),
                         1,(IData)(__Vtask_tb_pwm_core__DOT__check_current__2__exp_done),
                         1,((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0) 
                            & ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q) 
                               == (0x0000ffffU & ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q) 
                                                  - (IData)(1U))))),
                         16,(IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q),
                         64,VL_TIME_UNITED_Q(1),-12);
            vlSelfRef.tb_pwm_core__DOT__errors = ((IData)(1U) 
                                                  + vlSelfRef.tb_pwm_core__DOT__errors);
        }
        Vtb_pwm_core___024root____VbeforeTrig_h9d9a0fdf__0(vlSelf, 
                                                           "@(posedge tb_pwm_core.clk_i)");
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VtrigSched_h9d9a0fdf__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_pwm_core.clk_i)", 
                                                             "tb_pwm_core.sv", 
                                                             167);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(1ULL, 
                                             nullptr, 
                                             "tb_pwm_core.sv", 
                                             168);
        __Vtask_tb_pwm_core__DOT__check_cycles__1__unnamedblk1__DOT__i 
            = ((IData)(1U) + __Vtask_tb_pwm_core__DOT__check_cycles__1__unnamedblk1__DOT__i);
    }
    VL_WRITEF_NX("[TB] Test 2: period=8, duty=0, always low\n",0);
    __Vtask_tb_pwm_core__DOT__start_pwm__4__polarity = 0U;
    __Vtask_tb_pwm_core__DOT__start_pwm__4__duty = 0U;
    __Vtask_tb_pwm_core__DOT__start_pwm__4__period = 8U;
    vlSelfRef.tb_pwm_core__DOT__enable_i = 0U;
    vlSelfRef.tb_pwm_core__DOT__polarity_i = __Vtask_tb_pwm_core__DOT__start_pwm__4__polarity;
    vlSelfRef.tb_pwm_core__DOT__period_cfg_i = (0x0000ffffU 
                                                & __Vtask_tb_pwm_core__DOT__start_pwm__4__period);
    vlSelfRef.tb_pwm_core__DOT__duty_cfg_i = (0x0000ffffU 
                                              & __Vtask_tb_pwm_core__DOT__start_pwm__4__duty);
    Vtb_pwm_core___024root____VbeforeTrig_h9d9a0fdf__0(vlSelf, 
                                                       "@(posedge tb_pwm_core.clk_i)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_h9d9a0fdf__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_pwm_core.clk_i)", 
                                                         "tb_pwm_core.sv", 
                                                         137);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(1ULL, nullptr, 
                                         "tb_pwm_core.sv", 
                                         138);
    vlSelfRef.tb_pwm_core__DOT__enable_i = 1U;
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(1ULL, nullptr, 
                                         "tb_pwm_core.sv", 
                                         144);
    __Vtask_tb_pwm_core__DOT__check_cycles__5__num_cycles = 0x00000012U;
    __Vtask_tb_pwm_core__DOT__check_cycles__5__polarity = 0U;
    __Vtask_tb_pwm_core__DOT__check_cycles__5__duty = 0U;
    __Vtask_tb_pwm_core__DOT__check_cycles__5__period = 8U;
    vlSelfRef.__Vtask_tb_pwm_core__DOT__check_cycles__5__name = "period8_duty0"s;
    __Vtask_tb_pwm_core__DOT__check_cycles__5__exp_counter = 0U;
    __Vtask_tb_pwm_core__DOT__check_cycles__5__unnamedblk1__DOT__i = 0U;
    __Vtask_tb_pwm_core__DOT__check_cycles__5__unnamedblk1__DOT__i = 0U;
    while ((__Vtask_tb_pwm_core__DOT__check_cycles__5__unnamedblk1__DOT__i 
            < __Vtask_tb_pwm_core__DOT__check_cycles__5__num_cycles)) {
        __Vtask_tb_pwm_core__DOT__check_cycles__5__exp_counter 
            = ((0U == __Vtask_tb_pwm_core__DOT__check_cycles__5__period)
                ? 0U : VL_MODDIV_III(32, __Vtask_tb_pwm_core__DOT__check_cycles__5__unnamedblk1__DOT__i, __Vtask_tb_pwm_core__DOT__check_cycles__5__period));
        __Vtask_tb_pwm_core__DOT__check_current__6__exp_polarity 
            = __Vtask_tb_pwm_core__DOT__check_cycles__5__polarity;
        __Vtask_tb_pwm_core__DOT__check_current__6__exp_duty 
            = __Vtask_tb_pwm_core__DOT__check_cycles__5__duty;
        __Vtask_tb_pwm_core__DOT__check_current__6__exp_period 
            = __Vtask_tb_pwm_core__DOT__check_cycles__5__period;
        __Vtask_tb_pwm_core__DOT__check_current__6__exp_counter 
            = __Vtask_tb_pwm_core__DOT__check_cycles__5__exp_counter;
        vlSelfRef.__Vtask_tb_pwm_core__DOT__check_current__6__name 
            = vlSelfRef.__Vtask_tb_pwm_core__DOT__check_cycles__5__name;
        __Vtask_tb_pwm_core__DOT__check_current__6__exp_pwm = 0;
        __Vtask_tb_pwm_core__DOT__check_current__6__exp_done = 0;
        __Vtask_tb_pwm_core__DOT__check_current__6__exp_duty_clamped = 0U;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__7__polarity 
            = __Vtask_tb_pwm_core__DOT__check_current__6__exp_polarity;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__7__duty 
            = __Vtask_tb_pwm_core__DOT__check_current__6__exp_duty;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__7__period 
            = __Vtask_tb_pwm_core__DOT__check_current__6__exp_period;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__7__counter 
            = __Vtask_tb_pwm_core__DOT__check_current__6__exp_counter;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__7__Vfuncout = 0;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__7__duty_clamped = 0U;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__7__raw = 0;
        if ((0U == __Vfunc_tb_pwm_core__DOT__expected_pwm__7__period)) {
            __Vfunc_tb_pwm_core__DOT__expected_pwm__7__Vfuncout = 0U;
        } else {
            __Vfunc_tb_pwm_core__DOT__expected_pwm__7__duty_clamped 
                = ((__Vfunc_tb_pwm_core__DOT__expected_pwm__7__duty 
                    >= __Vfunc_tb_pwm_core__DOT__expected_pwm__7__period)
                    ? __Vfunc_tb_pwm_core__DOT__expected_pwm__7__period
                    : __Vfunc_tb_pwm_core__DOT__expected_pwm__7__duty);
            __Vfunc_tb_pwm_core__DOT__expected_pwm__7__raw 
                = (__Vfunc_tb_pwm_core__DOT__expected_pwm__7__counter 
                   < __Vfunc_tb_pwm_core__DOT__expected_pwm__7__duty_clamped);
            __Vfunc_tb_pwm_core__DOT__expected_pwm__7__Vfuncout 
                = (1U & ((IData)(__Vfunc_tb_pwm_core__DOT__expected_pwm__7__polarity)
                          ? (~ (IData)(__Vfunc_tb_pwm_core__DOT__expected_pwm__7__raw))
                          : (IData)(__Vfunc_tb_pwm_core__DOT__expected_pwm__7__raw)));
        }
        __Vtask_tb_pwm_core__DOT__check_current__6__exp_pwm 
            = __Vfunc_tb_pwm_core__DOT__expected_pwm__7__Vfuncout;
        __Vtask_tb_pwm_core__DOT__check_current__6__exp_done 
            = ((0U != __Vtask_tb_pwm_core__DOT__check_current__6__exp_period) 
               & (__Vtask_tb_pwm_core__DOT__check_current__6__exp_counter 
                  == (__Vtask_tb_pwm_core__DOT__check_current__6__exp_period 
                      - (IData)(1U))));
        __Vtask_tb_pwm_core__DOT__check_current__6__exp_duty_clamped 
            = ((__Vtask_tb_pwm_core__DOT__check_current__6__exp_duty 
                >= __Vtask_tb_pwm_core__DOT__check_current__6__exp_period)
                ? __Vtask_tb_pwm_core__DOT__check_current__6__exp_period
                : __Vtask_tb_pwm_core__DOT__check_current__6__exp_duty);
        if (VL_UNLIKELY((((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q) 
                          != (0x0000ffffU & __Vtask_tb_pwm_core__DOT__check_current__6__exp_counter))))) {
            VL_WRITEF_NX("[ERROR] %@: counter expected %0#, got %0# at t=%0t\n",0,
                         -1,&(vlSelfRef.__Vtask_tb_pwm_core__DOT__check_current__6__name),
                         32,__Vtask_tb_pwm_core__DOT__check_current__6__exp_counter,
                         16,(IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q),
                         64,VL_TIME_UNITED_Q(1),-12);
            vlSelfRef.tb_pwm_core__DOT__errors = ((IData)(1U) 
                                                  + vlSelfRef.tb_pwm_core__DOT__errors);
        }
        if (VL_UNLIKELY((((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q) 
                          != (0x0000ffffU & __Vtask_tb_pwm_core__DOT__check_current__6__exp_period))))) {
            VL_WRITEF_NX("[ERROR] %@: period_active expected %0#, got %0# at t=%0t\n",0,
                         -1,&(vlSelfRef.__Vtask_tb_pwm_core__DOT__check_current__6__name),
                         32,__Vtask_tb_pwm_core__DOT__check_current__6__exp_period,
                         16,(IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q),
                         64,VL_TIME_UNITED_Q(1),-12);
            vlSelfRef.tb_pwm_core__DOT__errors = ((IData)(1U) 
                                                  + vlSelfRef.tb_pwm_core__DOT__errors);
        }
        if (VL_UNLIKELY((((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__duty_active_q) 
                          != (0x0000ffffU & __Vtask_tb_pwm_core__DOT__check_current__6__exp_duty_clamped))))) {
            VL_WRITEF_NX("[ERROR] %@: duty_active expected %0#, got %0# at t=%0t\n",0,
                         -1,&(vlSelfRef.__Vtask_tb_pwm_core__DOT__check_current__6__name),
                         32,__Vtask_tb_pwm_core__DOT__check_current__6__exp_duty_clamped,
                         16,(IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__duty_active_q),
                         64,VL_TIME_UNITED_Q(1),-12);
            vlSelfRef.tb_pwm_core__DOT__errors = ((IData)(1U) 
                                                  + vlSelfRef.tb_pwm_core__DOT__errors);
        }
        if (VL_UNLIKELY((((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__pwm_o) 
                          != (IData)(__Vtask_tb_pwm_core__DOT__check_current__6__exp_pwm))))) {
            VL_WRITEF_NX("[ERROR] %@: pwm_o expected %0b, got %0b at counter=%0# t=%0t\n",0,
                         -1,&(vlSelfRef.__Vtask_tb_pwm_core__DOT__check_current__6__name),
                         1,(IData)(__Vtask_tb_pwm_core__DOT__check_current__6__exp_pwm),
                         1,vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__pwm_o,
                         16,(IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q),
                         64,VL_TIME_UNITED_Q(1),-12);
            vlSelfRef.tb_pwm_core__DOT__errors = ((IData)(1U) 
                                                  + vlSelfRef.tb_pwm_core__DOT__errors);
        }
        if (VL_UNLIKELY(((((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0) 
                           & ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q) 
                              == (0x0000ffffU & ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q) 
                                                 - (IData)(1U))))) 
                          != (IData)(__Vtask_tb_pwm_core__DOT__check_current__6__exp_done))))) {
            VL_WRITEF_NX("[ERROR] %@: period_done expected %0b, got %0b at counter=%0# t=%0t\n",0,
                         -1,&(vlSelfRef.__Vtask_tb_pwm_core__DOT__check_current__6__name),
                         1,(IData)(__Vtask_tb_pwm_core__DOT__check_current__6__exp_done),
                         1,((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0) 
                            & ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q) 
                               == (0x0000ffffU & ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q) 
                                                  - (IData)(1U))))),
                         16,(IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q),
                         64,VL_TIME_UNITED_Q(1),-12);
            vlSelfRef.tb_pwm_core__DOT__errors = ((IData)(1U) 
                                                  + vlSelfRef.tb_pwm_core__DOT__errors);
        }
        Vtb_pwm_core___024root____VbeforeTrig_h9d9a0fdf__0(vlSelf, 
                                                           "@(posedge tb_pwm_core.clk_i)");
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VtrigSched_h9d9a0fdf__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_pwm_core.clk_i)", 
                                                             "tb_pwm_core.sv", 
                                                             167);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(1ULL, 
                                             nullptr, 
                                             "tb_pwm_core.sv", 
                                             168);
        __Vtask_tb_pwm_core__DOT__check_cycles__5__unnamedblk1__DOT__i 
            = ((IData)(1U) + __Vtask_tb_pwm_core__DOT__check_cycles__5__unnamedblk1__DOT__i);
    }
    VL_WRITEF_NX("[TB] Test 3: period=8, duty=12, duty clamps to period\n",0);
    __Vtask_tb_pwm_core__DOT__start_pwm__8__polarity = 0U;
    __Vtask_tb_pwm_core__DOT__start_pwm__8__duty = 0x0000000cU;
    __Vtask_tb_pwm_core__DOT__start_pwm__8__period = 8U;
    vlSelfRef.tb_pwm_core__DOT__enable_i = 0U;
    vlSelfRef.tb_pwm_core__DOT__polarity_i = __Vtask_tb_pwm_core__DOT__start_pwm__8__polarity;
    vlSelfRef.tb_pwm_core__DOT__period_cfg_i = (0x0000ffffU 
                                                & __Vtask_tb_pwm_core__DOT__start_pwm__8__period);
    vlSelfRef.tb_pwm_core__DOT__duty_cfg_i = (0x0000ffffU 
                                              & __Vtask_tb_pwm_core__DOT__start_pwm__8__duty);
    Vtb_pwm_core___024root____VbeforeTrig_h9d9a0fdf__0(vlSelf, 
                                                       "@(posedge tb_pwm_core.clk_i)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_h9d9a0fdf__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_pwm_core.clk_i)", 
                                                         "tb_pwm_core.sv", 
                                                         137);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(1ULL, nullptr, 
                                         "tb_pwm_core.sv", 
                                         138);
    vlSelfRef.tb_pwm_core__DOT__enable_i = 1U;
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(1ULL, nullptr, 
                                         "tb_pwm_core.sv", 
                                         144);
    __Vtask_tb_pwm_core__DOT__check_cycles__9__num_cycles = 0x00000012U;
    __Vtask_tb_pwm_core__DOT__check_cycles__9__polarity = 0U;
    __Vtask_tb_pwm_core__DOT__check_cycles__9__duty = 0x0000000cU;
    __Vtask_tb_pwm_core__DOT__check_cycles__9__period = 8U;
    vlSelfRef.__Vtask_tb_pwm_core__DOT__check_cycles__9__name = "period8_duty12"s;
    __Vtask_tb_pwm_core__DOT__check_cycles__9__exp_counter = 0U;
    __Vtask_tb_pwm_core__DOT__check_cycles__9__unnamedblk1__DOT__i = 0U;
    __Vtask_tb_pwm_core__DOT__check_cycles__9__unnamedblk1__DOT__i = 0U;
    while ((__Vtask_tb_pwm_core__DOT__check_cycles__9__unnamedblk1__DOT__i 
            < __Vtask_tb_pwm_core__DOT__check_cycles__9__num_cycles)) {
        __Vtask_tb_pwm_core__DOT__check_cycles__9__exp_counter 
            = ((0U == __Vtask_tb_pwm_core__DOT__check_cycles__9__period)
                ? 0U : VL_MODDIV_III(32, __Vtask_tb_pwm_core__DOT__check_cycles__9__unnamedblk1__DOT__i, __Vtask_tb_pwm_core__DOT__check_cycles__9__period));
        __Vtask_tb_pwm_core__DOT__check_current__10__exp_polarity 
            = __Vtask_tb_pwm_core__DOT__check_cycles__9__polarity;
        __Vtask_tb_pwm_core__DOT__check_current__10__exp_duty 
            = __Vtask_tb_pwm_core__DOT__check_cycles__9__duty;
        __Vtask_tb_pwm_core__DOT__check_current__10__exp_period 
            = __Vtask_tb_pwm_core__DOT__check_cycles__9__period;
        __Vtask_tb_pwm_core__DOT__check_current__10__exp_counter 
            = __Vtask_tb_pwm_core__DOT__check_cycles__9__exp_counter;
        vlSelfRef.__Vtask_tb_pwm_core__DOT__check_current__10__name 
            = vlSelfRef.__Vtask_tb_pwm_core__DOT__check_cycles__9__name;
        __Vtask_tb_pwm_core__DOT__check_current__10__exp_pwm = 0;
        __Vtask_tb_pwm_core__DOT__check_current__10__exp_done = 0;
        __Vtask_tb_pwm_core__DOT__check_current__10__exp_duty_clamped = 0U;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__11__polarity 
            = __Vtask_tb_pwm_core__DOT__check_current__10__exp_polarity;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__11__duty 
            = __Vtask_tb_pwm_core__DOT__check_current__10__exp_duty;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__11__period 
            = __Vtask_tb_pwm_core__DOT__check_current__10__exp_period;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__11__counter 
            = __Vtask_tb_pwm_core__DOT__check_current__10__exp_counter;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__11__Vfuncout = 0;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__11__duty_clamped = 0U;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__11__raw = 0;
        if ((0U == __Vfunc_tb_pwm_core__DOT__expected_pwm__11__period)) {
            __Vfunc_tb_pwm_core__DOT__expected_pwm__11__Vfuncout = 0U;
        } else {
            __Vfunc_tb_pwm_core__DOT__expected_pwm__11__duty_clamped 
                = ((__Vfunc_tb_pwm_core__DOT__expected_pwm__11__duty 
                    >= __Vfunc_tb_pwm_core__DOT__expected_pwm__11__period)
                    ? __Vfunc_tb_pwm_core__DOT__expected_pwm__11__period
                    : __Vfunc_tb_pwm_core__DOT__expected_pwm__11__duty);
            __Vfunc_tb_pwm_core__DOT__expected_pwm__11__raw 
                = (__Vfunc_tb_pwm_core__DOT__expected_pwm__11__counter 
                   < __Vfunc_tb_pwm_core__DOT__expected_pwm__11__duty_clamped);
            __Vfunc_tb_pwm_core__DOT__expected_pwm__11__Vfuncout 
                = (1U & ((IData)(__Vfunc_tb_pwm_core__DOT__expected_pwm__11__polarity)
                          ? (~ (IData)(__Vfunc_tb_pwm_core__DOT__expected_pwm__11__raw))
                          : (IData)(__Vfunc_tb_pwm_core__DOT__expected_pwm__11__raw)));
        }
        __Vtask_tb_pwm_core__DOT__check_current__10__exp_pwm 
            = __Vfunc_tb_pwm_core__DOT__expected_pwm__11__Vfuncout;
        __Vtask_tb_pwm_core__DOT__check_current__10__exp_done 
            = ((0U != __Vtask_tb_pwm_core__DOT__check_current__10__exp_period) 
               & (__Vtask_tb_pwm_core__DOT__check_current__10__exp_counter 
                  == (__Vtask_tb_pwm_core__DOT__check_current__10__exp_period 
                      - (IData)(1U))));
        __Vtask_tb_pwm_core__DOT__check_current__10__exp_duty_clamped 
            = ((__Vtask_tb_pwm_core__DOT__check_current__10__exp_duty 
                >= __Vtask_tb_pwm_core__DOT__check_current__10__exp_period)
                ? __Vtask_tb_pwm_core__DOT__check_current__10__exp_period
                : __Vtask_tb_pwm_core__DOT__check_current__10__exp_duty);
        if (VL_UNLIKELY((((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q) 
                          != (0x0000ffffU & __Vtask_tb_pwm_core__DOT__check_current__10__exp_counter))))) {
            VL_WRITEF_NX("[ERROR] %@: counter expected %0#, got %0# at t=%0t\n",0,
                         -1,&(vlSelfRef.__Vtask_tb_pwm_core__DOT__check_current__10__name),
                         32,__Vtask_tb_pwm_core__DOT__check_current__10__exp_counter,
                         16,(IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q),
                         64,VL_TIME_UNITED_Q(1),-12);
            vlSelfRef.tb_pwm_core__DOT__errors = ((IData)(1U) 
                                                  + vlSelfRef.tb_pwm_core__DOT__errors);
        }
        if (VL_UNLIKELY((((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q) 
                          != (0x0000ffffU & __Vtask_tb_pwm_core__DOT__check_current__10__exp_period))))) {
            VL_WRITEF_NX("[ERROR] %@: period_active expected %0#, got %0# at t=%0t\n",0,
                         -1,&(vlSelfRef.__Vtask_tb_pwm_core__DOT__check_current__10__name),
                         32,__Vtask_tb_pwm_core__DOT__check_current__10__exp_period,
                         16,(IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q),
                         64,VL_TIME_UNITED_Q(1),-12);
            vlSelfRef.tb_pwm_core__DOT__errors = ((IData)(1U) 
                                                  + vlSelfRef.tb_pwm_core__DOT__errors);
        }
        if (VL_UNLIKELY((((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__duty_active_q) 
                          != (0x0000ffffU & __Vtask_tb_pwm_core__DOT__check_current__10__exp_duty_clamped))))) {
            VL_WRITEF_NX("[ERROR] %@: duty_active expected %0#, got %0# at t=%0t\n",0,
                         -1,&(vlSelfRef.__Vtask_tb_pwm_core__DOT__check_current__10__name),
                         32,__Vtask_tb_pwm_core__DOT__check_current__10__exp_duty_clamped,
                         16,(IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__duty_active_q),
                         64,VL_TIME_UNITED_Q(1),-12);
            vlSelfRef.tb_pwm_core__DOT__errors = ((IData)(1U) 
                                                  + vlSelfRef.tb_pwm_core__DOT__errors);
        }
        if (VL_UNLIKELY((((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__pwm_o) 
                          != (IData)(__Vtask_tb_pwm_core__DOT__check_current__10__exp_pwm))))) {
            VL_WRITEF_NX("[ERROR] %@: pwm_o expected %0b, got %0b at counter=%0# t=%0t\n",0,
                         -1,&(vlSelfRef.__Vtask_tb_pwm_core__DOT__check_current__10__name),
                         1,(IData)(__Vtask_tb_pwm_core__DOT__check_current__10__exp_pwm),
                         1,vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__pwm_o,
                         16,(IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q),
                         64,VL_TIME_UNITED_Q(1),-12);
            vlSelfRef.tb_pwm_core__DOT__errors = ((IData)(1U) 
                                                  + vlSelfRef.tb_pwm_core__DOT__errors);
        }
        if (VL_UNLIKELY(((((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0) 
                           & ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q) 
                              == (0x0000ffffU & ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q) 
                                                 - (IData)(1U))))) 
                          != (IData)(__Vtask_tb_pwm_core__DOT__check_current__10__exp_done))))) {
            VL_WRITEF_NX("[ERROR] %@: period_done expected %0b, got %0b at counter=%0# t=%0t\n",0,
                         -1,&(vlSelfRef.__Vtask_tb_pwm_core__DOT__check_current__10__name),
                         1,(IData)(__Vtask_tb_pwm_core__DOT__check_current__10__exp_done),
                         1,((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0) 
                            & ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q) 
                               == (0x0000ffffU & ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q) 
                                                  - (IData)(1U))))),
                         16,(IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q),
                         64,VL_TIME_UNITED_Q(1),-12);
            vlSelfRef.tb_pwm_core__DOT__errors = ((IData)(1U) 
                                                  + vlSelfRef.tb_pwm_core__DOT__errors);
        }
        Vtb_pwm_core___024root____VbeforeTrig_h9d9a0fdf__0(vlSelf, 
                                                           "@(posedge tb_pwm_core.clk_i)");
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VtrigSched_h9d9a0fdf__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_pwm_core.clk_i)", 
                                                             "tb_pwm_core.sv", 
                                                             167);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(1ULL, 
                                             nullptr, 
                                             "tb_pwm_core.sv", 
                                             168);
        __Vtask_tb_pwm_core__DOT__check_cycles__9__unnamedblk1__DOT__i 
            = ((IData)(1U) + __Vtask_tb_pwm_core__DOT__check_cycles__9__unnamedblk1__DOT__i);
    }
    VL_WRITEF_NX("[TB] Test 4: period=8, duty=2, active-low polarity\n",0);
    __Vtask_tb_pwm_core__DOT__start_pwm__12__polarity = 1U;
    __Vtask_tb_pwm_core__DOT__start_pwm__12__duty = 2U;
    __Vtask_tb_pwm_core__DOT__start_pwm__12__period = 8U;
    vlSelfRef.tb_pwm_core__DOT__enable_i = 0U;
    vlSelfRef.tb_pwm_core__DOT__polarity_i = __Vtask_tb_pwm_core__DOT__start_pwm__12__polarity;
    vlSelfRef.tb_pwm_core__DOT__period_cfg_i = (0x0000ffffU 
                                                & __Vtask_tb_pwm_core__DOT__start_pwm__12__period);
    vlSelfRef.tb_pwm_core__DOT__duty_cfg_i = (0x0000ffffU 
                                              & __Vtask_tb_pwm_core__DOT__start_pwm__12__duty);
    Vtb_pwm_core___024root____VbeforeTrig_h9d9a0fdf__0(vlSelf, 
                                                       "@(posedge tb_pwm_core.clk_i)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_h9d9a0fdf__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_pwm_core.clk_i)", 
                                                         "tb_pwm_core.sv", 
                                                         137);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(1ULL, nullptr, 
                                         "tb_pwm_core.sv", 
                                         138);
    vlSelfRef.tb_pwm_core__DOT__enable_i = 1U;
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(1ULL, nullptr, 
                                         "tb_pwm_core.sv", 
                                         144);
    __Vtask_tb_pwm_core__DOT__check_cycles__13__num_cycles = 0x00000012U;
    __Vtask_tb_pwm_core__DOT__check_cycles__13__polarity = 1U;
    __Vtask_tb_pwm_core__DOT__check_cycles__13__duty = 2U;
    __Vtask_tb_pwm_core__DOT__check_cycles__13__period = 8U;
    vlSelfRef.__Vtask_tb_pwm_core__DOT__check_cycles__13__name = "period8_duty2_polarity"s;
    __Vtask_tb_pwm_core__DOT__check_cycles__13__exp_counter = 0U;
    __Vtask_tb_pwm_core__DOT__check_cycles__13__unnamedblk1__DOT__i = 0U;
    __Vtask_tb_pwm_core__DOT__check_cycles__13__unnamedblk1__DOT__i = 0U;
    while ((__Vtask_tb_pwm_core__DOT__check_cycles__13__unnamedblk1__DOT__i 
            < __Vtask_tb_pwm_core__DOT__check_cycles__13__num_cycles)) {
        __Vtask_tb_pwm_core__DOT__check_cycles__13__exp_counter 
            = ((0U == __Vtask_tb_pwm_core__DOT__check_cycles__13__period)
                ? 0U : VL_MODDIV_III(32, __Vtask_tb_pwm_core__DOT__check_cycles__13__unnamedblk1__DOT__i, __Vtask_tb_pwm_core__DOT__check_cycles__13__period));
        __Vtask_tb_pwm_core__DOT__check_current__14__exp_polarity 
            = __Vtask_tb_pwm_core__DOT__check_cycles__13__polarity;
        __Vtask_tb_pwm_core__DOT__check_current__14__exp_duty 
            = __Vtask_tb_pwm_core__DOT__check_cycles__13__duty;
        __Vtask_tb_pwm_core__DOT__check_current__14__exp_period 
            = __Vtask_tb_pwm_core__DOT__check_cycles__13__period;
        __Vtask_tb_pwm_core__DOT__check_current__14__exp_counter 
            = __Vtask_tb_pwm_core__DOT__check_cycles__13__exp_counter;
        vlSelfRef.__Vtask_tb_pwm_core__DOT__check_current__14__name 
            = vlSelfRef.__Vtask_tb_pwm_core__DOT__check_cycles__13__name;
        __Vtask_tb_pwm_core__DOT__check_current__14__exp_pwm = 0;
        __Vtask_tb_pwm_core__DOT__check_current__14__exp_done = 0;
        __Vtask_tb_pwm_core__DOT__check_current__14__exp_duty_clamped = 0U;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__15__polarity 
            = __Vtask_tb_pwm_core__DOT__check_current__14__exp_polarity;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__15__duty 
            = __Vtask_tb_pwm_core__DOT__check_current__14__exp_duty;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__15__period 
            = __Vtask_tb_pwm_core__DOT__check_current__14__exp_period;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__15__counter 
            = __Vtask_tb_pwm_core__DOT__check_current__14__exp_counter;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__15__Vfuncout = 0;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__15__duty_clamped = 0U;
        __Vfunc_tb_pwm_core__DOT__expected_pwm__15__raw = 0;
        if ((0U == __Vfunc_tb_pwm_core__DOT__expected_pwm__15__period)) {
            __Vfunc_tb_pwm_core__DOT__expected_pwm__15__Vfuncout = 0U;
        } else {
            __Vfunc_tb_pwm_core__DOT__expected_pwm__15__duty_clamped 
                = ((__Vfunc_tb_pwm_core__DOT__expected_pwm__15__duty 
                    >= __Vfunc_tb_pwm_core__DOT__expected_pwm__15__period)
                    ? __Vfunc_tb_pwm_core__DOT__expected_pwm__15__period
                    : __Vfunc_tb_pwm_core__DOT__expected_pwm__15__duty);
            __Vfunc_tb_pwm_core__DOT__expected_pwm__15__raw 
                = (__Vfunc_tb_pwm_core__DOT__expected_pwm__15__counter 
                   < __Vfunc_tb_pwm_core__DOT__expected_pwm__15__duty_clamped);
            __Vfunc_tb_pwm_core__DOT__expected_pwm__15__Vfuncout 
                = (1U & ((IData)(__Vfunc_tb_pwm_core__DOT__expected_pwm__15__polarity)
                          ? (~ (IData)(__Vfunc_tb_pwm_core__DOT__expected_pwm__15__raw))
                          : (IData)(__Vfunc_tb_pwm_core__DOT__expected_pwm__15__raw)));
        }
        __Vtask_tb_pwm_core__DOT__check_current__14__exp_pwm 
            = __Vfunc_tb_pwm_core__DOT__expected_pwm__15__Vfuncout;
        __Vtask_tb_pwm_core__DOT__check_current__14__exp_done 
            = ((0U != __Vtask_tb_pwm_core__DOT__check_current__14__exp_period) 
               & (__Vtask_tb_pwm_core__DOT__check_current__14__exp_counter 
                  == (__Vtask_tb_pwm_core__DOT__check_current__14__exp_period 
                      - (IData)(1U))));
        __Vtask_tb_pwm_core__DOT__check_current__14__exp_duty_clamped 
            = ((__Vtask_tb_pwm_core__DOT__check_current__14__exp_duty 
                >= __Vtask_tb_pwm_core__DOT__check_current__14__exp_period)
                ? __Vtask_tb_pwm_core__DOT__check_current__14__exp_period
                : __Vtask_tb_pwm_core__DOT__check_current__14__exp_duty);
        if (VL_UNLIKELY((((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q) 
                          != (0x0000ffffU & __Vtask_tb_pwm_core__DOT__check_current__14__exp_counter))))) {
            VL_WRITEF_NX("[ERROR] %@: counter expected %0#, got %0# at t=%0t\n",0,
                         -1,&(vlSelfRef.__Vtask_tb_pwm_core__DOT__check_current__14__name),
                         32,__Vtask_tb_pwm_core__DOT__check_current__14__exp_counter,
                         16,(IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q),
                         64,VL_TIME_UNITED_Q(1),-12);
            vlSelfRef.tb_pwm_core__DOT__errors = ((IData)(1U) 
                                                  + vlSelfRef.tb_pwm_core__DOT__errors);
        }
        if (VL_UNLIKELY((((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q) 
                          != (0x0000ffffU & __Vtask_tb_pwm_core__DOT__check_current__14__exp_period))))) {
            VL_WRITEF_NX("[ERROR] %@: period_active expected %0#, got %0# at t=%0t\n",0,
                         -1,&(vlSelfRef.__Vtask_tb_pwm_core__DOT__check_current__14__name),
                         32,__Vtask_tb_pwm_core__DOT__check_current__14__exp_period,
                         16,(IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q),
                         64,VL_TIME_UNITED_Q(1),-12);
            vlSelfRef.tb_pwm_core__DOT__errors = ((IData)(1U) 
                                                  + vlSelfRef.tb_pwm_core__DOT__errors);
        }
        if (VL_UNLIKELY((((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__duty_active_q) 
                          != (0x0000ffffU & __Vtask_tb_pwm_core__DOT__check_current__14__exp_duty_clamped))))) {
            VL_WRITEF_NX("[ERROR] %@: duty_active expected %0#, got %0# at t=%0t\n",0,
                         -1,&(vlSelfRef.__Vtask_tb_pwm_core__DOT__check_current__14__name),
                         32,__Vtask_tb_pwm_core__DOT__check_current__14__exp_duty_clamped,
                         16,(IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__duty_active_q),
                         64,VL_TIME_UNITED_Q(1),-12);
            vlSelfRef.tb_pwm_core__DOT__errors = ((IData)(1U) 
                                                  + vlSelfRef.tb_pwm_core__DOT__errors);
        }
        if (VL_UNLIKELY((((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__pwm_o) 
                          != (IData)(__Vtask_tb_pwm_core__DOT__check_current__14__exp_pwm))))) {
            VL_WRITEF_NX("[ERROR] %@: pwm_o expected %0b, got %0b at counter=%0# t=%0t\n",0,
                         -1,&(vlSelfRef.__Vtask_tb_pwm_core__DOT__check_current__14__name),
                         1,(IData)(__Vtask_tb_pwm_core__DOT__check_current__14__exp_pwm),
                         1,vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__pwm_o,
                         16,(IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q),
                         64,VL_TIME_UNITED_Q(1),-12);
            vlSelfRef.tb_pwm_core__DOT__errors = ((IData)(1U) 
                                                  + vlSelfRef.tb_pwm_core__DOT__errors);
        }
        if (VL_UNLIKELY(((((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0) 
                           & ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q) 
                              == (0x0000ffffU & ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q) 
                                                 - (IData)(1U))))) 
                          != (IData)(__Vtask_tb_pwm_core__DOT__check_current__14__exp_done))))) {
            VL_WRITEF_NX("[ERROR] %@: period_done expected %0b, got %0b at counter=%0# t=%0t\n",0,
                         -1,&(vlSelfRef.__Vtask_tb_pwm_core__DOT__check_current__14__name),
                         1,(IData)(__Vtask_tb_pwm_core__DOT__check_current__14__exp_done),
                         1,((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0) 
                            & ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q) 
                               == (0x0000ffffU & ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q) 
                                                  - (IData)(1U))))),
                         16,(IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q),
                         64,VL_TIME_UNITED_Q(1),-12);
            vlSelfRef.tb_pwm_core__DOT__errors = ((IData)(1U) 
                                                  + vlSelfRef.tb_pwm_core__DOT__errors);
        }
        Vtb_pwm_core___024root____VbeforeTrig_h9d9a0fdf__0(vlSelf, 
                                                           "@(posedge tb_pwm_core.clk_i)");
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VtrigSched_h9d9a0fdf__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_pwm_core.clk_i)", 
                                                             "tb_pwm_core.sv", 
                                                             167);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(1ULL, 
                                             nullptr, 
                                             "tb_pwm_core.sv", 
                                             168);
        __Vtask_tb_pwm_core__DOT__check_cycles__13__unnamedblk1__DOT__i 
            = ((IData)(1U) + __Vtask_tb_pwm_core__DOT__check_cycles__13__unnamedblk1__DOT__i);
    }
    VL_WRITEF_NX("[TB] Test 5: period=0, invalid period forces low\n",0);
    __Vtask_tb_pwm_core__DOT__start_pwm__16__polarity = 0U;
    __Vtask_tb_pwm_core__DOT__start_pwm__16__duty = 3U;
    __Vtask_tb_pwm_core__DOT__start_pwm__16__period = 0U;
    vlSelfRef.tb_pwm_core__DOT__enable_i = 0U;
    vlSelfRef.tb_pwm_core__DOT__polarity_i = __Vtask_tb_pwm_core__DOT__start_pwm__16__polarity;
    vlSelfRef.tb_pwm_core__DOT__period_cfg_i = (0x0000ffffU 
                                                & __Vtask_tb_pwm_core__DOT__start_pwm__16__period);
    vlSelfRef.tb_pwm_core__DOT__duty_cfg_i = (0x0000ffffU 
                                              & __Vtask_tb_pwm_core__DOT__start_pwm__16__duty);
    Vtb_pwm_core___024root____VbeforeTrig_h9d9a0fdf__0(vlSelf, 
                                                       "@(posedge tb_pwm_core.clk_i)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_h9d9a0fdf__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_pwm_core.clk_i)", 
                                                         "tb_pwm_core.sv", 
                                                         137);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(1ULL, nullptr, 
                                         "tb_pwm_core.sv", 
                                         138);
    vlSelfRef.tb_pwm_core__DOT__enable_i = 1U;
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(1ULL, nullptr, 
                                         "tb_pwm_core.sv", 
                                         144);
    if (VL_UNLIKELY((vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__pwm_o))) {
        VL_WRITEF_NX("[ERROR] period0: pwm_o should be low\n",0);
        vlSelfRef.tb_pwm_core__DOT__errors = ((IData)(1U) 
                                              + vlSelfRef.tb_pwm_core__DOT__errors);
    }
    if (VL_UNLIKELY(((1U & (~ (IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_zero_o)))))) {
        VL_WRITEF_NX("[ERROR] period0: period_zero_o should be high\n",0);
        vlSelfRef.tb_pwm_core__DOT__errors = ((IData)(1U) 
                                              + vlSelfRef.tb_pwm_core__DOT__errors);
    }
    if (VL_LIKELY(((0U == vlSelfRef.tb_pwm_core__DOT__errors)))) {
        VL_WRITEF_NX("[TB] PWM core test PASSED\n",0);
    } else {
        VL_WRITEF_NX("[TB] PWM core test FAILED with %0# errors\n[%0t] %%Fatal: tb_pwm_core.sv:223: Assertion failed in %Ntb_pwm_core\n",0,
                     32,vlSelfRef.tb_pwm_core__DOT__errors,
                     64,VL_TIME_UNITED_Q(1),-12,vlSymsp->name());
        VL_STOP_MT("tb_pwm_core.sv", 223, "", false);
    }
    VL_FINISH_MT("tb_pwm_core.sv", 226, "");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_return;
}

void Vtb_pwm_core___024root___eval_triggers_vec__act(Vtb_pwm_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___eval_triggers_vec__act\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                      << 2U) 
                                                     | ((((~ (IData)(vlSelfRef.tb_pwm_core__DOT__rst_ni)) 
                                                          & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_pwm_core__DOT__rst_ni__0)) 
                                                         << 1U) 
                                                        | ((IData)(vlSelfRef.tb_pwm_core__DOT__clk_i) 
                                                           & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_pwm_core__DOT__clk_i__0)))))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_pwm_core__DOT__clk_i__0 
        = vlSelfRef.tb_pwm_core__DOT__clk_i;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_pwm_core__DOT__rst_ni__0 
        = vlSelfRef.tb_pwm_core__DOT__rst_ni;
}

bool Vtb_pwm_core___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vtb_pwm_core___024root___act_comb__TOP__0(Vtb_pwm_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___act_comb__TOP__0\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__duty_clamped 
        = ((0U == (IData)(vlSelfRef.tb_pwm_core__DOT__period_cfg_i))
            ? 0U : (((IData)(vlSelfRef.tb_pwm_core__DOT__duty_cfg_i) 
                     >= (IData)(vlSelfRef.tb_pwm_core__DOT__period_cfg_i))
                     ? (IData)(vlSelfRef.tb_pwm_core__DOT__period_cfg_i)
                     : (IData)(vlSelfRef.tb_pwm_core__DOT__duty_cfg_i)));
    vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_zero_o 
        = ((IData)(vlSelfRef.tb_pwm_core__DOT__enable_i) 
           & ((0U == (IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q)) 
              & (0U == (IData)(vlSelfRef.tb_pwm_core__DOT__period_cfg_i))));
    vlSelfRef.tb_pwm_core__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0 
        = ((IData)(vlSelfRef.tb_pwm_core__DOT__enable_i) 
           & (0U != (IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q)));
    vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_done_o 
        = ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0) 
           & ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q) 
              == (0x0000ffffU & ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q) 
                                 - (IData)(1U)))));
    vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__pwm_raw 
        = ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0) 
           & ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q) 
              < (IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__duty_active_q)));
    vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__pwm_o = 
        (1U & ((~ ((~ (IData)(vlSelfRef.tb_pwm_core__DOT__enable_i)) 
                   | (0U == (IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q)))) 
               & ((IData)(vlSelfRef.tb_pwm_core__DOT__polarity_i)
                   ? (~ (IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__pwm_raw))
                   : (IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__pwm_raw))));
}

void Vtb_pwm_core___024root___eval_act(Vtb_pwm_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___eval_act\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((5ULL & vlSelfRef.__VactTriggered[0U])) {
        Vtb_pwm_core___024root___act_comb__TOP__0(vlSelf);
    }
}

void Vtb_pwm_core___024root___nba_sequent__TOP__0(Vtb_pwm_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___nba_sequent__TOP__0\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    SData/*15:0*/ __Vdly__tb_pwm_core__DOT__i_dut__DOT__counter_q;
    __Vdly__tb_pwm_core__DOT__i_dut__DOT__counter_q = 0;
    // Body
    __Vdly__tb_pwm_core__DOT__i_dut__DOT__counter_q 
        = vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q;
    if (vlSelfRef.tb_pwm_core__DOT__rst_ni) {
        if (vlSelfRef.tb_pwm_core__DOT__enable_i) {
            if ((0U == (IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q))) {
                __Vdly__tb_pwm_core__DOT__i_dut__DOT__counter_q = 0U;
                vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q 
                    = vlSelfRef.tb_pwm_core__DOT__period_cfg_i;
                vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__duty_active_q 
                    = vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__duty_clamped;
            } else if (vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_done_o) {
                __Vdly__tb_pwm_core__DOT__i_dut__DOT__counter_q = 0U;
                vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q 
                    = vlSelfRef.tb_pwm_core__DOT__period_cfg_i;
                vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__duty_active_q 
                    = vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__duty_clamped;
            } else {
                __Vdly__tb_pwm_core__DOT__i_dut__DOT__counter_q 
                    = (0x0000ffffU & ((IData)(1U) + (IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q)));
            }
        } else {
            __Vdly__tb_pwm_core__DOT__i_dut__DOT__counter_q = 0U;
            vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q 
                = vlSelfRef.tb_pwm_core__DOT__period_cfg_i;
            vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__duty_active_q 
                = vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__duty_clamped;
        }
    } else {
        __Vdly__tb_pwm_core__DOT__i_dut__DOT__counter_q = 0U;
        vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q = 0U;
        vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__duty_active_q = 0U;
    }
    vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q 
        = __Vdly__tb_pwm_core__DOT__i_dut__DOT__counter_q;
}

void Vtb_pwm_core___024root___nba_comb__TOP__0(Vtb_pwm_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___nba_comb__TOP__0\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__duty_clamped 
        = ((0U == (IData)(vlSelfRef.tb_pwm_core__DOT__period_cfg_i))
            ? 0U : (((IData)(vlSelfRef.tb_pwm_core__DOT__duty_cfg_i) 
                     >= (IData)(vlSelfRef.tb_pwm_core__DOT__period_cfg_i))
                     ? (IData)(vlSelfRef.tb_pwm_core__DOT__period_cfg_i)
                     : (IData)(vlSelfRef.tb_pwm_core__DOT__duty_cfg_i)));
}

void Vtb_pwm_core___024root___nba_comb__TOP__1(Vtb_pwm_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___nba_comb__TOP__1\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_zero_o 
        = ((IData)(vlSelfRef.tb_pwm_core__DOT__enable_i) 
           & ((0U == (IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q)) 
              & (0U == (IData)(vlSelfRef.tb_pwm_core__DOT__period_cfg_i))));
    vlSelfRef.tb_pwm_core__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0 
        = ((IData)(vlSelfRef.tb_pwm_core__DOT__enable_i) 
           & (0U != (IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q)));
    vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_done_o 
        = ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0) 
           & ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q) 
              == (0x0000ffffU & ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q) 
                                 - (IData)(1U)))));
    vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__pwm_raw 
        = ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0) 
           & ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q) 
              < (IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__duty_active_q)));
    vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__pwm_o = 
        (1U & ((~ ((~ (IData)(vlSelfRef.tb_pwm_core__DOT__enable_i)) 
                   | (0U == (IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q)))) 
               & ((IData)(vlSelfRef.tb_pwm_core__DOT__polarity_i)
                   ? (~ (IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__pwm_raw))
                   : (IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__pwm_raw))));
}

void Vtb_pwm_core___024root___eval_nba(Vtb_pwm_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___eval_nba\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtb_pwm_core___024root___nba_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[3U] = 1U;
    }
    if ((5ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtb_pwm_core___024root___nba_comb__TOP__0(vlSelf);
    }
    if ((7ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtb_pwm_core___024root___nba_comb__TOP__1(vlSelf);
    }
}

void Vtb_pwm_core___024root___timing_ready(Vtb_pwm_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___timing_ready\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h9d9a0fdf__0.ready("@(posedge tb_pwm_core.clk_i)");
    }
}

void Vtb_pwm_core___024root___timing_resume(Vtb_pwm_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___timing_resume\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VtrigSched_h9d9a0fdf__0.moveToResumeQueue(
                                                          "@(posedge tb_pwm_core.clk_i)");
    vlSelfRef.__VtrigSched_h9d9a0fdf__0.resume("@(posedge tb_pwm_core.clk_i)");
    if ((4ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vtb_pwm_core___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_pwm_core___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vtb_pwm_core___024root___eval_phase__act(Vtb_pwm_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___eval_phase__act\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb_pwm_core___024root___eval_triggers_vec__act(vlSelf);
    Vtb_pwm_core___024root___timing_ready(vlSelf);
    Vtb_pwm_core___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_pwm_core___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vtb_pwm_core___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vtb_pwm_core___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vtb_pwm_core___024root___timing_resume(vlSelf);
        Vtb_pwm_core___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtb_pwm_core___024root___eval_phase__inact(Vtb_pwm_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___eval_phase__inact\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("tb_pwm_core.sv", 1, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vtb_pwm_core___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtb_pwm_core___024root___eval_phase__nba(Vtb_pwm_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___eval_phase__nba\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtb_pwm_core___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtb_pwm_core___024root___eval_nba(vlSelf);
        Vtb_pwm_core___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtb_pwm_core___024root___eval(Vtb_pwm_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___eval\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtb_pwm_core___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("tb_pwm_core.sv", 1, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("tb_pwm_core.sv", 1, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vtb_pwm_core___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("tb_pwm_core.sv", 1, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vtb_pwm_core___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vtb_pwm_core___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vtb_pwm_core___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

void Vtb_pwm_core___024root____VbeforeTrig_h9d9a0fdf__0(Vtb_pwm_core___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root____VbeforeTrig_h9d9a0fdf__0\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)(((IData)(vlSelfRef.tb_pwm_core__DOT__clk_i) 
                                  & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_pwm_core__DOT__clk_i__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_pwm_core__DOT__clk_i__0 
        = vlSelfRef.tb_pwm_core__DOT__clk_i;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h9d9a0fdf__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h9d9a0fdf__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h9d9a0fdf__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h9d9a0fdf__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h9d9a0fdf__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h9d9a0fdf__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h9d9a0fdf__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h9d9a0fdf__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h9d9a0fdf__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h9d9a0fdf__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h9d9a0fdf__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

#ifdef VL_DEBUG
void Vtb_pwm_core___024root___eval_debug_assertions(Vtb_pwm_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___eval_debug_assertions\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
