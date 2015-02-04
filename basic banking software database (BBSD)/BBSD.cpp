#define _CRT_SECURE_NO_WARNINGS // Prevnt OS depenency to Windows and using Microsoft functions (for time)....
// Project: Basic Banking Software Database
// Name: Brandan Tyler Lasley
// Date: 3/13/2014 18:50

// This will be based on a level system from 0 - 2
// 0 Customer
// 1 Employee
// 2 Boss (root?)

// ====== CUSTOMER ======
// Balance
// Depost
// Withdraw
// Transfer
// Total Cash (optional, A place to withdrawl money, employee or bank shouldn't beable to NSA spy on the customer?)

// ====== EMPLOYEE ======
// Everything above
// Add customer (account)
// Delete customer (account)
// Search records using "Name" using Swquential search

// ====== BOSS ======
// Everything in the bank teller and customer
// List total number of employees in bank
// List Ttoal amount of money in the bank
// Total deposits in a day
// total withdrawls in a day
// Abillity to see detailed log of all transactions
// Sort databade (optional)
// Create money (optional)

// ALL features requested in this program were built this time to a reasonable quality. Link lists, data hidden inside the private of a class etc. 

// Know Issues & Limiatations:
// If you use the illegal char '◦' anywhere in the program it will corrupt the database, I may fix this.
// I have no idea how a credit card, savings, or 'instant access' works. So those wasn't added.  
// Any illegal chars will break it.
// Ugh.... Detailed log wasn't possible... couldn't read certian parts of the data because some lines of the log file were longer than other
// It is nearly impossible to get more than 1 users online at once.
// LOG has some visual issues. 
// If you type a string in the records value it'll break. 
// This code is messier than the last one due to restraints. 
// Not all features were tested since the last program, some features that worked last time *may* not work on this one.
// of cource I could be wrong and they all work just fine. 

// The link list isn't really needed feature of this program, its just the best I could come up with at that time.


#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <ctime>
#include "BBSD.h"

