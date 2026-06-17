// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_fst_c.h"
#include "Vtb_pwm_core_file__Syms.h"


VL_ATTR_COLD void Vtb_pwm_core_file___024root__trace_init_sub__TOP__0(Vtb_pwm_core_file___024root* vlSelf, VerilatedFst* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root__trace_init_sub__TOP__0\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const int c = vlSymsp->__Vm_baseCode;
    tracep->pushPrefix("tb_pwm_core_file", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declDouble(c+23,0,"T_CLK_HI",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+23,0,"T_CLK_LO",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+25,0,"T_CLK",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+27,0,"T_APPL_DEL",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+27,0,"T_ACQ_DEL",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declArray(c+29,0,"STIMULI_FILE",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 167,0);
    tracep->declArray(c+35,0,"RESPONSE_FILE",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 247,0);
    tracep->declBus(c+43,0,"Width",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBit(c+11,0,"clk",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+0,0,"rst_n",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+1,0,"eoc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+2,0,"enable_i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+3,0,"polarity_i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+4,0,"period_cfg_i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+5,0,"duty_cfg_i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+12,0,"pwm_o",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+8,0,"counter_o",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+9,0,"period_active_o",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+10,0,"duty_active_o",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+13,0,"period_done_o",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+14,0,"period_zero_o",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+6,0,"rsp_idx",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+7,0,"errors",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+15,0,"load_stimuli__Vstatic__file",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declQuad(c+16,0,"load_stimuli__Vstatic__temp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+18,0,"load_exp_response__Vstatic__file",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declQuad(c+19,0,"load_exp_response__Vstatic__temp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->pushPrefix("i_dut", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+43,0,"Width",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBit(c+11,0,"clk_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+0,0,"rst_ni",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+2,0,"enable_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+3,0,"polarity_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+4,0,"period_cfg_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+5,0,"duty_cfg_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+12,0,"pwm_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+8,0,"counter_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+9,0,"period_active_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+10,0,"duty_active_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+13,0,"period_done_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+14,0,"period_zero_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+8,0,"counter_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+9,0,"period_active_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+10,0,"duty_active_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+21,0,"duty_clamped",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+22,0,"pwm_raw",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->popPrefix();
}

VL_ATTR_COLD void Vtb_pwm_core_file___024root__trace_init_top(Vtb_pwm_core_file___024root* vlSelf, VerilatedFst* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root__trace_init_top\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtb_pwm_core_file___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vtb_pwm_core_file___024root__trace_const_0(void* voidSelf, VerilatedFst::Buffer* bufp);
VL_ATTR_COLD void Vtb_pwm_core_file___024root__trace_full_0(void* voidSelf, VerilatedFst::Buffer* bufp);
void Vtb_pwm_core_file___024root__trace_chg_0(void* voidSelf, VerilatedFst::Buffer* bufp);
void Vtb_pwm_core_file___024root__trace_cleanup(void* voidSelf, VerilatedFst* /*unused*/);

VL_ATTR_COLD void Vtb_pwm_core_file___024root__trace_register(Vtb_pwm_core_file___024root* vlSelf, VerilatedFst* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root__trace_register\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    tracep->addConstCb(&Vtb_pwm_core_file___024root__trace_const_0, 0, vlSelf);
    tracep->addFullCb(&Vtb_pwm_core_file___024root__trace_full_0, 0, vlSelf);
    tracep->addChgCb(&Vtb_pwm_core_file___024root__trace_chg_0, 0, vlSelf);
    tracep->addCleanupCb(&Vtb_pwm_core_file___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vtb_pwm_core_file___024root__trace_const_0_sub_0(Vtb_pwm_core_file___024root* vlSelf, VerilatedFst::Buffer* bufp);

VL_ATTR_COLD void Vtb_pwm_core_file___024root__trace_const_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root__trace_const_0\n"); );
    // Body
    Vtb_pwm_core_file___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtb_pwm_core_file___024root*>(voidSelf);
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vtb_pwm_core_file___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

extern const VlWide<8>/*255:0*/ Vtb_pwm_core_file__ConstPool__CONST_hb0160424_0;

VL_ATTR_COLD void Vtb_pwm_core_file___024root__trace_const_0_sub_0(Vtb_pwm_core_file___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root__trace_const_0_sub_0\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlWide<6>/*191:0*/ __Vtemp_1;
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullDouble(oldp+23,(5.0));
    bufp->fullDouble(oldp+25,(10.0));
    bufp->fullDouble(oldp+27,(1.0));
    __Vtemp_1[0U] = 0x2e747874U;
    __Vtemp_1[1U] = 0x6d756c69U;
    __Vtemp_1[2U] = 0x2f737469U;
    __Vtemp_1[3U] = 0x6d756c69U;
    __Vtemp_1[4U] = 0x2f737469U;
    __Vtemp_1[5U] = 0x0000002eU;
    bufp->fullWData(oldp+29,(__Vtemp_1),168);
    bufp->fullWData(oldp+35,(Vtb_pwm_core_file__ConstPool__CONST_hb0160424_0),248);
    bufp->fullIData(oldp+43,(0x00000010U),32);
}

VL_ATTR_COLD void Vtb_pwm_core_file___024root__trace_full_0_sub_0(Vtb_pwm_core_file___024root* vlSelf, VerilatedFst::Buffer* bufp);

VL_ATTR_COLD void Vtb_pwm_core_file___024root__trace_full_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root__trace_full_0\n"); );
    // Body
    Vtb_pwm_core_file___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtb_pwm_core_file___024root*>(voidSelf);
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vtb_pwm_core_file___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtb_pwm_core_file___024root__trace_full_0_sub_0(Vtb_pwm_core_file___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_pwm_core_file___024root__trace_full_0_sub_0\n"); );
    Vtb_pwm_core_file__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullBit(oldp+0,(vlSelfRef.tb_pwm_core_file__DOT__rst_n));
    bufp->fullBit(oldp+1,(vlSelfRef.tb_pwm_core_file__DOT__eoc));
    bufp->fullBit(oldp+2,(vlSelfRef.tb_pwm_core_file__DOT__enable_i));
    bufp->fullBit(oldp+3,(vlSelfRef.tb_pwm_core_file__DOT__polarity_i));
    bufp->fullSData(oldp+4,(vlSelfRef.tb_pwm_core_file__DOT__period_cfg_i),16);
    bufp->fullSData(oldp+5,(vlSelfRef.tb_pwm_core_file__DOT__duty_cfg_i),16);
    bufp->fullIData(oldp+6,(vlSelfRef.tb_pwm_core_file__DOT__rsp_idx),32);
    bufp->fullIData(oldp+7,(vlSelfRef.tb_pwm_core_file__DOT__errors),32);
    bufp->fullSData(oldp+8,(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__counter_q),16);
    bufp->fullSData(oldp+9,(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_active_q),16);
    bufp->fullSData(oldp+10,(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__duty_active_q),16);
    bufp->fullBit(oldp+11,(vlSelfRef.tb_pwm_core_file__DOT__clk));
    bufp->fullBit(oldp+12,((1U & ((~ ((~ (IData)(vlSelfRef.tb_pwm_core_file__DOT__enable_i)) 
                                      | (0U == (IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_active_q)))) 
                                  & ((IData)(vlSelfRef.tb_pwm_core_file__DOT__polarity_i)
                                      ? (~ (IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__pwm_raw))
                                      : (IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__pwm_raw))))));
    bufp->fullBit(oldp+13,(((IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT____VdfgRegularize_h5d5bfbd3_0_0) 
                            & ((IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__counter_q) 
                               == (0x0000ffffU & ((IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_active_q) 
                                                  - (IData)(1U)))))));
    bufp->fullBit(oldp+14,(((IData)(vlSelfRef.tb_pwm_core_file__DOT__enable_i) 
                            & ((0U == (IData)(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__period_active_q)) 
                               & (0U == (IData)(vlSelfRef.tb_pwm_core_file__DOT__period_cfg_i))))));
    bufp->fullIData(oldp+15,(vlSelfRef.tb_pwm_core_file__DOT__load_stimuli__Vstatic__file),32);
    bufp->fullQData(oldp+16,(vlSelfRef.tb_pwm_core_file__DOT__load_stimuli__Vstatic__temp),64);
    bufp->fullIData(oldp+18,(vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__file),32);
    bufp->fullQData(oldp+19,(vlSelfRef.tb_pwm_core_file__DOT__load_exp_response__Vstatic__temp),64);
    bufp->fullSData(oldp+21,(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__duty_clamped),16);
    bufp->fullBit(oldp+22,(vlSelfRef.tb_pwm_core_file__DOT__i_dut__DOT__pwm_raw));
}
