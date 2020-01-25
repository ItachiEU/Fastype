#include<bits/stdc++.h>
using namespace std;

int main(){
	string line;
	bool enter = false;
	while(getline(cin, line)){
		for(int i=0; i<line.size(); i++){
			if((int)line[i] >= (int)('a') && (int)line[i] <= (int)('z') ){
				cout<<line[i];
				enter = true;
			}
			else
			if(enter){
				cout<<"\n";
				enter = false;
			}
		}
	}
}