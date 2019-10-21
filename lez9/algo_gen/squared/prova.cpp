#include <iostream>
#include <fstream>
#include <ostream>
#include <cmath>
#include <iomanip>
#include <sstream>

using namespace std;


void change(double* v, double* w, int p, int n){
	for(int j=0; j<n; j++){
	bool tr=true;
	for(int i=0; i<p; i++){
	if(v[i]==w[j]) tr=false;
	}
	if(tr) {
	v[p]=w[j];
	p++;}}
	}


void trunk(int p, int n, double* v){
	double* w = new double[p];
	for(int i=0; i<p; i++) {w[i] = v[i]; cout<<w[i]<<endl;}
	for(int i=0; i<n-p; i++) {v[i] = v[i+p]; cout<<v[i]<<endl;}
	for(int i=n-p; i<n; i++) {v[i] = w[i-n+p]; cout<<w[i-n+p]<<endl;}
	delete w;
	}



void mirror(int s, int l, double* v){
	int max = abs(s-l);
	double* w = new double[max];
	for(int i=0; i<max; i++) w[i] = v[i+s];
	for(int i=s; i<l; i++) {
	v[i] = w[max-1];
	max--;
	}
	delete w;
	}




int main(){



double* v = new double[6];
double* w = new double[6];

v[0] = 1;
v[1] = 3;
v[2] = 5;
v[3] = 2;
v[4] = 4;
v[5] = 6;

w[0] = 2;
w[1] = 3;
w[2] = 6;
w[3] = 4;
w[4] = 5;
w[5] = 1;

change(v, w, 2, 6);
//trunk(6, 6, w);
mirror(3,5,w);

//for(int i=0; i<6; i++) cout<<v[i]<<endl;
cout<<endl;
for(int i=0; i<6; i++) cout<<w[i]<<endl;

delete w,v;



return 0;
}
