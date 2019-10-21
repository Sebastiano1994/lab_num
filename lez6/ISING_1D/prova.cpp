#include <sstream>
#include <iostream>

using namespace std;

int main(){
int i = 123;
string pippo = "Io Pippo";
string fame  = "Fame";
string out_string;
stringstream ss;
ss << i <<"_" << pippo;
out_string = ss.str();



cout<<out_string<<endl;


ss <<fame;

out_string = ss.str();

cout<<out_string<<endl;
}
