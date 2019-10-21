/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

#ifndef __fluid_
#define __fluid_

//Random numbers
#include "random.h"
int seed[4];
Random rnd;

//parameters, observables
const int m_props=1000;
int n_props, iv, iw, igofr;
double vtail,ptail,bin_size,nbins,sd;
double walker[m_props];
int count;
int occio = 0;
const double kb = 1.38*pow(10,-23);
const double eps = 120*kb;
const double mass = 39.948*1.66*pow(10, -27);
const double sigma = 0.34*pow(10,-9);
const double sec = sigma*sqrt(mass/eps);
const double fatt_P =  pow(sigma*sigma*sigma/eps,-1);

// averages
double blk_av[m_props],blk_norm,accepted,attempted;
double glob_av[m_props],glob_av2[m_props];
double stima_pot,stima_pres,err_pot,err_press,err_gdir;
double *E_inst;
double *P_inst;

//configuration
const int m_part=108;
double x[m_part],y[m_part],z[m_part];

// thermodynamical state
int npart;
double beta,temp,vol,rho,box,rcut;

// simulation
int nstep, nblk;
double delta;

//pigreco
const double pi=3.1415927;

//functions
void Input(void);
void Reset(int);
void Accumulate(void);
void Averages(int);
void Move(void);
void ConfFinal(void);
void ConfXYZ(int);
void Measure(void);
double Boltzmann(double, double, double, int);
double Pbc(double);
double Error(double,double,int);
void Esporta(void);
double norm(double);
double d(int, int);
double d(int);

#endif

/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
