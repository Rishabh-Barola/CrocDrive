// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_pwm_core_file.h for the primary calling header

#include "Vtb_pwm_core_file__pch.h"

VlCoroutine Vtb_pwm_core_file___024root___eval_initial__TOP__Vtiming__0(Vtb_pwm_core_file___024root* vlSelf);
VlCoroutine Vtb_pwm_core_file___024root___eval_initial__TOP__Vtiming__1(Vtb_pwm_core_file___024root* vlSelf);

void Vtb_pwm_core_file___024root___eval_initial(Vtb_pwm_core_file___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___eval_initial\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtb_pwm_core_file___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
    Vtb_pwm_core_file___024root___eval_initial__TOP__Vtiming__1(vlSelf);
}

VlCoroutine Vtb_pwm_core_file___024root___eval_initial__TOP__Vtiming__0(Vtb_pwm_core_file___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_pwm_core_file__DOT__clk = 0U;
    do {
        vlSelfRef.tb_pwm_core_file__DOT__clk = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                             nullptr, 
                                             "tb_pwm_core_file.sv", 
                                             76);
        vlSelfRef.tb_pwm_core_file__DOT__clk = 0U;
        co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                             nullptr, 
                                             "tb_pwm_core_file.sv", 
                                             77);
    } while ((1U & (~ (IData)(vlSelfRef.tb_pwm_core_file__DOT__eoc))));
    co_return;
}

void Vtb_pwm_core_file___024root____VbeforeTrig_hdd35d4ed__0(Vtb_pwm_core_file___024root* vlSelf, const char* __VeventDescription);

