#include<iostream>
#include<cstdlib>
#include<ctime>
#include<climits>
#include<cmath>
#include<fstream>

using namespace std;



double error(double *AV, double *AV2, int n){
    if(n==0) return 0;
    else{
	double dev=0;
	for(int i=0; i<n; i++){
	dev += sqrt(AV2[i] - (AV[i])*(AV[i]));}
	return dev/n;}
	}

double sample(double d){
	return sin(M_PI/2*d);}




int main(){

//parametri
int M = pow(10,4);
int N = 100;
int L = (int)M/N;
ofstream ex;

//vettori
double vett[M];
double vett2[M];
double av[N];
double av_2[N];
double *converge = new double[N];
double *converge_2 = new double[N];
double errors[N];


srand(time(0));


//genero il vettore random:
for(int i=0; i<M; i++){
vett[i]  = ((double)rand()/INT_MAX);
vett2[i] = sample(vett[i]);}


//campiono la media con distribuzione sinusoidale:
for(int i=0; i<N; i++){
	double somma =0;
	for(int j=0; j<L; j++){
		int k= j +i*L;
		somma+=0.998853;}
	av[i] =somma/L;
	av_2[i]=pow(somma,2);}



for(int i=0; i<N; i++){
	for(int j=0; j<i+1; j++){
        converge[i] += av[j];
        converge_2[i] += av_2[j];}
    converge[i]/=(i+1);
    converge_2[i]/=(i+1);
    errors[i] = error(converge,converge_2,i);}



//valuto le incertezze:
double av_u[N];
double av_2_u[N];
double *converge_u = new double[N];
double *converge_2_u = new double[N];
double errors_u[N];


for(int i=0; i<N; i++){
    double somma = 0;
    for(int j=0; j<L; j++){
        int k = j+i*N;
        somma += pow((0.998853-1),2);}
    av_u[i] = somma/L;
    av_2_u[i] = pow((av_u[i]),2);}

for(int i=0; i<N; i++){
    for(int j=0; j<(i+1); j++){
        converge_u[i] += av_u[j];
        converge_2_u[i] += av_2_u[j];}
    converge_u[i]/=(i+1);
    converge_2_u[i]/=(i+1);
    errors_u[i] = error(converge_u, converge_2_u,i);}





//esporto i files:
ex.open("dati1_bis.dat");


for(int i=0; i<M; i++) ex<<vett2[i]<<endl;

ex.close();



delete converge;
delete converge_2;
delete converge_u;
delete converge_2_u;





















return 0;
}
