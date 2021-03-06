/*
 * lessnasty.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Description of these functions can be found at the end of the script, after main().*/ 
double f(double omega_ext, double t);
double Euler_forward(double x, double v, double t, double t_final, int Nsteps, double omega_ext);

/* Specific parameters for damped oscillator model */                                                                                                                                                         
/* ---------------------------------------------------------------------- */ 
double beta  = 0.25;        /* drag coefficient */
double omega_nat = 1.0;     /* natural frequency of the oscillator */


/* ============================================================================================================== */
int main(int argc, char *argv[])
{
  const double pi = 3.14159265359;
  
  double t, t_final, period_nat;
  double x, v;  
  double omega_ext;
  int i, Nsteps;

  period_nat = 2*pi/omega_nat;    /* natural period of the oscillator */

  /* Specify initial conditions */  
  /* -------------------------------------------------------------------- */
  t = 0.0;      /* initial time */
  x = 0.0;      /* initial particle position */
  v = 0.0;      /* initial particle velocity */

  printf("%15.8f %15.8f %15.8f\n", t, x, v);

  /* Specify final time of integration, frequency of external driving force, and number of time-steps */
  /* ------------------------------------------------------------------------------------------------ */
  t_final = 3*period_nat;   
  
  omega_ext = atof(argv[1]);     /* frequency of external driving force <--- read from command line (1st argument) */  
  Nsteps = atoi(argv[2]);        /* number of integration steps  <--- read from command line (2nd argument) */ 

  /* printf("%f, %d\n", omega_ext, Nsteps);

  /* CALL THE ODE SOLVER */
  /* ------------------- */
  Euler_forward(x, v, t, t_final, Nsteps, omega_ext);

  return 0;
}
/* ============================================================================================================== */


/* function for external driving force */
/* ----------------------------------- */
double f(double omega_ext, double t)
{
  double ext_force;
  ext_force = cos(omega_ext*t);
  return(ext_force);
}

/* function for forward Euler method for ode integration */
/* ----------------------------------------------------- */
double Euler_forward(double x, double v, double t, double t_final, int Nsteps, double omega_ext)
{
  double dt;
  int i; 
  
  dt = t_final / Nsteps; /* integration time-step */
  for (i=0; i < Nsteps; ++i)
  {
    /* position, velocity and time, for time-step (i) */
    double x_old = x;                                                                                                                                                 
    double v_old = v;
    double t_old = t;                          
    
    /* update position, velocity and time, for time-step (i+1) */                
    x = x_old + v_old*dt;
    v = v_old + (f(omega_ext, t) - (omega_nat*omega_nat)*x_old - 2*beta*v_old)*dt;                                                                                                                            
    t = t_old + dt;
                                                                                                                                                                                                  
    printf("%15.8f %15.8f %15.8f\n", t, x, v);                                                                                                                                                               
  }                                                                                                                                                                                                           
  printf("\n");
  return 0;
}
