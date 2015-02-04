#ifndef BBSD_H
#define BBSD_H

using namespace std; 

enum AccountType {
	unknown = -1, Checking, Savings, CreditCard, InstantAccess
};

enum Permissions {
	Customer, Employee, Root
};

struct Account {
	// Login Info
	string username;
	string password;

	int account = -1;
	string firstName;
	string lastName;
	AccountType type = AccountType::Checking;
	Permissions Permissions = Permissions::Customer;
	float money = 0; // Money is like debit
	float cash = 0;  // Cash is what the 'customer' has on hand. hypothetical.
};

class root{
private:
	const std::string currentDateTime(); 

	typedef struct node {
		string username;
		string password;
		node * next;
	}*nodePtr;

	nodePtr head;
	nodePtr curr;
	nodePtr temp;

	Account* accounts;
protected:
	int ARRAY_SIZE;
public:
	
	// List
	root(int SIZE);
	void AddUser(string username, string password);
	void DelUser(string username);
	void PrtUserList();

	void initializeAccounts();
	void unloadAccounts();
	void listEmployees();
	void listAdmin();
	void totalDeposits();
	void totalWithdrawl();
	void viewLog();
	void reloadDatabase();
	void saveDatabase();
	bool createMoney(double ammount, int customerid);
	bool addCustomer(string username, string password, string firstname, string lastname, Permissions permissions, AccountType accounttype);
	bool delCustomer(int customerid);
	void search(string customername);
	void balance(int customerid);
	bool depost(int customerid, double amount);
	bool withdraw(int customerid, double amount);
	bool transfer(int customerid, double amount, int accountid);
	void customercash(int customerid);
	bool login(string username, string password);
	int getAccount(string username);
	int permission(int customerid);
	string permissionname(int permissionlvl);
};

class logging {

public:
	const std::string currentDateTime();
	void WriteLogFile(string text);
};
#endif