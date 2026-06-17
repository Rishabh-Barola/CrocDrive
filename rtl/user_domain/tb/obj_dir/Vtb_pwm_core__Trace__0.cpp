// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_fst_c.h"
#include "Vtb_pwm_core__Syms.h"


void Vtb_pwm_core___024root__trace_chg_0_sub_0(Vtb_pwm_core___024root* vlSelf, VerilatedFst::Buffer* bufp);

void Vtb_pwm_core___024root__trace_chg_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root__trace_chg_0\n"); );
    // Body
    Vtb_pwm_core___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtb_pwm_core___024root*>(voidSelf);
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    Vtb_pwm_core___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vtb_pwm_core___024root__trace_chg_0_sub_0(Vtb_pwm_core___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root__trace_chg_0_sub_0\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 0);
    if (VL_UNLIKELY(((vlSelfRef.__Vm_traceActivity[1U] 
                      | vlSelfRef.__Vm_traceActivity[2U])))) {
        bufp->chgBit(oldp+0,(vlSelfRef.tb_pwm_core__DOT__rst_ni));
        bufp->chgBit(oldp+1,(vlSelfRef.tb_pwm_core__DOT__enable_i));
        bufp->chgBit(oldp+2,(vlSelfRef.tb_pwm_core__DOT__polarity_i));
        bufp->chgSData(oldp+3,(vlSelfRef.tb_pwm_core__DOT__period_cfg_i),16);
        bufp->chgSData(oldp+4,(vlSelfRef.tb_pwm_core__DOT__duty_cfg_i),16);
        bufp->chgIData(oldp+5,(vlSelfRef.tb_pwm_core__DOT__errors),32);
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[3U]))) {
        bufp->chgSData(oldp+6,(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q),16);
        bufp->chgSData(oldp+7,(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q),16);
        bufp->chgSData(oldp+8,(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__duty_active_q),16);
    }
    bufp->chgBit(oldp+9,(vlSelfRef.tb_pwm_core__DOT__clk_i));
    bufp->chgBit(oldp+10,((1U & ((~ ((~ (IData)(vlSelfRef.tb_pwm_core__DOT__enable_i)) 
                                     | (0U == (IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q)))) 
                                 & ((IData)(vlSelfRef.tb_pwm_core__DOT__polarity_i)
                                     ? (~ (IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__pwm_raw))
                                     : (IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__pwm_raw))))));
    bufp->chgBit(oldp+11,(((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0) 
                           & ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q) 
                              == (0x0000ffffU & ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q) 
                                                 - (IData)(1U)))))));
    bufp->chgBit(oldp+12,(((IData)(vlSelfRef.tb_pwm_core__DOT__enable_i) 
                           & ((0U == (IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q)) 
                              & (0U == (IData)(vlSelfRef.tb_pwm_core__DOT__period_cfg_i))))));
    bufp->chgSData(oldp+13,(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__duty_clamped),16);
    bufp->chgBit(oldp+14,(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__pwm_raw));
}

void Vtb_pwm_core___024root__trace_cleanup(void* voidSelf, VerilatedFst* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root__trace_cleanup\n"); );
    // Body
    Vtb_pwm_core___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtb_pwm_core___024root*>(voidSelf);
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[3U] = 0U;
}
