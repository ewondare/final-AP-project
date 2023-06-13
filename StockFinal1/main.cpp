
#include "ClassDeclaration.h"
#include <bits/stdc++.h>
using namespace std;

static int counter = 0;
//vector to store all stock market data
vector <Share> Market; 
//vector to store all users' data
vector <User> user; 

//checks to see whether username "u" already exists or not. if not, then the new user is made.
bool signupcheck(vector<User> user , string u ) {
    int s=user.size();
	for (int i=0 ; i<s ; i++) {
		if (u == user[i].getusername()) {
			return false;
		}
	}	
	return true;	
}
//verifies that the account exists and the password to it is p, if so user is granted access
bool logincheck(vector<User>& user , string u , string p  ) {
	
    int s = user.size();
    for (int i = 0 ; i < s ; i++) {
		if (user[i].getusername() == u) {
			if (user[i].getpassword() == p) {
				user[i].condition = true;
				counter = i;
				return true;
			} else {
				user[i].condition = false;
				return false;
			}
		}
	}
	return false;
}
//CSV handling 
//updates UserInfo after each modification by users
void write_csv(vector<User> user_) {
	
	fstream fin,fout;
	
	fin.open("UserInfo.csv" , std::ios::in);
	//updated information is first saved to a new file and then renamed to its original file and the old file is erased
	fout.open("UserInfoNew.csv", std::ios::out | std::ios::app);
	
	for (int i = 0 ; i < user_.size() ; i++) {
		std::string stocksList;
		//to save all users stock data in this format: stockname;units+stockname;units+
		for (int k = 0; k < user_[i].StocksBought.size(); k++) {
		 	std::string temp = user_[i].StocksBought[k].first;
		 	temp+=";";
		 	temp+=to_string(user_[i].StocksBought[k].second);
		 	temp+="+";
		 	stocksList += (temp);
			}
		//info is saved into the new file user by user
		fout << user_[i].getfullname() << ", "  
			 << user_[i].getusername() << ", " 
		   	 << user_[i].getpassword() << ", " 
             << to_string(user_[i].getBalance()) << ", " 
             << stocksList << ", " 
             << user_[i].getIDnumber() << ", " 
			 << user_[i].getAccountNo()  
             << "\n";
  	}
  	
  	fin.close();
 	fout.close();
 	remove("UserInfo.csv");
 	rename("UserInfoNew.csv", "UserInfo.csv");		
}
//reads stock_market file line by line an stores it in the vector Market
void read_csv_share(std::vector<Share> &Market) {
std::string fname="stock_market.csv";
std::vector<std::vector<std::string>> content;
std::vector<std::string> row;
std::string line, word;

std::fstream file (fname, std::ios::in);
if(file.is_open())
{
	while(std::getline(file, line))
	{
row.clear();

std::stringstream str(line);

	while(std::getline(str, word, ',')) {
			row.push_back(word);	
	}
	//a dynamic object is created to temporarily store a single stock info
	Share *temp= new Share;
	temp->Num=stoi(row[0]);
	temp->Symbol=row[1];
	temp->ShareName=row[2];
	temp->Currentprice=std::stod(row[3]);
	temp->Marketcap=std::stod(row[4]);
	//eventually added to the vector Market
	Market.push_back(*temp);
	delete temp;
	}
}
	file.close();
}
//reads UserInfo file line by line an stores it in the vector user after each execution of program
void read_csv_user(std::vector<User> &user) {
	//same mechanism as the function above
std::string fname="UserInfo.csv";
std::vector<std::vector<std::string>> content;
std::vector<std::string> row;
std::string line, word;

std::fstream file (fname, std::ios::in);
	if(file.is_open()) {
		while(std::getline(file >> ws, line)) {
			row.clear();
			std::stringstream str(line);
			while(std::getline(str >> ws, word, ',')) {
			row.push_back(word);	
			}
		User *temp= new User;
		temp->setFullName(row[0]);
		temp->setusername(row[1]);
		temp->setpassword(row[2]);
		temp->setBalance(std::stod(row[3]));
		vtos(temp->StocksBought, row[4]);
		temp->setIDnumber(row[5]);
		temp->setAccountNo(row[6]);
		user.push_back(*temp);
		delete temp;
		}
	}
	file.close();
}
//checks for the number of a stock by its name
int stockNum(string stockName) { 
	bool flag = false;
	int stock;
	for (int i = 0; i < Market.size(); i++){
		if (Market[i].Symbol == stockName){
			stock = i;
			flag = true;
			break;
		}
	}
	if (flag){
		return stock;
	}
	else {
		//in case stockName was not found in the list of stocks
		return -1;
	}
}

