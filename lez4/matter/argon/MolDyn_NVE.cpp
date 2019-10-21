/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
#include <stdlib.h>     // srand, rand: to generate random number
#include <iostream>     // cin, cout: Standard Input/Output Streams Library
#include <fstream>      // Stream class to both read and write from/to files.
#include <cmath>        // rint, pow
#include "MolDyn_NVE.h"

using namespace std;

int main(){ 
  Input();             //Inizialization
  int nconf = 1;
  for(int istep=1; istep <= nstep; ++istep){
     Move();           //Move particles with Verlet algorithm
     if(istep%iprint == 0) cout << "Number of time-steps: " << istep << endl;
     if(istep%10 == 0){
        Measure();     //Properties measurement
//        ConfXYZ(nconf);//Write actual configuration in XYZ format //Commented to avoid "filesystem full"! 
        nconf += 1;
     }
  }
  ConfFinal();         //Write final configuration to restart

  return 0;
}


void Input(void){ //Prepare all stuff for the simulation
  ifstream ReadInput,ReadConf;
  double ep, ek, pr, et, vir;

  cout << "Classic Lennard-Jones fluid        " << endl;
  cout << "Molecular dynamics simulation in NVE ensemble  " << endl << endl;
  cout << "Interatomic potential v(r) = 4 * [(1/r)^12 - (1/r)^6]" << endl << endl;
  cout << "The program uses Lennard-Jones units " << endl;

  seed = 1;    //Set seed for random numbers
  srand(seed); //Initialize random number generator
  
  ReadInput.open("input.dat"); //Read input

  ReadInput >> temp;
  cout<<"Temperature: "<<temp*fatt_t<<endl;


  ReadInput >> npart;
  cout << "Number of particles = " << npart << endl;

  ReadInput >> rho;
  cout << "Density of particles = " << rho << endl;
  vol = (double)npart/rho;
  cout << "Volume of the simulation box = " << vol << endl;
  box = pow(vol,1.0/3.0);
  cout << "Edge of the simulation box = " << box << endl;

  ReadInput >> rcut;
  ReadInput >> delta;
  ReadInput >> nstep;
  ReadInput >> iprint;
  ReadInput >> option;

  cout << "The program integrates Newton equations with Verlet method " << endl;
  cout << "Time step = " << delta << endl;
  cout << "Number of steps = " << nstep << endl << endl;
  ReadInput.close();

//Prepare array for measurements
  iv = 0; //Potential energy
  ik = 1; //Kinetic energy
  ie = 2; //Total energy
  it = 3; //Temperature
  n_props = 4; //Number of observables
//however, we must introduce the g(r) histogram:
  bin_size = (box/2.0)/(double)nbins;


  if(option==1){

//Read initial configuration
  cout << "Read initial configuration from file config.0 " << endl << endl;
  ReadConf.open("config.0");
  for (int i=0; i<npart; ++i){
    ReadConf >> x[i] >> y[i] >> z[i];
    x[i] = x[i] * box;
    y[i] = y[i] * box;
    z[i] = z[i] * box;
  }
  ReadConf.close();

//set g(r) bins to zero:
   for(int i=0; i<nbins; i++) g[i] = 0;



//Prepare initial velocities
   cout << "Prepare random velocities with center of mass velocity equal to zero " << endl << endl;
   double sumv[3] = {0.0, 0.0, 0.0};
   for (int i=0; i<npart; ++i){
     vx[i] = rand()/double(RAND_MAX) - 0.5;
     vy[i] = rand()/double(RAND_MAX) - 0.5;
     vz[i] = rand()/double(RAND_MAX) - 0.5;

     sumv[0] += vx[i];
     sumv[1] += vy[i];
     sumv[2] += vz[i];
   }
   for (int idim=0; idim<3; ++idim) sumv[idim] /= (double)npart;
   double sumv2 = 0.0, fs;
   for (int i=0; i<npart; ++i){
     vx[i] = vx[i] - sumv[0];
     vy[i] = vy[i] - sumv[1];
     vz[i] = vz[i] - sumv[2];

     sumv2 += vx[i]*vx[i] + vy[i]*vy[i] + vz[i]*vz[i];
   }
   sumv2 /= (double)npart;

   fs = sqrt(3 * temp / sumv2);   // fs = velocity scale factor 
   for (int i=0; i<npart; ++i){
     vx[i] *= fs;
     vy[i] *= fs;
     vz[i] *= fs;

     xold[i] = Pbc(x[i] - vx[i] * delta);
     yold[i] = Pbc(y[i] - vy[i] * delta);
     zold[i] = Pbc(z[i] - vz[i] * delta);
   }
   }



   else if(option==0){
	double vx2=0, vy2=0, vz2=0, T, alpha;
	//Read final-1 configuration (from previous simulation):
	cout << "Read final-1 configuration from file old.0 " << endl << endl;
	ReadConf.open("old.0");
	for (int i=0; i<npart; ++i){
	ReadConf >> xold[i] >> yold[i] >> zold[i];
	xold[i] = x[i] * box;
	yold[i] = y[i] * box;
	zold[i] = z[i] * box;
	}
	ReadConf.close();
	//read final configuration:
	cout << "Read final configuration from file config.final " << endl << endl;
	ReadConf.open("config.final");
	for (int i=0; i<npart; ++i){
	ReadConf >> x[i] >> y[i] >> z[i];
	x[i] = x[i] * box;
	y[i] = y[i] * box;
	z[i] = z[i] * box;
	}
	ReadConf.close();

	

	for(int i=0; i<npart; ++i){ //Verlet integration scheme

	

	vx[i] = Pbc(x[i] - xold[i])/(2.0 * delta);
	vy[i] = Pbc(y[i] - yold[i])/(2.0 * delta);
	vz[i] = Pbc(z[i] - zold[i])/(2.0 * delta);
	
	vx2+=vx[i]*vx[i];
	vy2+=vy[i]*vy[i];
	vz2+=vz[i]*vz[i];
	}
	
	//Temperature scaling:
	T=(vx2+vy2+vz2)/(3*npart);
	alpha = temp/T;
	
	//Velocities rescaling and new position computing:
	for(int i=0; i<npart; ++i){
	vx[i]*=sqrt(alpha);
	vy[i]*=sqrt(alpha);
	vz[i]*=sqrt(alpha);
	

	//first step
	xold[i] = x[i];
	yold[i] = y[i];
	zold[i] = z[i];

	x[i] = Pbc(x[i] - delta*vx[i]);
	y[i] = Pbc(y[i] - delta*vy[i]);
	z[i] = Pbc(z[i] - delta*vz[i]);
	}
   }


	//Tail corrections for potential energy and pressure
	vtail = (8.0*pi*rho)/(9.0*pow(rcut,9)) - (8.0*pi*rho)/(3.0*pow(rcut,3));
	ptail = (32.0*pi*rho)/(9.0*pow(rcut,9)) - (16.0*pi*rho)/(3.0*pow(rcut,3));
	cout << "Tail correction for the potential energy = " << vtail << endl;
	cout << "Tail correction for the virial           = " << ptail << endl; 


	return;
	}






