#ifndef __fluid_
#define __fluid_

//Random numbers
#include "random.h"
int seed[4];
Random rnd;

//parameters:
const int n_cities=30;      //number of cities
const int npop = 5*pow(10,1); //number of chromosomes
int ind=0;
int nstep;
int maximum;
double beta;		    //temperature for annealing!
//grids:
double** coord;			//coordinates of cities
double* q;			//cost vector
int** population;		//population of chromosomes!
double* end;			//best result (per step)



//functions:
void Input(void);
void Shuffle(void); //recombine chromosomes via annealing
void Mix(void); //random shuffles
double Error(double,double,int);
void selection_sort (void);
void ConfFinal(void);
//scambio, minimo functions:
void scambio (int &, int &);
void scambio_d(double &, double &);
int minimo (int, int);
int massimo(int, int);
double min (double* , int);
int argmin (double* , int);
//costs:
double L(int);
double L(int *);
//Metropolis:
double Boltzmann(double, double);
void Metro_mut(int);
void Metro_cr(int);
void Metro_mir(int);
//genetic operators:
void mutation(int, int, int*);
void mutation(int, int, int);
void cross(int*, int, int);
void cross(int, int, int);
void mirror(int, int, int);
void mirror(int, int, int*);


























#endif
