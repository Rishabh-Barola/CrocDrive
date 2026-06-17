// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_fst_c.h"
#include "Vtb_pwm_core__Syms.h"


VL_ATTR_COLD void Vtb_pwm_core___024root__trace_init_sub__TOP__0(Vtb_pwm_core___024root* vlSelf, VerilatedFst* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root__trace_init_sub__TOP__0\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const int c = vlSymsp->__Vm_baseCode;
    tracep->pushPrefix("tb_pwm_core", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+15,0,"Width",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declQuad(c+16,0,"Tclk",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::TIME, false,-1, 63,0);
    tracep->declBit(c+9,0,"clk_i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+0,0,"rst_ni",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+1,0,"enable_i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+2,0,"polarity_i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+3,0,"period_cfg_i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+4,0,"duty_cfg_i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+10,0,"pwm_o",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+6,0,"counter_o",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+7,0,"period_active_o",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+8,0,"duty_active_o",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+11,0,"period_done_o",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+12,0,"period_zero_o",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+5,0,"errors",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->pushPrefix("i_dut", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+15,0,"Width",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBit(c+9,0,"clk_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+0,0,"rst_ni",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+1,0,"enable_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+2,0,"polarity_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+3,0,"period_cfg_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+4,0,"duty_cfg_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+10,0,"pwm_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+6,0,"counter_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+7,0,"period_active_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+8,0,"duty_active_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+11,0,"period_done_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+12,0,"period_zero_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+6,0,"counter_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+7,0,"period_active_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+8,0,"duty_active_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+13,0,"duty_clamped",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+14,0,"pwm_raw",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->popPrefix();
}

VL_ATTR_COLD void Vtb_pwm_core___024root__trace_init_top(Vtb_pwm_core___024root* vlSelf, VerilatedFst* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root__trace_init_top\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtb_pwm_core___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vtb_pwm_core___024root__trace_const_0(void* voidSelf, VerilatedFst::Buffer* bufp);
VL_ATTR_COLD void Vtb_pwm_core___024root__trace_full_0(void* voidSelf, VerilatedFst::Buffer* bufp);
void Vtb_pwm_core___024root__trace_chg_0(void* voidSelf, VerilatedFst::Buffer* bufp);
void Vtb_pwm_core___024root__trace_cleanup(void* voidSelf, VerilatedFst* /*unused*/);

VL_ATTR_COLD void Vtb_pwm_core___024root__trace_register(Vtb_pwm_core___024root* vlSelf, VerilatedFst* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root__trace_register\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    tracep->addConstCb(&Vtb_pwm_core___024root__trace_const_0, 0, vlSelf);
    tracep->addFullCb(&Vtb_pwm_core___024root__trace_full_0, 0, vlSelf);
    tracep->addChgCb(&Vtb_pwm_core___024root__trace_chg_0, 0, vlSelf);
    tracep->addCleanupCb(&Vtb_pwm_core___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vtb_pwm_core___024root__trace_const_0_sub_0(Vtb_pwm_core___024root* vlSelf, VerilatedFst::Buffer* bufp);

VL_ATTR_COLD void Vtb_pwm_core___024root__trace_const_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root__trace_const_0\n"); );
    // Body
    Vtb_pwm_core___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtb_pwm_core___024root*>(voidSelf);
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vtb_pwm_core___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtb_pwm_core___024root__trace_const_0_sub_0(Vtb_pwm_core___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root__trace_const_0_sub_0\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullIData(oldp+15,(0x00000010U),32);
    bufp->fullQData(oldp+16,(0x0000000000002710ULL),64);
}

VL_ATTR_COLD void Vtb_pwm_core___024root__trace_full_0_sub_0(Vtb_pwm_core___024root* vlSelf, VerilatedFst::Buffer* bufp);

VL_ATTR_COLD void Vtb_pwm_core___024root__trace_full_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root__trace_full_0\n"); );
    // Body
    Vtb_pwm_core___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtb_pwm_core___024root*>(voidSelf);
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vtb_pwm_core___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtb_pwm_core___024root__trace_full_0_sub_0(Vtb_pwm_core___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core___024root__trace_full_0_sub_0\n"); );
    Vtb_pwm_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullBit(oldp+0,(vlSelfRef.tb_pwm_core__DOT__rst_ni));
    bufp->fullBit(oldp+1,(vlSelfRef.tb_pwm_core__DOT__enable_i));
    bufp->fullBit(oldp+2,(vlSelfRef.tb_pwm_core__DOT__polarity_i));
    bufp->fullSData(oldp+3,(vlSelfRef.tb_pwm_core__DOT__period_cfg_i),16);
    bufp->fullSData(oldp+4,(vlSelfRef.tb_pwm_core__DOT__duty_cfg_i),16);
    bufp->fullIData(oldp+5,(vlSelfRef.tb_pwm_core__DOT__errors),32);
    bufp->fullSData(oldp+6,(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q),16);
    bufp->fullSData(oldp+7,(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q),16);
    bufp->fullSData(oldp+8,(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__duty_active_q),16);
    bufp->fullBit(oldp+9,(vlSelfRef.tb_pwm_core__DOT__clk_i));
    bufp->fullBit(oldp+10,((1U & ((~ ((~ (IData)(vlSelfRef.tb_pwm_core__DOT__enable_i)) 
                                      | (0U == (IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q)))) 
                                  & ((IData)(vlSelfRef.tb_pwm_core__DOT__polarity_i)
                                      ? (~ (IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__pwm_raw))
                                      : (IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__pwm_raw))))));
    bufp->fullBit(oldp+11,(((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0) 
                            & ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__counter_q) 
                               == (0x0000ffffU & ((IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q) 
                                                  - (IData)(1U)))))));
    bufp->fullBit(oldp+12,(((IData)(vlSelfRef.tb_pwm_core__DOT__enable_i) 
                            & ((0U == (IData)(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__period_active_q)) 
                               & (0U == (IData)(vlSelfRef.tb_pwm_core__DOT__period_cfg_i))))));
    bufp->fullSData(oldp+13,(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__duty_clamped),16);
    bufp->fullBit(oldp+14,(vlSelfRef.tb_pwm_core__DOT__i_dut__DOT__pwm_raw));
}
