#include <iostream>
using namespace std;

int main(int argc,char **argv) {
    
	
    cout<<"argc="<<argc<<endl;
	//for (int i=1;i<argc;i++)
		//cout<<argv[i]<<endl;
	
	for (int i=1;i<argc;i++)
		for (int j=0;argv[i][j]!=0;j++)//string 0(NULL) ile sonladırılıyor
		cout<<"argv["<<i<<"]["<<j<<"]="<<argv[i][j]<<endl;
	//cout<<"argc="<<argc<<endl;
	
	
    return 0;
}
