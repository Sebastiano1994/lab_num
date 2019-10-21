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
#include "Monte_Carlo_ISING_1D.h"

using namespace std;

int main()
{
for(int l=0; l<30; l++){
  Input(l); //Inizialization
  //temp = 0.2 + (double)l*.1;
  //beta = 1/temp;
  for(int iblk=1; iblk <= nblk; ++iblk) //Simulation
  {
    Reset(iblk);   //Reset block averages
    for(int istep=1; istep <= nstep; ++istep)
    {
      Move(metro);
      Measure();
      Accumulate(); //Update block averages
    }
    Averages(iblk);   //Print results for current block
  }
  ConfFinal(l); //Write final configuration
}
  return 0;
}


void Input(int k)
{
  ifstream ReadInput;

  cout << "Classic 1D Ising model             " << endl;
  cout << "Monte Carlo simulation             " << endl << endl;
  cout << "Nearest neighbour interaction      " << endl << endl;
  cout << "Boltzmann weight exp(- beta * H ), beta = 1/T " << endl << endl;
  cout << "The program uses k_B=1 and mu_B=1 units " << endl;

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

  ReadInput >> temp;
  beta = 1.0/(temp + (double)k*.1);
  cout << "Temperature = " << temp + (double)k*.1<< endl;

  ReadInput >> nspin;
  cout << "Number of spins = " << nspin << endl;

  ReadInput >> J;
  cout << "Exchange interaction = " << J << endl;

  ReadInput >> h;
  cout << "External field = " << h << endl << endl;
  
  ReadInput >> metro; // if=1 Metropolis else Gibbs

  ReadInput >> nblk;

  ReadInput >> nstep;

  ReadInput >> equil;

  if(metro==1) cout << "The program perform Metropolis moves" << endl;
  else cout << "The program perform Gibbs moves" << endl;
  cout << "Number of blocks = " << nblk << endl;
  cout << "Number of steps in one block = " << nstep << endl << endl;
  ReadInput.close();



//initial configuration
  if(equil==0){
  for (int i=0; i<nspin; ++i){
    if(rnd.Rannyu() >= 0.5) s[i] = 1;
    else s[i] = -1;
  }
  }

  else{
  ifstream Apri;
  Apri.open("config.final");
  for(int i=0; i<nspin; i++) Apri >> s[i];
  Apri.close();
  }

  //for(int i=0; i<(int)nstep/3; i++) Move(metro);


//Prepare arrays for measurements
  iu = 0; //Energy
  ic = 1; //Heat capacity
  im = 2; //Magnetization
  ix = 3; //Magnetic susceptibility
 
  n_props = 4; //Number of observables


  
  
//Evaluate energy etc. of the initial configuration
  Measure();

//Print initial values for the potential energy and virial
  cout << "Initial energy = " << walker[iu]/(double)nspin << endl;
}


void Move(int metro)
{
  int o;
  double p, energy_old, energy_new, sm; //Ingredienti x il Metropolis
  double energy_up, energy_down;	//Ingredienti x il Gibbs

  for(int i=0; i<nspin; ++i)
  {
  //Select randomly a spin (for C++ syntax, 0 <= o <= nspin-1)
    o = (int)(rnd.Rannyu()*nspin);
    //cout<<o<<endl;
    if(metro==1) //Metropolis
    {
    if(exp(beta*Boltzmann(s[o], o))>=rnd.Rannyu()) {
    accepted++;
    attempted++;
    s[o]=-s[o];
    }
    else attempted++;
// INCLUDE YOUR CODE HERE, I think I've done it
    }
    else //Gibbs sampling
    {
    accepted++;
    attempted++;

    if(1/(1+exp(beta*Boltzmann(+1, o))>=rnd.Rannyu()))  s[o]=+1;
    else   s[o]=-1;

// INCLUDE YOUR CODE HERE, to controll it indeed
    }
  }
}

double Boltzmann(int sm, int ip)
{
  double ene = -J *2* sm * ( s[Pbc(ip-1)] + s[Pbc(ip+1)] ) - h * sm; //sm è la direzione dello spin flippato, ip il suo indice
  return ene;
}

void Measure()
{
  int bin;
  double u = 0.0, m = 0.0, u2 = 0.0, chi = 0.0;

//cycle over spins
  for (int i=0; i<nspin; ++i)
  {
     u += -J * s[i] * s[Pbc(i+1)] - 0.5 * h * (s[i] + s[Pbc(i+1)]); //h=0 o h=0.002 viene stabilito nel file input.dat
     m += s[i];
  }
  //procedo con le misure quadratiche:
  chi = m*m;
  u2  = u*u;
  //misuro l'energia e la magnetizzazione totali nel vettore:
  walker[iu] = u;
  walker[ic] = u2;
  walker[im] = m;
  walker[ix] = chi;

}


void Reset(int iblk) //Reset block averages, iblk è il numero del block cui mi riferisco
{
   
   if(iblk == 1)
   {
       for(int i=0; i<n_props; ++i)
       {
           glob_av[i] = 0;
           glob_av2[i] = 0;
       }
   }

   for(int i=0; i<n_props; ++i)
   {
     blk_av[i] = 0;
   }
   blk_norm = 0;
   attempted = 0;
   accepted = 0;
}


