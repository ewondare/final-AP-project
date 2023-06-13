#include <bits/stdc++.h>
using namespace std;
int main()  
{  	std::vector <std::pair<std::string, int>> Stocks;
    string S, T; 
   
    getline(cin, S);   
   
    stringstream X(S); 
   
   int _user = 0;
   
    while (getline(X, T, '+')) {
	    string nametemp,numtemp;  
	    int i=0;
	    for ( i ; T[i] != ';' ; i++) {
	    	
	    	nametemp+=T[i];
		}
		Stocks[_user].first=nametemp;
		i++;
		for ( i ; i<T.size() ; i++) {
			
			numtemp+=T[i];
		}
		Stocks[_user].second=stoi(numtemp);
	    _user++;	
	        
	          
	    cout << T << ": "<<nametemp<<" "<<numtemp<<endl;
    }  
   
    return 0;  
}  
