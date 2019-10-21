#ifndef __fluid_
#define __fluid_

//Random numbers
#include "random.h"
int seed[4];
Random rnd;

//parameters, observables
const int m_props=1000;
int n_props,ie; //variabili e n_variabili
double walker[m_props];
int count;    //counter for histogram

// averages
double blk_av[m_props],blk_norm,accepted,attempted;
double glob_av[m_props],glob_av2[m_props];
double stima_e;
double err_e;



//quantum parameters:
double m,mu,sigma,h;
//positions:
double x_0;			//actual position
const int ngrid = 1000;		//number of elements in the grid
double a=10;			//grid size
double dx = (double)a/ngrid;    //pass
//grids:
double pos[ngrid];		//position
double V_f(double);		//potential energy (function)
double *Psi2;			//wave function (as a vector) for filling histogram
double W_f(double);		//Wave function (as a function)

// simulation
int nstep, nblk;

//functions
void Input(void);
void Reset(int);
void Accumulate(void);
void Averages(int);
void Move();
void ConfFinal(void);
void End(void);
void Measure(void);
double Error(double,double,int);

#endif
