#include"media.h"


using namespace std;












//funzione media:
	double media(double** vett, int fixed, int M, int N){
	
	int L = (int) M/N;
	double av[N];
	
	//media effettiva:
	for(int i=0; i<N; i++){
	double somma =0;
	for(int j=0; j<L; j++){
	int k= j +i*L;
	somma+=vett[fixed][k];}
	av[i] =somma/L;}
	
	double sum=0;
	for(int i=0; i<N; i++) sum+=av[i];


	return sum/N;
	}


//funzione incertezza:
	/*double Media::varianza(double** vett, int fixed){
	double somma=0;
	for(int i=0; i<N; i++){
        somma += -av[i]*av[i]/L+av2[i];}
	somma/= (L-1);
	return sqrt(somma);}*/















	
