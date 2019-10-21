#include<iostream>
#include<cstdlib>
#include<ctime>
#include<climits>
#include<cmath>
#include<fstream>
#include"random.h"

using namespace std;







double error(double *AV, double *AV2, int n){
    if(n==0) return 0;
    else{
	double dev=0;
	for(int i=0; i<n; i++){
	dev += sqrt(AV2[i] - (AV[i])*(AV[i]));}
	return dev/n;}
	}






int main(){



int trials = pow(10,4);
int blocks = 100;
int rapporto = int(trials/blocks);
double *vett = new double[trials];
double media[blocks];
double media2[blocks];
double *convergenza = new double[blocks];
double *convergenza_quadrato = new double[blocks];
double errori[blocks];
double s = pow(12,-1);
ofstream scrivi;
Random rnd;

srand(time(0));


//genero il vettore random:
for(int i=0; i<trials; i++){
vett[i] = ((double)rand()/INT_MAX);
}





//calcolo i momenti primo (media) e la media del quadrato:
for(int i=0; i<blocks; i++){
double somma =0;
for(int j=0; j<rapporto; j++){
int k= j +i*rapporto;
somma+=vett[k];
//cout<<vett[i]<<endl;
}
media[i] =somma/rapporto;
media2[i]=pow(somma,2);
}



for(int i=0; i<blocks; i++){
for(int j=0; j<i+1; j++){
        convergenza[i] += media[j];
        convergenza_quadrato[i] += media2[j];
	}
    convergenza[i]/=(i+1);
    convergenza_quadrato[i]/=(i+1);
    errori[i] = error(convergenza,convergenza_quadrato,i);}


cout<<errori[1]<<endl;


//INCERTEZZE MONTE CARLO


double media_s[blocks];
double media2_s[blocks];
double *convergenza_s = new double[blocks];
double *convergenza_quadrato_s = new double[blocks];
double errori_s[blocks];


for(int i=0; i<blocks; i++){
    double sum = 0;
    for(int j=0; j<rapporto; j++){
        int k = j+i*rapporto;
        sum += pow((vett[k]-0.5),2);}
    media_s[i] = sum/rapporto;
    media2_s[i] = pow((media_s[i]),2);}

for(int i=0; i<blocks; i++){
    for(int j=0; j<(i+1); j++){
        convergenza_s[i] += media_s[j];
        convergenza_quadrato_s[i] += media2_s[j];}
    convergenza_s[i]/=(i+1);
    convergenza_quadrato_s[i]/=(i+1);
    errori_s[i] = error(convergenza_s, convergenza_quadrato_s,i);}








//esporto i files:
scrivi.open("media.csv");
for(int i=0; i<blocks; i++) scrivi<<convergenza[i]-0.5<<","<< '\t'<< errori[i]-s <<endl;
scrivi.close();

scrivi.open("sigma.csv");
for(int i=0; i<blocks; i++) scrivi<<convergenza_s[i]-0.5<<","<< '\t'<< errori_s[i]-s <<endl;
scrivi.close();


scrivi.open("dati.dat");
for(int i=0; i<blocks; i++) scrivi<<vett[i]-0.5<<endl;
scrivi.close();




delete vett;
delete convergenza;
delete convergenza_quadrato;
delete convergenza_s;
delete convergenza_quadrato_s;



return 0;
}











