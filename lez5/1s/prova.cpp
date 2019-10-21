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


int M=pow(10,2);  //total steps
int N=pow(10,2);  //numero di blocchi
int S=pow(10,4);  //numero totale delle simulazioni
int vecx_d[M][S]; //il pedice _d sta per discreto
int vecy_d[M][S];
int vecz_d[M][S];
int pos_fin_d[3] = {0,0,0};



double x=0;
double y=0;
double z=0;

double pos[3];

//limite al continuo:
double* theta = new double[M];  //angolo polare
double* phi = new double[M];	//angolo radiale 
//vettore delle coordinate cartesiane: il pedice _c indica il limite al continuo:
//coordinate x
double** vecx_c = new double*[M];
for(int i=0; i<M; i++) vecx_c[i] = new double[S];
//coordinate y
double** vecy_c = new double*[M];
for(int i=0; i<M; i++) vecy_c[i] = new double[S];
//coordinate z
double** vecz_c = new double*[M];
for(int i=0; i<M; i++) vecz_c[i] = new double[S];

double R_m[M];        //vettore delle medie sulle traiettorie
double pos_fin_c[3] = {0,0,0};



srand(time(0));


//genero il vettore discreto random:
/*
	for(int i=0; i<M; i++){
	for(int j=0; j<3; j++){
	//vec_d[i][j] = (((int)rand()/INT_MAX)*2-1);
	if(((double)rand()/INT_MAX)-.5<0) pos[j]=-1;
	else pos[j]=1;
	vecx_d[i][tr]=pos[i];
	}}*/
	

/*
//genero il vettore continuo random:
	//ciclo sulle traiettorie:
	for(int tr=0; tr<S; tr++){
	//ciclo sugli step:
	for(int i=0; i<M; i++){
	for(int k=0; k<3; k++){
	if(((double)rand()/INT_MAX)-.5<0) pos[k]=-1;
	else pos[k]=1;}
	vecx_d[i][tr] = pos[0];
	vecy_d[i][tr] = pos[1];
	vecz_d[i][tr] = pos[2];
	//cout<<vecx_c[i][tr]<<endl;
	}}




//cout<<vec_d[M-2][1]<<endl;
//cout<<vec_d[M-2][2]<<endl;
//cout<<vec_d[M-2][3]<<endl;


	for(int j=0; j<S; j++){
	for(int i =0; i<M; i++){
	pos_fin_d[0]+=vecx_d[i][j];
	pos_fin_d[1]+=vecy_d[i][j];
	pos_fin_d[2]+=vecz_d[i][j];}}



cout<<"Posizione finale nel discreto: "<<endl;
cout<<"(";
for(int j=0; j<3; j++){
	for(int i=0; i<M-2; i++){
		pos_fin_d[j]+=vec_d[i][j];}
	cout<<pos_fin_d[j]<<", ";}
cout<<")"<<endl;

*/

x=0;
y=0;
z=0;





//genero il vettore continuo random:
	//ciclo sulle traiettorie:
	for(int tr=0; tr<S; tr++){
	//ciclo sugli step:
	for(int i=0; i<M; i++){
	phi[i] = (((double)rand()/INT_MAX)*2*M_PI);
	theta[i] = (((double)rand()/INT_MAX)*M_PI);
	vecx_c[i][tr] = X(theta[i], phi[i]);
	vecy_c[i][tr] = Y(theta[i], phi[i]);
	vecz_c[i][tr] = Z(theta[i]);
	//cout<<vecx_c[i][tr]<<endl;
	}}
	
	
	for(int j=0; j<S; j++){
	for(int i =0; i<M; i++){
	pos_fin_c[0]+=vecx_c[i][j];
	pos_fin_c[1]+=vecy_c[i][j];
	pos_fin_c[2]+=vecz_c[i][j];}}



cout<<"Coordinate finali nel continuo (di una generica traiettoria): "<<endl;
cout<<"("<<pos_fin_c[0]/S<<", "<<pos_fin_c[1]/S<<", "<<pos_fin_c[2]/S<<")"<<endl;

	



//cout<<"theta finale: "<<theta[M-1]<<endl;
//cout<<"phi finale: "<<phi[M-1]<<endl;



delete theta;
delete phi;

cout<<"Tutto ok"<<endl;






x=0;
y=0;
z=0;


for(int i=0; i<M; i++){
	x += media(vecx_c, i, S, N);
	y += media(vecy_c, i, S, N);
	z += media(vecz_c, i, S, N);
	
	//cout<<y<<endl;
	R_m[i] = sqrt(x*x + y*y + z*z);
	//cout<<R_m[i]<<endl;
	}


 




delete vecx_c;
delete vecy_c;
delete vecz_c;




return 0;
}