VlCoroutine Vtb_pwm_core_file___024root___eval_initial__TOP__Vtiming__1(Vtb_pwm_core_file___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ tb_pwm_core_file__DOT__unnamedblk1_1__DOT____Vrepeat0;
    tb_pwm_core_file__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    IData/*31:0*/ tb_pwm_core_file__DOT__unnamedblk1__DOT__i;
    tb_pwm_core_file__DOT__unnamedblk1__DOT__i = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core_file__DOT__load_stimuli__0__i;
    __Vtask_tb_pwm_core_file__DOT__load_stimuli__0__i = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core_file__DOT__load_stimuli__0__line_count;
    __Vtask_tb_pwm_core_file__DOT__load_stimuli__0__line_count = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core_file__DOT__load_exp_response__1__i;
    __Vtask_tb_pwm_core_file__DOT__load_exp_response__1__i = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core_file__DOT__load_exp_response__1__line_count;
    __Vtask_tb_pwm_core_file__DOT__load_exp_response__1__line_count = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core_file__DOT__check_response__2__vector_idx;
    __Vtask_tb_pwm_core_file__DOT__check_response__2__vector_idx = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core_file__DOT__check_response__2__sample_idx;
    __Vtask_tb_pwm_core_file__DOT__check_response__2__sample_idx = 0;
    IData/*31:0*/ __Vtask_tb_pwm_core_file__DOT__check_response__2__response_idx;
    __Vtask_tb_pwm_core_file__DOT__check_response__2__response_idx = 0;
    QData/*50:0*/ __Vtask_tb_pwm_core_file__DOT__check_response__2__exp;
    __Vtask_tb_pwm_core_file__DOT__check_response__2__exp = 0;
    // Body
    vlSelfRef.tb_pwm_core_file__DOT__eoc = 0U;
    vlSelfRef.tb_pwm_core_file__DOT__errors = 0U;
    vlSelfRef.tb_pwm_core_file__DOT__rsp_idx = 0U;
    vlSelfRef.tb_pwm_core_file__DOT__rst_n = 0U;
    vlSelfRef.tb_pwm_core_file__DOT__enable_i = 0U;
    vlSelfRef.tb_pwm_core_file__DOT__polarity_i = 0U;
    vlSelfRef.tb_pwm_core_file__DOT__period_cfg_i = 0U;
    vlSelfRef.tb_pwm_core_file__DOT__duty_cfg_i = 0U;
    vlSymsp->_vm_contextp__->dumpfile("tb_pwm_core_file.fst"s);
    vlSymsp->_traceDumpOpen();
    VL_WRITEF_NX("[TB] Loading stimuli from ./stimuli/stimuli.txt\n",0);
    vlSelfRef.__Vtask_tb_pwm_core_file__DOT__load_stimuli__0__filename = "./stimuli/stimuli.txt"s;
    __Vtask_tb_pwm_core_file__DOT__load_stimuli__0__i = 0U;
    __Vtask_tb_pwm_core_file__DOT__load_stimuli__0__line_count = 0U;
    vlSelfRef.tb_pwm_core_file__DOT__load_stimuli__Vstatic__file 
        = VL_FOPEN_NN("./stimuli/stimuli.txt"s, "r"s);
    ;
    if (VL_UNLIKELY(((0U == vlSelfRef.tb_pwm_core_file__DOT__load_stimuli__Vstatic__file)))) {
        VL_WRITEF_NX("[%0t] %%Fatal: tb_pwm_core_file.sv:204: Assertion failed in %Ntb_pwm_core_file.load_stimuli: Error: Failed to open file '%@'\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_pwm_core_file__DOT__load_stimuli__0__filename));
        VL_STOP_MT("tb_pwm_core_file.sv", 204, "", false);
    }
    while ((! (vlSelfRef.tb_pwm_core_file__DOT__load_stimuli__Vstatic__file ? feof(VL_CVT_I_FP(vlSelfRef.tb_pwm_core_file__DOT__load_stimuli__Vstatic__file)) : true))) {
        if ((0U != VL_FGETS_NI(vlSelfRef.tb_pwm_core_file__DOT__load_stimuli__Vstatic__line, vlSelfRef.tb_pwm_core_file__DOT__load_stimuli__Vstatic__file))) {
            if (VL_LTS_III(32, 1U, VL_LEN_IN(vlSelfRef.tb_pwm_core_file__DOT__load_stimuli__Vstatic__line))) {
                __Vtask_tb_pwm_core_file__DOT__load_stimuli__0__line_count 
                    = ((IData)(1U) + __Vtask_tb_pwm_core_file__DOT__load_stimuli__0__line_count);
            }
        }
    }
    VL_FCLOSE_I(vlSelfRef.tb_pwm_core_file__DOT__load_stimuli__Vstatic__file); vlSelfRef.tb_pwm_core_file__DOT__stimuli.renew(__Vtask_tb_pwm_core_file__DOT__load_stimuli__0__line_count);
    vlSelfRef.tb_pwm_core_file__DOT__load_stimuli__Vstatic__file 
        = VL_FOPEN_NN(vlSelfRef.__Vtask_tb_pwm_core_file__DOT__load_stimuli__0__filename
                      , "r"s);
    ;
    while ((! (vlSelfRef.tb_pwm_core_file__DOT__load_stimuli__Vstatic__file ? feof(VL_CVT_I_FP(vlSelfRef.tb_pwm_core_file__DOT__load_stimuli__Vstatic__file)) : true))) {
        if ((0U != VL_FGETS_NI(vlSelfRef.tb_pwm_core_file__DOT__load_stimuli__Vstatic__line, vlSelfRef.tb_pwm_core_file__DOT__load_stimuli__Vstatic__file))) {
            if (VL_LTS_III(32, 1U, VL_LEN_IN(vlSelfRef.tb_pwm_core_file__DOT__load_stimuli__Vstatic__line))) {
                if (VL_UNLIKELY(((1U != VL_SSCANF_INNX(64,vlSelfRef.tb_pwm_core_file__DOT__load_stimuli__Vstatic__line,"%b",0,
                                                       64,
                                                       &(vlSelfRef.tb_pwm_core_file__DOT__load_stimuli__Vstatic__temp)) )))) {
                    VL_WRITEF_NX("[%0t] %%Fatal: tb_pwm_core_file.sv:223: Assertion failed in %Ntb_pwm_core_file.load_stimuli: Could not parse binary line: %@\n",0,
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,vlSymsp->name(),
                                 -1,&(vlSelfRef.tb_pwm_core_file__DOT__load_stimuli__Vstatic__line));
                    VL_STOP_MT("tb_pwm_core_file.sv", 223, "", false);
                }
                vlSelfRef.tb_pwm_core_file__DOT__stimuli.atWrite(__Vtask_tb_pwm_core_file__DOT__load_stimuli__0__i) 
                    = ((0x0000ffffffffffffULL & vlSelfRef.tb_pwm_core_file__DOT__stimuli.atWrite(__Vtask_tb_pwm_core_file__DOT__load_stimuli__0__i)) 
                       | ((QData)((IData)((1U & (IData)(
                                                        (vlSelfRef.tb_pwm_core_file__DOT__load_stimuli__Vstatic__temp 
                                                         >> 0x30U))))) 
                          << 0x00000030U));
                vlSelfRef.tb_pwm_core_file__DOT__stimuli.atWrite(__Vtask_tb_pwm_core_file__DOT__load_stimuli__0__i) 
                    = ((0x00010000ffffffffULL & vlSelfRef.tb_pwm_core_file__DOT__stimuli.atWrite(__Vtask_tb_pwm_core_file__DOT__load_stimuli__0__i)) 
                       | ((QData)((IData)((0x0000ffffU 
                                           & (IData)(
                                                     (vlSelfRef.tb_pwm_core_file__DOT__load_stimuli__Vstatic__temp 
                                                      >> 0x20U))))) 
                          << 0x00000020U));
                vlSelfRef.tb_pwm_core_file__DOT__stimuli.atWrite(__Vtask_tb_pwm_core_file__DOT__load_stimuli__0__i) 
                    = ((0x0001ffff0000ffffULL & vlSelfRef.tb_pwm_core_file__DOT__stimuli.atWrite(__Vtask_tb_pwm_core_file__DOT__load_stimuli__0__i)) 
                       | ((QData)((IData)((0x0000ffffU 
                                           & (IData)(
                                                     (vlSelfRef.tb_pwm_core_file__DOT__load_stimuli__Vstatic__temp 
                                                      >> 0x10U))))) 
                          << 0x00000010U));
                vlSelfRef.tb_pwm_core_file__DOT__stimuli.atWrite(__Vtask_tb_pwm_core_file__DOT__load_stimuli__0__i) 
                    = ((0x0001ffffffff0000ULL & vlSelfRef.tb_pwm_core_file__DOT__stimuli.atWrite(__Vtask_tb_pwm_core_file__DOT__load_stimuli__0__i)) 
                       | (IData)((IData)((0x0000ffffU 
                                          & (IData)(vlSelfRef.tb_pwm_core_file__DOT__load_stimuli__Vstatic__temp)))));
                __Vtask_tb_pwm_core_file__DOT__load_stimuli__0__i 
                    = ((IData)(1U) + __Vtask_tb_pwm_core_file__DOT__load_stimuli__0__i);
            }
        }
    }
    VL_FCLOSE_I(vlSelfRef.tb_pwm_core_file__DOT__load_stimuli__Vstatic__file); VL_WRITEF_NX("[TB] Loading expected responses from ./stimuli/expected_response.txt\n",0);
    vlSelfRef.__Vtask_tb_pwm_core_file__DOT__load_exp_response__1__filename = "./stimuli/expected_response.txt"s;
    __Vtask_tb_pwm_core_file__DOT__load_exp_response__1__i = 0U;
    __Vtask_tb_pwm_core_file__DOT__load_exp_response__1__line_count = 0U;
    vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__file 
        = VL_FOPEN_NN("./stimuli/expected_response.txt"s
                      , "r"s);
    ;
    if (VL_UNLIKELY(((0U == vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__file)))) {
        VL_WRITEF_NX("[%0t] %%Fatal: tb_pwm_core_file.sv:249: Assertion failed in %Ntb_pwm_core_file.load_exp_response: Error: Failed to open file '%@'\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_pwm_core_file__DOT__load_exp_response__1__filename));
        VL_STOP_MT("tb_pwm_core_file.sv", 249, "", false);
    }
    while ((! (vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__file ? feof(VL_CVT_I_FP(vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__file)) : true))) {
        if ((0U != VL_FGETS_NI(vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__line, vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__file))) {
            if (VL_LTS_III(32, 1U, VL_LEN_IN(vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__line))) {
                __Vtask_tb_pwm_core_file__DOT__load_exp_response__1__line_count 
                    = ((IData)(1U) + __Vtask_tb_pwm_core_file__DOT__load_exp_response__1__line_count);
            }
        }
    }
    VL_FCLOSE_I(vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__file); vlSelfRef.tb_pwm_core_file__DOT__exp_response.renew(__Vtask_tb_pwm_core_file__DOT__load_exp_response__1__line_count);
    vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__file 
        = VL_FOPEN_NN(vlSelfRef.__Vtask_tb_pwm_core_file__DOT__load_exp_response__1__filename
                      , "r"s);
    ;
    while ((! (vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__file ? feof(VL_CVT_I_FP(vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__file)) : true))) {
        if ((0U != VL_FGETS_NI(vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__line, vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__file))) {
            if (VL_LTS_III(32, 1U, VL_LEN_IN(vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__line))) {
                if (VL_UNLIKELY(((1U != VL_SSCANF_INNX(64,vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__line,"%b",0,
                                                       64,
                                                       &(vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__temp)) )))) {
                    VL_WRITEF_NX("[%0t] %%Fatal: tb_pwm_core_file.sv:268: Assertion failed in %Ntb_pwm_core_file.load_exp_response: Could not parse binary line: %@\n",0,
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,vlSymsp->name(),
                                 -1,&(vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__line));
                    VL_STOP_MT("tb_pwm_core_file.sv", 268, "", false);
                }
                vlSelfRef.tb_pwm_core_file__DOT__exp_response.atWrite(__Vtask_tb_pwm_core_file__DOT__load_exp_response__1__i) 
                    = ((0x0003ffffffffffffULL & vlSelfRef.tb_pwm_core_file__DOT__exp_response.atWrite(__Vtask_tb_pwm_core_file__DOT__load_exp_response__1__i)) 
                       | ((QData)((IData)((1U & (IData)(
                                                        (vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__temp 
                                                         >> 0x32U))))) 
                          << 0x00000032U));
                vlSelfRef.tb_pwm_core_file__DOT__exp_response.atWrite(__Vtask_tb_pwm_core_file__DOT__load_exp_response__1__i) 
                    = ((0x0005ffffffffffffULL & vlSelfRef.tb_pwm_core_file__DOT__exp_response.atWrite(__Vtask_tb_pwm_core_file__DOT__load_exp_response__1__i)) 
                       | ((QData)((IData)((1U & (IData)(
                                                        (vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__temp 
                                                         >> 0x31U))))) 
                          << 0x00000031U));
                vlSelfRef.tb_pwm_core_file__DOT__exp_response.atWrite(__Vtask_tb_pwm_core_file__DOT__load_exp_response__1__i) 
                    = ((0x0006ffffffffffffULL & vlSelfRef.tb_pwm_core_file__DOT__exp_response.atWrite(__Vtask_tb_pwm_core_file__DOT__load_exp_response__1__i)) 
                       | ((QData)((IData)((1U & (IData)(
                                                        (vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__temp 
                                                         >> 0x30U))))) 
                          << 0x00000030U));
                vlSelfRef.tb_pwm_core_file__DOT__exp_response.atWrite(__Vtask_tb_pwm_core_file__DOT__load_exp_response__1__i) 
                    = ((0x00070000ffffffffULL & vlSelfRef.tb_pwm_core_file__DOT__exp_response.atWrite(__Vtask_tb_pwm_core_file__DOT__load_exp_response__1__i)) 
                       | ((QData)((IData)((0x0000ffffU 
                                           & (IData)(
                                                     (vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__temp 
                                                      >> 0x20U))))) 
                          << 0x00000020U));
                vlSelfRef.tb_pwm_core_file__DOT__exp_response.atWrite(__Vtask_tb_pwm_core_file__DOT__load_exp_response__1__i) 
                    = ((0x0007ffff0000ffffULL & vlSelfRef.tb_pwm_core_file__DOT__exp_response.atWrite(__Vtask_tb_pwm_core_file__DOT__load_exp_response__1__i)) 
                       | ((QData)((IData)((0x0000ffffU 
                                           & (IData)(
                                                     (vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__temp 
                                                      >> 0x10U))))) 
                          << 0x00000010U));
                vlSelfRef.tb_pwm_core_file__DOT__exp_response.atWrite(__Vtask_tb_pwm_core_file__DOT__load_exp_response__1__i) 
                    = ((0x0007ffffffff0000ULL & vlSelfRef.tb_pwm_core_file__DOT__exp_response.atWrite(__Vtask_tb_pwm_core_file__DOT__load_exp_response__1__i)) 
                       | (IData)((IData)((0x0000ffffU 
                                          & (IData)(vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__temp)))));
                __Vtask_tb_pwm_core_file__DOT__load_exp_response__1__i 
                    = ((IData)(1U) + __Vtask_tb_pwm_core_file__DOT__load_exp_response__1__i);
            }
        }
    }
    VL_FCLOSE_I(vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__file); tb_pwm_core_file__DOT__unnamedblk1_1__DOT____Vrepeat0 = 3U;
    while (VL_LTS_III(32, 0U, tb_pwm_core_file__DOT__unnamedblk1_1__DOT____Vrepeat0)) {
        Vtb_pwm_core_file___024root____VbeforeTrig_hdd35d4ed__0(vlSelf, 
                                                                "@(posedge tb_pwm_core_file.clk)");
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VtrigSched_hdd35d4ed__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_pwm_core_file.clk)", 
                                                             "tb_pwm_core_file.sv", 
                                                             104);
        tb_pwm_core_file__DOT__unnamedblk1_1__DOT____Vrepeat0 
            = (tb_pwm_core_file__DOT__unnamedblk1_1__DOT____Vrepeat0 
               - (IData)(1U));
    }
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "tb_pwm_core_file.sv", 
                                         105);
    vlSelfRef.tb_pwm_core_file__DOT__rst_n = 1U;
    Vtb_pwm_core_file___024root____VbeforeTrig_hdd35d4ed__0(vlSelf, 
                                                            "@(posedge tb_pwm_core_file.clk)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_hdd35d4ed__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_pwm_core_file.clk)", 
                                                         "tb_pwm_core_file.sv", 
                                                         108);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "tb_pwm_core_file.sv", 
                                         109);
    tb_pwm_core_file__DOT__unnamedblk1__DOT__i = 0U;
    while (VL_LTS_III(32, tb_pwm_core_file__DOT__unnamedblk1__DOT__i, vlSelfRef.tb_pwm_core_file__DOT__stimuli.size())) {
        VL_WRITEF_NX("[TB] Vector %0d: polarity=%0# period=%0# duty=%0# samples=%0#\n",0,
                     32,tb_pwm_core_file__DOT__unnamedblk1__DOT__i,
                     1,(1U & (IData)((vlSelfRef.tb_pwm_core_file__DOT__stimuli.at(tb_pwm_core_file__DOT__unnamedblk1__DOT__i) 
                                      >> 0x00000030U))),
                     16,(0x0000ffffU & (IData)((vlSelfRef.tb_pwm_core_file__DOT__stimuli.at(tb_pwm_core_file__DOT__unnamedblk1__DOT__i) 
                                                >> 0x00000020U))),
                     16,(0x0000ffffU & (IData)((vlSelfRef.tb_pwm_core_file__DOT__stimuli.at(tb_pwm_core_file__DOT__unnamedblk1__DOT__i) 
                                                >> 0x00000010U))),
                     16,(0x0000ffffU & (IData)(vlSelfRef.tb_pwm_core_file__DOT__stimuli.at(tb_pwm_core_file__DOT__unnamedblk1__DOT__i))));
        vlSelfRef.tb_pwm_core_file__DOT__enable_i = 0U;
        vlSelfRef.tb_pwm_core_file__DOT__polarity_i 
            = (1U & (IData)((vlSelfRef.tb_pwm_core_file__DOT__stimuli.at(tb_pwm_core_file__DOT__unnamedblk1__DOT__i) 
                             >> 0x00000030U)));
        vlSelfRef.tb_pwm_core_file__DOT__period_cfg_i 
            = (0x0000ffffU & (IData)((vlSelfRef.tb_pwm_core_file__DOT__stimuli.at(tb_pwm_core_file__DOT__unnamedblk1__DOT__i) 
                                      >> 0x00000020U)));
        vlSelfRef.tb_pwm_core_file__DOT__duty_cfg_i 
            = (0x0000ffffU & (IData)((vlSelfRef.tb_pwm_core_file__DOT__stimuli.at(tb_pwm_core_file__DOT__unnamedblk1__DOT__i) 
                                      >> 0x00000010U)));
        Vtb_pwm_core_file___024root____VbeforeTrig_hdd35d4ed__0(vlSelf, 
                                                                "@(posedge tb_pwm_core_file.clk)");
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VtrigSched_hdd35d4ed__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_pwm_core_file.clk)", 
                                                             "tb_pwm_core_file.sv", 
                                                             122);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "tb_pwm_core_file.sv", 
                                             123);
        vlSelfRef.tb_pwm_core_file__DOT__enable_i = 1U;
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "tb_pwm_core_file.sv", 
                                             129);
        vlSelfRef.tb_pwm_core_file__DOT__unnamedblk1__DOT__unnamedblk2__DOT__j = 0U;
        while ((vlSelfRef.tb_pwm_core_file__DOT__unnamedblk1__DOT__unnamedblk2__DOT__j 
                < (0x0000ffffU & (IData)(vlSelfRef.tb_pwm_core_file__DOT__stimuli.at(tb_pwm_core_file__DOT__unnamedblk1__DOT__i))))) {
            __Vtask_tb_pwm_core_file__DOT__check_response__2__response_idx 
                = vlSelfRef.tb_pwm_core_file__DOT__rsp_idx;
            __Vtask_tb_pwm_core_file__DOT__check_response__2__sample_idx 
                = vlSelfRef.tb_pwm_core_file__DOT__unnamedblk1__DOT__unnamedblk2__DOT__j;
            __Vtask_tb_pwm_core_file__DOT__check_response__2__vector_idx 
                = tb_pwm_core_file__DOT__unnamedblk1__DOT__i;
            __Vtask_tb_pwm_core_file__DOT__check_response__2__exp = 0;
            __Vtask_tb_pwm_core_file__DOT__check_response__2__exp 
                = vlSelfRef.tb_pwm_core_file__DOT__exp_response.at(__Vtask_tb_pwm_core_file__DOT__check_response__2__response_idx);
            if (VL_UNLIKELY(((((((((IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__pwm_o) 
                                   != (1U & (IData)(
                                                    (__Vtask_tb_pwm_core_file__DOT__check_response__2__exp 
                                                     >> 0x00000032U)))) 
                                  | (((IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0) 
                                      & ((IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__counter_q) 
                                         == (0x0000ffffU 
                                             & ((IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_active_q) 
                                                - (IData)(1U))))) 
                                     != (1U & (IData)(
                                                      (__Vtask_tb_pwm_core_file__DOT__check_response__2__exp 
                                                       >> 0x00000031U))))) 
                                 | ((IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_zero_o) 
                                    != (1U & (IData)(
                                                     (__Vtask_tb_pwm_core_file__DOT__check_response__2__exp 
                                                      >> 0x00000030U))))) 
                                | ((IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__counter_q) 
                                   != (0x0000ffffU 
                                       & (IData)((__Vtask_tb_pwm_core_file__DOT__check_response__2__exp 
                                                  >> 0x00000020U))))) 
                               | ((IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_active_q) 
                                  != (0x0000ffffU & (IData)(
                                                            (__Vtask_tb_pwm_core_file__DOT__check_response__2__exp 
                                                             >> 0x00000010U))))) 
                              | ((IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__duty_active_q) 
                                 != (0x0000ffffU & (IData)(__Vtask_tb_pwm_core_file__DOT__check_response__2__exp))))))) {
                VL_WRITEF_NX("[ERROR] vec=%0# sample=%0# rsp_idx=%0# time=%0t\n        expected: pwm=%0b done=%0b zero=%0b counter=%0# period_active=%0# duty_active=%0#\n        actual:   pwm=%0b done=%0b zero=%0b counter=%0# period_active=%0# duty_active=%0#\n",0,
                             32,__Vtask_tb_pwm_core_file__DOT__check_response__2__vector_idx,
                             32,__Vtask_tb_pwm_core_file__DOT__check_response__2__sample_idx,
                             32,__Vtask_tb_pwm_core_file__DOT__check_response__2__response_idx,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,1,(1U & (IData)((__Vtask_tb_pwm_core_file__DOT__check_response__2__exp 
                                                 >> 0x00000032U))),
                             1,(1U & (IData)((__Vtask_tb_pwm_core_file__DOT__check_response__2__exp 
                                              >> 0x00000031U))),
                             1,(1U & (IData)((__Vtask_tb_pwm_core_file__DOT__check_response__2__exp 
                                              >> 0x00000030U))),
                             16,(0x0000ffffU & (IData)(
                                                       (__Vtask_tb_pwm_core_file__DOT__check_response__2__exp 
                                                        >> 0x00000020U))),
                             16,(0x0000ffffU & (IData)(
                                                       (__Vtask_tb_pwm_core_file__DOT__check_response__2__exp 
                                                        >> 0x00000010U))),
                             16,(0x0000ffffU & (IData)(__Vtask_tb_pwm_core_file__DOT__check_response__2__exp)),
                             1,(IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__pwm_o),
                             1,((IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0) 
                                & ((IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__counter_q) 
                                   == (0x0000ffffU 
                                       & ((IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_active_q) 
                                          - (IData)(1U))))),
                             1,(IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_zero_o),
                             16,vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__counter_q,
                             16,(IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_active_q),
                             16,vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__duty_active_q);
                vlSelfRef.tb_pwm_core_file__DOT__errors 
                    = ((IData)(1U) + vlSelfRef.tb_pwm_core_file__DOT__errors);
            }
            vlSelfRef.tb_pwm_core_file__DOT__rsp_idx 
                = ((IData)(1U) + vlSelfRef.tb_pwm_core_file__DOT__rsp_idx);
            Vtb_pwm_core_file___024root____VbeforeTrig_hdd35d4ed__0(vlSelf, 
                                                                    "@(posedge tb_pwm_core_file.clk)");
            vlSelfRef.__Vm_traceActivity[2U] = 1U;
            co_await vlSelfRef.__VtrigSched_hdd35d4ed__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_pwm_core_file.clk)", 
                                                                 "tb_pwm_core_file.sv", 
                                                                 135);
            vlSelfRef.__Vm_traceActivity[2U] = 1U;
            co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                                 nullptr, 
                                                 "tb_pwm_core_file.sv", 
                                                 136);
            vlSelfRef.tb_pwm_core_file__DOT__unnamedblk1__DOT__unnamedblk2__DOT__j 
                = ((IData)(1U) + vlSelfRef.tb_pwm_core_file__DOT__unnamedblk1__DOT__unnamedblk2__DOT__j);
        }
        tb_pwm_core_file__DOT__unnamedblk1__DOT__i 
            = ((IData)(1U) + tb_pwm_core_file__DOT__unnamedblk1__DOT__i);
    }
    if (VL_UNLIKELY(((vlSelfRef.tb_pwm_core_file__DOT__rsp_idx 
                      != vlSelfRef.tb_pwm_core_file__DOT__exp_response.size())))) {
        VL_WRITEF_NX("[ERROR] Used %0# expected responses, but file contains %0d\n",0,
                     32,vlSelfRef.tb_pwm_core_file__DOT__rsp_idx,
                     32,vlSelfRef.tb_pwm_core_file__DOT__exp_response.size());
        vlSelfRef.tb_pwm_core_file__DOT__errors = ((IData)(1U) 
                                                   + vlSelfRef.tb_pwm_core_file__DOT__errors);
    }
    if (VL_LIKELY(((0U == vlSelfRef.tb_pwm_core_file__DOT__errors)))) {
        VL_WRITEF_NX("[TB] PWM file-based test PASSED\n",0);
    } else {
        VL_WRITEF_NX("[TB] PWM file-based test FAILED with %0# errors\n[%0t] %%Fatal: tb_pwm_core_file.sv:150: Assertion failed in %Ntb_pwm_core_file\n",0,
                     32,vlSelfRef.tb_pwm_core_file__DOT__errors,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("tb_pwm_core_file.sv", 150, "", false);
    }
    vlSelfRef.tb_pwm_core_file__DOT__eoc = 1U;
    VL_FINISH_MT("tb_pwm_core_file.sv", 155, "");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_return;
}

