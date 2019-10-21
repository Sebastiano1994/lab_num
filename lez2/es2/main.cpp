#include<iostream>
#include<cstdlib>
#include<ctime>
#include<climits>
#include<cmath>
#include<iomanip>
#include<fstream>
#include"random.h"

using namespace std;





double X(double th, double ph){
	return cos(ph)*sin(th);}

double Y(double th, double ph){
	return sin(th)*sin(ph);}

double Z(double th){
	return cos(th);}





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







//Numero totale di step:
int M=pow(10,2);
//Numero totale di traiettorie:
int T=pow(10,4); //pow(10,4);
//ofstream
ofstream ex;
ofstream exerr;

//vettori posizione: pos[traiettorie][steps]

//vettore x:
int** pos_x = new int*[T];
for(int i=0; i<T; i++) pos_x[i] = new int[M];

//vettore y:
int** pos_y = new int*[T];
for(int i=0; i<T; i++) pos_y[i] = new int[M];

//vettore z:
int** pos_z = new int*[T];
for(int i=0; i<T; i++) pos_z[i] = new int[M];



//vettore delle medie sulle traiettorie (per ogni passo):

//vettore x:
double* av_x = new double[M];

//vettore y:
double* av_y = new double[M];

//vettore z:
double* av_z = new double[M];

//vettore distanza media percorsa (per ogni passo):
double* R = new double[M];







//VETTORE X

//genero il primo passo (devo partire dall'origine):
	//ciclo sulle traiettorie:
	for(int j=0; j<T; j++){
	pos_x[j][0]=0;
	//cout<<pos_y[j][0]<<endl;
	}


//genero il vettore pass_x:
	//ciclo sulle traiettorie:
	for(int j=0; j<T; j++){
	//ciclo sugli step:
	for(int k=1; k<M; k++){
	//ciclo sulle coordinate:
	if(rnd.Rannyu()-.5<0) pos_x[j][k]=-1+pos_x[j][k-1];
	else pos_x[j][k]=1+pos_x[j][k-1];}}
	
	




//VETTORE Y

//genero il primo passo:
	//ciclo sulle traiettorie:
	for(int j=0; j<T; j++){
	pos_y[j][0]=0;
	//cout<<pos_y[j][0]<<endl;
	}


//genero il vettore pass_y:
	//ciclo sulle traiettorie:
	for(int j=0; j<T; j++){
	//ciclo sugli step:
	for(int k=1; k<M; k++){
	//ciclo sulle coordinate:
	if(rnd.Rannyu()-.5<0) pos_y[j][k]=-1+pos_y[j][k-1];
	else pos_y[j][k]=1+pos_y[j][k-1];}}
	
	




//VETTORE Z

//genero il primo passo:
	//ciclo sulle traiettorie:
	for(int j=0; j<T; j++){
	pos_z[j][0]=0;
//	cout<<pos_z[j][0]<<endl;
	}


//genero il vettore complessivo sulle z:
	//ciclo sulle traiettorie:
	for(int j=0; j<T; j++){
	//ciclo sugli step:
	for(int k=1; k<M; k++){
	//ciclo sulle coordinate:
	if(rnd.Rannyu()-.5<0) pos_z[j][k]=-1+pos_z[j][k-1];
	else pos_z[j][k]=1+pos_z[j][k-1];}}

	

	//cout<<pos_z[0][40]<<endl;
	//cout<<"funziona"<<endl;



//MEDIA SULLE TRAIETTORIE:

