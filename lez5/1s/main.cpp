#include<iostream>
#include<cstdlib>
#include<ctime>
#include<climits>
#include<cmath>
#include<math.h>
#include<fstream>
#include"random.h"

using namespace std;





double X(double th, double ph){
	return cos(ph)*sin(th);}

double Y(double th, double ph){
	return sin(th)*sin(ph);}

double Z(double th){
	return cos(th);}

double d(double x, double y, double z){
	return sqrt(x*x+y*y+z*z);
	}


double gauss(double x){
	return .5*(1+erf(x));}




int main(int argc, char *argv[]){


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


rnd.SaveSeed();





//PARAMETRI DI PROGRAMMA

//Numero totale di step:
int M=pow(10,6);
//variabile per decidere se fare passi gaussiani o uniformi:
int option;

//FUNZIONE S:

//posizioni da campionare
//variabili cartesiane (vecchie e nuove):
double x, y, z;
double xnew, ynew, znew;
//variabili angolari:
double th, phi;
//posizione iniziale:
double r_0;

//posizione finale:
double r_1;

//campiono il vettore con cui fare la media:
double vett[M];

//variabile random per il Metropolis:
double rdm;

//variabili di conteggio per l'accettanza (~50%):
int count=1;


//passo
double passo;

//indici:
int i=0;
int j=0;

//ofstreams
ofstream ex, exx, exy, exz;
//ifstreams
ifstream ReadInput;

ReadInput.open("input.dat");
ReadInput >> passo;
ReadInput >> option;
ReadInput.close();





//assegno una posizione iniziale ragionevole (~1):
	th  = rnd.Rannyu()*M_PI;
	phi = rnd.Rannyu()*2*M_PI;
	
	x = passo*X(th, phi);
	y = passo*Y(th, phi);
	z = passo*Z(th);
	r_0 = d(x, y, z);
	
	//cout<<"Valore iniziale: "<<r_0<<endl;






//prova sull'accettanza del Metropolis (e campionamento di tot valori):
	exx.open("dati_x.csv");
	exy.open("dati_y.csv");
	exz.open("dati_z.csv");
	//Metropolis usuale
	if(option == 1){
	while(j<M){
	rdm = (rnd.Rannyu());
	th  = rnd.Rannyu()*M_PI;
	phi = rnd.Rannyu()*2*M_PI;
	xnew = x+passo*X(th, phi);
	ynew = y+passo*Y(th, phi);
	znew = z+passo*Z(th);
	r_1 = d(xnew, ynew, znew);
	
	
	if((exp(2*r_0-2*r_1))>=rdm){
	r_0=r_1;
	count++;
	vett[j]=r_0;
	j++;
	x=xnew;
	y=ynew;
	z=znew;
	}
	else{vett[j]=r_0; j++;}
	if(j<pow(10,4)){
	exx<<x<<endl;
	exy<<y<<endl;
	exz<<z<<endl;}
	i++;
	}
	}
	
	//Metropolis con accettanza gaussiana
	else if(option == 0){
	while(j<M){
	rdm = (rnd.Rannyu());
	/*xnew = gauss(rnd.Rannyu());
	ynew = gauss(rnd.Rannyu());
	znew = gauss(rnd.Rannyu());*/
	xnew = x+rnd.Gauss(0,1);
	ynew = y+rnd.Gauss(0,1);
	znew = z+rnd.Gauss(0,1);
	r_1 = d(xnew, ynew, znew);
	
	
	if((exp(2*r_0-2*r_1))>=rdm){
	r_0=r_1;
	count++;
	vett[j]=r_0;
	j++;
	x=xnew;
	y=ynew;
	z=znew;
	}
	else{vett[j]=r_0; j++;}}
	
	
	}
	
	exx.close();
	exy.close();
	exz.close();


	cout<<"Accettazione: "<<(double)count/j*100<<"%"<<endl;











//MEDIA SU 1s:

//media col peso delle armoniche sferiche:
	double somma =0;
	ex.open("dati.csv");
	for(int i=0; i<M; i++){
	somma+=vett[i];
	ex<<vett[i]<<endl;
	}
	somma/=M;
	ex.close();
	cout<<"Media: "<<somma<<endl;













return 0;
}



