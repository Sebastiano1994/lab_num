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
	//double y_0=pow(sqrt(2), -1);
	coord = new double*[n_cities];
	for(int i=0; i<n_cities; i++){
	coord[i] = new double[i];
	double x_0 = (rnd.Rannyu()*2*M_PI);
	coord[i][0]=cos(x_0);
	coord[i][1]=sin(x_0);
	}


	cout<<endl;


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
	return sum+pow(coord[population[k][0]][1]-coord[population[k][n_cities-1]][1],2) + pow(coord[population[k][0]][0]-coord[population[k][n_cities-1]][0],2);}



	void selection_sort(){
	int i;
	int t;
	for(int j=0; j<npop; j++) q[j]=L(j);
	for (i=0; i<npop; i++) {
	t=minimo(q, i, npop);
	scambio(sort[i], sort[t]);
	scambio_d(q[i], q[t]);
	//cout<<sort[i]<<setw(20)<<q[i]<<setw(20)<<L(i)<<endl;
	}}
	
	
	void permutaz(double *v, int k){
	
	for(int i=0; i<k; i++) scambio(v[i], v[i+1]);
	
	
	}

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

	
	int minimo (double* v, int inizio, int n){
	unsigned int i;
	int p;
	double m;	
	for (i=inizio; i<n; i++){
	if (i==inizio){
	m=v[i];
	p=i;}
	if (v[i]<m){
	m=v[i];
	p=i;}
	}
	return p;}



	void mutation(int k){
	int i = (int)(abs(rnd.Rannyu())*n_cities);
	int j = (int)(abs(rnd.Rannyu())*n_cities);
	scambio(population[k][i], population[k][j]);
	}

	void cross(int i){
	int l = (int)(rnd.Rannyu()*n_cities);
	for(int j=l; j<n_cities; j++) scambio(population[i][j], population[i+1][j]);
	}
	
	
	//Shuffle with mutations and crossings:
	void Shuffle(){
	//crossings:
	//for(int i=(int)npop*.25; i<(int)npop*.75; i+=2) cross(sort[i]);
	//mutations:
	for(int i=(int)npop*.5; i<npop; i++){
	//cout<<"Acting on "<<sort[i]<<endl;
	mutation(sort[i]);}
	for(int i=0; i<npop; i++) sort[i]=i;
	//re-order vector:
	selection_sort();
	end[ind]=q[0];
	end[ind+1]=q[1];
	ind+=2;
	//print:
	//for(int i=0; i<npop; i++){
	//cout<<"Popolazione "<<sort[i]<<": ";
	//for(int j=0; j<n_cities; j++) {cout<<population[sort[i]][j]<<setw(4); }
	//sort[i]=i;
	//cout<<setw(15)<<q[i]<<endl;
	//}
	//cout<<endl<<endl;
	}


	void ConfFinal(){
	fstream expo;
	expo.open("dati.dat",ios::app);
	for(int i=0; i<maximum; i+=2) expo << setw(3) << end[i] << setw(12) << end[i+1] << endl;
	expo.close();
	
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
