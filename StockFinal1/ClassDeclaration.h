#ifndef CLASSDECLARATION_H
#define CLASSDECLARATION_H
#include <bits/stdc++.h>

class User
{	
private:
	std::string username, password;
	std::string fullName, AccountNo, shCode, id;
	double debt = 0.0, balance = 0.0, stockSum;
public:
	bool completeName = false, completeID = false, completeNo = false, completeBalance = false; //check for complete info
	std::vector <std::pair<std::string, int>> StocksBought;
	int Change[6] = { 0 }; //Array keeps track of information change
	bool condition;
	User();
	User(std::string , std::string);
	~User();
	void setAccountNo(std::string);
	void setFullName(std::string);
    void setusername(std::string);
	void setpassword(std::string);
	void setIDnumber(std::string);
	std::string getusername();
	std::string getpassword();
	std::string getfullname();
	std::string getIDnumber();
	std::string getAccountNo();
	void setBalance(double);
	void Deposit(double);
	bool Withdraw(double);
	double getBalance(); 
};

class Share
{
public:
 	std::string Symbol, ShareName;
 	int Num;
 	double Currentprice, Marketcap;
};

void display_csv(std::string);
void read_csv(std::vector<Share> &);
void write_csv(std::vector<User>);
void append_csv(std::vector<User>);
void update_csv(std::vector<User>, int  );
void vtos(std::vector <std::pair<std::string, int>> &, std::string );
#endif // CLASSDECLARATION_H_INCLUDED