//ciclo sugli step:
	ex.open("dati_discr.csv");
	exerr.open("err_discr.csv");
	for(int j=0; j<M; j++){
	double a=0;
	double b=0;
	for(int i=0; i<T; i++){
	a+=(pos_x[i][j]*pos_x[i][j]+pos_y[i][j]*pos_y[i][j]+pos_z[i][j]*pos_z[i][j]);
	b =(pos_x[i][j]*pos_x[i][j]+pos_y[i][j]*pos_y[i][j]+pos_z[i][j]*pos_z[i][j]);
	exerr<<b<<endl;
	//cout<<a<<endl;
	}
	R[j]=a/T;
	ex<<sqrt(R[j])<<endl;
	//exerr<<endl;
	//cout<<j<<") "<<R_c[j]<<endl;
	}
	ex.close();
	exerr.close();



	double al[T];
	double bl[T];
	double a1=0;
	double b1=0;

	for(int i=0; i<T; i++){
	al[i] = pos_x[i][99]*pos_x[i][99]+pos_y[i][99]*pos_y[i][99]+pos_z[i][99]*pos_z[i][99];
	bl[i] = al[i]*al[i];
	}
	for(int i=0; i<T; i++){
	a1 +=al[i];
	b1 +=bl[i];
	}
	b1/=T;
	a1/=T;
	cout<<b1<<endl;
	cout<<a1*a1<<endl;
	cout<<sqrt(b1-a1*a1)<<endl;


delete pos_x;
delete pos_y;
delete pos_z;

delete av_x;
delete av_y;
delete av_z;

delete R;





///////////////LIMITE AL CONTINUO/////////////////





//vettore x:
double** pos_c_x = new double*[T];
for(int i=0; i<T; i++) pos_c_x[i] = new double[M];

//vettore y:
double** pos_c_y = new double*[T];
for(int i=0; i<T; i++) pos_c_y[i] = new double[M];

//vettore z:
double** pos_c_z = new double*[T];
for(int i=0; i<T; i++) pos_c_z[i] = new double[M];




//vettore distanza media (per ogni passo):
double R_c[M];



//genero il primo passo:
	//ciclo sulle traiettorie:
	for(int j=0; j<T; j++){
	//genero gli angoli:
	double th  = (rnd.Rannyu()*M_PI);
	double phi = (rnd.Rannyu()*2*M_PI);
	
	pos_c_x[j][0] = X(th, phi);
	pos_c_y[j][0] = Y(th, phi);
	pos_c_z[j][0] = Z(th);
	//cout<<pos_c_y[j][0]<<endl;
	}


	
	
//genero il resto della traiettoria:
	//ciclo sulle traiettorie:
	for(int i=0; i<T; i++){
	//ciclo sui passi:
	for(int j=1; j<M; j++){
	//genero gli angoli:
	double th  = (rnd.Rannyu()*M_PI);
	double phi = (rnd.Rannyu()*2*M_PI);
	//genero le posizioni cartesiane:
	pos_c_x[i][j] = X(th, phi)+pos_c_x[i][j-1];
	pos_c_y[i][j] = Y(th, phi)+pos_c_y[i][j-1];
	pos_c_z[i][j] = Z(th)+pos_c_z[i][j-1];
	}}


//	for(int i=0; i<M; i++) cout<<i+1<<") "<<pos_c_y[4][i]<<endl;






//VETTORE DISTANZA:
	//ciclo sugli step:
	ex.open("dati_cont.csv");
	exerr.open("err_cont.csv");
	for(int j=0; j<M; j++){
	double a=0;
	double b=0;
	for(int i=0; i<T; i++){
	a+=(pos_c_x[i][j]*pos_c_x[i][j]+pos_c_y[i][j]*pos_c_y[i][j]+pos_c_z[i][j]*pos_c_z[i][j]);
	b =(pos_c_x[i][j]*pos_c_x[i][j]+pos_c_y[i][j]*pos_c_y[i][j]+pos_c_z[i][j]*pos_c_z[i][j]);
	exerr<<b<<endl;
	//cout<<a<<endl;
	}
	R_c[j]=a/T;
	ex<<sqrt(R_c[j])<<endl;
	//cout<<j<<") "<<R_c[j]<<endl;
	}
	ex.close();
	exerr.close();











delete pos_c_x;
delete pos_c_y;
delete pos_c_z;
















return 0;
}