void Vtb_pwm_core_file___024root___eval_triggers_vec__act(Vtb_pwm_core_file___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___eval_triggers_vec__act\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                      << 2U) 
                                                     | ((((~ (IData)(vlSelfRef.tb_pwm_core_file__DOT__rst_n)) 
                                                          & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_pwm_core_file__DOT__rst_n__0)) 
                                                         << 1U) 
                                                        | ((IData)(vlSelfRef.tb_pwm_core_file__DOT__clk) 
                                                           & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_pwm_core_file__DOT__clk__0)))))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_pwm_core_file__DOT__clk__0 
        = vlSelfRef.tb_pwm_core_file__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_pwm_core_file__DOT__rst_n__0 
        = vlSelfRef.tb_pwm_core_file__DOT__rst_n;
}

bool Vtb_pwm_core_file___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___trigger_anySet__act\n"); );
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

void Vtb_pwm_core_file___024root___act_comb__TOP__0(Vtb_pwm_core_file___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___act_comb__TOP__0\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__duty_clamped 
        = ((0U == (IData)(vlSelfRef.tb_pwm_core_file__DOT__period_cfg_i))
            ? 0U : (((IData)(vlSelfRef.tb_pwm_core_file__DOT__duty_cfg_i) 
                     >= (IData)(vlSelfRef.tb_pwm_core_file__DOT__period_cfg_i))
                     ? (IData)(vlSelfRef.tb_pwm_core_file__DOT__period_cfg_i)
                     : (IData)(vlSelfRef.tb_pwm_core_file__DOT__duty_cfg_i)));
    vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_zero_o 
        = ((IData)(vlSelfRef.tb_pwm_core_file__DOT__enable_i) 
           & ((0U == (IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_active_q)) 
              & (0U == (IData)(vlSelfRef.tb_pwm_core_file__DOT__period_cfg_i))));
    vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0 
        = ((IData)(vlSelfRef.tb_pwm_core_file__DOT__enable_i) 
           & (0U != (IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_active_q)));
    vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_done_o 
        = ((IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0) 
           & ((IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__counter_q) 
              == (0x0000ffffU & ((IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_active_q) 
                                 - (IData)(1U)))));
    vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__pwm_raw 
        = ((IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0) 
           & ((IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__counter_q) 
              < (IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__duty_active_q)));
    vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__pwm_o 
        = (1U & ((~ ((~ (IData)(vlSelfRef.tb_pwm_core_file__DOT__enable_i)) 
                     | (0U == (IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_active_q)))) 
                 & ((IData)(vlSelfRef.tb_pwm_core_file__DOT__polarity_i)
                     ? (~ (IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__pwm_raw))
                     : (IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__pwm_raw))));
}