void Accumulate(void) //Update block averages
{

   for(int i=0; i<n_props; ++i)
   {
     blk_av[i] = blk_av[i] + walker[i];
   }
   blk_norm = blk_norm + 1.0; //aumento la norma dei blocchi: ho più misure, devo aumentare il numero al denominatore (blk_norm)
}


void Averages(int iblk) //Print results for current block
{
    
   ofstream Ene, Heat, Mag, Chi;
   const int wd=12;
   string u = "output_ene.csv";
   string c = "output_heat.csv";
   string m = "output_mag.csv";
   string x = "output_chi.csv";
   /*stringstream su, sc, sm, sx;
   su << u <<"_"<<temp;
   u = su.str();
   sc << c <<"_"<<temp;
   c = sc.str();
   sm << m <<"_"<<temp;
   m = sm.str();
   sx << x <<"_"<<temp;
   x = sx.str();*/
 
    cout << "Block number " << iblk << endl;
    cout << "Acceptance rate " << accepted/attempted << endl << endl;
    
    
    if(h==0.0){
    Ene.open(u,ios::app);
    stima_u = blk_av[iu]/blk_norm/(double)nspin; //Energy
    glob_av[iu]  += stima_u;
    glob_av2[iu] += stima_u*stima_u;
    err_u=Error(glob_av[iu],glob_av2[iu],iblk);  //iblk perché è una running average (della varianza)
    Ene << setw(wd) << iblk<<"," <<  setw(wd) << stima_u<<"," << setw(wd) << glob_av[iu]/(double)iblk <<","<< setw(wd) << err_u << endl;
    Ene.close();

    Heat.open(c,ios::app);
    stima_c = (blk_av[ic] - blk_av[iu]*blk_av[iu]/blk_norm)*beta*beta/blk_norm; //blk_av[ic]/blk_norm/(double)nspin; //Energy
    glob_av[ic]  += stima_c;
    glob_av2[ic] += stima_c*stima_c;
    err_c=Error(glob_av[ic],glob_av2[ic],iblk);
    Heat << setw(wd) << iblk<<"," <<  setw(wd) << stima_c<<"," << setw(wd) << glob_av[ic]/(double)iblk<<"," << setw(wd) << err_c << endl;
    Heat.close();

    Chi.open(x,ios::app);
    stima_x = blk_av[ix]/blk_norm/(double)nspin; //Suscettibilità
    glob_av[ix]  += stima_x;
    glob_av2[ix] += stima_x*stima_x;
    err_x=Error(glob_av[ix],glob_av2[ix],iblk);
    Chi<< setw(wd) << iblk <<"," <<  setw(wd) << stima_x<<"," << setw(wd) << glob_av[ix]/(double)iblk<<"," << setw(wd) << err_x << endl;
    Chi.close();
    }

    else if(h==0.02){
    Mag.open("output_mag.csv",ios::app);
    stima_m = blk_av[im]/blk_norm/(double)nspin; //Magnetizzazione
    glob_av[im]  += stima_m;
    glob_av2[im] += stima_m*stima_m;
//cout<<glob_av2[im]/(double)nblk<<endl;
//cout<<pow(glob_av[im]/(double)nblk,2)<<endl;
//cout<<glob_av2[im]/(double)nblk-pow(glob_av[im]/(double)nblk,2)<<endl;
    err_m=Error(glob_av[im],glob_av2[im],nblk);
    Mag<< setw(wd) << iblk <<","<<  setw(wd) << stima_m<<"," << setw(wd) << glob_av[im]/(double)iblk<<"," << setw(wd) << err_m << endl;
    Mag.close();
    }

    

// INCLUDE YOUR CODE HERE, I think I've done it

    cout << "----------------------------" << endl << endl;
}


void ConfFinal(int k)
{
  if(h==0.0){
  ofstream WriteConf, All;
  const int wd=12;

  cout << "Print final configuration to file config.final " << endl << endl;
  WriteConf.open("config.final");
  for (int i=0; i<nspin; ++i)
  {
    WriteConf << s[i] << endl;
  }
  WriteConf.close();

  rnd.SaveSeed();
  
  All.open("Info.csv",ios::app);
  //All << setw(wd) << "T" << setw(wd) << "U" <<setw(wd)<< "C" << setw(wd) << "X" << endl;
  All << setw(wd) << temp + (double)k*.1<<"," << setw(wd) << glob_av[iu]/(double)nblk <<"," << setw(wd) << glob_av[ic]<<","<< setw(wd)<< glob_av[ix] << endl;
  All.close();}

  else if(h==0.02){
  ofstream WriteConf, All;
  const int wd=12;

  cout << "Print final configuration to file config.final " << endl << endl;
  WriteConf.open("config.final");
  for (int i=0; i<nspin; ++i)
  {
    WriteConf << s[i] << endl;
  }
  WriteConf.close();

  rnd.SaveSeed();
  
  All.open("Info_m.csv",ios::app);
  //All << setw(wd) << "T," << setw(wd) << "M"<< endl;
  All << setw(wd) << temp + (double)k*.1 <<"," << setw(wd) << glob_av[im]/(double)nblk << endl;
  All.close();}
	
  }





int Pbc(int i)  //Algorithm for periodic boundary conditions
{
    if(i >= nspin) i = i - nspin;
    else if(i < 0) i = i + nspin;
    return i;
}

double Error(double sum, double sum2, int iblk)
{
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
