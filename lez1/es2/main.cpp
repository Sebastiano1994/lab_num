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


//funzioni:





double espo(double x){
	return -log(1-x);
	}


double lorentz(double x){
	double y = atan(x)/M_PI + .5;
	//double ecce = Gamma/(M_PI*((pow(y + mu ),2) + Gamma*Gamma)*((1+pow(y,2))*M_PI/2));
	return y;}

 
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

//es vero e proprio:
int max = pow(10,5);
double vett[max];
double vettlin[max];
double vettexp[max];
double vettlor[max];
ofstream ex;
int num = 2;
double flex = (double) num;
cout<<flex<<endl;

for(int i=0; i<max; i++){
vettlin[i] =   0;
vettexp[i]= 0;
vettlor[i]= 0;
}



for(int j=0; j<num; j++){
for(int i=0; i<max; i++){
vett[i] = rnd.Rannyu();
cout<<"v "<<vett[i]<<endl;
cout<<espo(vett[i])<<endl;
vettlin[i] += vett[i]*6;
vettexp[i]+=espo(vett[i]);
vettlor[i]+= lorentz(vett[i]);
}}

//exporting:
ex.open("linear_10.csv");
for(int i=0; i<max; i++) ex << setw(6) << vettlin[i]/flex << endl;
ex.close();

ex.open("exp_10.csv");
for(int i=0; i<max; i++) ex << setw(12) << vettexp[i]/flex << endl;
ex.close();

ex.open("lorentz_10.csv");
for(int i=0; i<max; i++) ex << setw(12) << vettlor[i]/flex << endl;
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
