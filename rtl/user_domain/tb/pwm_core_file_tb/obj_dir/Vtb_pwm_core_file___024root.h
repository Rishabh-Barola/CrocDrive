// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_pwm_core_file.h for the primary calling header

#ifndef VERILATED_VTB_PWM_CORE_FILE___024ROOT_H_
#define VERILATED_VTB_PWM_CORE_FILE___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_pwm_core_file__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_pwm_core_file___024root final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ tb_pwm_core_file__DOT__clk;
    CData/*0:0*/ tb_pwm_core_file__DOT__rst_n;
    CData/*0:0*/ tb_pwm_core_file__DOT__eoc;
    CData/*0:0*/ tb_pwm_core_file__DOT__enable_i;
    CData/*0:0*/ tb_pwm_core_file__DOT__polarity_i;
    CData/*0:0*/ tb_pwm_core_file__DOT__i_dut__DOT__pwm_o;
    CData/*0:0*/ tb_pwm_core_file__DOT__i_dut__DOT__period_done_o;
    CData/*0:0*/ tb_pwm_core_file__DOT__i_dut__DOT__period_zero_o;
    CData/*0:0*/ tb_pwm_core_file__DOT__i_dut__DOT__pwm_raw;
    CData/*0:0*/ tb_pwm_core_file__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VstlPhaseResult;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_pwm_core_file__DOT__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_pwm_core_file__DOT__rst_n__0;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VinactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    SData/*15:0*/ tb_pwm_core_file__DOT__period_cfg_i;
    SData/*15:0*/ tb_pwm_core_file__DOT__duty_cfg_i;
    SData/*15:0*/ tb_pwm_core_file__DOT__i_dut__DOT__counter_q;
    SData/*15:0*/ tb_pwm_core_file__DOT__i_dut__DOT__period_active_q;
    SData/*15:0*/ tb_pwm_core_file__DOT__i_dut__DOT__duty_active_q;
    SData/*15:0*/ tb_pwm_core_file__DOT__i_dut__DOT__duty_clamped;
    IData/*31:0*/ tb_pwm_core_file__DOT__rsp_idx;
    IData/*31:0*/ tb_pwm_core_file__DOT__errors;
    IData/*31:0*/ tb_pwm_core_file__DOT__load_stimuli__Vstatic__file;
    IData/*31:0*/ tb_pwm_core_file__DOT__load_exp_response__Vstatic__file;
    IData/*31:0*/ tb_pwm_core_file__DOT__unnamedblk1__DOT__unnamedblk2__DOT__j;
    IData/*31:0*/ __VactIterCount;
    IData/*31:0*/ __VinactIterCount;
    IData/*31:0*/ __Vi;
    QData/*63:0*/ tb_pwm_core_file__DOT__load_stimuli__Vstatic__temp;
    QData/*63:0*/ tb_pwm_core_file__DOT__load_exp_response__Vstatic__temp;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggeredAcc;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    VlUnpacked<CData/*0:0*/, 4> __Vm_traceActivity;
    VlQueue<QData/*48:0*/> tb_pwm_core_file__DOT__stimuli;
    VlQueue<QData/*50:0*/> tb_pwm_core_file__DOT__exp_response;
    std::string tb_pwm_core_file__DOT__load_stimuli__Vstatic__line;
    std::string tb_pwm_core_file__DOT__load_exp_response__Vstatic__line;
    std::string __Vtask_tb_pwm_core_file__DOT__load_stimuli__0__filename;
    std::string __Vtask_tb_pwm_core_file__DOT__load_exp_response__1__filename;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_hdd35d4ed__0;

    // INTERNAL VARIABLES
    Vtb_pwm_core_file__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_pwm_core_file___024root(Vtb_pwm_core_file__Syms* symsp, const char* namep);
    ~Vtb_pwm_core_file___024root();
    VL_UNCOPYABLE(Vtb_pwm_core_file___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
