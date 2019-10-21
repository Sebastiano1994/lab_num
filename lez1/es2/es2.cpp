#include<iostream>
#include<cstdlib>
#include<ctime>
#include<climits>
#include<cmath>
#include<fstream>

using namespace std;



double espo(double x, double lambda=1){
	return exp(- lambda*tan(x*M_PI/2))/((1+pow(tan(x*M_PI/2),2))*M_PI/2);}

double lorentz(double x, double Gamma=1, double mu=0){
	double y = tan((x-.5)*M_PI);
	//double ecce = Gamma/(M_PI*((pow(y + mu ),2) + Gamma*Gamma)*((1+pow(y,2))*M_PI/2));
	return Gamma/(M_PI*(pow(y+ mu,2)+Gamma*Gamma)*y);}


int main(){

int max = pow(10,4);
double vett[max];
double vettexp[max];
double vettlor[max];


srand(time(0));


//genero il vettore random e converto i valori nelle distribuzioni:
for(int i=0; i<max; i++){
vett[i] = ((double)rand()/INT_MAX);
vettexp[i]=espo(vett[i]);
//cout<<vettexp[i]<<endl;
vettlor[i] = lorentz(vett[i]);
cout<<vettlor[i]<<endl;
}



//probabilità esponenziale:









return 0;
}