void Move(void){ //Move particles with Verlet algorithm
  double xnew, ynew, znew, fx[m_part], fy[m_part], fz[m_part];

  for(int i=0; i<npart; ++i){ //Force acting on particle i
    fx[i] = Force(i,0);
    fy[i] = Force(i,1);
    fz[i] = Force(i,2);
  }

  for(int i=0; i<npart; ++i){ //Verlet integration scheme

    xnew = Pbc( 2.0 * x[i] - xold[i] + fx[i] * pow(delta,2) );
    ynew = Pbc( 2.0 * y[i] - yold[i] + fy[i] * pow(delta,2) );
    znew = Pbc( 2.0 * z[i] - zold[i] + fz[i] * pow(delta,2) );

    vx[i] = Pbc(xnew - xold[i])/(2.0 * delta);
    vy[i] = Pbc(ynew - yold[i])/(2.0 * delta);
    vz[i] = Pbc(znew - zold[i])/(2.0 * delta);
    
        
    xold[i] = x[i];
    yold[i] = y[i];
    zold[i] = z[i];

    x[i] = xnew;
    y[i] = ynew;
    z[i] = znew;
  }
  return;
}

double Force(int ip, int idir){ //Compute forces as -Grad_ip V(r)
  double f=0.0;
  double dvec[3], dr;

  for (int i=0; i<npart; ++i){
    if(i != ip){
      dvec[0] = Pbc( x[ip] - x[i] );  // distance ip-i in pbc
      dvec[1] = Pbc( y[ip] - y[i] );
      dvec[2] = Pbc( z[ip] - z[i] );

      dr = dvec[0]*dvec[0] + dvec[1]*dvec[1] + dvec[2]*dvec[2];
      dr = sqrt(dr);

      if(dr < rcut){
        f += dvec[idir] * (48.0/pow(dr,14) - 24.0/pow(dr,8)); // -Grad_ip V(r)
      }
    }
  }
  
  return f;
}

