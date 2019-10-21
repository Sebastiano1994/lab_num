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
	//Simulation
	//for(int sig=0; sig<10; sig++){
	//for(int med=0; med<10; med++){
	cout<<"mu: "<<mu<<endl;
	cout<<"sigma (squared): "<<sigma<<endl; //sigma in realtà è sigma^2
	for(int iblk=1; iblk <= nblk; ++iblk){
	//Reset block averages
	Reset(iblk);
	//cout<<"funziona"<<endl;
	for(int istep=1; istep <= nstep; ++istep){
	Move();
	//cout<<"funziona"<<endl;
	Measure();
	Accumulate(); //Update block averages
	}
	Averages(iblk);   //Print results for current block
	}
	ConfFinal(); //Write final configuration
	mu+=.1;
	//}
	sigma+=.1;
	a = 5*sigma;
	mu=0;
	//}
	End();
	return 0;
	}





void Input(void){
  ifstream ReadInput;

  cout << "Quantum Variational Monte Carlo    " << endl;
  cout << "Boltzmann weight: |Psi|^2          " << endl << endl;
  cout << "The program uses ħ=1 and m=1 units " << endl;

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
  ReadInput.open("input.dat");

  ReadInput >> m;
  cout << "Particle mass = " << m << endl;

  ReadInput >> h;
  cout << "ħ in natural units = " << h << endl <<endl;

  ReadInput >> sigma;
  cout << "Sigma parameter (squared) = " << sigma << endl;
  
  //ReadInput >> a;
  a = 5*sigma;
  cout << "Pass = " << a << endl;

  
  ReadInput >> mu;
  cout << "Mu parameter = " << mu << endl <<endl;

  ReadInput >> nblk;
  ReadInput >> nstep;

  cout << "The program perform Metropolis moves" << endl;
  cout << "Number of blocks = " << nblk << endl;
  cout << "Number of steps in one block = " << nstep << endl << endl;
  ReadInput.close();



//Prepare arrays for measurements
  ie = 0; //Energy
 
  n_props = 1; //Number of observables

//initial configuration: choose x_0 in a reasonable place
  x_0 = rnd.Rannyu();

  cout<<"starting position: "<<x_0<<endl;
  
//Evaluate energy etc. of the initial configuration
  Measure();

//Print initial values for the potential energy and virial
  cout << "Initial energy = " << walker[ie] << endl;

//install vector for histogram
  int max=nstep*nblk;
  Psi2 = new double[max];
  count=0;

}



//Metropolis step
	void Move(){
	double x;
	//try a step in [-a;+a] interval:
	x = x_0+((rnd.Rannyu()-.5)*a);
	//Metropolis algorithm:
	if(pow(W_f(x)/W_f(x_0),2)>=abs(rnd.Rannyu())){
	accepted++;
	attempted++;
	x_0 = x;
	}
	else attempted++;
	Psi2[count] = x_0;
	cout<<x_0<<endl;
	count++;
	}

//minus wave function:
	double W_fl(double x){
	return exp(-(x-mu)*(x-mu)/(2*sigma));
	}

//plus  wave function:
	double W_fr(double x){
	return exp(-(x+mu)*(x+mu)/(2*sigma));
	}



//Wave function
	double W_f(double x){
	return W_fl(x) + W_fr(x);
	}



//Potential energy (function)
	double V_f(double x){
	return (x*x - 2.5)*x*x;
	}






//Hamiltonian operator:
	double H(double x){
	return -h*h/(2*m)*((x+mu)*(x+mu)/sigma-1)/sigma*W_fr(x) -h*h/(2*m)*((x-mu)*(x-mu)/sigma-1)/sigma*W_fl(x) + V_f(x);
	}






//Measure actual results:
	void Measure(){
	int bin;
	
	walker[ie] = H(x_0);
	}


	void Reset(int iblk){
	
	

	if(iblk == 1){
	//for(int i=0; i<n_props; ++i){
	glob_av[ie] = 0;
	glob_av2[ie] = 0;
	}

	//for(int i=0; i<n_props; ++i){
	blk_av[ie] = 0;
	blk_norm = 0;
	attempted = 0;
	accepted = 0;
	}

//Update block averages
	void Accumulate(void){

	//for(int i=0; i<n_props; i++){
	blk_av[ie] = blk_av[ie] + walker[ie];
	blk_norm = blk_norm + 1.0;
	}


	void Averages(int iblk){

	ofstream Ene;
	const int wd=12;

	cout << "Block number " << iblk << endl;
	cout << "Acceptance rate " << accepted/attempted << endl << endl;

	if(accepted/attempted<=0.9){
	Ene.open("output_E",ios::app);
	stima_e = blk_av[ie]/blk_norm; //Energy
	glob_av[ie]  += stima_e;
	glob_av2[ie] += stima_e*stima_e;
	err_e=Error(glob_av[ie],glob_av2[ie],iblk);  //iblk perché è una running average (della varianza)
	Ene << setw(wd) << iblk <<  setw(wd) << stima_e << setw(wd) << glob_av[ie]/(double)iblk << setw(wd) << err_e << endl;
	cout<<"System Energy: "<<glob_av[ie]/(double)iblk<<endl;
	Ene.close();

	}

	cout << "----------------------------" << endl << endl;
	}


	void ConfFinal(void){
	ofstream WriteConf, All, Histo;
	const int wd=12;

	cout << "Print final configuration to file config.final " << endl << endl;

	rnd.SaveSeed();

	All.open("Info.csv",ios::app);
	//All << setw(wd) << "sigma" << setw(wd) << "mu" <<setw(wd)<< "E" << endl;
	All << setw(wd) << sigma <<"," << setw(wd) << mu <<"," << setw(wd) << glob_av[ie]/(double)nblk << endl;
	cout<<"Final energy: "<<glob_av[ie]/(double)nblk<<endl<<endl;
	All.close();
	
	Histo.open("Histo.csv",ios::app);
	for(int i=0; i<nstep*nblk; i++) Histo << setw(wd) << Psi2[i] << endl;
	cout<<"Final energy: "<<glob_av[ie]/(double)nblk<<endl<<endl;
	Histo.close();
	

	}

	void End(void){
		delete Psi2;}


double Error(double sum, double sum2, int iblk){
    return sqrt((sum2/(double)iblk - pow(sum/(double)iblk,2))/(double)iblk);
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
