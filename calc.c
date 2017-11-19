/*******************************************************************************
 * NAME:	    calc.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Do some calculations!
 *
 * CREATED:	    11/06/2017
 *
 * LAST EDITED:	    11/18/2017
 ***/

/*******************************************************************************
 * INCLUDES
 ***/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "calc.h"
#include "error.h"

/*******************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***/

static float get_vf(float i_out);

/*******************************************************************************
 * API FUNCTIONS
 ***/

/*******************************************************************************
 * FUNCTION:	    calc_std
 *
 * DESCRIPTION:	    This function uses the values in `params' to calculate the
 *		    values of the components that support the MC34063, and place
 *		    their values into `components.' This function assumes
 *		    use of the step-down topography.
 *
 * ARGUMENTS:	    params: (struct mc34063_params *) -- the i/o parameters.
 *		    components: (struct mc34063_components *) -- component
 *			values.
 *
 * RETURN:	    int -- 0 on success, non-zero otherwise.
 *
 * NOTES:	    none.
 ***/
int calc_std(struct mc34063_params * params,
	     struct mc34063_components * components)
{
  /* Calculate diode forward voltage drop */
  float v_f = get_vf(params->i_out);

  /* Calculate t_off */
  float t_off =
    (1 / params->f_s)
    / (
       ((params->v_out + v_f)
	/ (params->v_in - v_sat - params->v_out))
       + 1);

  /* Calculate value of switching cap */
  components->c_t = 4.0e-5 * ((1 / params->f_s) - t_off);

  /* Calculate sensing resistor */
  components->r_sc = 0.3 / (2 * params->i_out);

  /* Calculate minimum value of Darlington inductor */
  components->l_min = ((params->v_in - v_sat - params->v_out)
		       / (2 * params->i_out)) * ((1 / params->f_s) - t_off);

  /* Calculate output capacitor value */
  components->c_o = ((2 * params->i_out * (1 / params->f_s))
		     / (8 * params->v_rip));

  /* Calculate R2/R1 */
  float r_rat = (fabsf(params->v_out) / 1.25) - 1;

  /* Calculate R2, assuming R1 = 10k */
  /* TODO: Table of values to approximate components */
  components->r_1 = 1.2e3;
  components->r_2 = r_rat * components->r_1;
  return 0;
}

/*******************************************************************************
 * FUNCTION:	    calc_lmin
 *
 * DESCRIPTION:	    This function uses the values in `params' and the value of
 *		    `components->l_min' as a basepoint. It calculates the rest
 *		    of the components and finds a circuit which has approximal
 *		    input/output characteristics.
 *
 * ARGUMENTS:	    params: (struct mc34063_params *) -- the i/o parameters.
 *		    components: (struct mc34063_components *) -- component
 *			values.
 *
 * RETURN:	    int -- 0 on success, non-zero otherwise.
 *
 * NOTES:	    none.
 ***/
int calc_lmin(struct mc34063_params * params,
	      struct mc34063_components * components)
{
  return -1; /* Not yet implemented */
}

/*******************************************************************************
 * MAIN
 ***/

int main(int argc, char * argv[])
{
  struct mc34063_params params = (struct mc34063_params) {
    .v_in   = 32.0F,
    .v_out  = 12.1F,
    .v_rip  = 0.1F,
    .f_s    = 1.5e3,
    .i_out  = 0.33
  };

  struct mc34063_components components;
  if(calc_std(&params, &components))
    StopIf(1, 1, "Error: calc_std returned an error code.\n");

  /* Print the results */
  printf("L_min\t= %8g\n"
	 "C_t\t= %8g\n"
	 "C_o\t= %8g\n"
	 "R_sc\t= %8g\n"
	 "R_2\t= %8g\n"
	 "R_1\t= %8g\n",

	 components.c_t,
	 components.r_sc,
	 components.l_min,
	 components.c_o,
	 components.r_2,
	 components.r_1);
}

/*******************************************************************************
 * STATIC FUNCTIONS
 ***/

/*******************************************************************************
 * FUNCTION:	    get_vf
 *
 * DESCRIPTION:	    Return the corresponding value of the Schottky diode's
 *		    forward voltage drop at the corresponding instantaneous
 *		    forward current value.
 *
 * ARGUMENTS:	    i_out: (float) -- the forward current value.
 *
 * RETURN:	    float -- the value of the forward voltage drop at a current
 *		    of i_out.
 *
 * NOTES:	    No error codes. The value returned is always valid at the
 *		    value given.
 ***/
static float get_vf(float i_out)
{
  if (signbit(i_out))
    return 0.0F;

  float v_f = 0.0F, diff1 = 0.0F, diff2 = 0.0F;
  while (1) {
    diff2 = diff1;
    diff1 = vf[(size_t)(v_f * 10)] / i_out;
    if (diff1 < diff2 || v_f >= 0.6) {
      v_f -= 0.1;
      break;
    }
    v_f += 0.1;
  }

  return v_f;
}

/******************************************************************************/