const std::string root::currentDateTime() {
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);

		strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

		return buf;
	}
	root::root(int SIZE)     // constuctor
	{
		ARRAY_SIZE = SIZE;
		
		head = NULL;
		curr = NULL;
		temp = NULL;
	}

	void root::initializeAccounts() {
		accounts = new Account[ARRAY_SIZE];
	}

	void root::unloadAccounts() {
		delete this;
	}

	void root::AddUser(string username, string password) {
		nodePtr n = new node;
		n->next = NULL;
		n->username = username;
		n->password = password;

		if (head != NULL) {
			curr = head;
			
			while (curr->next != NULL) {
				curr = curr->next;
			}
			curr->next = n;
		}
		else {
			head = n;
		}
	}

	void root::DelUser(string username) {
		nodePtr DelPtr = NULL;
		temp = head;
		curr = head;

		while (curr != NULL && curr->username != username) {
			temp = curr;
			curr = curr->next;
		}

		if (curr == NULL){
			cout << "User '" << username << "' was not found!" << endl;
		}
		else {
			DelPtr = curr;
			curr = curr->next;
			temp->next = curr;
			delete DelPtr;
			cout << "User '" << username << "' was deleted!" << endl;
		}

	}

	void root::PrtUserList() {
		curr = head;

		cout << "Current Users logged in:" << endl;
		
		while (curr != NULL) {
			cout << curr->username << endl;
			curr = curr->next;
		}

	}

	// ====== BOSS ======
	// Everything in the bank teller and customer
	// List total number of employees in bank
	// List total amount of money in the bank
	// Total deposits in a day
	// total withdrawls in a day
	// Abillity to see detailed log of all transactions
	// Sort databade (optional)
	// Create money (optional)
	// Reload DB (optional)
	// Save DB (optional)

	void root::listEmployees() {
		for (int i = 0; i <= ARRAY_SIZE - 1; i++) {
			if (accounts[i].Permissions == Permissions::Employee) {
				if (accounts[i].account != -1) {
					cout
						<< "=======================================" << endl
						<< "Account Infomation: " << endl
						<< "Account #: " << accounts[i].account << endl
						<< "Username: " << accounts[i].username << endl;
				}
			}
		}
	}

	// Not added to the options/command list!!!! <================================== <- Fixed
	void root::listAdmin() {
		for (int i = 0; i <= ARRAY_SIZE - 1; i++) {
				if (accounts[i].Permissions == Permissions::Root) {
				if (accounts[i].account != -1) {
					cout
						<< "=======================================" << endl
						<< "Account Infomation: " << endl
						<< "Account #: " << accounts[i].account << endl
						<< "Username: " << accounts[i].username << endl;
				}
			}
		}
	}

	// Sorry about the CTRL + C CTRL + V code, I normally dont do this, just for time sake. Need to debug other things then worry about
	// Fixing this code so its more robust. 
	void root::totalDeposits() { // <--- Needs work
		string date;
		string td = currentDateTime();
		std::string delimiter = ".";

		size_t pos = 0;
		std::string token;
		while ((pos = td.find(delimiter)) != std::string::npos) {
			token = td.substr(0, pos);
			date = token;
			break;
			td.erase(0, pos + delimiter.length());
		}

		string filename;
		ifstream data;

		data.open("log_file.txt");

		// Exit on I/O error
		if (!data.is_open()) {
			cout << "Failed to open file, press enter to exit";
			getchar();
			getchar();
		}

		double amount = 0;
		while (!data.eof()) {
			string date2 = "";
			string timestamp = "";
			string type;
			double in = 0;
			string dummy = "";

			data >> timestamp >> type >> dummy >> in;
			td = timestamp;
			data.ignore();

			while ((pos = td.find(delimiter)) != std::string::npos) {
				token = td.substr(0, pos);
				date2 = token;
				td.erase(0, pos + delimiter.length());
			}
			if (type == "Deposit") {
				if (date == date2) {
					amount += in;
				}
			}
		}

		cout << "Todays Total Deposits: " << amount << endl;
	}

	void root::totalWithdrawl() { // <--- Needs Work
		string date;
		string td = currentDateTime();
		std::string delimiter = ".";

		size_t pos = 0;
		std::string token;
		while ((pos = td.find(delimiter)) != std::string::npos) {
			token = td.substr(0, pos);
			date = token;
			break;
			td.erase(0, pos + delimiter.length());
		}

		string filename;
		ifstream data;

		data.open("log_file.txt");

		// Exit on I/O error
		if (!data.is_open()) {
			cout << "Failed to open file, press enter to exit";
			getchar();
			getchar();
		}

		double amount = 0;
		while (!data.eof()) {
			string date2 = "";
			string timestamp = "";
			string type;
			double in = 0;
			string dummy = "";


			while ((pos = td.find(delimiter)) != std::string::npos) {
				token = td.substr(0, pos);
				date2 = token;
				td.erase(0, pos + delimiter.length());
			}

			data >> timestamp >> type >> dummy >> in;
			
			data.ignore();
			td = timestamp;

			
			while ((pos = td.find(delimiter)) != std::string::npos) {
				token = td.substr(0, pos);
				date2 = token;
				td.erase(0, pos + delimiter.length());
			}
			if (type == "Withdraw") {
				if (date == date2) {
					amount += in;
				}
			}
		}

		cout << "Todays Total Withdrawl: " << amount << endl;

	}

	void root::viewLog() {
		ifstream myReadFile;
		myReadFile.open("log_file.txt");
		char output[100];
		if (myReadFile.is_open()) {
			while (!myReadFile.eof()) {
				myReadFile >> output;
				cout << output << endl;
			}
		}
		cout << endl;
		myReadFile.close();
	}

	void root::reloadDatabase() {
		
		// Clean DB
		for (int i = 0; i <= ARRAY_SIZE - 1; i++) {
				// Clean up and remove user!
				accounts[i].account = -1;
				accounts[i].username = "";
				accounts[i].password = "";
				accounts[i].cash = 0;
				accounts[i].money = 0;
				accounts[i].type = AccountType::Checking;
				accounts[i].Permissions = Permissions::Customer;
		}


		string filename;
		ifstream data;

		int account;
		string username;
		string password;
		string firstname;
		string lastname;
		double cash;
		double money;

		int type;
		int permissions;

		data.open("members.db");

		// Exit on I/O error
		if (!data.is_open()) {
			cout << "Failed to open file...";
			getchar();
			getchar();
		}

		int i = 0;

		while (!data.eof()){
			data >> account >> username >> password >> firstname >> lastname >> cash >> money >> type >> permissions;
			accounts[i].account = account;
			accounts[i].username = username;
			accounts[i].password = password;
			accounts[i].firstName = firstname;
			accounts[i].lastName = lastname;
			accounts[i].cash = cash;
			accounts[i].money = money;
			accounts[i].type = static_cast<AccountType>(type);
			accounts[i].Permissions = static_cast<Permissions>(permissions);
			i++;
		}

	}

	void root::saveDatabase() {
		if (remove("members.db") != 0){
			cout << "Error deleting file";
		}
		ofstream membersdb("members.db");
		if (membersdb.is_open())
		{
			for (int i = 0; i <= ARRAY_SIZE - 1; i++) {
				if (accounts[i].account != -1) {
					if (i != 0) { 
						membersdb << endl; // Duct tape over a real issue.
					}
					
					membersdb << accounts[i].account << " " << accounts[i].username << " " << accounts[i].password
						<< " " << accounts[i].firstName << " " << accounts[i].lastName
						<< " " << accounts[i].cash << " " << accounts[i].money << " " << accounts[i].type
						<< " " << accounts[i].Permissions;
				}
			}
		}
		membersdb.close();
	}

	bool root::createMoney(double ammount, int customerid) {
		if (customerid != -1) {
			for (int i = 0; i <= ARRAY_SIZE - 1; i++) {
				if (accounts[i].account == customerid) {
					accounts[i].money = accounts[i].money + ammount;
					break;
				}
			}
		}
		else {
			return false;
		}
	}

	bool root::addCustomer(string username, string password, string firstname, string lastname, Permissions permissions, AccountType accounttype) { //AC
		bool found = false;
		int AccountID = -1;
		/*
		// Account # Algorithm (will break after 2000, unless the array size is changed)
		for (int i = 0; i <= size - 1; i++) {
		for (int b = 0; b <= size - 1; b++) {
		if (accounts[i].account == b) {
		found = true;
		}
		if (found == true) {
		AccountID = b;
		break;
		}
		}
		}
		*/

		for (int i = 0; i <= ARRAY_SIZE - 1; i++) {
			if (accounts[i].account == -1) {
				accounts[i].account = i + 1;
				accounts[i].username = username;
				accounts[i].password = password;
				accounts[i].firstName = firstname;
				accounts[i].lastName = lastname;
				accounts[i].type = accounttype;
				accounts[i].Permissions = permissions;
				cout << "Success! Account #: " << i + 1;
				return true;
				break;
			}
		}
		return false;
	}

	bool root::delCustomer(int customerid) { // DC
		if (customerid != -1) {
			for (int i = 0; i <= ARRAY_SIZE - 1; i++) {
				if (accounts[i].account == customerid) {

					// Clean up and remove user!
					accounts[i].account = -1;
					accounts[i].username = "";
					accounts[i].password = "";
					accounts[i].cash = 0;
					accounts[i].money = 0;
					accounts[i].type = AccountType::Checking;
					accounts[i].Permissions = Permissions::Customer;

					return true;
					break;
				}
			}
		}
		return false;
	}

	// Case Sensitive!
	void root::search(string customername) { // search
		for (int i = 0; i <= ARRAY_SIZE - 1; i++) {
			if (accounts[i].firstName == customername) {
				cout << "Account Infomation: " << endl
					<< "Account #: " << accounts[i].account << endl
					<< "Username: " << accounts[i].username << endl
					<< "Money (in checking): " << accounts[i].money << endl
					<< "Account Type: " << accounts[i].type << endl
					<< "Permissions: " << accounts[i].Permissions << endl;
			}
		}
	}

	void root::balance(int customerid) { // <B>
		if (customerid != -1) {
			for (int i = 0; i <= ARRAY_SIZE - 1; i++) {
				if (customerid == accounts[i].account) {
					cout << "Current balance: " << accounts[i].money << endl;
				}
			}
		}
	}

	bool root::depost(int customerid, double amount) { // <D>
		if (customerid != -1) {
			for (int i = 0; i <= ARRAY_SIZE - 1; i++) {
				if (customerid == accounts[i].account) {
					if (amount > accounts[i].cash) {
						cout << "You do not have enough cash to make this deposit!" << endl;
						return false;
					}
					else {
						accounts[i].money = accounts[i].money + amount;
						accounts[i].cash = accounts[i].cash - amount;
						cout << "Deposit Successful! Amount: " << amount << endl;
						return true;
					}
				}
			}
		}
		cout << "Could not find account!" << endl;
		return false;
	}

	bool root::withdraw(int customerid, double amount) { // <W>
		if (customerid != -1) {
			for (int i = 0; i <= ARRAY_SIZE - 1; i++) {
				if (customerid == accounts[i].account) {
					if (amount > accounts[i].money) {
						cout << "You do not have enough money to make this withdrawl!" << endl;
						return false;
					}
					else {
						accounts[i].money = accounts[i].money - amount;
						accounts[i].cash = accounts[i].cash + amount;
						cout << "Withdraw Successful! Amount: " << amount << endl;
						return true;
					}
				}
			}
		}
		cout << "Could not find account!" << endl;
		return false;
	}

	bool root::transfer(int customerid, double amount, int accountid) { // <W>
		if (customerid != -1) {
			int myaccount = -1;
			// Find my account number (index). 
			for (int i = 0; i <= ARRAY_SIZE - 1; i++) {
				if (customerid == accounts[i].account) {
					myaccount = i;
				}
			}

			if (myaccount == -1) {
				return false;
			}

			// Find the account number of the transfer person. 
			for (int i = 0; i <= ARRAY_SIZE - 1; i++) {
				if (accountid == accounts[i].account) {
					if (accounts[myaccount].money < amount) { // < means less than, abit dyslexic when it comes to <> so I get it wrong, its the other way.
						return false;
					}
					else {
						accounts[myaccount].money = accounts[myaccount].money - amount;
						accounts[i].money = accounts[i].money + amount;
						cout << "Transfer Successful! Amount: " << amount << endl;
						return true;
					}
				}
			}
		}
		cout << "Could not find account!" << endl;
		return true;
	}

	void root::customercash(int customerid) { // <CC>
		if (customerid != -1) {
			for (int i = 0; i <= ARRAY_SIZE - 1; i++) {
				if (accounts[i].account == customerid) {
					cout << "Your current cash is: " << accounts[i].cash << endl;
					break;
				}
			}
		}
	}

	bool root::login(string username, string password) {

		for (int i = 0; i <= ARRAY_SIZE - 1; i++) {
			// Case Sensitive ALL FEILDS!
			if ((username == accounts[i].username) && (password == accounts[i].password)) {
				return true;
			}


		}
		return false;
	}

	int root::getAccount(string username) {
		for (int i = 0; i <= ARRAY_SIZE - 1; i++) {
			if ((username == accounts[i].username)) {
				return accounts[i].account;
			}
		}
		return -1;
	}

	int root::permission(int customerid) {
		for (int i = 0; i <= ARRAY_SIZE - 1; i++) {
			if ((customerid == accounts[i].account)) {
				return accounts[i].Permissions;
			}
		}
		return -1;
	}

	string root::permissionname(int permissionlvl) {
		if (permissionlvl == Permissions::Customer) {
			return "Customer";
		}
		else if (permissionlvl == Permissions::Employee) {
			return "Employee";
		}
		else if (permissionlvl == Permissions::Root) {
			return "Root/Administrator";
		}
		else {
			return "Malicious User";
		}
	}

	void logging::WriteLogFile(string text)
	{
		std::ofstream log_file("log_file.txt", std::ios_base::out | std::ios_base::app);

		log_file << text;
	}

	// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
	const std::string logging::currentDateTime() {
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);

		strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

		return buf;
	}

