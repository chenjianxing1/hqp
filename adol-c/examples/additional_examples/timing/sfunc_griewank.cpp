#define _SFUNC_GRIEWANK_C_
/*
   --------------------------------------------------------------
   File sfunc_griewank.C 
   of ADOL-C version 1.8.0                        as of Dec/01/98
   --------------------------------------------------------------
   based on 1. ICEO Testproblems 

   Example: function module containing Griewanks function

   Each << function module >> contains:
          
     (1) const char* const controlFileName 
     (2) int indepDim; 
 
     (3) void initProblemParameters( void )
     (4) void initIndependents( double* indeps )
     (5) double originalScalarFunction( double* indeps )
     (6) double tapingScalarFunction( int tag, double* indeps )   

   Last changes: 
     981201 olvo new headers
     980826 olvo first version

   --------------------------------------------------------------
*/


/****************************************************************************/
/*                                                                 INCLUDES */
#include "../../../adolc/adolc.h"

#include <math.h>


/****************************************************************************/
/*                                                         GLOBAL VARIABLES */

/*--------------------------------------------------------------------------*/
/*                                                        Control file name */
const char* controlFileName = "griewankexam.ctrl";

/*--------------------------------------------------------------------------*/
/*                                                               Dimensions */
int indepDim;

/*--------------------------------------------------------------------------*/
/*                                       Other problem dependent parameters */
const double D = 4000.0;


/****************************************************************************/
/*                                                  INIT PROBLEM PARAMETERS */
void initProblemParameters( void )
{ fprintf(stdout,"GRIEWANKs FUNCTION (ADOL-C Example)\n\n");
  if (indepDim <= 0)
  { fprintf(stdout,"    number of independent variables = ? ");
    fscanf(stdin,"%d",&indepDim);
    fprintf(stdout,"\n");
  }
}


/****************************************************************************/
/*                                                        INITIALIZE INDEPs */
void initIndependents( double* indeps )
{ int i;
  for (i=0; i<indepDim; i++)
    indeps[i] = 600.0*(i+1.0)/(2.0+i);
}


/****************************************************************************/
/*                                                 ORIGINAL SCALAR FUNCTION */

/*--------------------------------------------------------------------------*/
/*                                                       Griewanks function */
double griewank( int dim, double* indeps ) 
{ int i;
  double Val1,
	 Val2,
         tmp;

  for (Val1 = 0.0, Val2 = 1.0, i = 0; i < dim; i++) 
  { tmp   = indeps[i]-100.0;
    Val1 += tmp * tmp;
    Val2 *= cos(tmp / sqrt((double) (i + 1)) );
  }

  return Val1 / D - Val2 + 1.0;
}

/*--------------------------------------------------------------------------*/
/*                                                   The interface function */
double originalScalarFunction( double* indeps )
{ return griewank(indepDim, indeps);
}


/****************************************************************************/
/*                                                   TAPING SCALAR FUNCTION */

/*--------------------------------------------------------------------------*/
/*                                                active Griewnaks function */
adouble activeGriewank( int dim, adouble* indeps ) 
{ int i;
  adouble Val1,
	  Val2,
          tmp;

  for (Val1 = 0.0, Val2 = 1.0, i = 0; i < dim; i++) 
  { tmp   = indeps[i]-100.0;  
    Val1 += tmp * tmp;
    Val2 *= cos(tmp / sqrt((double) (i + 1)) );
  }

  return Val1 / D - Val2 + 1.0;
}

/*--------------------------------------------------------------------------*/
/*                                                   The interface function */
double tapingScalarFunction( int tag, double* indeps )
{ int i;
  trace_on(tag);
  adouble* activeIndeps = new adouble[indepDim];
  adouble* aIP = activeIndeps;
  double*  iP  = indeps; 
  for (i=0; i<indepDim; i++)
     *aIP++ <<= *iP++; 
  adouble ares = activeGriewank(indepDim, activeIndeps);
  double res = 0;
  ares >>= res;
  trace_off();
  return res; 
}

#undef _SFUNC_GRIEWANK_C_




