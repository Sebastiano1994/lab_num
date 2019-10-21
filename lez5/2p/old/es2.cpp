#include<iostream>
#include<cstdlib>
#include<ctime>
#include<climits>
#include<cmath>
#include<fstream>
#include"media.h"

using namespace std;





double X(double th, double ph){
	return cos(ph)*sin(th);}

double Y(double th, double ph){
	return sin(th)*sin(ph);}

double Z(double th){
	return cos(th);}





int main(){


int M=pow(10,4);
int vec_d[M][3]; //il pedice _d sta per discreto
int pos_fin_d[3] = {0,0,0};

//limite al continuo:
double* theta = new double[M];  //angolo polare
double* phi = new double[M];	//angolo radiale
double vec_c[M][3];              //vettore delle coordinate cartesiane; il pedice _c indica il limite al continuo
double pos_fin_c[3] = {0,0,0};


srand(time(0));


//genero il vettore discreto random:
for(int j=0; j<3; j++){
	for(int i=0; i<M; i++){
		//vec_d[i][j] = (((int)rand()/INT_MAX)*2-1);
		if(((double)rand()/INT_MAX)-.5<0) vec_d[i][j]=-1;
		else vec_d[i][j]=1;}}

//cout<<vec_d[M-2][1]<<endl;
//cout<<vec_d[M-2][2]<<endl;
//cout<<vec_d[M-2][3]<<endl;



cout<<"Posizione finale nel discreto: "<<endl;
cout<<"(";
for(int j=0; j<3; j++){
	for(int i=0; i<M-2; i++){
		pos_fin_d[j]+=vec_d[i][j];}
	cout<<pos_fin_d[j]<<", ";}
cout<<")"<<endl;


//genero il vettore continuo random:
for(int i=0; i<M; i++){
	phi[i] = (((double)rand()/INT_MAX)*2*M_PI);
	theta[i] = (((double)rand()/INT_MAX)*M_PI);
	vec_c[i][0] = X(theta[i], phi[i]);
	vec_c[i][1] = Y(theta[i], phi[i]);
	vec_c[i][2] = Z(theta[i]);
	pos_fin_c[0]+=vec_c[i][0];
	pos_fin_c[1]+=vec_c[i][1];
	pos_fin_c[2]+=vec_c[i][2];}



cout<<"Coordinate finali nel continuo: "<<endl;
cout<<"("<<pos_fin_c[0]<<", "<<pos_fin_c[1]<<", "<<pos_fin_c[2]<<")"<<endl;

//cout<<"theta finale: "<<theta[M-1]<<endl;
//cout<<"phi finale: "<<phi[M-1]<<endl;






delete theta;
delete phi;
 






return 0;
}















