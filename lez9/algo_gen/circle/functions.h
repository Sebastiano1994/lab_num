#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;




	//cost function L (lenght):
	double L(){
	double sum=0;
	//sum from 1 to 29 all i-(i+1) distances:
	for(int i=0; i<n_cities-1; i++) sum+= pow(grid[iter[i]][1]-grid[iter[i+1]][1],2) + pow(grid[iter[i]][0]-grid[iter[i+1]][0],2);
	//final sum between 1st and last term:
	return sum+pow(grid[iter[0]][1]-grid[iter[n_cities-1]][1],2) + pow(grid[iter[0]][0]-grid[iter[n_cities-1]][0],2);}
