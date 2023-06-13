#include <bits/stdc++.h>
void update_csv (int index , int count ,  vector<User> user) {
	fstream fin, fout;
	fin.open("UserInfo.csv" , std::ios::in);
	fout.open("UserInfoNew.csv" , std::ios::out);
	
	std::string new_info;
	std::string line, word;
 	std::vector<std::string> row;
		if (index == 0){
		 	new_info = u[count].getfullname();
		 }
		 else if (index == 1){
		 	new_info = u[count].getusername();
		 }
		 else if (index == 2){
		 	new_info = u[count].getpassword();
		 }
		 else if (index == 3){
		 	new_info = std::to_string(u[count].getBalance());
		 }
		 else if (index == 4){
		 	std::string stocksList;
		 	for (int i = 0; i < u[count].StocksBought.size(); i++){
		 		std::string temp = u[count].StocksBought[i].first;
		 		temp+=";";
		 		temp+=u[count].StocksBought[i].second;
		 		temp+="+";
		 		stocksList += (temp);
			 }
		 	new_info = stocksList;
		 } else if (index == 5){
 			new_info = u[count].getIDnumber();
 		}
	int i=-1;
	int usercount=0;
	while (!fin.eof()) {
		getline(fin  >> std::ws, line);
		i++; //first time i=0;
		std::stringstream s(line);
		while (getline(s >> std::ws, word, ',')) {
			if (i!=count) {
				row.push_back(word);
			}  else {
				word=u[count].getfullname();
				row.push_back(word);
				u[count].getusername();
				row.push_back(word);
				word = u[count].getpassword();
				row.push_back(word);
				word = std::to_string(u[count].getBalance());
				row.push_back(word);
				for (int k = 0; k < u[count].StocksBought.size(); k++) {
		 		std::string temp = u[count].StocksBought[k].first;
		 		temp+=";";
		 		temp+=u[count].StocksBought[k].second;
		 		temp+="+";
		 		stocksList += (temp);
			  }
		 		word = stocksList;
		 		row.push_back(word);
		 		word = = u[count].getIDnumber();
		 		row.push_back(word);
		 		
			}
	    
	  	}
	}
	
	for (int q=0 ; q<6 * (row.size()-1 ); q++) {
		
		if (q%6==5 ) {
			fout<<row[q]<<"\n";
		} else {
			fout<<row[q]<<","
		}
		
	}
	
	fin.close();
 	fout.close();
 	remove("UserInfo.csv");
 	rename("UserInfoNew.csv", "UserInfo.csv");
	
}