void Measure(){ //Properties measurement
  int bin;
  double v, w, t, vij, wij;
  double dx, dy, dz, dr;
  ofstream Epot, Ekin, Etot, Temp, Pres, Gofr;

  Epot.open("output_epot.dat",ios::app);
  Ekin.open("output_ekin.dat",ios::app);
  Temp.open("output_temp.dat",ios::app);
  Etot.open("output_etot.dat",ios::app);
  Pres.open("output_pres.dat",ios::app);
  Gofr.open("output.gofr.csv",ios::app);

  v = 0.0; //reset observables
  t = 0.0;
//reset the hystogram of g(r)
  for (int k=0; k<nbins; ++k) g[k]=0.0;

//cycle over pairs of particles
  for (int i=0; i<npart-1; ++i){
    for (int j=i+1; j<npart; ++j){

     dx = Pbc( x[i] - x[j] );
     dy = Pbc( y[i] - y[j] );
     dz = Pbc( z[i] - z[j] );

     dr = dx*dx + dy*dy + dz*dz;
     dr = sqrt(dr);
//update of the histogram of g(r)
	int a = (int)(2*dr/(box)*nbins);
	g[a]+=2/norm(dr);

     if(dr < rcut){
       vij = 4.0/pow(dr,12) - 4.0/pow(dr,6);
       wij = 48.0/pow(dr,12) - 24.0/pow(dr,6);
       //cout<<dr<<endl;
//Potential energy
       v += vij;
       w += wij/3;
     }
    }          
  }

//Kinetic energy
  for (int i=0; i<npart; ++i) t += 0.5 * (vx[i]*vx[i] + vy[i]*vy[i] + vz[i]*vz[i]);
   
    stima_pot = (v/(double)npart+vtail)*eps; //Potential energy per particle
    stima_kin = t/(double)npart*fatt_k; //Kinetic energy per particle
    stima_temp = (2.0 / 3.0) * t/(double)npart*fatt_t; //Temperature
    stima_etot = stima_kin+stima_pot; //Total energy per particle

    Epot << stima_pot  << endl;
    Ekin << stima_kin  << endl;
    Temp << stima_temp << endl;
    Etot << stima_etot << endl;
    Pres << fatt_P*(rho*temp + (w+ptail*(double)npart)/(3*vol)) << endl;
    //cout << fatt_P*(rho*t + w/(3*vol)) << endl;
    //cout << w <<endl; 

//exporting g(r) data:
    for(int k=0; k<nbins; ++k){
    Gofr << g[k]<<endl;
    }

    Epot.close();
    Ekin.close();
    Temp.close();
    Etot.close();
    Pres.close();
    Gofr.close();

    return;
}




//norm function: it computes the factor to divide for g(r) calculation
	double norm(double dr){
	return rho*npart*4/3*M_PI*abs(pow(dr + bin_size ,3)-pow(dr,3));
	}


//modulus function: it evaluates i-th particle distance from the origin
	double dist(int i){
	double dx = Pbc(x[i]);
	double dy = Pbc(y[i]);
	double dz = Pbc(z[i]);
	double dr = dx*dx + dy*dy + dz*dz;
	return sqrt(dr);
	}







void ConfFinal(void){ //Write final configuration
  ofstream WriteConf;

  cout << "Print final configuration to file config.final " << endl << endl;
  WriteConf.open("config.final");

  for (int i=0; i<npart; ++i){
    WriteConf << x[i]/box << "   " <<  y[i]/box << "   " << z[i]/box << endl;
  }
  WriteConf.close();

  //write "final-1" configuration
  cout << "Print final-1 step configuration to file old.0 " << endl << endl;
  WriteConf.open("old.0");

  for (int i=0; i<npart; ++i){
    WriteConf << xold[i]/box << "   " <<  yold[i]/box << "   " << zold[i]/box << endl;
  }
  WriteConf.close();
  return;
}

void ConfXYZ(int nconf){ //Write configuration in .xyz format
  ofstream WriteXYZ;

  WriteXYZ.open("frames/config_" + to_string(nconf) + ".xyz");
  WriteXYZ << npart << endl;
  WriteXYZ << "This is only a comment!" << endl;
  for (int i=0; i<npart; ++i){
    WriteXYZ << "LJ  " << Pbc(x[i]) << "   " <<  Pbc(y[i]) << "   " << Pbc(z[i]) << endl;
  }
  WriteXYZ.close();
}

double Pbc(double r){  //Algorithm for periodic boundary conditions with side L=box
    return r - box * rint(r/box);
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
