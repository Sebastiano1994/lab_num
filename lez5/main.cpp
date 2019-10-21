#include<iostream>
#include<cstdlib>
#include<ctime>
#include<climits>
#include<cmath>
#include<fstream>
#include"funzioni.h"

using namespace std;










int main(){



//PARAMETRI DI PROGRAMMA

//Numero totale di step:
int M=pow(10,6);
//Numero totale di blocchi:
int N=pow(10,2);
//rapporto:
int L=(int)M/N;




//FUNZIONE S:

//posizioni da campionare:
//posizione iniziale:
double r_0;

//posizione finale:
double r_1;

//campiono il vettore con cui fare la media:
double vett[M];

//variabile random per il Metropolis:
double rdm;

//variabili di conteggio per l'accettanza (~50%):
int count=0;

//variabili per la media di r:
double r[N];
for(int i=0; i<N; i++) r[i]=0;
double r_m=0;

//variabili per la varianza (con i blocchi):
double r2[N];
for(int i=0; i<L; i++) r2[i]=0;
double dev[L];
for(int i=0; i<L; i++) dev[i]=0;
double dev2[L];
for(int i=0; i<L; i++) r2[i]=0;
double var=0;

//indici:
int i=0;
int j=0;


srand(time(0));



//assegno una posizione iniziale ragionevole (~1):
	r_0 = ((double)rand()/INT_MAX+.5);
	
	//cout<<"Valore iniziale: "<<r_0<<endl;






//prova sull'accettanza del Metropolis (e campionamento di tot valori):

	while(count<M){
	rdm = ((double)rand()/INT_MAX);
	r_1 = ((double)rand()/INT_MAX*5);
	//r_1 = -log(1-((double)rand()/INT_MAX));
	
	if((exp(2*r_0-2*r_1))>=rdm){
	r_0=r_1;
	count+=1;
	vett[j]=r_0;
	j++;
	}
	i++;
	}

	cout<<vett[M-1]<<" "<<vett[M-2]<<endl;

	cout<<"Accettazione: "<<(double)count/i*100<<"%"<<endl;











//MEDIA SU 1s:

//media col peso delle armoniche sferiche:
	for(int i=0; i<N; i++){
	double somma =0;
	for(int j=0; j<L; j++){
	int k= j +i*L;
	somma+=vett[k],3;
	}
	r[i] =somma/L;
	r2[i]=pow(somma,2);
	}
	
	for(int i=0; i<N; i++) r_m+=r[i]/N;
	
	cout<<"Media: "<<2*r_m<<endl;














///////////////ORBITALI 2p/////////////////












return 0;
}



