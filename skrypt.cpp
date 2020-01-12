#include<bits/stdc++.h>
using namespace std;

int main(){
	string line;
	while(getline(cin, line)){
		for(int i=0; i<line.size(); i++){
			if(line[i] == '\'')
				cout<<"\""; 
			else
			if(line[i] == '[')
				cout<<'{';
			else
			if(line[i] == ']')
				cout<<"}\n";
			else
				cout<<line[i];
		}
	}
}