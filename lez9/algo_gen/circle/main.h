#ifndef __fluid_
#define __fluid_

//Random numbers
#include "random.h"
int seed[4];
Random rnd;

//parameters:
const int n_cities=30;      //number of cities
const int npop = pow(10,2); //number of chromosomes
const int nstep = pow(10,5);//number of steps
int ind=0;
const int maximum=nstep;
//grids:
double** coord;			//coordinates of cities
int* sort; 			//ordering grid vector
double* q;			//cost vector
int** population;		//population of chromosomes!
double end[maximum];		//better result (per step)
double save;			//variable to save the minimum distance we've found



//functions:
void Input(void);
void Shuffle(void); //recombine chromosomes
double Error(double,double,int);
double L(int); //cost function L (lenght)
void ConfFinal(void);
//genetic operators:
void mutation(int);
void cross(int);
//scambio, minimo functions:
double min (double* , int, int);
double argmin(double*, int, int);

























#endif