void Vtb_pwm_core_file___024root___eval_act(Vtb_pwm_core_file___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___eval_act\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((5ULL & vlSelfRef.__VactTriggered[0U])) {
        Vtb_pwm_core_file___024root___act_comb__TOP__0(vlSelf);
    }
}

void Vtb_pwm_core_file___024root___nba_sequent__TOP__0(Vtb_pwm_core_file___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___nba_sequent__TOP__0\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    SData/*15:0*/ __Vdly__tb_pwm_core_file__DOT__i_dut__DOT__counter_q;
    __Vdly__tb_pwm_core_file__DOT__i_dut__DOT__counter_q = 0;
    // Body
    __Vdly__tb_pwm_core_file__DOT__i_dut__DOT__counter_q 
        = vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__counter_q;
    if (vlSelfRef.tb_pwm_core_file__DOT__rst_n) {
        if (vlSelfRef.tb_pwm_core_file__DOT__enable_i) {
            if ((0U == (IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_active_q))) {
                __Vdly__tb_pwm_core_file__DOT__i_dut__DOT__counter_q = 0U;
                vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_active_q 
                    = vlSelfRef.tb_pwm_core_file__DOT__period_cfg_i;
                vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__duty_active_q 
                    = vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__duty_clamped;
            } else if (vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_done_o) {
                __Vdly__tb_pwm_core_file__DOT__i_dut__DOT__counter_q = 0U;
                vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_active_q 
                    = vlSelfRef.tb_pwm_core_file__DOT__period_cfg_i;
                vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__duty_active_q 
                    = vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__duty_clamped;
            } else {
                __Vdly__tb_pwm_core_file__DOT__i_dut__DOT__counter_q 
                    = (0x0000ffffU & ((IData)(1U) + (IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__counter_q)));
            }
        } else {
            __Vdly__tb_pwm_core_file__DOT__i_dut__DOT__counter_q = 0U;
            vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_active_q 
                = vlSelfRef.tb_pwm_core_file__DOT__period_cfg_i;
            vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__duty_active_q 
                = vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__duty_clamped;
        }
    } else {
        __Vdly__tb_pwm_core_file__DOT__i_dut__DOT__counter_q = 0U;
        vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_active_q = 0U;
        vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__duty_active_q = 0U;
    }
    vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__counter_q 
        = __Vdly__tb_pwm_core_file__DOT__i_dut__DOT__counter_q;
}

