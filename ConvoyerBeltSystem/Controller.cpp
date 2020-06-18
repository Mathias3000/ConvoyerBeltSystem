#include "Controller.h"

void Controller::oneStep()
{
	static boolean_T OverrunFlag = false;

	/* Disable interrupts here */

	/* Check for overrun */
	if (OverrunFlag) {
		rtmSetErrorStatus(Discrete_M, "Overrun");
		return;
	}

	OverrunFlag = true;

	/* Save FPU context here (if necessary) */
	/* Re-enable timer or interrupt here */
	/* Set model inputs here */

	/* Step the model */
	Discrete_step();

	/* Get model outputs here */

	/* Indicate task complete */
	OverrunFlag = false;

	/* Disable interrupts here */
	/* Restore FPU context here (if necessary) */
	/* Enable interrupts here */
}
