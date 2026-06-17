// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_pwm_core_file.h for the primary calling header

#include "Vtb_pwm_core_file__pch.h"

VL_ATTR_COLD void Vtb_pwm_core_file___024root___eval_static__TOP(Vtb_pwm_core_file___024root* vlSelf);
void Vtb_pwm_core_file___024root___timing_ready(Vtb_pwm_core_file___024root* vlSelf);

VL_ATTR_COLD void Vtb_pwm_core_file___024root___eval_static(Vtb_pwm_core_file___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___eval_static\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtb_pwm_core_file___024root___eval_static__TOP(vlSelf);
    vlSelfRef.__Vtrigprevexpr___TOP__tb_pwm_core_file__DOT__clk__0 
        = vlSelfRef.tb_pwm_core_file__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_pwm_core_file__DOT__rst_n__0 
        = vlSelfRef.tb_pwm_core_file__DOT__rst_n;
    Vtb_pwm_core_file___024root___timing_ready(vlSelf);
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((IData)(1U) + vlSelfRef.__Vi);
    } while ((0U >= vlSelfRef.__Vi));
}

VL_ATTR_COLD void Vtb_pwm_core_file___024root___eval_static__TOP(Vtb_pwm_core_file___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___eval_static__TOP\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_pwm_core_file__DOT__load_stimuli__Vstatic__file = 0U;
    vlSelfRef.tb_pwm_core_file__DOT__load_stimuli__Vstatic__line = ""s;
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_pwm_core_file__DOT__load_stimuli__Vstatic__temp = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 16703181939221724939ull);
    vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__file = 0U;
    vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__line = ""s;
    vlSelf->tb_pwm_core_file__DOT__load_exp_response__Vstatic__temp = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 11146477377016462751ull);
}

VL_ATTR_COLD void Vtb_pwm_core_file___024root___eval_final(Vtb_pwm_core_file___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___eval_final\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_pwm_core_file___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtb_pwm_core_file___024root___eval_phase__stl(Vtb_pwm_core_file___024root* vlSelf);

VL_ATTR_COLD void Vtb_pwm_core_file___024root___eval_settle(Vtb_pwm_core_file___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___eval_settle\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtb_pwm_core_file___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("tb_pwm_core_file.sv", 3, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vtb_pwm_core_file___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vtb_pwm_core_file___024root___eval_triggers_vec__stl(Vtb_pwm_core_file___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___eval_triggers_vec__stl\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vtb_pwm_core_file___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_pwm_core_file___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_pwm_core_file___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtb_pwm_core_file___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___trigger_anySet__stl\n"); );
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

void Vtb_pwm_core_file___024root___act_comb__TOP__0(Vtb_pwm_core_file___024root* vlSelf);

VL_ATTR_COLD void Vtb_pwm_core_file___024root___eval_stl(Vtb_pwm_core_file___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___eval_stl\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vtb_pwm_core_file___024root___act_comb__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vtb_pwm_core_file___024root___eval_phase__stl(Vtb_pwm_core_file___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___eval_phase__stl\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtb_pwm_core_file___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_pwm_core_file___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vtb_pwm_core_file___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vtb_pwm_core_file___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vtb_pwm_core_file___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_pwm_core_file___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_pwm_core_file___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge tb_pwm_core_file.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge tb_pwm_core_file.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_pwm_core_file___024root___ctor_var_reset(Vtb_pwm_core_file___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root___ctor_var_reset\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_pwm_core_file__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11892952812511321296ull);
    vlSelf->tb_pwm_core_file__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1271818906897597092ull);
    vlSelf->tb_pwm_core_file__DOT__eoc = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4120583969264910644ull);
    vlSelf->tb_pwm_core_file__DOT__stimuli.atDefault() = VL_SCOPED_RAND_RESET_Q(49, __VscopeHash, 11441420249540545106ull);
    vlSelf->tb_pwm_core_file__DOT__exp_response.atDefault() = VL_SCOPED_RAND_RESET_Q(51, __VscopeHash, 16371998636366253926ull);
    vlSelf->tb_pwm_core_file__DOT__enable_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9812565232659553534ull);
    vlSelf->tb_pwm_core_file__DOT__polarity_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2344666839551410796ull);
    vlSelf->tb_pwm_core_file__DOT__period_cfg_i = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 13929904665701245602ull);
    vlSelf->tb_pwm_core_file__DOT__duty_cfg_i = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 16942172638866926801ull);
    vlSelf->tb_pwm_core_file__DOT__rsp_idx = 0;
    vlSelf->tb_pwm_core_file__DOT__errors = 0;
    vlSelf->tb_pwm_core_file__DOT__unnamedblk1__DOT__unnamedblk2__DOT__j = 0;
    vlSelf->tb_pwm_core_file__DOT__i_dut__DOT__pwm_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9605647354379388139ull);
    vlSelf->tb_pwm_core_file__DOT__i_dut__DOT__period_done_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16243470183822101161ull);
    vlSelf->tb_pwm_core_file__DOT__i_dut__DOT__period_zero_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6292087881870904524ull);
    vlSelf->tb_pwm_core_file__DOT__i_dut__DOT__counter_q = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 10072998629006910051ull);
    vlSelf->tb_pwm_core_file__DOT__i_dut__DOT__period_active_q = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 14687835207421867647ull);
    vlSelf->tb_pwm_core_file__DOT__i_dut__DOT__duty_active_q = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 13381429382611437769ull);
    vlSelf->tb_pwm_core_file__DOT__i_dut__DOT__duty_clamped = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 7018654144998875962ull);
    vlSelf->tb_pwm_core_file__DOT__i_dut__DOT__pwm_raw = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7464882031694713185ull);
    vlSelf->tb_pwm_core_file__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__tb_pwm_core_file__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_pwm_core_file__DOT__rst_n__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