void Vtb_pwm_core_file___024root___nba_comb__TOP__0(Vtb_pwm_core_file___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___nba_comb__TOP__0\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__duty_clamped 
        = ((0U == (IData)(vlSelfRef.tb_pwm_core_file__DOT__period_cfg_i))
            ? 0U : (((IData)(vlSelfRef.tb_pwm_core_file__DOT__duty_cfg_i) 
                     >= (IData)(vlSelfRef.tb_pwm_core_file__DOT__period_cfg_i))
                     ? (IData)(vlSelfRef.tb_pwm_core_file__DOT__period_cfg_i)
                     : (IData)(vlSelfRef.tb_pwm_core_file__DOT__duty_cfg_i)));
}

void Vtb_pwm_core_file___024root___nba_comb__TOP__1(Vtb_pwm_core_file___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___nba_comb__TOP__1\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_zero_o 
        = ((IData)(vlSelfRef.tb_pwm_core_file__DOT__enable_i) 
           & ((0U == (IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_active_q)) 
              & (0U == (IData)(vlSelfRef.tb_pwm_core_file__DOT__period_cfg_i))));
    vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0 
        = ((IData)(vlSelfRef.tb_pwm_core_file__DOT__enable_i) 
           & (0U != (IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_active_q)));
    vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_done_o 
        = ((IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0) 
           & ((IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__counter_q) 
              == (0x0000ffffU & ((IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_active_q) 
                                 - (IData)(1U)))));
    vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__pwm_raw 
        = ((IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0) 
           & ((IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__counter_q) 
              < (IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__duty_active_q)));
    vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__pwm_o 
        = (1U & ((~ ((~ (IData)(vlSelfRef.tb_pwm_core_file__DOT__enable_i)) 
                     | (0U == (IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_active_q)))) 
                 & ((IData)(vlSelfRef.tb_pwm_core_file__DOT__polarity_i)
                     ? (~ (IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__pwm_raw))
                     : (IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__pwm_raw))));
}

