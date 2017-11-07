/*******************************************************************************
 * NAME:	    calc.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Do some calculations!
 *
 * CREATED:	    11/06/2017
 *
 * LAST EDITED:	    11/06/2017
 ***/

/*******************************************************************************
 * INCLUDES
 ***/

#include "calc.h"
#include "error.h"

/*******************************************************************************
 * API FUNCTIONS
 ***/

/*******************************************************************************
 * FUNCTION:	    calc_std
 *
 * DESCRIPTION:	    This function uses the values in `params' to calculate the
 *		    values of the components that support the MC34063, and place
 *		    their values into `components.'
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
  return -1; /* Not yet implemented */
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
    .v_in   = 32F,
    .v_out  = 12F,
    .v_rip  = 0.1F,
    .f_s    = 100e3,
    .i_out  = 0.33
  };

  struct mc34063_components components;
  if(calc_std(&params, &components))
    StopIf(1, 1, "Error: calc_std returned an error code.\n");

  /* Print the results */
  printf("C_t\t= %g\n"
	 "R_sc\t= %g\n"
	 "L_min\t= %g\n"
	 "C_o\t= %g\n",

	 components.c_t,
	 components.r_sc,
	 components.l_min,
	 components.c_o);
}

/******************************************************************************/
