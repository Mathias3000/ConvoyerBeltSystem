/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Discrete.h
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

#ifndef RTW_HEADER_Discrete_h_
#define RTW_HEADER_Discrete_h_

#ifndef Discrete_COMMON_INCLUDES_
# define Discrete_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Discrete_COMMON_INCLUDES_ */

#include "Discrete_types.h"
#include "defines.h"
/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S31>/Integrator' */
} DW_Discrete_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T u;                            /* '<Root>/u' */
} ExtU_Discrete_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T y;                            /* '<Root>/y' */
} ExtY_Discrete_T;

/* Real-time Model Data Structure */
struct tag_RTM_Discrete_T {
  const char_T * volatile errorStatus;
};

/* Block states (default storage) */
extern DW_Discrete_T Discrete_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_Discrete_T Discrete_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_Discrete_T Discrete_Y;

/* Model entry point functions */
extern void Discrete_initialize(void);
extern void Discrete_step(void);
extern void Discrete_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Discrete_T *const Discrete_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('GesamtmodellSimple/Discrete PI Speed')    - opens subsystem GesamtmodellSimple/Discrete PI Speed
 * hilite_system('GesamtmodellSimple/Discrete PI Speed/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'GesamtmodellSimple'
 * '<S1>'   : 'GesamtmodellSimple/Discrete PI Speed'
 * '<S2>'   : 'GesamtmodellSimple/Discrete PI Speed/Anti-windup'
 * '<S3>'   : 'GesamtmodellSimple/Discrete PI Speed/D Gain'
 * '<S4>'   : 'GesamtmodellSimple/Discrete PI Speed/Filter'
 * '<S5>'   : 'GesamtmodellSimple/Discrete PI Speed/Filter ICs'
 * '<S6>'   : 'GesamtmodellSimple/Discrete PI Speed/I Gain'
 * '<S7>'   : 'GesamtmodellSimple/Discrete PI Speed/Ideal P Gain'
 * '<S8>'   : 'GesamtmodellSimple/Discrete PI Speed/Ideal P Gain Fdbk'
 * '<S9>'   : 'GesamtmodellSimple/Discrete PI Speed/Integrator'
 * '<S10>'  : 'GesamtmodellSimple/Discrete PI Speed/Integrator ICs'
 * '<S11>'  : 'GesamtmodellSimple/Discrete PI Speed/N Copy'
 * '<S12>'  : 'GesamtmodellSimple/Discrete PI Speed/N Gain'
 * '<S13>'  : 'GesamtmodellSimple/Discrete PI Speed/P Copy'
 * '<S14>'  : 'GesamtmodellSimple/Discrete PI Speed/Parallel P Gain'
 * '<S15>'  : 'GesamtmodellSimple/Discrete PI Speed/Reset Signal'
 * '<S16>'  : 'GesamtmodellSimple/Discrete PI Speed/Saturation'
 * '<S17>'  : 'GesamtmodellSimple/Discrete PI Speed/Saturation Fdbk'
 * '<S18>'  : 'GesamtmodellSimple/Discrete PI Speed/Sum'
 * '<S19>'  : 'GesamtmodellSimple/Discrete PI Speed/Sum Fdbk'
 * '<S20>'  : 'GesamtmodellSimple/Discrete PI Speed/Tracking Mode'
 * '<S21>'  : 'GesamtmodellSimple/Discrete PI Speed/Tracking Mode Sum'
 * '<S22>'  : 'GesamtmodellSimple/Discrete PI Speed/postSat Signal'
 * '<S23>'  : 'GesamtmodellSimple/Discrete PI Speed/preSat Signal'
 * '<S24>'  : 'GesamtmodellSimple/Discrete PI Speed/Anti-windup/Back Calculation'
 * '<S25>'  : 'GesamtmodellSimple/Discrete PI Speed/D Gain/Disabled'
 * '<S26>'  : 'GesamtmodellSimple/Discrete PI Speed/Filter/Disabled'
 * '<S27>'  : 'GesamtmodellSimple/Discrete PI Speed/Filter ICs/Disabled'
 * '<S28>'  : 'GesamtmodellSimple/Discrete PI Speed/I Gain/Internal Parameters'
 * '<S29>'  : 'GesamtmodellSimple/Discrete PI Speed/Ideal P Gain/Passthrough'
 * '<S30>'  : 'GesamtmodellSimple/Discrete PI Speed/Ideal P Gain Fdbk/Disabled'
 * '<S31>'  : 'GesamtmodellSimple/Discrete PI Speed/Integrator/Discrete'
 * '<S32>'  : 'GesamtmodellSimple/Discrete PI Speed/Integrator ICs/Internal IC'
 * '<S33>'  : 'GesamtmodellSimple/Discrete PI Speed/N Copy/Disabled wSignal Specification'
 * '<S34>'  : 'GesamtmodellSimple/Discrete PI Speed/N Gain/Disabled'
 * '<S35>'  : 'GesamtmodellSimple/Discrete PI Speed/P Copy/Disabled'
 * '<S36>'  : 'GesamtmodellSimple/Discrete PI Speed/Parallel P Gain/Internal Parameters'
 * '<S37>'  : 'GesamtmodellSimple/Discrete PI Speed/Reset Signal/Disabled'
 * '<S38>'  : 'GesamtmodellSimple/Discrete PI Speed/Saturation/Enabled'
 * '<S39>'  : 'GesamtmodellSimple/Discrete PI Speed/Saturation Fdbk/Disabled'
 * '<S40>'  : 'GesamtmodellSimple/Discrete PI Speed/Sum/Sum_PI'
 * '<S41>'  : 'GesamtmodellSimple/Discrete PI Speed/Sum Fdbk/Disabled'
 * '<S42>'  : 'GesamtmodellSimple/Discrete PI Speed/Tracking Mode/Disabled'
 * '<S43>'  : 'GesamtmodellSimple/Discrete PI Speed/Tracking Mode Sum/Passthrough'
 * '<S44>'  : 'GesamtmodellSimple/Discrete PI Speed/postSat Signal/Forward_Path'
 * '<S45>'  : 'GesamtmodellSimple/Discrete PI Speed/preSat Signal/Forward_Path'
 */
#endif                                 /* RTW_HEADER_Discrete_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
