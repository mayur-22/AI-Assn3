#include<bits/stdc++.h>
#include<fstream>
using namespace std;

int main(int argc, char** argv)
{

	string filename = argv[1];
	ifstream file(filename+".graphs");
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

	ofstream wfile(filename+".temp");
	wfile<<to_string(n)<<" "<<to_string(m)<<"\n";
	wfile.close();

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

	// for(int i=0;i<m;i++){
	// 	for(int j=0;j<m;j++)
	// 		cout<<gPhone[i][j]<<" ";
	// 	cout<<endl;
	// }

	// for(int i=0;i<n;i++){
	// 	for(int j=0;j<n;j++)
	// 		cout<<gEmail[i][j]<<" ";
	// 	cout<<endl;
	// }

	ofstream wrfile(filename+".satinput");
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
		int k=1;
		str = "";
		for(int j=0;j<n;j++){
			if(j!=i){
				int id = offset + i*(n-1) + k;
				k++;
				// cout<<id<<" "<<i<<" "<<j<<" \n";
				if(gEmail[i][j]==0)
					str += "-"+to_string(id)+" 0\n";
				else
					str += to_string(id)+" 0\n";
			}
		}
		wrfile<<str;
	}


	offset += (n)*(n-1);
	//trivial are true
	for(int i=0;i<m;i++){
		int k=1;
		str = "";
		for(int j=0;j<m;j++){
			if(j!=i){
				int id = offset + i*(m-1) + k;
				k++;
				// cout<<id<<" ";
				if(gPhone[i][j]==0)
					str += "-"+to_string(id)+" 0\n";
				else
					str += to_string(id)+" 0\n";
			}
		}
		wrfile<<str;
	}


	//graphs constraints
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			//binded i and j
			int id1 = i*m+1+j;
			str = "";
			for(int k=0;k<n;k++){
				if(k!=i){
					for(int l=0;l<m;l++){
						if(l!=j){
							// cout<<i<<j<<k<<l<<endl;
							//binded k and l
							int id2 = k*m+1+l;
							int temp = n*m + i*(n-1);
							if(i>k)
								temp += k+1;
							else
								temp += k;

							int temp2 = n*m + n*(n-1) + j*(m-1);
							if(j>l)
								temp2 += l+1;
							else
								temp2 += l;
							// cout<<id1<<" "<<id2<<" "<<temp<<" "<<temp2<<"\n";

							if(gEmail[i][k]==1)
								str += "-"+to_string(id1) + "-"+to_string(id2) + " "+to_string(temp2) + " 0\n";
							else
								str += "-"+to_string(id1) + "-"+to_string(id2) + " -"+to_string(temp2) + " 0\n";


						}
					}


				}
			}
			wrfile<<str;
		}
	}


	//no more than one is true
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			str = "";
			for(int k=j+1;k<n;k++){
				str += "-"+to_string(j*m+i+1) + " -"+to_string(k*m+i+1)+" 0\n";
			}
			wrfile<<str;
		}
	}


	wrfile.close();
	return 0;
}