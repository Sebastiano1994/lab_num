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



double sgn(double x){
	if(x<0) return -1;
	else return 1;}


double angolo(double, double);



 
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

//es vero e proprio: superficie di altezza y=10, con distanza tra i solchi D=1 e lunghezza dell'ago 0.5
double y1;
double y2;
double y;
double x2;
double len = .5;
int throws = pow(10,6)+1000;
double count=0;
double pigreco;
double pi[throws];






/*s
for(int mi=0; mi<100; mi++){
double l = rnd.Rannyu();
double p = rnd.Rannyu();
//cout<<(l-.5)*(l-.5)*4+(p-.5)*(p-.5)*4<<endl;
if(angolo(l, p)!=-1){
cout<<mi<<"  "<<angolo(l, p)<<endl;
}
else mi--;
}*/



for(int i=1; i<=throws; i++){

y1 = rnd.Rannyu()*4;
//x1 could be fixed as 0, as we have translation invariance along x axis
x2 = (rnd.Rannyu()*len/2);
double th=-1;
while(th==-1){
double l = rnd.Rannyu();
double p = rnd.Rannyu();
//cout<<(l-.5)*(l-.5)*4+(p-.5)*(p-.5)*4<<endl;
th=angolo(l, p);
}
//cout<<th<<endl;
//y2 = y1 + x2;
//y2 = y1+len*rnd.Rannyu();
//cout<<sgn(rnd.Rannyu()-.5)<<endl;
//y2 = y + sqrt(len*len/4-x2*x2);
//y1 = y - sqrt(len*len/4-x2*x2);
y2 = y1+cos(th)*len;
//cout<<"y1: "<<y<<endl;
//cout<<"y2: "<<y2<<endl;
if((y1<0 && y2>0) ) count++; //cout<<count<<endl<<endl;}
if((y1<1 && y2>1) ) count++; //cout<<count<<endl<<endl;}
if((y1<2 && y2>2) ) count++; //cout<<count<<endl<<endl;}
if((y1<3 && y2>3) ) count++; //cout<<count<<endl<<endl;}
if((y1<4 && y2>4) ) count++; //cout<<count<<endl<<endl;}
if((y1<5 && y2>5) ) count++; //cout<<count<<endl<<endl;}

//else cout<<endl;
double k = (double)i;
pi[i] = k/count/2;
if(i % 1000 == 0){
pigreco = k/count; //D=1, len*2=1, quindi li ometto
cout<<"pi for "<<i<<" throws: "<<pi[i]<<endl;}
}


cout<<throws/(2*count)<<endl;




ofstream ex;
ex.open("dati.csv");

for(int i=1000; i<throws; i++) ex<<pi[i]<<endl;

ex.close();













   return 0;
}




double angolo(double a, double b){
	double lim=4, ang;
	double x = (a-.5)*2;
	double y = (b-.5)*2;
	lim=x*x+y*y;
	//cout<<"x: "<<x<<endl;
	//cout<<"y: "<<y<<endl;
	//cout<<"x^2+y^2: "<<lim<<endl;
	if(lim<=1){
	if(y>=0) ang = acos(x/sqrt(lim));
	else     ang = 2*M_PI-acos(x/sqrt(lim));
	return ang;}
	else return -1;
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