/*
   --------------------------------------------------------------
   File helm-diff-exam.c of ADOL-C version 1.8.0  as of Nov/01/98
   --------------------------------------------------------------
   based on helm-diff-exam.c version 1.7 

   Example: Helmholtz energy example 
            Computes gradient using divide differences

   Last changes: 

   --------------------------------------------------------------
*/

/****************************************************************************/
/*                                                                 INCLUDES */
#include <sys/types.h>
#include <stdio.h>

#include <math.h>
#include <stdlib.h>


/****************************************************************************/
/*                                                    CONSTANTS & VARIABLES */
#define delta 0.000001
#define TE    0.01     
#define R     sqrt(2.0)

 
/****************************************************************************/
/*                                                         HELMHOLTZ ENERGY */
double energy( int n, double x[], double bv[] )
{ double he, xax, bx, tem;
  int i,j;
  xax = 0;
  bx  = 0;
  he  = 0;
  for (i=0; i<n; i++)
  { he += x[i]*log(x[i]);
    bx +=  bv[i]*x[i];
    tem = (2.0/(1.0+i+i))*x[i];
    for (j=0; j<i; j++) 
      tem += (1.0/(1.0+i+j))*x[j];
    xax += x[i]*tem;
  }
  xax *= 0.5;
  he   = 1.3625E-3*(he-TE*log(1.0-bx));
  he   = he - log((1+bx*(1+R))/(1+bx*(1-R)))*xax/bx;
  return he;
}


/****************************************************************************/
/*                                                                     MAIN */
/* 
   This program computes first order directional derivatives 
   for the helmholtz energy function */
int main(int argc, char *argv[]) 
{ int nf, n, j, l;
  double result1, result2;
  double q, jd, r;
  double *x, *bv;

  fprintf(stdout,"HELM-DIFF-EXAM (ADOL-C Example)\n\n");
  fprintf(stdout," # of independents/10 =? \n ");
  scanf("%d",&nf);

/*--------------------------------------------------------------------------*/
  n = 10 * nf;                                            /* Initilizations */
  x   = (double*) malloc(n*sizeof(double));
  bv  = (double*) malloc(n*sizeof(double));

  r = 1.0/n;
  for (j=0; j<n; j++) 
  { jd     = j;
    bv[j]  = 0.02*(1.0+fabs(sin(jd)));
    x[j]   = r*sqrt(1.0+jd);
  }

/*--------------------------------------------------------------------------*/
  result2 = energy(n,x,bv);                                    /* basepoint */
  fprintf(stdout,"%14.6le -- energy\n",result2);

/*--------------------------------------------------------------------------*/
  for (l=0; l<n; l++)                            /* directional derivatives */
  { x[l]    = x[l]+delta;
    result1 = energy(n,x,bv);
    x[l]    = x[l]-delta;
    q       = (result1-result2)/delta;
    fprintf(stdout,"%3d: %14.6le,  \n",l,q);
  }
  fprintf(stdout,"%14.6le -- energy\n",result2);
 
  free((char*) bv);
  free((char*) x);

  return 0;
}


/****************************************************************************/
/*                                                               THAT'S ALL */

