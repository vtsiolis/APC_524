/*
 * nasty.c
 */

#include <stdio.h>
#include <math.h>


double f(double omega, double t);
double Euler_forward(double x, double v, double t, double t_final, int Nsteps);

int main()
{
  double t, dt;
  double x, v;
  double period;
  double beta, omega0;
  
  int i, Nsteps;

  /* Initialize time (t), particle position (x) and particle velocity (v) */  
  /* -------------------------------------------------------------------- */
  t = 0.0;
  x = 0.0;
  v = 0.0;

  /* Specific parameters for damped oscillator model */
  /* ----------------------------------------------- */
  beta = 1.0;
  omega0 = 1.0;
  printf("%15.8f %15.8f %15.8f\n", t, x, v);

  /* Declare number of steps and final time of integration */
  /* ----------------------------------------------------- */
  period = 18.84955592153876;
  Nsteps = 10;
  dt = period / Nsteps;

  /* CALL THE ODE SOLVER */
  /* ------------------- */

  Euler_forward(x, v, t, period, Nsteps);

  return 0;
}

double f(double omega, double t)
{
  double ext_force;
  ext_force = cos(omega*t);
  return(ext_force);
}

double Euler_forward(double x, double v, double t, double t_final, int Nsteps)
{
  double dt;
  int i; 
  
  dt = t_final / Nsteps;
  for (i=0; i < Nsteps; ++i)
  {
    double x_old = x;                                                                                                                                                                                         
    double v_old = v;                                                                                                                                                                                         
                                                                                                                                                                                                               
    x = x_old + v_old*dt;                                                                                                                                                                                     
    v = v_old + (f(0.5, t) - x_old - 0.5*v_old)*dt;                                                                                                                                           
    t += dt;                                                                                                                                                                                                  
    printf("%15.8f %15.8f %15.8f\n", t, x, v);                                                                                                                                                               
  }                                                                                                                                                                                                           
  printf("\n");
  return 0;
}

