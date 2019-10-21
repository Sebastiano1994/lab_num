#include<iostream>
#include<cstdlib>
#include<ctime>
#include<climits>
#include<cmath>
#include<math.h>
#include<fstream>
#include <algorithm>
#include<iomanip>
#include"random.h"
#include"main.h"


using namespace std;






double S(double t){
	return S0*exp((risk_rate-.5*volat*volat)*t+ volat*rnd.Gauss(0,t));}







int main(int argc, char *argv[]){



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


rnd.SaveSeed();


//variables I need: total trials and vectors to save my sampling:
int trials = pow(10,5);
double delta = pow(10, -2);
double C[trials], P[trials];
ofstream c, p;
double zero = 0;

//FIRST WAY TO CALCULATE C[S(0),0] AND P[S(0), 0] (direct one):



for(int i=0; i<trials; i++){
	C[i] = exp(-risk_rate*T)*max(S(T)-K,zero);
	//cout<<C[i]<<endl;
	P[i] = exp(-risk_rate*T)*max(K-S(T),zero);
	}

c.open("C_direct.csv");
p.open("P_direct.csv");


for(int i=0; i<trials; i++){
	c << C[i]<<endl;
	p << P[i] <<endl;
	}

c.close();
p.close();



//COMPUTING C[S(0),0] and P[S(0), 0] VIA DISCRETE t-PATH
double s1 = S0;
double s2;
double t0;
double t;

c.open("C_discrete.csv");
p.open("P_discrete.csv");

for(int i=0; i<trials; i++){
	t0=0;
	t = delta;
	s1 = S0;
	while(t<T){
	s2 = s1*exp((risk_rate-.5*volat*volat)*(t-t0)+volat*rnd.Gauss(0,1)*sqrt(t-t0));
	s1 = s2;
	t0 = t;
	t+=delta;
	//cout<<s2<<endl;
	}
	c << exp(-risk_rate*T)*(max(s2-K,zero)) <<endl;
	//cout<< C_call(exp(-risk_rate*T)*(max(s2-K,zero)),0) <<endl;
	p << exp(-risk_rate*T)*(max(K-s2,zero))  <<endl;
	
	}





c.close();
p.close();












return 0;
}

