int main() {
	//read the previous data stored of users.
	read_csv_user(user); 
	//reads the datastorage of stocks.
	read_csv_share(Market); 
	string command1, command2, command3; 
	cout << "Welcome!" << endl;
	while (true) {
		cout << "Please enter what you'd like to do with the program:" << endl << "SignUp" << endl;
		cout << "LogIn" << endl << "ChangeInformation" << endl << "ExitProgram"<<endl;
		cin >> command1;
		if (command1 == "SignUp") {
        string u, p;
        cout << "Please enter your chosen username:" << endl;
        cin >> u;
        cout << "Please enter your chosen password:" << endl;
        cin >> p;
			if (signupcheck(user, u)) { 
            cout << "User successfully created. Please LogIn after this and compelete your information for future uses of our program." << endl;
            User temp(u, p);
            //new user pushed back into the vector of users
			user.push_back(temp);
			//also added to UserInfo
			append_csv(user);
		    } 
			else {
            cout<<"username or id already exists."<<endl;
		    }
	    }
		else if (command1 == "LogIn") {
      		string u,p;
      		double cash;
	    	cout << "Please enter your username:" << endl;
	    	cin >> u;
	    	cout << "Please enter your password:" << endl;
	    	cin >> p;
		    if (logincheck(user, u ,p)) { 
				cout << "Succesfully logged in." << endl;
				//for breaking out of command2's while whenever user LogOut
				int C2 = 0;	
                while (C2 < 5) {
                	cout << "Please choose what you would like to do next:" << endl;
					cout << "1.ChangeInformation\n"
							"2.Deposit\n"
							"3.Withdrawal\n"
							"4.MarketMenu\n"
							"-1.LogOut\n";
					cin>>command2;
                    if (command2 == "1") {
                    	string Changeobj, tmp;
                    	cout << "Please enter what info you'd like to change.\n"
								"A.FullName, B.username, C.password, D.AccountNo\n"
								"E.set ID (not changable afterwards)\n"
								"F.Exit.\n";
                    	cin >> Changeobj;
						if(Changeobj == "A") {
							cin.ignore();
							getline(cin, tmp);
							user[counter].setFullName(tmp);
						}
						else if (Changeobj == "E") {
							cout << "You can only enter id once. please be careful entering it." << endl;
							string idtemp;
							cin >> idtemp;
							if (idtemp.size() == 10) {
								cout << "id successfully submitted." << endl;
								user[counter].setIDnumber(idtemp);
							}
							else {
								cout<<"format not correct."<<endl<<"try again:"<<endl;
								if (idtemp.size()==10) {
								cout<<"id successfully submitted."<<endl;
								user[counter].setIDnumber(idtemp);
								} 
							}
						}
						else if (Changeobj == "B"){
							cin >> tmp;
							user[counter].setusername(tmp);
						}
						else if (Changeobj == "C"){
							cin >> tmp;
							user[counter].setpassword(tmp);
						}
						else if (Changeobj == "D"){
						cin >> tmp;
						user[counter].setAccountNo(tmp);
						}
                    } if (command2=="2") {
						cout << "Please enter the amount you want to deposit: ";
						cin >> cash;
						user[counter].Deposit(cash);
                    } else if (command2 == "3") {
						cout << "Please enter the amount you want to withdraw: ";
						cin >> cash;
						user[counter].Withdraw(cash);
                    } else if (command2=="4") {
                    	if (user[counter].completeName && user[counter].completeID && user[counter].completeNo && user[counter].completeBalance){
						//for breaking out of command3's while whenever user chooses 5.Back
						int C3 = 0; 
					    while(C3 < 5) {
					   	cout << "Please enter the number of your chosen command:\n"
					   		"1.DisplayStockList\n"
					   	 	"2.BuyStock\n"
					   		"3.SellStock\n"
					   		"4.DisplayBoughtStocks\n"
					   		"5.Back\n";
					   	cin >> command3;
					   	string stockName_;
					   	int num, units; 
						double price;
						//DisplayStockList
					   	if (command3 == "1") { 
					   		display_csv("stock_market_data.csv");	
						   } else if (command3 == "2") { //BuyStock
						   		cout << "Please enter the symbol of and the number of units of the stock you wish to buy: " << endl;
						   		cin >> stockName_ >> units;
								num = stockNum(stockName_);
								price = units * Market[num].Currentprice;
								int exist = 0;
								//checks if entered stockName already has already been bought
								//if so increments the number of units
								for (int i = 0; i < user[counter].StocksBought.size(); i++){
									if (user[counter].StocksBought[i].first == stockName_){
										if (user[counter].Withdraw(price)){
											exist = 1;
											cout << user[counter].getBalance() << endl;
											user[counter].StocksBought[i].second += units;
											cout << "Purchase was successful." << endl;
										}
									}
								}
								//if not adds it to the list of bought stocks
								if ((exist != 1)){
									if (stockNum(stockName_) != -1){
										if (user[counter].Withdraw(price)){
											user[counter].StocksBought.push_back(make_pair(stockName_,units));
											cout << "Purchase was successful." << endl;
										}
										else {
											cout << "Balance not enough for the requested purchase." << endl;
										}
									}
									else{
										cout << "Symbol was not found." << endl;
									}
								}		   	
						   	}
							else if (command3=="3") { //SellStock
						   		cout << "Please enter the symbol and the number of units of the stock you wish to sell: " << endl;
						   		cin >> stockName_ >> units;
								num = stockNum(stockName_);
								price = units * Market[num].Currentprice;
								//checks whether entered stockName had already been bought
								//if so decrements the units
								for (int i = 0; i < user[counter].StocksBought.size(); i++){
									if (user[counter].StocksBought[i].first == stockName_){ //if units are equal to boughtStock the whole stock is removed
										if (user[counter].StocksBought[i].second == units){
										user[counter].StocksBought.erase(user[counter].StocksBought.begin() + i);
										user[counter].Deposit(price);
										cout << "Your stock was successfully sold." << endl;
										}
										else if (user[counter].StocksBought[i].second > units){
											user[counter].StocksBought[i].second -= units;
											user[counter].Deposit(price);
											cout << "Your stock was successfully sold." << endl;
										}
										else {
											cout << "Number of units you wish to sell is more than the number of units you have bought." << endl;
										}
									}//if not displays error(since you can't sell what you don't have!)
									else {
										cout << "Stock symbol not is not available in the list of bought stocks." << endl;
									}
								} 
						   } else if (command3 == "4"){ //DisplayBoughtStocks
						   		cout << "List of bought stocks is: " << endl;
						   		for (int i = 0; i < user[counter].StocksBought.size(); i++){
						   			cout << user[counter].StocksBought[i].first << " " << user[counter].StocksBought[i].second << endl;
								   }
						   } else if (command3 == "5") {
						   		//for breaking out of the third while
						   	  	C3 = 10; 
						   	}
					    }
					} else {
						if(user[counter].completeName == false){
							cout << "Missing FullName" << endl;
						}
						if (user[counter].completeID == false){
							cout << "Missing ID" << endl;
						}
						if (user[counter].completeNo == false){
							cout << "Missing AccountNo" << endl;
						}
						if (user[counter].completeBalance == false){
							cout << "Missing initial deposit" << endl;
						}
						//checks whether user has completed their info before accessing market menu
						cout << "In order to access the market menu you need to complete the requested information." << endl;
					}
                    } else if (command2 == "-1") { //logOut
                    	//updates user info and saves them into a file
                    	write_csv(user);
                    	//for breaking out of the second while
                    	C2=10; 
					}				
                }
            }
			else {
            cout<<"could not log in. please try again."<<endl;
            }

		}
		else if (command1=="ChangeInformantion") {
			cout<<"you need to log in first.";
        } 
		else if (command1 == "ExitProgram") {
			return false;
    	}
	}

	return 0;
}
