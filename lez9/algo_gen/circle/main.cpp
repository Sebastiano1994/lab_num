/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

#include <iostream>
#include <fstream>
#include <ostream>
#include <cmath>
#include <iomanip>
#include <sstream>
#include "main.h"

using namespace std;

	int main(){ 
	Input(); //Inizialization
	int i=0;
	while(i<nstep){
	Shuffle();
	i++;}
	ConfFinal();
	return 0;
	}


	
//Input function (initialize):	
	void Input(void){
	cout << "GENETIC ALGORITHMS FOR COMBINATORIAL OPTIMIZATION    " << endl;
	cout << "NUMBER OF CITIES: " << n_cities << endl;
	cout << "POPULATION WIDTH: " << npop << endl ;
	cout << "NUMBER OF STEPS:  " << nstep << endl<< endl;

	//Read seed for random numbers
	int p1, p2;
	ifstream Primes("Primes");
	Primes >> p1 >> p2 ;
	Primes.close();

	ifstream input("seed.in");
	input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
	rnd.SetRandom(seed,p1,p2);
	input.close();

	//install coord grid:
	coord = new double*[n_cities];
	for(int i=0; i<n_cities; i++){
	coord[i] = new double[i];
	double x_0 = (rnd.Rannyu()*2*M_PI);
	coord[i][0]=cos(x_0);
	coord[i][1]=sin(x_0);}

	cout<<endl;
	cout<<endl;
	cout<<"Random cities generated on a circle line"<<endl<<endl;
	
	//export cities coords:
	ofstream out;
	out.open("positions.csv");
	for(int i=0; i<n_cities; i++) {out<<coord[i][0]<<","<<setw(12)<<coord[i][1]<<endl;} //cout<<coord[i][0]<<","<<setw(12)<<coord[i][1]<<endl; }
	out.close();
	
	//install population (and sort and q vector):
	sort = new int[npop];
	q = new double[npop];
	population = new int*[npop];
	for(int i=0; i<npop; i++){
	population[i] = new int[n_cities];
	for(int j=0; j<n_cities; j++){
	population[i][j] = j;}
	sort[i]=i;}
	}










	
	double L(int k){
	double sum=0;
	//sum from 1 to 29 all i-(i+1) distances:
	for(int i=0; i<n_cities-1; i++) sum+= pow(coord[population[k][i]][1]-coord[population[k][i+1]][1],2) + pow(coord[population[k][i]][0]-coord[population[k][i+1]][0],2);
	//final sum between 1st and last term:
	return sqrt(sum+pow(coord[population[k][0]][1]-coord[population[k][n_cities-1]][1],2) + pow(coord[population[k][0]][0]-coord[population[k][n_cities-1]][0],2));}



	

	void scambio_d (double &a, double &b){
	double c;
	c=a;
	a=b;
	b=c;}


	void scambio (int &a, int &b) {
	int c;
	c=a;
	a=b;
	b=c;}

	
	
	
	double min (double* v, int inizio, int n){
	unsigned int i;
	int p;
	double m;	
	for (i=inizio; i<n; i++){
	if (i==inizio){
	m=v[i];
	}
	if (v[i]<m){
	m=v[i];
	}
	}
	return m;}
	
	double argmin (double* v, int inizio, int n){
	unsigned int i;
	int p;
	double m;	
	for (i=inizio; i<n; i++){
	if (i==inizio){
	m=v[i];
	}
	if (v[i]<m){
	m=v[i];
	p=i;
	}
	}
	return p;}


	//mutations
	void mutation(int k){
	int i = (int)(abs(rnd.Rannyu())*n_cities);
	int j = (int)(abs(rnd.Rannyu())*n_cities);
	//int l = (int)(abs(rnd.Rannyu())*n_cities);
	//int m = (int)(abs(rnd.Rannyu())*n_cities);
	scambio(population[k][i], population[k][j]);
	//scambio(population[k][l], population[k][m]);
	}
	
	void slice(int p, int l){
	double* w = new double[p];
	for(int i=0; i<p; i++) w[i] = population[l][i];
	for(int i=0; i<n_cities-p; i++) population[l][i] = population[l][i+p];
	for(int i=n_cities-p; i<n_cities; i++) population[l][i] = w[i-n_cities+p];
	delete w;
	}
	
	void mirror(int s, int l, int u){
	int max = abs(s-l);
	double* w = new double[max];
	for(int i=0; i<max; i++) w[i] = population[u][i+s];
	for(int i=s; i<l; i++) {
	population[u][i] = w[max-1];
	max--;
	}
	delete w;
	}
	
	//cross-over:	
	void cross(int l, int m, int p){
	for(int j=0; j<n_cities; j++){
	bool tr=true;
	for(int i=0; i<p; i++){
	if(population[l][i]==population[m][j]) tr=false;
	}
	if(tr) {
	population[l][p]=population[m][j];
	p++;}}
	}


	
	
	
	//Shuffle with mutations and crossings:
	void Shuffle(){
	//cout<<"works"<<endl;
	double extreme = min(q,0, npop);
	//cout<<extreme<<endl;
	for(int i=0; i<npop; i++){
	if (L(i)>extreme) {
	mutation(i);
	}
	else {save=L(i);}
	int p = abs(rnd.Rannyu()*npop);
	int k = abs(rnd.Rannyu()*npop);
	int s = abs(rnd.Rannyu()*n_cities);
	int m = abs(rnd.Rannyu()*n_cities);
	if(L(p)>extreme) {
	cross(p, k, s);
	slice(s, p);
	mirror(s,m,p);
	}
	}
	//save minimum
	for(int j=0; j<npop; j++) q[j]=L(j);
	end[ind]=extreme;
	ind++;
	}


	void ConfFinal(){
	fstream expo;
	expo.open("dati.dat",ios::app);
	for(int i=0; i<maximum; i++) expo<<setw(6)<<end[i]<<endl;
	expo.close();
	
	
	//exporting best configuration
	ofstream out;
	out.open("conf_final.csv");
	for(int i=0; i<npop; i++){
	if (L(i)==save){
	for(int j=0; j<n_cities; j++) out<<population[i][j]<<endl;
	break;
	}
	}
	out.close();
	
	
	delete sort;
	delete population;
	delete coord;
	}
	





/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
