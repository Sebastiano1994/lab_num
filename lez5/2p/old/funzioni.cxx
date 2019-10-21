#include"funzioni.h"


using namespace std;




//orbitale s:
	double Y_s(double r){
	return pow(exp(-r)/sqrt(M_PI),2);
	}
	

//orbitale 2p:
	double Y_2p(double* vett){
	return pow(exp(-2*vett[0])*sqrt(2/M_PI)*vett[0]/8*cos(vett[1]),2);
	}



//funzione per il calcolo degli errori:
	double error(double *AV, double *AV2, int n){
	if(n==0) return 0;
	else{
	double dev=0;
	for(int i=0; i<n; i++){
	dev += sqrt(AV2[i] - (AV[i])*(AV[i]));}
	return dev/n;}
	}
	
	
	











	
