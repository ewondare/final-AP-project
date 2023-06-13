#include "ClassDeclaration.h"

//User constructors and destructors
User::User(){

}
User::User(std::string u , std::string p ) {

	username = u;
	password = p;

}
User::~User(){
	
}
//User setters and getters
void User::setAccountNo(std::string _AccountNo ) {
    if(_AccountNo.length() == 10){
    	AccountNo = _AccountNo;
    	shCode = "IR";
    	shCode += _AccountNo;
    	completeNo = true;
	}
	else {
		std::cout << "Account Number must be 10 digits long." << std::endl;
	}
}
void User::setFullName(std::string name1){
	if (name1.length() > 40){ //check for standard length
		std::cout << "Name exceeds standard length" << std::endl;
	}
	else {
		fullName = name1;
		Change[0]=1;
		completeName = true;
	}
}
void User::setusername(std::string _username){
	Change[1]=1;
    username=_username;
}
void User::setpassword(std::string _password){
	Change[2]=1;
    this->password=_password;
}
void User::setIDnumber(std::string _id) {
	completeID = true;
	this->id=_id;
	
}
std::string User::getIDnumber() {
		return id;
	}
std::string User::getusername() {
	return username;
}
std::string User::getpassword(){
    return password;
}
void User::setBalance(double bal){
	completeBalance = true;
	Change[3]=1;
	balance = bal;
}
double User::getBalance(){
	return balance;
}
std::string User::getfullname(){
	return fullName;
}
std::string User::getAccountNo(){
	return AccountNo;
}
//Deposits money to account
void User::Deposit(double deposit_){
	completeBalance = true;
	Change[3] = 1;
	balance += deposit_;
}
//withdraws money from account
bool User::Withdraw(double withdraw_){
	if (balance - withdraw_ >= -1000000.0){ //checks that debt remains under a certain amount
		balance -= withdraw_;
		Change[3] = 1;
		return true;
	}
	else {
		std::cout << "Insufficient balance for requested withdraw" << std::endl;
		return false;
	}
}

//CSV file handling functions
//reads a csv file line by line and displays it
void display_csv(std::string fname)
{

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

while(std::getline(str, word, ','))
row.push_back(word); //pushes words into the vector row(equivalent to one line of file)
  content.push_back(row); //pushes rows(lines) into the vector content to save the entire block of file in a vector
}
}
else
std::cout<<"Could not open the file\n";

for(int i=0;i<content.size();i++)
{
for(int j=0;j<content[i].size();j++)
{
std::cout<<content[i][j]<<" ";//displays content word by word
}
std::cout<<"\n";
}
file.close();
return;
}
//adds a new user to UserInfo file at the time of signUp
void append_csv(std::vector<User> u){ 
	std::fstream file;
	std::string filename="UserInfo.csv", username_, password_, stocks, AccountNo_;
	std::string id="0",Fullname="null";
	std::string balance_;
	int count = u.size() - 1;
	username_ = u[count].getusername();
	password_ = u[count].getpassword();
	balance_ = "0.0";
	stocks = " ";
	AccountNo_ = " ";
	file.open(filename, std::ios_base::app);
	file << Fullname << "," <<username_ << "," << password_ << "," << balance_ << "," << stocks << "," << id << "," << AccountNo_ << "\n";

	file.close();
}
//converts string to vector(boughtStocks)
void vtos(std::vector <std::pair<std::string, int>> &Stocks, std::string S) {  
    std::string T; 
    std::stringstream X(S); 
   	int _user = 0;
   	//A user's bought stocks is saved in this format: "stockname;units+stockname;units+" and this part of the code separates them
    while (getline(X, T, '+')) {
    std::string nametemp,numtemp;  
    int i=0;
    for ( i ; T[i] != ';' ; i++) {
    	nametemp+=T[i];
  	}
  	i++;
  	for ( i ; i<T.size() ; i++) {
		numtemp+=T[i];
  	}
  	//sets the first part of the separated string st as the name and the second part as the unit
  	Stocks.push_back(make_pair(nametemp, stoi(numtemp))); 
		_user++;
    }  
}

bool signupcheck(std::vector<User> , std::string);
bool logincheck(std::vector<User> , std::string , std::string);