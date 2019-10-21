/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "random.h"
#include <cmath>
#include <iomanip>

using namespace std;



double error(double *AV, double *AV2, int n){
    if(n==0) return 0;
    else{
	double dev=0;
	for(int i=0; i<n; i++){
	dev += sqrt(AV2[i] - (AV[i])*(AV[i]));}
	return dev/n;}
	}


 
int main (int argc, char *argv[]){

   Random rnd;
   int seed[4];
   int p1, p2;
   ifstream Primes("Primes");
   if (Primes.is_open()){
      Primes >> p1 >> p2 ;
   } else cerr << "PROBLEM: Unable to open Primes" << endl;
   Primes.close();

   ifstream input("seed.in");
   string property;
   if (input.is_open()){
      while ( !input.eof() ){
         input >> property;
         if( property == "RANDOMSEED" ){
            input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
            rnd.SetRandom(seed,p1,p2);
         }
      }
      input.close();
   } else cerr << "PROBLEM: Unable to open seed.in" << endl;

	/*
   for(int i=0; i<20; i++){
      cout << rnd.Rannyu() << endl;
   }*/

   rnd.SaveSeed();



//es vero e proprio: campiono l'integrale di una funzione sinusoidale
//parametri
int M = pow(10,4);
ofstream ex;

//vettori
double vett[M];
double vett2[M];




//genero il vettore random:
for(int i=0; i<M; i++){
vett[i] = rnd.Rannyu();
vett2[i] = M_PI/2*cos(vett[i]*M_PI/2);}








//esporto i files:
ex.open("dati.csv");


for(int i=0; i<M; i++) ex<<vett2[i]<<endl;

ex.close();






   return 0;
}

/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
