/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Discrete.c
 *
 * Code generated for Simulink model 'Discrete'.
 *
 * Model version                  : 1.30
 * Simulink Coder version         : 9.1 (R2019a) 23-Nov-2018
 * C/C++ source code generated on : Mon May  4 18:01:22 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Discrete.h"
#include "Discrete_private.h"
#include <stdio.h>
/* Block states (default storage) */
DW_Discrete_T Discrete_DW;

/* External inputs (root inport signals with default storage) */
ExtU_Discrete_T Discrete_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Discrete_T Discrete_Y;

/* Real-time model */
RT_MODEL_Discrete_T Discrete_M_;
RT_MODEL_Discrete_T *const Discrete_M = &Discrete_M_;

/* Model step function */
void Discrete_step(void)
{
  real_T rtb_Sum;

  /* Sum: '<S40>/Sum' incorporates:
   *  DiscreteIntegrator: '<S31>/Integrator'
   *  Gain: '<S36>/Proportional Gain'
   *  Inport: '<Root>/u'
   */
  rtb_Sum = 0.0008 * Discrete_U.u + Discrete_DW.Integrator_DSTATE;

  /* Saturate: '<S38>/Saturation' */
  if (rtb_Sum > 7.0) {
    Discrete_Y.y = 7.0;
  } else if (rtb_Sum < -7.0) {
    Discrete_Y.y = -7.0;
  } else {
    Discrete_Y.y = rtb_Sum;
  }

  /* End of Saturate: '<S38>/Saturation' */

  /* Update for DiscreteIntegrator: '<S31>/Integrator' incorporates:
   *  Gain: '<S24>/Kb'
   *  Gain: '<S28>/Integral Gain'
   *  Inport: '<Root>/u'
   *  Sum: '<S24>/SumI2'
   *  Sum: '<S24>/SumI4'
   */
  Discrete_DW.Integrator_DSTATE += ((Discrete_Y.y - rtb_Sum) * 0.04 + 0.04 *
    Discrete_U.u) * 0.02;
}

/* Model initialize function */
void Discrete_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Discrete_M, (NULL));

  /* states (dwork) */
  Discrete_DW.Integrator_DSTATE = 0.0;

  /* external inputs */
  Discrete_U.u = 0.0;

  /* external outputs */
  Discrete_Y.y = 0.0;
}

/* Model terminate function */
void Discrete_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