// How do we do the account # thing for the current user logged in?
// Do we just load the info at start?
// Should we also ask if they want to deposit to another user?
// Transer? 

int main() {

	// Class Declarisons 

	logging logging;
	
	cout << "Welcome to Brandans Banking System!" << endl;
	int ARRAY_SIZE;
	//logging.WriteLogFile("test");
	cout << "Please enter the amount of records: ";
	cin >> ARRAY_SIZE;

	root* dbm; // Database manager
	dbm = new root(ARRAY_SIZE);


	// Username & Password, this is a secure system. 
	string username;
	string password;
	
	// Create accounts
	dbm->initializeAccounts();
	dbm->reloadDatabase(); // Load DB


	cout << "Username: ";
	cin >> username;          // Usernames cannot contains spaces 
	getchar();               // Fix annoying auto input from enter.
	cout << "Password: "; 
	cin >> password; // nor can password, no catch for this though.

	// ==== Login ====
	if (dbm->login(username, password)) {

		dbm->AddUser(username, password);

		int id = dbm->getAccount(username); // Gets the ID, faster to seek than searching strings, good pratice for MySQL also. 
		int Accesslvl = dbm->permission(id);

		string input;
		int input2;
		double input3;

		while (true) {

			if (Accesslvl <= -1 || Accesslvl > 2) {
				// Prevents memory hacking... probably.
				// Well only if they dont know the permission system is 0 - 2. 
				// If they do oh well...

				cout << "Access Denied" << endl;
				dbm->unloadAccounts();
				getchar();
				getchar();
				return 0;
			}

			cout << endl << "Please Enter Command: ";
			cin >> input;

			if (input == "Q" || input == "q") {
				// Quit (Permissions >CUSTOMER)
				dbm->saveDatabase();
				dbm->DelUser(username);
				dbm->unloadAccounts();
				return 0;
			}
			else if (input == "B" || input == "b") {
				if (Accesslvl == Permissions::Customer) {
					dbm->balance(id);
				}
				else {
					int cust_ID = 0;
					cin >> cust_ID;
					dbm->balance(cust_ID);
				}
				// Balance (Permissions >CUSTOMER)
			}
			else if (input == "D" || input == "d") {
				if (Accesslvl == Permissions::Customer) {
					double amount; 
					cin >> amount;
					bool success = dbm->depost(id, amount);
					
				if (success) {
						// Build log string
						string log = logging.currentDateTime();
						log += " Deposit ";
						log += std::to_string(id);
						log += " ";
						log += std::to_string(amount);
						log += "\n";

						logging.WriteLogFile(log);
					}

				}
				else {
					int cust_ID = 0;
					cin >> cust_ID;
					double amount = 0;
					cin >> amount;

					bool success = dbm->depost(cust_ID, amount);

					if (success) {
						// Build log string
						string log = logging.currentDateTime();
						log += " Deposit ";
						log += std::to_string(id);
						log += " ";
						log += std::to_string(amount);
						log += "\n";

						logging.WriteLogFile(log);
				  }
		
				}
				// Deposit (Permissions >CUSTOMER)
			}
			else if (input == "W" || input == "w") {
				if (Accesslvl == Permissions::Customer) {
					double amount;
					cin >> amount;
					bool success = dbm->withdraw(id, amount);

					if (success) {
						// Build log string
						string log = logging.currentDateTime();
						log += " Withdraw ";
						log += std::to_string(id);
						log += " ";
						log += std::to_string(amount);
						log += "\n";

						logging.WriteLogFile(log);
					}
				}
				else {
					int cust_ID = 0;
					cin >> cust_ID;
					double amount = 0;
					cin >> amount;

					bool success = dbm->withdraw(cust_ID, amount);

					if (success) {
						// Build log string
						string log = logging.currentDateTime();
						log += " Withdraw ";
						log += std::to_string(cust_ID);
						log += " ";
						log += std::to_string(amount);
						log += "\n";

						logging.WriteLogFile(log);
					}
				}
				// Withdrawl (Permissions >CUSTOMER)
			}
			else if (input == "T" || input == "T") {
				if (Accesslvl == Permissions::Customer) {
					int toid;
					cin >> toid;
					int amount;
					cin >> amount;
					bool success = dbm->transfer(id, amount, toid);

					if (success) {
						// Build log string
						string log = logging.currentDateTime();
						log += " Transfer ";
						log += std::to_string(id);
						log += " ";
						log += std::to_string(amount);
						log += "\n";

						logging.WriteLogFile(log);
					}
				}
				else {
					int fromid = 0;
					cin >> fromid;
					int toid = 0;
					cin >> toid;
					double amount = 0;
					cin >> amount;
					bool success = dbm->transfer(fromid, amount, toid);

					if (success) {
						// Build log string
						string log = logging.currentDateTime();
						log += " Deposit ";
						log += std::to_string(id);
						log += " ";
						log += std::to_string(amount);
						log += "\n";

						logging.WriteLogFile(log);
					}
				}
				// Transfer (Permissions <CUSTOMER)
			}
			else if (input == "CC" || input == "Cc") {
				if (Accesslvl == Permissions::Customer) {
					dbm->customercash(id);
				}
				// Customer Cash (Permissions <CUSTOMER)
			}
			else if (input == "AC" || input == "Ac" || input == "ac") {
				if (Accesslvl >= Permissions::Employee) {
					string usrname;
					string psword;
					string firstname;
					string lastname;
					int permission;
					int type;
					cin >> usrname;
					cin >> psword;
					cin >> firstname;
					cin >> lastname;
					cin >> permission;
					cin >> type;

					bool success = dbm->addCustomer(usrname, psword, firstname, lastname, static_cast<Permissions>(permission), static_cast<AccountType>(type));

				}
				// Add Customer (Permissions >EMPLOYEE)
			}
			else if (input == "DC" || input == "Dc" || input == "dc") {
				if (Accesslvl >= Permissions::Employee) {
					int custid;
					cin >> custid;
					bool success = dbm->delCustomer(custid);
				}
				// Delete Customer (Permissions >EMPLOYEE)
			}
			else if (input == "SEARCH" || input == "Search" || input == "search") {
				string firstname;
				cin >> firstname;
				if (Accesslvl >= Permissions::Employee) {
					dbm->search(firstname); // Case Sensitive
				}
			}
			else if (input == "TE" || input == "Te" || input == "te") {
				if (Accesslvl >= Permissions::Root) {
					dbm->listEmployees();
				}
				// Total Empoyees (Permissions ROOT)
			}
			else if (input == "TR" || input == "Tr" || input == "tr") {
				if (Accesslvl == Permissions::Root) {
					dbm->listAdmin();
				}
				else {

				}
				// Total Roots (Permissions ROOT)
			}
			else if (input == "TD" || input == "Td" || input == "td") {
				if (Accesslvl == Permissions::Root) {
					dbm->totalDeposits();

				}
				// Total Deposits (TODAY) (Permissions ROOT)
			}
			else if (input == "TW" || input == "Tw" || input == "tw") {
				if (Accesslvl == Permissions::Root) {
					dbm->totalWithdrawl();
				}
				// Total Wutgdrawks (TODAY) (Permissions ROOT)
			}
			else if (input == "CM" || input == "Cm" || input == "cm") {
				if (Accesslvl == Permissions::Root) {
					int custid;
					cin >> custid;
					double amount;
					cin >> amount;

					dbm->createMoney(amount, custid);
				}
				// Create Money (Permissions ROOT)
			}
			else if (input == "REHASH" || input == "Rehash" || input == "rehash") {
				if (Accesslvl == Permissions::Root) {
					dbm->reloadDatabase();
				}
				// Reload Database (Permissions ROOT)
			}
			else if (input == "LOG" || input == "log" || input == "Log") {
				if (Accesslvl == Permissions::Root) {
					dbm->viewLog();
				}
				// Save Database (Permissions ROOT)
			}
			else if (input == "SAVE" || input == "Save" || input == "save") {
				if (Accesslvl == Permissions::Root) {
					dbm->saveDatabase();
				}
				// Save Database (Permissions ROOT)
			} else if (input == "TU" || input == "tu" || input == "Tu") {
				if (Accesslvl == Permissions::Root) {
					dbm->PrtUserList();
				}
			} else if (input == "help" || input == "HELP" || input == "Help") {
			
				if (Accesslvl >= Permissions::Customer) {
					cout << endl <<
						"Current Commands for permission level: " << dbm->permissionname(Accesslvl) << endl;
					if (Accesslvl >= Permissions::Employee) {
						cout << "Balance          <B> (usage B <ID>)" << endl
							<< "Depost           <D> (usage D <ID>)" << endl
							<< "Withdraw         <W> (usage W <ID>)" << endl
							<< "Transfer         <W> (usage T <FROM ID> <TO ID> <AMOUNT>)" << endl
							<< "Quit             <Q> (usage Q)" << endl;
					}
					else {
							cout << "Balance          <B> (usage B <AMOUNT>)" << endl
							<< "Depost           <D> (usage D <AMOUNT>)" << endl
							<< "Withdraw         <W> (usage W <AMOUNT>)" << endl
							<< "Transfer         <W> (usage T <ID> <AMOUNT>)" << endl
							<< "Customercash     <CC> (usage CC)" << endl
							<< "Quit             <Q> (usage Q)" << endl;
					}
				}
				//int customerid, string username, string password, string firstname, string lastname, Permissions permissions, AccountType accounttype { //AC
				if (Accesslvl >= Permissions::Employee) {
					cout << "Addcustomer      <AC> (usage Addcustomer <USERNAME> <PASSWORD> <FIRSTNAME> <LASTNAME> <PERMISIONS> <ACCOUNT TYPE>)" << endl
						<< "Delcustomer      <DC (usage Delcustomer <ID>)" << endl
						<< "Search (by name) <search> (usage Search Brandan)" << endl;
				}

				if (Accesslvl == Permissions::Root) {
					cout << "Total Employees  <TE> (usage TE)" << endl
						 << "Total Roots      <TR> (usage TR)" << endl
					   	 << "Total Deposits   <TD> (usage TD)" << endl
						 << "Total Users      <TU> (usage TU)" << endl
						 << "Total Withdraws  <TW> (usage TW)" << endl
				         << "Create Money     <CM> (usage CM <ID> <AMOUNT>)" << endl
						 << "View Log         <LOG> (usage LOG) " << endl
						 << "Reload Database  <REHASH> (usage REHASH) " << endl
						 << "Save   Database  <SAVE> (usage SAVE)" << endl;
				}

				cout << endl;
			} else {
				cout << "Invalid Command, type help for list of commands" << endl << endl;
			}

		}
	} else {

		// Prevents brute force attacks, memory hacking etc... probably.. in theory. 
		cout << endl << "You have entered an invalid login credential, for your safety this application will now terminate!";
		dbm->unloadAccounts();
		getchar();
		getchar();
		return 0;
	}
}