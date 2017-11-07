/*******************************************************************************
 * NAME:	    calc.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    The public interface for the source code in calc.c.
 *
 * CREATED:	    11/06/2017
 *
 * LAST EDITED:	    11/06/2017
 ***/

#ifndef __ET_CALC_H__
#define __ET_CALC_H__

/*******************************************************************************
 * TYPE DEFINITIONS
 ***/

/* These values are chosen. */
struct mc34063_params {
  float	f_s;	/* The switching frequency */
  float v_in;	/* Input voltage */
  float v_out;	/* Output voltage */
  float v_rip;	/* Output ripple voltage (Peak) */
  float i_out;	/* Desired output current */
};

/* The values of the peripheral components */
struct mc34063_components {
  float c_t;	/* Switching frequency capacitor */
  float r_sc;	/* Sensing resistor */
  float l_min;	/* Minimum value for inductor */
  float c_o;	/* Output filter capacitance */
};

/*******************************************************************************
 * API FUNCTION PROTOTYPE
 ***/

/**
 * Calculate the component values using the values in params. Return non-zero
 * if an error is encountered.
 */
extern int calc_std(struct mc34063_params * params,
		    struct mc34063_components * components);

/**
 * Approximate the values given in params using the value of l_min as a
 * boundary. Values in params may be changed to allow value of l_min.
 */
extern int calc_lmin(struct mc34063_params * params,
		    struct mc34063_components * components);

#endif /* __ET_CALC_H__ */

/******************************************************************************/
