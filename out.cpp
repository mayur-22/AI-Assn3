#include<bits/stdc++.h>
#include<fstream>
#include <sstream>
using namespace std;

int main(int argc,char** argv){

    string filename = argv[1];
    ifstream file(filename+".temp");
    int n,m;
    file>>n>>m;
    // cout<<n<<" "<<m<<endl;
    file.close();


    ifstream rfile(filename+".satoutput");
    string str;
    getline(rfile,str);
    // cout<<str;


    ofstream wfile(filename+".mapping");
    if(str.compare("UNSAT")==0){
        wfile<< "0";
        wfile.close();
        return 0;
    }

    getline(rfile,str);
    // cout<<str<<endl;

    stringstream ssin(str);
    int i = 0;
    string arr;
    while (ssin.good() && i < n*m){
      ssin >> arr;
      i++;
      // cout << arr << endl;
      int x = stoi(arr);
      if(x>0){
        x--;
        int a = x/m +1;
        int b = x%m + 1;
        wfile << to_string(a) << " " << to_string(b) << endl;

      }
    }

    wfile.close();
    rfile.close();


}

