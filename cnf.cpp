#include<bits/stdc++.h>
#include<fstream>
using namespace std;

int main()
{
	ifstream file("test.graphs");
	bool flag = true;
	int a,b;
	int m=-1,n=-1;


	//noEmail=n && noPhones = m

	while(file>>a>>b){
		if(a!=0){
			if(flag){
				m = max(m,a);
				m = max(m,b);
			}
			else{
				n = max(n,a);
				n = max(n,b);
			}

		}
		else
			flag = false;


	}
	// cout<<m<<n;

	int gEmail[n][n];
	int gPhone[m][m];

	for(int i=0;i<m;i++)
		for(int j=0;j<m;j++)
			gPhone[i][j]=0;

	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			gEmail[i][j]=0;

	file.clear();
	file.seekg(0,file.beg);
	flag = true;
	while(file>>a>>b){
		if(a!=0){
			a--;
			b--;
			if(flag)
				gPhone[a][b]=1;
			else
				gEmail[a][b]=1;
		}
		else
			flag = false;

	}

	for(int i=0;i<m;i++){
		for(int j=0;j<m;j++)
			cout<<gPhone[i][j]<<" ";
		cout<<endl;
	}

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			cout<<gEmail[i][j]<<" ";
		cout<<endl;
	}

	ofstream wrfile("test.satinput");
	string str = "";

	//atleast one of them is true;
	for(int i=0;i<n;i++){
		str = "";
		for(int j=0;j<m;j++){
			str += to_string(i*m + j+1) + " ";
		}
		str+="0\n";
		wrfile<<str;
	}

	//no more than one is true
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			str = "";
			for(int k=j+1;k<m;k++){
				str += "-"+to_string(i*m+j+1) + " -"+to_string(i*m+k+1)+" 0\n";
			}
			wrfile<<str;
		}
	}

	int offset = n*m;
	//trivial are true
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(j!=i){
				str = "";
				int id = offset + i*n + j;
				cout<<id<<" ";
				if(gEmail[i][j]==0)
					str += "-"+to_string(id)+" 0\n";
				else
					str += to_string(id)+" 0\n";
			}
		}
		wrfile<<str;
	}


	wrfile.close();
	return 0;
}