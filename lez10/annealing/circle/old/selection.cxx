#include"selection.h"



	void scambio (double &a, double &b) {
	int c;
	c=a;
	a=b;
	b=c;}


	void scambio (int &a, int &b) {
	int c;
	c=a;
	a=b;
	b=c;}

	
	int minimo (double* v, int inizio, int n) {
	
	unsigned int i;
	int p;
	double m;
	
	
	for (i=inizio; i<n; i++) {
	
	if (i==inizio){
	m=v[i];
	p=i;}
	
	if (v[i]<m){
	m=v[i];
	p=i;}
	}
	
	return p;}


	double funzica(double r1, double r2){
	return r1+r2;}


	void selection_sort (double* r, int* l) {
	int i;
	int t;
	for (i=0; i<5; i++) {
	t=minimo(r, i, 5);
	//cout<<"t: "<<t<<endl;
	scambio(l[i], l[t]);
	scambio(r[i], r[t]);
	//cout<<"t = "<<t<<endl;
	}
	//for(i=0; i<5; i++) p[i] = 
	}










