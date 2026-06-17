// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_pwm_core.h for the primary calling header

#include "Vtb_pwm_core__pch.h"

void Vtb_pwm_core___024root___timing_ready(Vtb_pwm_core___024root* vlSelf);

VL_ATTR_COLD void Vtb_pwm_core___024root___eval_static(Vtb_pwm_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___eval_static\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__tb_pwm_core__DOT__clk_i__0 
        = vlSelfRef.tb_pwm_core__DOT__clk_i;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_pwm_core__DOT__rst_ni__0 
        = vlSelfRef.tb_pwm_core__DOT__rst_ni;
    Vtb_pwm_core___024root___timing_ready(vlSelf);
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((IData)(1U) + vlSelfRef.__Vi);
    } while ((0U >= vlSelfRef.__Vi));
}

VL_ATTR_COLD void Vtb_pwm_core___024root___eval_final(Vtb_pwm_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___eval_final\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_pwm_core___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtb_pwm_core___024root___eval_phase__stl(Vtb_pwm_core___024root* vlSelf);

VL_ATTR_COLD void Vtb_pwm_core___024root___eval_settle(Vtb_pwm_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___eval_settle\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtb_pwm_core___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("tb_pwm_core.sv", 1, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vtb_pwm_core___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vtb_pwm_core___024root___eval_triggers_vec__stl(Vtb_pwm_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___eval_triggers_vec__stl\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vtb_pwm_core___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_pwm_core___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_pwm_core___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtb_pwm_core___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___trigger_anySet__stl\n"); );
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

void Vtb_pwm_core___024root___act_comb__TOP__0(Vtb_pwm_core___024root* vlSelf);

VL_ATTR_COLD void Vtb_pwm_core___024root___eval_stl(Vtb_pwm_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___eval_stl\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vtb_pwm_core___024root___act_comb__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vtb_pwm_core___024root___eval_phase__stl(Vtb_pwm_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___eval_phase__stl\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtb_pwm_core___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_pwm_core___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vtb_pwm_core___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vtb_pwm_core___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vtb_pwm_core___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_pwm_core___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_pwm_core___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge tb_pwm_core.clk_i)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge tb_pwm_core.rst_ni)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_pwm_core___024root___ctor_var_reset(Vtb_pwm_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root___ctor_var_reset\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_pwm_core__DOT__clk_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15207444547388630269ull);
    vlSelf->tb_pwm_core__DOT__rst_ni = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11177148983819551613ull);
    vlSelf->tb_pwm_core__DOT__enable_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5000536489879233749ull);
    vlSelf->tb_pwm_core__DOT__polarity_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16431047231829664893ull);
    vlSelf->tb_pwm_core__DOT__period_cfg_i = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 4919949134578684864ull);
    vlSelf->tb_pwm_core__DOT__duty_cfg_i = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 11242451191251236827ull);
    vlSelf->tb_pwm_core__DOT__errors = 0;
    vlSelf->tb_pwm_core__DOT__i_dut__DOT__pwm_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11767052802568651063ull);
    vlSelf->tb_pwm_core__DOT__i_dut__DOT__period_done_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11013121028729751896ull);
    vlSelf->tb_pwm_core__DOT__i_dut__DOT__period_zero_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8455329421147797310ull);
    vlSelf->tb_pwm_core__DOT__i_dut__DOT__counter_q = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 7118290228781148559ull);
    vlSelf->tb_pwm_core__DOT__i_dut__DOT__period_active_q = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 8936493525656558044ull);
    vlSelf->tb_pwm_core__DOT__i_dut__DOT__duty_active_q = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 1338299833828674808ull);
    vlSelf->tb_pwm_core__DOT__i_dut__DOT__duty_clamped = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 16562713780163498124ull);
    vlSelf->tb_pwm_core__DOT__i_dut__DOT__pwm_raw = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16431283500115714530ull);
    vlSelf->tb_pwm_core__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__tb_pwm_core__DOT__clk_i__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_pwm_core__DOT__rst_ni__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