void Vtb_pwm_core_file___024root___eval_nba(Vtb_pwm_core_file___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___eval_nba\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtb_pwm_core_file___024root___nba_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[3U] = 1U;
    }
    if ((5ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtb_pwm_core_file___024root___nba_comb__TOP__0(vlSelf);
    }
    if ((7ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtb_pwm_core_file___024root___nba_comb__TOP__1(vlSelf);
    }
}

void Vtb_pwm_core_file___024root___timing_ready(Vtb_pwm_core_file___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___timing_ready\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_hdd35d4ed__0.ready("@(posedge tb_pwm_core_file.clk)");
    }
}

void Vtb_pwm_core_file___024root___timing_resume(Vtb_pwm_core_file___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___timing_resume\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VtrigSched_hdd35d4ed__0.moveToResumeQueue(
                                                          "@(posedge tb_pwm_core_file.clk)");
    vlSelfRef.__VtrigSched_hdd35d4ed__0.resume("@(posedge tb_pwm_core_file.clk)");
    if ((4ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vtb_pwm_core_file___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___trigger_orInto__act_vec_vec\n"); );
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
VL_ATTR_COLD void Vtb_pwm_core_file___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vtb_pwm_core_file___024root___eval_phase__act(Vtb_pwm_core_file___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___eval_phase__act\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb_pwm_core_file___024root___eval_triggers_vec__act(vlSelf);
    Vtb_pwm_core_file___024root___timing_ready(vlSelf);
    Vtb_pwm_core_file___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_pwm_core_file___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vtb_pwm_core_file___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vtb_pwm_core_file___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vtb_pwm_core_file___024root___timing_resume(vlSelf);
        Vtb_pwm_core_file___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtb_pwm_core_file___024root___eval_phase__inact(Vtb_pwm_core_file___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___eval_phase__inact\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("tb_pwm_core_file.sv", 3, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vtb_pwm_core_file___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtb_pwm_core_file___024root___eval_phase__nba(Vtb_pwm_core_file___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___eval_phase__nba\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtb_pwm_core_file___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtb_pwm_core_file___024root___eval_nba(vlSelf);
        Vtb_pwm_core_file___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtb_pwm_core_file___024root___eval(Vtb_pwm_core_file___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___eval\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtb_pwm_core_file___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("tb_pwm_core_file.sv", 3, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("tb_pwm_core_file.sv", 3, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vtb_pwm_core_file___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("tb_pwm_core_file.sv", 3, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vtb_pwm_core_file___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vtb_pwm_core_file___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vtb_pwm_core_file___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

void Vtb_pwm_core_file___024root____VbeforeTrig_hdd35d4ed__0(Vtb_pwm_core_file___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root____VbeforeTrig_hdd35d4ed__0\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)(((IData)(vlSelfRef.tb_pwm_core_file__DOT__clk) 
                                  & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_pwm_core_file__DOT__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_pwm_core_file__DOT__clk__0 
        = vlSelfRef.tb_pwm_core_file__DOT__clk;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_hdd35d4ed__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_hdd35d4ed__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_hdd35d4ed__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_hdd35d4ed__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

#ifdef VL_DEBUG
void Vtb_pwm_core_file___024root___eval_debug_assertions(Vtb_pwm_core_file___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___eval_debug_assertions\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
