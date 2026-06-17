// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_pwm_core.h for the primary calling header

#ifndef VERILATED_VTB_PWM_CORE___024ROOT_H_
#define VERILATED_VTB_PWM_CORE___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_pwm_core__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_pwm_core___024root final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ tb_pwm_core__DOT__clk_i;
    CData/*0:0*/ tb_pwm_core__DOT__rst_ni;
    CData/*0:0*/ tb_pwm_core__DOT__enable_i;
    CData/*0:0*/ tb_pwm_core__DOT__polarity_i;
    CData/*0:0*/ tb_pwm_core__DOT__i_dut__DOT__pwm_o;
    CData/*0:0*/ tb_pwm_core__DOT__i_dut__DOT__period_done_o;
    CData/*0:0*/ tb_pwm_core__DOT__i_dut__DOT__period_zero_o;
    CData/*0:0*/ tb_pwm_core__DOT__i_dut__DOT__pwm_raw;
    CData/*0:0*/ tb_pwm_core__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VstlPhaseResult;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_pwm_core__DOT__clk_i__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_pwm_core__DOT__rst_ni__0;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VinactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    SData/*15:0*/ tb_pwm_core__DOT__period_cfg_i;
    SData/*15:0*/ tb_pwm_core__DOT__duty_cfg_i;
    SData/*15:0*/ tb_pwm_core__DOT__i_dut__DOT__counter_q;
    SData/*15:0*/ tb_pwm_core__DOT__i_dut__DOT__period_active_q;
    SData/*15:0*/ tb_pwm_core__DOT__i_dut__DOT__duty_active_q;
    SData/*15:0*/ tb_pwm_core__DOT__i_dut__DOT__duty_clamped;
    IData/*31:0*/ tb_pwm_core__DOT__errors;
    IData/*31:0*/ __VactIterCount;
    IData/*31:0*/ __VinactIterCount;
    IData/*31:0*/ __Vi;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggeredAcc;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    VlUnpacked<CData/*0:0*/, 4> __Vm_traceActivity;
    std::string __Vtask_tb_pwm_core__DOT__check_cycles__1__name;
    std::string __Vtask_tb_pwm_core__DOT__check_current__2__name;
    std::string __Vtask_tb_pwm_core__DOT__check_cycles__5__name;
    std::string __Vtask_tb_pwm_core__DOT__check_current__6__name;
    std::string __Vtask_tb_pwm_core__DOT__check_cycles__9__name;
    std::string __Vtask_tb_pwm_core__DOT__check_current__10__name;
    std::string __Vtask_tb_pwm_core__DOT__check_cycles__13__name;
    std::string __Vtask_tb_pwm_core__DOT__check_current__14__name;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_h9d9a0fdf__0;

    // INTERNAL VARIABLES
    Vtb_pwm_core__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_pwm_core___024root(Vtb_pwm_core__Syms* symsp, const char* namep);
    ~Vtb_pwm_core___024root();
    VL_UNCOPYABLE(Vtb_pwm_core___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
