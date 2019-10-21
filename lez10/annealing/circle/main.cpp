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
	//mixing (to create genetic variety)
	for(int st=0; st<500; st++) Mix();
	cout<<"End of 'genetic' mixing"<<endl;
	//annealing
	while(i<nstep){
	Shuffle();
	if(i % 10==0) {end[ind]=min(q,npop); end[ind+1]=beta; ind+=2;}
	beta+=.1;
	i++;}
	ConfFinal();
	return 0;
	}


	
//Input function (initialize):
	void Input(void){
	cout << "SIMULATED ANNEALING FOR COMBINATORIAL OPTIMIZATION    " << endl;
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
	
	//Read input informations
	ifstream ReadInput;
	ReadInput.open("input.dat");

	ReadInput >> nstep;
	cout << "number of steps = " << nstep << endl;
	
	ReadInput >> beta;
	cout << "initial value of beta = " << beta << endl;


	//install coord grid:
	//double y_0=pow(sqrt(2), -1);
	coord = new double*[n_cities];
	for(int i=0; i<n_cities; i++){
	coord[i] = new double[i];
	double x_0 = (rnd.Rannyu()*2*M_PI);
	coord[i][0]=cos(x_0);
	coord[i][1]=sin(x_0);
	}


	cout<<endl;
	
	
	//export cities coords:
	ofstream out;
	out.open("positions.csv");
	for(int i=0; i<n_cities; i++) {out<<coord[i][0]<<","<<setw(12)<<coord[i][1]<<endl;}
	out.close();	
	
	
	//install vector for final values:
	maximum=nstep*.2;
	end = new double[maximum];

	//install population (and q vector):
	q = new double[npop];
	population = new int*[npop];
	for(int i=0; i<npop; i++){
	population[i] = new int[n_cities];
	for(int j=0; j<n_cities; j++) population[i][j] = j;}


	}


	//Metropolis for mutations:
	void Metro_mut(int k){
	//generate k-th chromosome copy, evaluate transformation cost then apply Metropolis: if advantageous, the transformation will act on the chromosome too
	int l = (int)abs(rnd.Rannyu()*(n_cities-1));
	int p = (int)abs(rnd.Rannyu()*(n_cities-1));
	double r = rnd.Rannyu();
	int* w = new int[n_cities];
	for(int i=0; i<n_cities; i++) w[i] = population[k][i];
	mutation(l,p,w);
	if(exp(Boltzmann(L(k), L(w)))>=r) mutation(k, l ,p);
	delete w;
	}
	
	
	//Metropolis for cross-over:
	void Metro_cr(int k){

	int p = (int)abs(rnd.Rannyu()*(n_cities-1));
	int l = (int) rnd.Rannyu()*npop;
	double r = rnd.Rannyu();
	int* w = new int[n_cities];
	for(int i=0; i<n_cities; i++) w[i] = population[k][i];
	cross(w,l,p);
	if(exp(Boltzmann(L(k), L(w)))>=r) cross(k, l, p);
	delete w;
	}
	
	
	//Metropolis for mirroring:
	void Metro_mir(int k){
	
	int l = (int)abs(rnd.Rannyu()*(n_cities-1));
	int p = (int)abs(rnd.Rannyu()*(n_cities-1));
	double r = rnd.Rannyu();
	int* w = new int[n_cities];
	for(int i=0; i<n_cities; i++) w[i] = population[k][i];
	mirror(l,p,w);
	if(exp(Boltzmann(L(k), L(w)))>=r) mirror(k, l ,p);
	delete w;
	}
	
	
	
	
	
	
	
	//Evaluation of Boltzmann's distribution argument for exp (valid for all transformations)
	double Boltzmann(double L1, double L2){
	return beta*(L1-L2);
	}
	



	//cost function for a gene:
	double L(int k){
	double sum=0;
	//sum from 0 to 29 all i-(i+1) distances:
	for(int i=0; i<n_cities-1; i++) sum+= pow(coord[population[k][i]][1]-coord[population[k][i+1]][1],2) + pow(coord[population[k][i]][0]-coord[population[k][i+1]][0],2);
	//final sum between 1st and last term:
	return sum+pow(coord[population[k][0]][1]-coord[population[k][n_cities-1]][1],2) + pow(coord[population[k][0]][0]-coord[population[k][n_cities-1]][0],2);}


	
	//cost function for a generic vector of positions w:
	double L(int* w){
	double sum=0;
	//sum from 0 to 29 all i-(i+1) distances:
	for(int i=0; i<n_cities-1; i++) sum+= pow(coord[w[i]][1]-coord[w[i+1]][1],2) + pow(coord[w[i]][0]-coord[w[i+1]][0],2);
	//final sum between 1st and last term:
	return sum+pow(coord[w[0]][1]-coord[w[n_cities-1]][1],2) + pow(coord[w[0]][0]-coord[w[n_cities-1]][0],2);}
	
	
	


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

	
	int minimo(int l, int p){
	if(p<=l) return p;
	else return l;
	}
	
	int massimo(int l, int p){
	if(p>=l) return p;
	else return l;
	}
	
	
	
	double min (double* v, int n){
	unsigned int i;
	int p;
	double m;	
	for (i=0; i<n; i++){
	if (i==0){
	m=v[i];
	}
	if (v[i]<m){
	m=v[i];
	}}
	return m;}
	
	
	int argmin (double* v, int n){
	unsigned int i;
	int p;
	double m;	
	for (i=0; i<n; i++){
	if (i==0){
	m=v[i];
	}
	if (v[i]<m){
	m=v[i];
	p=i;
	}
	}
	return p;}


	//mutation for a generic vector
	void mutation(int l, int p, int* w){
	scambio(w[l], w[p]);
	}

	//mutation for genes:	
	void mutation(int k, int l, int p){
	scambio(population[k][l], population[k][p]);
	}

	
	
	//cross-over between generic vector v and a gene (with label k):
	void cross(int* v, int k, int p){
	for(int j=0; j<n_cities; j++){
	bool tr=true;
	for(int i=0; i<p; i++){
	if(v[i]==population[k][j]) tr=false;
	}
	if(tr) {
	v[p]=population[k][j];
	p++;}}
	}
	
	//cross-over for genes:	
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
	
	
	//mirroring for genes:
	void mirror(int s, int l, int k){
	int max = abs(s-l);
	double* w = new double[max];
	for(int i=0; i<max; i++) w[i] = population[k][i+s];
	for(int i=s; i<l; i++) {
	population[k][i] = w[max-1];
	max--;
	}
	delete w;
	}
	
	
	//mirroring for generic vector:
	void mirror(int s, int l, int* v){
	int max = abs(s-l);
	int* w = new int[max];
	for(int i=0; i<max; i++) w[i] = v[i+s];
	for(int i=s; i<l; i++) {
	v[i] = w[max-1];
	max--;
	}
	delete w;
	}
	
	
	
	//Random shuffles (for genetic recombining):
	void Mix(){
	for(int i=0; i<npop; i++) {
	int p = abs(rnd.Rannyu()*n_cities);
	int s = abs(rnd.Rannyu()*n_cities);
	int k = abs(rnd.Rannyu()*npop);
	int m = abs(rnd.Rannyu()*n_cities);
	mutation(i,s,m);
	cross(i,k,p);
	mirror(p,s,i);
	q[i]=L(i);}
	}
	
	
	//Shuffle with mutations:
	void Shuffle(){
	for(int i=0; i<npop; i++) {
	Metro_mut(i);
	Metro_cr(i);
	Metro_mir(i);
	q[i]=L(i);}
	}


	void ConfFinal(){
	fstream expo;
	expo.open("dati.dat",ios::app);
	for(int i=0; i<maximum; i+=2) expo<<setw(6)<<end[i]<<endl;
	expo.close();
	
	int k = argmin(q,npop);
	//exporting best configuration
	ofstream out;
	out.open("conf_final.csv");
	cout<<L(k)<<endl;
	for(int j=0; j<n_cities; j++) out<<population[k][j]<<endl;
	out.close();
	
	delete end;
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
