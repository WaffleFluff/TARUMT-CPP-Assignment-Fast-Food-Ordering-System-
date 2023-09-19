#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

/*                 GLOBAL VARIABLES                */
/*				Login/Register Module			   */
struct Customer
{
	int choice = 0;
	string name = " ";
	string ageString = " ";
	string contact = " ";
	string memberID = " ";
	string memberNumber = " ";
	double memberPoint = 0.00;
	double balance = 0.00;
	int age = 0;
};

/*					  Menu Module					*/
struct menu { //store data from menu display files
	int list = 0, quantity = 0;
	string itemName = "";
	double alaCarte = 0.0, setMeal = 0.0, medium = 0.0, large = 0.0, price = 0.0;
};
vector<menu> orderList;
/***********************************************************************************/

/*                FUNCTION PROTOTYPES               */
/*                Login/Register Module             */
void home();
void logo();
void registerNewCustomer(vector<Customer>& customers);
void login(vector<Customer>& customers);
bool validateName(const string& name);
bool validateContact(const string& contact);
bool validateAge(const string& ageString);
void writeToFile(const Customer& customer);

/*						 Top up Module                  */
void topup();
void TOP_UP_MENU();
double addbalance(int option);

/*					     Menu Module				       */
void MENU();
void BREAKFAST_MENU();
void CHICKEN_MENU();
void BEEF_MENU();
void PREMIUM_MENU();
void DRINKS_MENU();
void DESSERT_MENU();
void SIDES_MENU();

/*                  Payment & Member Point Module                */
void payment(int dine);
double memberpointadd(double subtotal, double memberpoint);
double memberpointsub1(double subtotal, double convertmemberpoint);
double memberpointsub2(double subtotal, double* convert, double topupvalue);

/*                     Exit Program Module                  */
void exitProgram();
/***********************************************************************************/


int main() {

	home();

	return 0;
}

/***********************************************************************************/
/*                REGISRATION MODULE USER-DECLARED FUNCTIONS               */
//homepage 
void home() {
	vector<Customer> customers;


	int choice = 0;

	do
	{

		logo();
		cout << "Your Choice Here: ";
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cin.ignore();
		}


		switch (choice)
		{
		case 1:
		{
			registerNewCustomer(customers);
			break;
		}

		case 2:
		{
			login(customers);
			break;
		}
		
		case 3:
		{
			topup(); 
			break;
		}

		case 4:
		{
			MENU();
			break;
		}

		case 5:
		{
			exitProgram();
			break;
		}

		default:
			cout << "\nPlease Enter a Valid Number." << endl;
			break;
		}

		cout << "\nPress Enter to continue...";
		cin.get();
		
	} while (choice != 5);

}

//function display logo
void logo()
{
	int choice = 0;
	cout << "\n __          __  ______   _         _____    ____    __  __   ______     _______    ____    " << endl;
	cout << " \\ \\        / / |  ____| | |       / ____|  / __ \\  |  \\/  | |  ____|   |__   __|  / __ \\   " << endl;
	cout << "  \\ \\  /\\  / /  | |__    | |      | |      | |  | | | \\  / | | |__         | |    | |  | |  " << endl;
	cout << "   \\ \\/  \\/ /   |  __|   | |      | |      | |  | | | |\\/| | |  __|        | |    | |  | |  " << endl;
	cout << "    \\  /\\  /    | |____  | |____  | |____  | |__| | | |  | | | |____       | |    | |__| |  " << endl;
	cout << "     \\/  \\/     |______| |______|  \\_____|  \\____/  |_|  |_| |______|      |_|     \\____/   " << endl;
	cout << "\n \n";
	cout << "  ____    _    _   _____     _____   ______   _____      _  __  _____   _   _    _____      " << endl;
	cout << " |  _ \\  | |  | | |  __ \\   / ____| |  ____| |  __ \\    | |/ / |_   _| | \\ | |  / ____|     " << endl;
	cout << " | |_) | | |  | | | |__) | | |  __  | |__    | |__) |   | ' /    | |   |  \\| | | |  __      " << endl;
	cout << " |  _ <  | |  | | |  _  /  | | |_ | |  __|   |  _  /    |  <     | |   | . ` | | | |_ |     " << endl;
	cout << " | |_) | | |__| | | | \\ \\  | |__| | | |____  | | \\ \\    | . \\   _| |_  | |\\  | | |__| |     " << endl;
	cout << " |____/   \\____/  |_|  \\_\\  \\_____| |______| |_|  \\_\\   |_|\\_\\ |_____| |_| \\_|  \\_____|     " << endl;
	cout << "\n";

	cout << "************************************************* \n";
	cout << "************************************************* \n";
	cout << "|*| How Can I Help You? \n\n";
	cout << "	1.Register - Make a new Account\n";
	cout << "	2.Check Member Account info\n";
	cout << "	3.Top Up Member Card\n";
	cout << "	4.Menu\n";
	cout << "	5.Exit\n\n";
	cout << "************************************************* \n";
	cout << "************************************************* \n";

}

/*                    REGISTER MODULE USER-DECLARED FUNCTIONS                  */
// Function to validate the customer name
bool validateName(const string& name)
{
	if (name.empty() || name.length() < 3 || name.length() > 30) //check the name should not be empty , length between 3 - 30 char , only contain alphatic char and special symbol and space 

	{
		return false;
	}
	for (char i : name)
	{
		if (!isalpha(i) && i != ' ' && i != '\'' && i != '-' && i != '.' && i != '_')
		{
			return false;
		}
	}
	return true;
}


// Function to validate the contact number
bool validateContact(const string& contact)
{
	if (contact.empty() || contact.length() < 5)//check the contact number should not be empty , length greater than 5 , only contain digit and special symbol and space
	{
		return false;
	}
	for (char i : contact)
	{
		if (!isdigit(i) && i != '-' && i != ' ' && i != '+')
		{
			return false;
		}
	}
	return true;
}


// Function to validate the age
bool validateAge(const string& ageString)
{
	if (ageString.empty()) //check the age should not be empty, only contain digit and range 1 - 120
	{
		return false;
	}
	for (char i : ageString)
	{
		if (!isdigit(i))
		{
			return false;
		}
	}
	int age = stoi(ageString);
	return (age > 0 && age <= 120);
}


void writeToFile(const Customer& customer)
{
	ofstream outFile("customer_data.txt", ios::app);
	if (outFile.is_open())
	{

		outFile << customer.memberID << "," << customer.name << "," << customer.contact << "," << customer.age << " " << fixed << setprecision(2) << customer.balance << " " << customer.memberPoint << endl;
		outFile.close();
	}
	else
	{
		cout << "Unable to open file for writing.\n";
	}

}


void registerNewCustomer(vector<Customer>& customers)
{
	Customer newCustomer;        // Create a new Customer instance
	string randomString;
	
	cout << "\n======================REGISTER======================\n\n";
	cin.ignore();
	while (true) // Validate the name
	{
		cout << "Full Name		-->";
		getline(cin,newCustomer.name);//get user input

		if (validateName(newCustomer.name))
		{
			// The name is valid
			break;
		}
		else
		{	//if the name is invalid
			cout << "Please enter a valid name, Thank You\n";
			cout << flush;
		}
	}

	while (true) // Validate the contact number
	{
		cout << "\nContact Number		-->";
		getline(cin, newCustomer.contact); //get user input

		if (validateContact(newCustomer.contact))
		{
			// The contact number is valid
			break;
		}
		else
		{	//if the input is invalid
			cout << "Please enter a valid contact number, Thank You\n";
		}
	}

	while (true) // Validate the age
	{
		cout << "\nAge			-->";
		getline(cin, newCustomer.ageString); //get user input

		if (validateAge(newCustomer.ageString))
		{
			// The age is valid
			newCustomer.age = stoi(newCustomer.ageString);
			break;
		}
		else
		{	//if the user input is invalid
			cout << "Invalid age. Please enter a valid age,Thank You\n";
		}
	}

	// Generate random memberID
	srand(static_cast<unsigned int>(time(0)));  // to prevent the same number to be generate
	int randomNumber = rand() % 1000000; // generate a random number between 0 and 999,999
	randomString = to_string(randomNumber);		// convert the random number to a 6 digit string with leading zeros
	while (randomString.length() < 6)
	{
		randomString = "0" + randomString;
	}
	newCustomer.memberID = "ABC" + randomString; // asign the formatted string to the memberID


	newCustomer.balance = 0;		// initial the member balance
	newCustomer.memberPoint = 0;	// initial the member point

	cout << "\nCongratulations Registration successful!\n" << endl;

	cout << "\n====================ACCOUNT INFO====================\n\n";
	cout << "-----------------------------------------------------------" << endl;
	cout << setw(27) << "Customer Info" << endl;
	cout << "Name \t\t\t: " << newCustomer.name << endl;
	cout << "MemberID \t\t: " << newCustomer.memberID << endl;
	cout << "Card Balance (RM) \t: " << fixed << setprecision(2) << newCustomer.balance << endl;
	cout << "Member Point \t\t: " << fixed << setprecision(2) << newCustomer.memberPoint << endl;
	cout << "Member Age \t\t: " << newCustomer.ageString << endl;
	cout << "Member Contact\t\t: " << newCustomer.contact << endl;
	cout << "-----------------------------------------------------------" << endl;

	writeToFile(newCustomer);	//call the write file function, write the member data into a txt file
	cout << flush;
}


void login(vector<Customer>& customers)
{
	string MemberID;
	Customer customer; //create a customer object to store data
	ifstream inFile;
	string templine;
	int lcter = 0;
	cout << "\n====================ACCOUNT INFO====================\n\n";
	
	do {
		cout << "Enter Member ID: ";
		cin >>MemberID;
		transform(MemberID.begin(), MemberID.end(), MemberID.begin(), ::toupper);

		lcter = 0;
		inFile.open("customer_data.txt", ios::in);
		if (inFile.fail()) {
			cout << "Error Reading File" << endl;// if file cannot open print Error Reading File and close the program
		}
		else if (!inFile.eof()) {
			while (getline(inFile, templine)) {
				lcter++;
				istringstream iss(templine); // store line in iss
				getline(iss, customer.memberID, ',');
				getline(iss, customer.name, ',');
				getline(iss, customer.contact, ',');
				iss >> customer.age;
				iss >> customer.balance;
				iss >> customer.memberPoint;
				iss.ignore();//ignore the buffer
				//print customer info
				if (MemberID == customer.memberID) {
					cout << "-----------------------------------------------------------" << endl;
					cout << setw(27) << "Customer Info" << endl;
					cout << "Name \t\t\t: " << customer.name << endl;
					cout << "MemberID \t\t: " << customer.memberID << endl;
					cout << "Card Balance (RM) \t: " << fixed << setprecision(2) << customer.balance << endl;
					cout << "Member Point \t\t: " << fixed << setprecision(2) << customer.memberPoint << endl;
					cout << "Member Age \t\t: " << customer.age << endl;
					cout << "Member Contact\t\t: " << customer.contact << endl;
					cout << "-----------------------------------------------------------" << endl;
					break;
				}
			}
			inFile.close();
			if (MemberID != customer.memberID) { //if the id is not at file then will print Enter a valid member id 
				cout << "Enter a valid member id" << endl;
			}
		}
	} while (MemberID != customer.memberID);
	cin.get();
}

/*                    TOPUP MODULE USER-DECLARED FUNCTIONS                   */
struct TOPUP {
	int option = 0;
	double amount = 0.0;
};

struct Members {
	string memberids;
	string names;
	string contact;
	int age = 0;
	double topupvalue = 0.0;
	double memberPoints = 0.0;
};

void topup()
{
	//declare variable
	string memberidInput = " ", line = " ", card_num = " ", card_pin = " ";
	vector<string>lines;
	int topup_option = 0, linecounter = 0;
	double topup_total = 0.0, add_balance = 0.0;
	char cont = '0';
	fstream idFile;
	ofstream temp;
	Members members;

	cout << "\n===========================================================" << endl;
	cout << "                         TOP UP                           " << endl;
	cout << "===========================================================" << endl;

	do {
		cout << "Enter the card number: ";
		cin >> memberidInput;
		transform(memberidInput.begin(), memberidInput.end(), memberidInput.begin(), ::toupper);// convert lower case to upper case

		linecounter = 0;//reset counter
		idFile.open("customer_data.txt", ios::in);
		if (idFile.fail()) {
			cout << "Error Reading File" << endl;// if file cannot open print Error Reading File and close the program
		}
		else if (!idFile.eof()) {
			while (getline(idFile, line)) {
				linecounter++; //counter for the line number or customer info
				istringstream iss(line); // store line in iss
				getline(iss, members.memberids, ',');
				getline(iss, members.names, ',');  // Read name until comma
				getline(iss, members.contact, ',');
				iss >> members.age;
				iss >> members.topupvalue; //read data from iss
				iss >> members.memberPoints;
				iss.ignore();//ignore the buffer
				//print customer info
				if (memberidInput == members.memberids) {
					cout << "-----------------------------------------------------------" << endl;
					cout << setw(27) << "Customer Info" << endl;
					cout << "Name                     : " << members.names << endl;
					cout << "MemberID                 : " << members.memberids << endl;
					cout << "Contact                  : " << members.contact << endl;
					cout << "Age                      : " << members.age << endl;
					cout << "Card Balance (RM)        : " << members.topupvalue << endl;
					cout << "Member Point(RM1 = 100)  : " << fixed << setprecision(2) << members.memberPoints << endl;
					cout << "-----------------------------------------------------------" << endl;
					break;
				}
			}
			idFile.close();
			if (memberidInput != members.memberids) { //if the id is not at file then will print Enter a valid member id
				cout << "Enter a valid member id" << endl;
			}
		}
	} while (memberidInput != members.memberids);

	do {
		do {
			TOP_UP_MENU();
			cout << "Enter the top up option (Press 0 to exit)  " << endl;
			cout << "Option : ";
			cin >> topup_option;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore();
				cin.sync();
				cin.get();
				cout << "Please enter valid selection." << endl;
				topup_option = 90;
			}

			else if (topup_option != 0 && topup_option != 1 && topup_option != 2 && topup_option != 3 && topup_option != 4)
			{
				cout << "\n";
				cout << "Please enter valid selection : " << endl;
			}
		} while (topup_option != 0 && topup_option != 1 && topup_option != 2 && topup_option != 3 && topup_option != 4);

		// ---------------------- PAYMENT  ---------------------- 
		add_balance = addbalance(topup_option);
		members.topupvalue += add_balance;

		if (topup_option == 0) {
			idFile.open("customer_data.txt", ios::in);
			if (idFile.fail()) { // if file fail to open will print error message
				cout << "Error Reading File" << endl;
			}
			else if (idFile.is_open()) {
				while (getline(idFile, line)) {
					lines.push_back(line); //read all the data line by line and store it in vector
				}
			}idFile.close();

			temp.open("customer_data.txt");
			if (temp.is_open()) {
				linecounter--;
				for (int i = 0; i < lines.size(); i++) {
					if (i != linecounter)
						temp << lines[i] << endl;
					else
						temp << members.memberids << "," << members.names << "," << members.contact << "," << members.age << " " << fixed << setprecision(2) << members.topupvalue << " " << members.memberPoints <<  endl;
				}
			}temp.close();
			home();
		}
		else
		{
			cout << "\n";
			cout << "Payment Successful.\n" << endl;
			cout << "===========================================================" << endl;
			cout << "New Account Balance\t\t\t\t: RM" << fixed << setprecision(2) << members.topupvalue << endl ;
			cout << "===========================================================" << endl;

			// Prompt user whether want to top up again
			do {
				cout << "\nDo you wish to top up again ? (Y/N) "<<endl;
				cout << "Option : ";
				cin >> cont;

				if (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n')
				{
					cout << "\n";
					cout << "Please enter valid selection." << endl;
				}
				else if (cont == 'n' || cont == 'N')
				{
					// Display the new balance of the member account
					cout << "\n";
					cout << "New Account Balance				: RM" << fixed << setprecision(2) << members.topupvalue << endl;
					cout << "Thank You." << endl;
					cout << "\nPress Enter to continue...";
					cin.get();
					cin.ignore();
					break;
				}
			} while (cont != 'Y' && cont != 'y');
		}
	} while (cont == 'Y' || cont == 'y');

		idFile.open("customer_data.txt", ios::in);
		if (idFile.fail()) { // if file fail to open will print error message
			cout << "Error Reading File" << endl;
		}
		else if (idFile.is_open()) {
			while (getline(idFile, line)) {
				lines.push_back(line); //read all the data line by line and store it in vector
			}
		}idFile.close();

		temp.open("customer_data.txt");
		if (temp.is_open()) { 
			linecounter--; 
			for (int i = 0; i < lines.size(); i++) { 
				if (i != linecounter) 
					temp << lines[i] << endl; 
				else
					temp << members.memberids << "," << members.names << "," << members.contact << "," << members.age << " " << fixed << setprecision(2) << members.topupvalue << " " << members.memberPoints << endl; 
			}  
		}temp.close(); 

	home(); 
}

void TOP_UP_MENU()
{
	string temp_line = "";
	ifstream topup_menu;
	TOPUP topup;
	topup.option = 0;
	topup.amount = 0.0;
	topup_menu.open("top_up.txt");

	if (!topup_menu)
	{
		cout << "Error opening file" << endl; //check if file opens successfully
	}

	else if (!topup_menu.eof()) {
		cout << "\n";
		cout << "TOP UP OPTION : " << endl;
	}

	// Display the available top up option
	do {
		getline(topup_menu, temp_line); //read from the file line by line
		istringstream menuSS(temp_line); //create a stringstream object and store line in menuSS
		menuSS >> topup.option;// read the number of option
		menuSS.ignore();
		menuSS >> topup.amount; // read the option of top up amount
		cout <<"     " << topup.option << ".   >> " << "  RM " << fixed << setprecision(2) << topup.amount << endl;
	} while (topup_menu.good());
	topup_menu.close();
}

double addbalance(int option)
{
	int count = 0, payment_option = 0;
	double add_bal = 0.0;
	double topup_value[4] = { 0.0 };
	string temp_line = "";
	ifstream topup_menu;
	TOPUP topup;
	Members members;
	const double CHARGE = 0.50;		// fixed the service charges
	topup.option = 0;
	topup.amount = 0.0;

	topup_menu.open("top_up.txt");
	if (!topup_menu)
	{
		cout << "Error opening file" << endl; //check if file opens successfully
	}

	else if (!topup_menu.eof()) {
		do {
			getline(topup_menu, temp_line); //read from the file line by line
			istringstream menuSS(temp_line); //create a stringstream object and store line in menuSS
			menuSS >> topup.option;// read the number of option
			menuSS.ignore();
			menuSS >> topup.amount; // read the option of top up amount
			topup_value[count] = topup.amount;		// store the top up amount in an array to be display
			count++;
		} while (topup_menu.good());
	}
	topup_menu.close();


	// add the value to the balance according to user selection
	switch (option)
	{
	case 0:
		add_bal = add_bal;
		cout << "Thank You.";
		return add_bal; // return the value to the topup function

	case 1:
		add_bal = topup_value[0] - CHARGE;		// each topup_value refers to top up amount according to the sequence 
		break;

	case 2:
		add_bal = topup_value[1] - CHARGE;
		break;

	case 3:
		add_bal = topup_value[2] - CHARGE;
		break;

	case 4:
		add_bal = topup_value[3] - CHARGE;
		break;

	default:
		cout << "Please enter valid option." << endl;
	}

	do {
		cout << "\n";
		cout << "===========================================================" << endl;
		cout << setw(32) << "CHECKOUT" << endl;
		cout << "===========================================================" << endl;
		cout << "Top up amount					: RM" << fixed << setprecision(2) << add_bal + CHARGE << endl;
		cout << "Service Charges					: -RM" << fixed << setprecision(2) << CHARGE << endl;
		cout << "Subtotal					: RM" << fixed << setprecision(2) << add_bal << endl;
		cout << "\nPress 1 to confirm payment, 0 to cancel payment." << endl;		// confirmation of payment
		cout << "Enter your selection : ";
		cin >> payment_option;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cin.sync();
			cout << "Please enter valid selection." << endl;
			payment_option = 9;
		}

		else if (payment_option != 1 && payment_option != 0)
		{
			cout << "\n";
			cout << "Please enter valid selection. " << endl;
		}

	} while (payment_option != 1 && payment_option != 0);


	if (payment_option == 0)
	{
		cout << "Thank You.";
		home();
	}

	return add_bal;
}

/*                    MENU MODULE USER-DECLARED FUNCTIONS                   */
void MENU() {
	//declare variables to be used
	int categoryChoice = 0, checkoutChoice = 0, diningMethod = 0; //variables for selection of menu category, checkout menu, dine-in or take-away
	int editNum = 0, i = 0, newQuantity = 0; //variables to accomodate editing of orders and printing of vector
	int maxNameWidth = 0, maxPriceWidth = 0, maxQuantityWidth = 0; //used to set a fixed with between variables when printing checkout
	double total = 0.0; //variables for adding on service charge or packaging charge 
	const float dine_in = 0.10;
	const float take_away = 2.00;//declare constants for dine-in and take-away charges


	do { //loop to return to menu if user wishes to add on different orders after checkout menu displayed
		do {
			cout << "\n\n================================================================" << endl;
			cout << "			   MENU                               " << endl;
			cout << "================================================================\n" << endl;
			cout << setw(65) << setfill('=') << endl;
			cout << "\n";
			cout << "Select a Menu Category" << endl;
			cout << "\n";
			cout << "1: \t Breakfast" << setw(20) << setfill(' ') << "5: \t Drinks" << endl;
			cout << "2: \t Chicken" << setw(23) << setfill(' ') << "6: \t Dessert" << endl;
			cout << "3: \t Beef" << setw(24) << setfill(' ') << "7: \t Sides" << endl;
			cout << "4: \t Premium" << endl;
			cout << "================================================================";
			cout << "\nEnter 0 to exit to main menu. \t Enter 9 to proceed to checkout.";
			cout << "\n\nEnter selection: ";
			cin >> categoryChoice;
			if (cin.fail()) { //validate input is only an integer 
				cin.clear();
				cin.sync();
				cin.ignore();
				categoryChoice = 95; //assign a value to categoryChoice to prevent it from being 0
			}
			//use switch selection to choose which subcategory to display
			switch (categoryChoice) {
			case 0:
				orderList.clear(); //cancels order selection
				home();			// returns to main menu
				break;
			case 1: {
				BREAKFAST_MENU();
				break;
			}
			case 2: {
				CHICKEN_MENU();
				break;
			}
			case 3: {
				BEEF_MENU();
				break;
			}
			case 4: {
				PREMIUM_MENU();
				break;
			}
			case 5: {
				DRINKS_MENU();
				break;
			}
			case 6: {
				DESSERT_MENU();
				break;
			}
			case 7: {
				SIDES_MENU();
				break;
			}
			case 9: {
				break;	//proceed to checkout
			}
			default: {
				cout << "\n";
				cout << "Please Enter a Valid Selection.";
				cout << "\n";
			}
			}
		} while (categoryChoice != 9);


		do {
			//display order list
			cout << setw(65) << setfill('=') << endl;
			cout << "\n";
			cout << "CHECKOUT:\n" << endl;



			for (i = 0; i < orderList.size(); i++) //set a fixed width between itemName, price and quantity
			{
				int nameWidth = orderList[i].itemName.length();
				int priceWidth = to_string(orderList[i].price).length();
				int quantityWidth = to_string(orderList[i].quantity).length();

				if (nameWidth > maxNameWidth) {
					maxNameWidth = nameWidth;
				}

				if (priceWidth > maxPriceWidth) {
					maxPriceWidth = priceWidth;
				}

				if (quantityWidth > maxQuantityWidth) {
					maxQuantityWidth = quantityWidth;
				}
			}

			for (i = 0; i < orderList.size(); i++) //print ordered items from vector
			{
				cout << i + 1 << " " << setw(maxNameWidth) << setfill(' ') << left << orderList[i].itemName << " " << setw(maxPriceWidth) << fixed << setprecision(2) << right << "Price: RM " << orderList[i].price << setw(maxQuantityWidth) << "	 Qty: " << orderList[i].quantity << endl;
			}

			cout << setw(65) << setfill('=') << endl;
			cout << "\n";
			cout << "\nPress : 0 to return to order menu" << endl;
			cout << "        1 to edit orders"<<endl;
			cout << "        2 to remove an order" << endl;
			cout << "        3 to clear all orders" << endl;
			cout << "        9 to proceed" << endl;
			cout << "\nEnter selection: ";
			cin >> checkoutChoice;
			if (cin.fail()) { //validate input is only an integer
				cin.clear();
				cin.sync();
				cin.ignore();
				checkoutChoice = 5; //set to invalid number to continue loop
			}

			if (checkoutChoice == 0) {
				MENU();
			}
			else if (checkoutChoice == 1) {
				//edit orders
				cout << "\n";
				cout << "     ======================" << endl;
				cout << "           EDIT ORDER" << endl;
				cout << "     ======================" << endl;
				cout << "Enter the order number to edit : ";
				cin >> editNum;
				if (editNum >= 1 && editNum <= orderList.size()) { //check if order number is valid using vector size, checking starts from i=1
					cout << "Enter the new quantity         : ";			//if valid, prompt user to enter new quantity
					cin >> newQuantity;
					orderList[editNum - 1].quantity = newQuantity;
					orderList[editNum - 1].price = orderList[editNum - 1].price * newQuantity;
				}
				else {
					cout << "\nPlease enter a Valid Selection.";
					cout << "\n";
					continue;
				}
			}
			else if (checkoutChoice == 2) {
				//remove an order
				cout << "\n";
				cout << "     ======================" << endl;
				cout << "           REMOVE ORDER" << endl;
				cout << "     ======================" << endl;
				cout << "Enter the order number to remove: ";
				cin >> editNum;
				if (editNum >= 1 && editNum <= orderList.size()) {
					orderList.erase(orderList.begin() + editNum - 1);
				}
				else {
					cout << "\nPlease enter a Valid Selection.";
					cout << "\n";
					continue;
				}
			}
			else if (checkoutChoice == 3) {
				//clear all orders
				cout << "\n";
				cout << "     ======================" << endl;
				cout << "           ORDER CLEAR" << endl;
				cout << "     ======================" << endl;
				orderList.clear();
				continue;
			} 
			else if (checkoutChoice == 9) {
				//proceed to payment
				break;
			}
			else {
				cout << "\nPlease enter a Valid Selection.";
				cout << "\n";
				continue;
			}
		} while (checkoutChoice != 9);

		if (checkoutChoice == 9)
		{
			do
			{
				cout << setw(65) << setfill('=') << endl;
				cout << "\n";
				cout << "     ===============================" << endl;
				cout << "           Dine-In or Take-away" << endl;
				cout << "     ===============================" << endl;

				cout << "\nPress 1 for dine-in, 2 for take-away." << endl;
				cout << "Enter selection: ";

				cout << fixed << setprecision(2) ; //to ensure display for price has two decimal points (RM x.xx)

				cin >> diningMethod;
				if (cin.fail()) {
					cin.clear();
					cin.sync();
					cin.ignore();
					diningMethod = 99; //set to invalid number to continue loop
				}
				switch (diningMethod)
				{
				case 1:
				case 2:
				{
					cin.get();
					payment(diningMethod);
					break;
				}
				default: {
					cout << "\nPlease enter a Valid Selection." << endl;
				}
				}
			} while (diningMethod != 1 && diningMethod != 2);
		}
		else
			continue;
	} while (categoryChoice != 9 || checkoutChoice != 9);
}

void BREAKFAST_MENU() {
	//declare input from file to stream
	ifstream inBreakfast;
	//declare variables to be used
	int listChoice = 0, meal_selection = 0;
	string temp_line = "";
	menu breakfast;
	breakfast.list = 0;
	breakfast.itemName = "";
	breakfast.alaCarte = 0.0;
	breakfast.setMeal = 0.0;
	//declare an array to store user input data 


	inBreakfast.open("breakfast.txt");
	if (!inBreakfast) {
		cout << "Error opening file" << endl; //check if file opens successfully
	}
	else if (!inBreakfast.eof()) {
		cout << setw(65) << setfill('=') << endl;
		cout << "\n";
		cout << "	BREAKFAST MENU";
		cout << setw(65) << setfill('=') << endl;
		cout << "\n";

		do {
			getline(inBreakfast, temp_line); //read from the file line by line
			istringstream menuSS(temp_line); //create a stringstream object and store line in menuSS
			menuSS >> breakfast.list; //read list number
			menuSS.ignore(); //ignores buffer
			getline(menuSS, breakfast.itemName, ','); //read until comma
			menuSS >> breakfast.alaCarte; //read alaCarte price
			menuSS >> breakfast.setMeal; //read setMeal price
			cout << breakfast.list << " " << breakfast.itemName << fixed << setprecision(2) << endl;
		} while (inBreakfast.good());
		inBreakfast.close();
		cout << "\nPress 0 to return to main menu" << endl;
		cout << "Enter selection: ";

		cin >> listChoice;
		cout << '\n';
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cin.ignore();
			listChoice = 55; //set to invalid number to continue loop
		}
		if (listChoice == 0)
		{
			return; //returns to menu
		}
		else if (listChoice > breakfast.list) { //checks for user input error (selection num greater than listed)
			cout << "\nPlease enter a Valid Selection.";
			cout << "\n";
			return;
		}
		else
		{
		cout << "\n";
		cout << "     ======================" << endl;
		cout << "     Ala Carte or Set Meal?" << endl;
		cout << "     ======================" << endl;
			inBreakfast.open("breakfast.txt");
			while (getline(inBreakfast, temp_line))
			{
				istringstream menuSS(temp_line);
				menuSS >> breakfast.list;
				menuSS.ignore();
				getline(menuSS, breakfast.itemName, ',');
				menuSS >> breakfast.alaCarte;
				menuSS >> breakfast.setMeal;
				if (listChoice == breakfast.list)//match the selection to the list from file
				{
					cout << breakfast.itemName << endl;
					cout << "Ala Carte:	 RM " << breakfast.alaCarte << endl;
					cout << "Set Meal :	 RM " << breakfast.setMeal << endl;
					break;
				}
			}
			inBreakfast.close();
		}

		cout << "\nPress 1 for ala carte, 2 for set meal." << endl;
		cout << "Enter selection: ";
		cin >> meal_selection;
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cin.ignore();
		}
		switch (meal_selection) {
		case 1:
		{
			cout << "\n";
			cout << "     ======================" << endl;
			cout << "            Quantity" << endl;
			cout << "     ======================" << endl;
			cout << "Enter quantity : ";
			cin >> breakfast.quantity;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				cout << "\nPlease enter a Valid Selection." << endl;
				break;
			}
			breakfast.itemName += " (A)";
			breakfast.price = breakfast.alaCarte * breakfast.quantity;
			orderList.push_back(breakfast);  //add ordered items to vector
			cout << "\nOrder has been added to checkout list ~ ~";
			break;
		}
		case 2:
		{
			cout << "\n";
			cout << "     ======================" << endl;
			cout << "            Quantity" << endl;
			cout << "     ======================" << endl;
			cout << "Enter quantity: ";
			cin >> breakfast.quantity;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				cout << "\nPlease enter a Valid Selection." << endl;
				break;
			}
			breakfast.itemName += " (SET)";
			breakfast.price = breakfast.setMeal * breakfast.quantity;
			orderList.push_back(breakfast);
			cout << "\nOrder has been added to checkout list ~ ~";
			break;
		}
		default:
			cout << "\nPlease enter a Valid Selection." << endl;
		}

	}
}
void CHICKEN_MENU() {
	//declare input from file to stream
	ifstream inChicken;
	//declare variables to be used
	int listChoice = 0, meal_selection = 0;
	string temp_line = "";
	menu chicken;
	chicken.list = 0;
	chicken.itemName = "";
	chicken.alaCarte = 0.0;
	chicken.medium = 0.0;
	chicken.large = 0.0;
	//declare an array to store user input data 


	inChicken.open("chicken.txt");
	if (!inChicken) {
		cout << "Error opening file" << endl; //check if file opens successfully
	}
	else if (!inChicken.eof()) {
		cout << setw(65) << setfill('=') << endl;
		cout << "\n";
		cout << "	CHICKEN BURGERS MENU";
		cout << setw(65) << setfill('=') << endl;
		cout << "\n";

		do {
			getline(inChicken, temp_line); //read from the file line by line
			istringstream menuSS(temp_line); //create a stringstream object and store line in menuSS
			menuSS >> chicken.list;
			menuSS.ignore(); //ignores buffer
			getline(menuSS, chicken.itemName, ','); //read until comma
			menuSS >> chicken.alaCarte;
			menuSS >> chicken.medium;
			menuSS >> chicken.large;
			cout << chicken.list << " " << chicken.itemName << fixed << setprecision(2) << endl;
		} while (inChicken.good());
		inChicken.close();
		cout << "Press 0 to return to main menu" << endl;
		cout << '\n';
		cout << "Enter selection: ";

		cin >> listChoice;
		cout << '\n';
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cin.ignore();
		}
		if (listChoice == 0)
		{
			return; //returns to main menu
		}
		else if (listChoice > chicken.list) { //checks for user input error (selection num greater than listed)
			cout << "Please Enter a Valid Selection.";
			cout << "\n";
			return;
		}
		else
		{
			cout << "\n";
			cout << "     ===============================" << endl;
			cout << "     Ala Carte, Medium or Large set?" << endl;
			cout << "     ===============================" << endl;

			inChicken.open("chicken.txt");
			while (getline(inChicken, temp_line))
			{
				istringstream menuSS(temp_line);
				menuSS >> chicken.list; //read list number
				menuSS.ignore();
				getline(menuSS, chicken.itemName, ',');
				menuSS >> chicken.alaCarte;
				menuSS >> chicken.medium; //read Medium Set price
				menuSS >> chicken.large; //read Large Set price
				if (listChoice == chicken.list)//match the selection to the list from file
				{
					cout << chicken.itemName << endl;
					cout << "Ala Carte :	RM " << chicken.alaCarte << endl;
					cout << "Medium Set:	RM " << chicken.medium << endl;
					cout << "Large Set :	RM " << chicken.large << endl;
					break;
				}
			}
			inChicken.close();
		}

		cout << "\nPress 1 for ala carte, 2 for medium set, 3 for large set." << endl;
		cout << "Enter selection: ";
		cin >> meal_selection;
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cin.ignore();
		}
		switch (meal_selection) {
		case 1:
		{
			cout << "\n";
			cout << "     ======================" << endl;
			cout << "            Quantity" << endl;
			cout << "     ======================" << endl;
			cout << "Enter quantity: ";
			cin >> chicken.quantity;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				cout << "\nPlease enter a Valid Selection." << endl;
				break;
			}
			chicken.itemName += " (A)";
			chicken.price = chicken.alaCarte * chicken.quantity;
			orderList.push_back(chicken); //add ordered items to vector
			cout << "\nOrder has been added to checkout list ~ ~";
			break;
		}
		case 2:
		{
			cout << "\n";
			cout << "     ======================" << endl;
			cout << "            Quantity" << endl;
			cout << "     ======================" << endl;
			cout << "Enter quantity: ";
			cin >> chicken.quantity;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				cout << "\nPlease enter a Valid Selection." << endl;
				break;
			}
			chicken.itemName += " (M)";
			chicken.price = chicken.medium * chicken.quantity;
			orderList.push_back(chicken);
			cout << "\nOrder has been added to checkout list ~ ~";
			break;
		}
		case 3:
		{
			cout << "\n";
			cout << "     ======================" << endl;
			cout << "            Quantity" << endl;
			cout << "     ======================" << endl;
			cout << "Enter quantity: ";
			cin >> chicken.quantity;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				cout << "\nPlease enter a Valid Selection." << endl;
				break;
			}
			chicken.itemName += " (L)";
			chicken.price = chicken.large * chicken.quantity;
			orderList.push_back(chicken);
			cout << "\nOrder has been added to checkout list ~ ~";
			break;
		}
		default:
			cout << "\nPlease Enter a Valid Selection." << endl;
		}

	}
}
void BEEF_MENU() {
	//declare input from file to stream
	ifstream inBeef;
	//declare variables to be used
	int listChoice = 0, meal_selection = 0;
	string temp_line = "";
	menu beef;
	beef.list = 0;
	beef.itemName = "";
	beef.alaCarte = 0.0;
	beef.medium = 0.0;
	beef.large = 0.0;
	//declare an array to store user input data 


	inBeef.open("beef.txt");
	if (!inBeef) {
		cout << "Error opening file" << endl; //check if file opens successfully
	}
	else if (!inBeef.eof()) {
		cout << setw(65) << setfill('=') << endl;
		cout << "\n";
		cout << "	BEEF BURGERS MENU";
		cout << setw(65) << setfill('=') << endl;
		cout << "\n";

		do {
			getline(inBeef, temp_line); //read from the file line by line
			istringstream menuSS(temp_line); //create a stringstream object and store line in menuSS
			menuSS >> beef.list; //read list number
			menuSS.ignore(); //ignores buffer
			getline(menuSS, beef.itemName, ','); //read until comma
			menuSS >> beef.alaCarte;
			menuSS >> beef.medium; //read Medium Set price
			menuSS >> beef.large; //read Large Set price
			cout << beef.list << " " << beef.itemName << fixed << setprecision(2) << endl;
		} while (inBeef.good());
		inBeef.close();
		cout << "\nPress 0 to return to main menu" << endl;
		cout << "Enter selection: ";


		cin >> listChoice;
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cin.ignore();
		}
		cout << "\n";
		if (listChoice == 0)
		{
			return; //returns to main menu
		}
		else if (listChoice > beef.list) { //checks for user input error (selection num greater than listed)
			cout << "\nPlease Enter a Valid Selection.";
			cout << "\n";
			return;
		}
		else
		{
		cout << "\n";
		cout << "     ===============================" << endl;
		cout << "     Ala Carte, Medium or Large set?" << endl;
		cout << "     ===============================" << endl;
		inBeef.open("beef.txt");
		while (getline(inBeef, temp_line))
		{

			istringstream menuSS(temp_line);
			menuSS >> beef.list;
			menuSS.ignore();
			getline(menuSS, beef.itemName, ',');
			menuSS >> beef.alaCarte;
			menuSS >> beef.medium;
			menuSS >> beef.large;

			if (listChoice == beef.list)//match the selection to the list from file
			{
				cout << beef.itemName << endl;
				cout << "Ala Carte :	RM " << beef.alaCarte << endl;
				cout << "Medium Set:	RM " << beef.medium << endl;
				cout << "Large Set :	RM " << beef.large << endl;
				break;
			}
		}
		inBeef.close();
		}

		cout << "\nPress 1 for ala carte, 2 for medium set, 3 for large set." << endl;
		cout << "Enter selection: ";
		cin >> meal_selection;
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cin.ignore();
		}
		switch (meal_selection) {
		case 1:
		{
			cout << "\n";
			cout << "     ======================" << endl;
			cout << "            Quantity" << endl;
			cout << "     ======================" << endl;
			cout << "Enter quantity: ";
			cin >> beef.quantity;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				cout << "\nPlease enter a Valid Selection." << endl;
				break;
			}
			beef.itemName += " (A)";
			beef.price = beef.alaCarte * beef.quantity;
			orderList.push_back(beef); //add ordered items to vector
			cout << "\nOrder has been added to checkout list ~ ~";
			break;
		}
		case 2:
		{
			cout << "\n";
			cout << "     ======================" << endl;
			cout << "            Quantity" << endl;
			cout << "     ======================" << endl;
			cout << "Enter quantity: ";
			cin >> beef.quantity;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				cout << "\nPlease enter a Valid Selection." << endl;
				break;
			}
			beef.itemName += " (M)";
			beef.price = beef.medium * beef.quantity;
			orderList.push_back(beef);
			cout << "\nOrder has been added to checkout list ~ ~";
			break;
		}
		case 3:
		{
			cout << "\n";
			cout << "     ======================" << endl;
			cout << "            Quantity" << endl;
			cout << "     ======================" << endl;
			cout << "Enter quantity: ";
			cin >> beef.quantity;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				cout << "\nPlease enter a Valid Selection." << endl;
				break;
			}
			beef.itemName += " (L)";
			beef.price = beef.large * beef.quantity;
			orderList.push_back(beef); 
			cout << "\nOrder has been added to checkout list ~ ~";
			break;
		}
		default:
			cout << "\nPlease Enter a Valid Selection." << endl;
		}

	}
}
void PREMIUM_MENU() {
	//declare input from file to stream
	ifstream inPremium;
	//declare variables to be used
	int listChoice = 0, meal_selection = 0;
	string temp_line = "";
	menu premium;
	premium.list = 0;
	premium.itemName = "";
	premium.alaCarte = 0.0;
	premium.medium = 0.0;
	premium.large = 0.0;
	//declare an array to store user input data 


	inPremium.open("premium.txt");
	if (!inPremium) {
		cout << "Error opening file" << endl; //check if file opens successfully
	}
	else if (!inPremium.eof()) {
		cout << setw(65) << setfill('=') << endl;
		cout << "\n";
		cout << "	PREMIUM BURGERS MENU";
		cout << setw(65) << setfill('=') << endl;
		cout << "\n";

		do {
			getline(inPremium, temp_line); //read from the file line by line
			istringstream menuSS(temp_line); //create a stringstream object and store line in menuSS
			menuSS >> premium.list; //read list number
			menuSS.ignore(); //ignores buffer
			getline(menuSS, premium.itemName, ','); //read until comma
			menuSS >> premium.alaCarte;
			menuSS >> premium.medium; //read Medium Set price
			menuSS >> premium.large; //read Large Set price
			cout << premium.list << " " << premium.itemName << fixed << setprecision(2) << endl;
		} while (inPremium.good());
		inPremium.close();
		cout << "\nPress 0 to return to main menu" << endl;
		cout << "Enter selection: ";


		cin >> listChoice;
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cin.ignore();
		}
		cout << "\n";
		if (listChoice == 0)
		{
			return; //returns to main menu
		}
		else if (listChoice > premium.list) { //checks for user input error (selection num greater than listed)
			cout << "\nPlease Enter a Valid Selection.";
			cout << "\n";
			return;
		}
		else{
			cout << "\n";
			cout << "     ===============================" << endl;
			cout << "     Ala Carte, Medium or Large set?" << endl;
			cout << "     ===============================" << endl;
				inPremium.open("premium.txt");
			while (getline(inPremium, temp_line))
			{
				istringstream menuSS(temp_line);
				menuSS >> premium.list;
				menuSS.ignore();
				getline(menuSS, premium.itemName, ',');
				menuSS >> premium.alaCarte;
				menuSS >> premium.medium;
				menuSS >> premium.large;

				if (listChoice == premium.list)//match the selection to the list from file
				{
					cout << premium.itemName << endl;
					cout << "Ala Carte :	RM " << premium.alaCarte << endl;
					cout << "Medium Set:	RM " << premium.medium << endl;
					cout << "Large Set :	RM " << premium.large << endl;
					break;
				}
			}
				inPremium.close();
			}

		cout << "\nPress 1 for ala carte, 2 for medium set, 3 for large set." << endl;
		cout << "Enter selection: ";
		cin >> meal_selection;
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cin.ignore();
		}
		switch (meal_selection) {
		case 1:
		{
			cout << "\n";
			cout << "     ======================" << endl;
			cout << "            Quantity" << endl;
			cout << "     ======================" << endl;
			cout << "Enter quantity: ";
			cin >> premium.quantity;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				cout << "\nPlease enter a Valid Selection." << endl;
				break;
			}
			premium.itemName += " (A)";
			premium.price = premium.alaCarte * premium.quantity;
			orderList.push_back(premium); //add ordered items to vector
			cout << "\nOrder has been added to checkout list ~ ~";
			break;
		}
		case 2:
		{
			cout << "\n";
			cout << "     ======================" << endl;
			cout << "            Quantity" << endl;
			cout << "     ======================" << endl;
			cout << "Enter quantity: ";
			cin >> premium.quantity;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				cout << "\nPlease enter a Valid Selection." << endl;
				break;
			}
			premium.itemName += " (M)";
			premium.price = premium.medium * premium.quantity;
			orderList.push_back(premium);
			cout << "\nOrder has been added to checkout list ~ ~";
			break;
		}
		case 3:
		{
			cout << "\n";
			cout << "     ======================" << endl;
			cout << "            Quantity" << endl;
			cout << "     ======================" << endl;
			cout << "Enter quantity: ";
			cin >> premium.quantity;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				cout << "\nPlease enter a Valid Selection." << endl;
				break;
			}
			premium.itemName += " (L)";
			premium.price = premium.large * premium.quantity;
			orderList.push_back(premium);
			cout << "\nOrder has been added to checkout list ~ ~";
			break;
		}
		default:
			cout << "\nPlease Enter a Valid Selection." << endl;
		}

	}
}
void DRINKS_MENU() {
	//declare input from file to stream
	ifstream inDrinks;
	//declare variables to be used
	int listChoice = 0;
	string temp_line = "";
	menu drinks;
	drinks.list = 0;
	drinks.itemName = "";
	drinks.alaCarte = 0.0;
	//declare an array to store user input data 


	inDrinks.open("drinks.txt");
	if (!inDrinks) {
		cout << "Error opening file" << endl; //check if file opens successfully
	}
	else if (!inDrinks.eof()) {
		cout << setw(65) << setfill('=') << endl;
		cout << "\n";
		cout << "	DRINKS MENU";
		cout << setw(65) << setfill('=') << endl;
		cout << "\n";

		do {
			getline(inDrinks, temp_line); //read from the file line by line
			istringstream menuSS(temp_line); //create a stringstream object and store line in menuSS
			menuSS >> drinks.list; //read list number
			menuSS.ignore(); //ignores buffer
			getline(menuSS, drinks.itemName, ','); //read until comma
			menuSS >> drinks.alaCarte; //read price
			cout << drinks.list << " " << drinks.itemName << fixed << setprecision(2) << endl;
		} while (inDrinks.good());
		inDrinks.close();
		cout << "\nPress 0 to return to main menu" << endl;
		cout << "Enter selection: ";

		cin >> listChoice;
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cin.ignore();
		}
		cout << '\n';
		if (listChoice == 0)
		{
			return; //returns to main menu
		}
		else if (listChoice > drinks.list) { //checks for user input error (selection num greater than listed)
			cout << "\nPlease Enter a Valid Selection.";
			cout << "\n";
			return;
		}
		else
		{
			cout << "\n";
			cout << "     ====================================" << endl;
			cout << "     Only ala carte available for drinks." << endl;
			cout << "     ====================================" << endl;
			inDrinks.open("drinks.txt");
			while (getline(inDrinks, temp_line))
			{
				istringstream menuSS(temp_line);
				menuSS >> drinks.list;
				menuSS.ignore();
				getline(menuSS, drinks.itemName, ',');
				menuSS >> drinks.alaCarte;
				if (listChoice == drinks.list)//match the selection to the list from file
				{
					cout << drinks.itemName << endl;
					cout << "Ala Carte :	RM " << drinks.alaCarte << endl;
					break;
				}
			}
			inDrinks.close();
		}

		cout << "\n";
		cout << "     ======================" << endl;
		cout << "            Quantity" << endl;
		cout << "     ======================" << endl;
		cout << "Enter quantity: ";
		cin >> drinks.quantity;
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cin.ignore();
			cout << "\nPlease enter a Valid Selection." << endl;
		}
		drinks.itemName += " (A)";
		drinks.price = drinks.alaCarte * drinks.quantity;
		orderList.push_back(drinks);  //add ordered items to vector
		cout << "\nOrder has been added to checkout list ~ ~";
	}
}
void DESSERT_MENU() {
	//declare input from file to stream
	ifstream inDessert;
	//declare variables to be used
	int listChoice = 0;
	string temp_line = "";
	menu dessert;
	dessert.list = 0;
	dessert.itemName = "";
	dessert.alaCarte = 0.0;
	//declare an array to store user input data 


	inDessert.open("dessert.txt");
	if (!inDessert) {
		cout << "Error opening file" << endl; //check if file opens successfully
	}
	else if (!inDessert.eof()) {
		cout << setw(65) << setfill('=') << endl;
		cout << "\n";
		cout << "	DESSERT MENU";
		cout << setw(65) << setfill('=') << endl;
		cout << "\n";

		do {
			getline(inDessert, temp_line); //read from the file line by line
			istringstream menuSS(temp_line); //create a stringstream object and store line in menuSS
			menuSS >> dessert.list; //read list number
			menuSS.ignore(); //ignores buffer
			getline(menuSS, dessert.itemName, ','); //read until comma
			menuSS >> dessert.alaCarte; //read price
			cout << dessert.list << " " << dessert.itemName << fixed << setprecision(2) << endl;
		} while (inDessert.good());
		inDessert.close();
		cout << "Press 0 to return to main menu" << endl;
		cout << '\n';
		cout << "Enter selection: ";

		cin >> listChoice;
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cin.ignore();
		}
		cout << '\n';
		if (listChoice == 0)
		{
			return; //returns to main menu
		}
		else if (listChoice > dessert.list) { //checks for user input error (selection num greater than listed)
			cout << "\nPlease Enter a Valid Selection.";
			cout << "\n";
			return;
		}
		else
		{
			cout << "\n";
			cout << "     ====================================" << endl;
			cout << "     Only ala carte available for dessert." << endl;
			cout << "     ====================================" << endl;
			inDessert.open("dessert.txt");
			while (getline(inDessert, temp_line))
			{
				istringstream menuSS(temp_line);
				menuSS >> dessert.list;
				menuSS.ignore();
				getline(menuSS, dessert.itemName, ',');
				menuSS >> dessert.alaCarte;
				if (listChoice == dessert.list)//match the selection to the list from file
				{
					cout << dessert.itemName << endl;
					cout << "Ala Carte :	RM " << dessert.alaCarte << endl;
					break;
				}
			}
			inDessert.close();
		}

		cout << "\n";
		cout << "     ======================" << endl;
		cout << "            Quantity" << endl;
		cout << "     ======================" << endl;
		cout << "Enter quantity: ";
		cin >> dessert.quantity;
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cin.ignore();
			cout << "\nPlease enter a Valid Selection." << endl;
		}
		dessert.itemName += " (A)";
		dessert.price = dessert.alaCarte * dessert.quantity;
		orderList.push_back(dessert);  //add ordered items to vector
		cout << "\nOrder has been added to checkout list ~ ~";
	}
}
void SIDES_MENU() {
	//declare input from file to stream
	ifstream inSides;
	//declare variables to be used
	int listChoice = 0;
	string temp_line = "";
	menu sides;
	sides.list = 0;
	sides.itemName = "";
	sides.alaCarte = 0.0;
	//declare an array to store user input data 


	inSides.open("sides.txt");
	if (!inSides) {
		cout << "Error opening file" << endl; //check if file opens successfully
	}
	else if (!inSides.eof()) {
		cout << setw(65) << setfill('=') << endl;
		cout << "\n";
		cout << "	SIDES MENU";
		cout << setw(65) << setfill('=') << endl;
		cout << "\n";

		do {
			getline(inSides, temp_line); //read from the file line by line
			istringstream menuSS(temp_line); //create a stringstream object and store line in menuSS
			menuSS >> sides.list; //read list number
			menuSS.ignore(); //ignores buffer
			getline(menuSS, sides.itemName, ','); //read until comma
			menuSS >> sides.alaCarte; //read price
			cout << sides.list << " " << sides.itemName << fixed << setprecision(2) << endl;
		} while (inSides.good());
		inSides.close();
		cout << "\nPress 0 to return to main menu" << endl;
		cout << "Enter selection: ";

		cin >> listChoice;
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cin.ignore();
		}
		cout << '\n';
		if (listChoice == 0)
		{
			return; //returns to main menu
		}
		else if (listChoice > sides.list) { //checks for user input error (selection num greater than listed)
			cout << "\nPlease Enter a Valid Selection.";
			cout << "\n";
			return;
		}
		else
		{
			cout << "\n";
			cout << "     ===================================" << endl;
			cout << "     Only ala carte available for sides." << endl;
			cout << "     ===================================" << endl;
			inSides.open("sides.txt");
			while (getline(inSides, temp_line))
			{
				istringstream menuSS(temp_line);
				menuSS >> sides.list;
				menuSS.ignore();
				getline(menuSS, sides.itemName, ',');
				menuSS >> sides.alaCarte;
				if (listChoice == sides.list)//match the selection to the list from file
				{
					cout << sides.itemName << endl;
					cout << "Ala Carte:	RM " << sides.alaCarte << endl;
					break;
				}
			}
			inSides.close();
		}

		cout << "\n";
		cout << "     ======================" << endl;
		cout << "            Quantity" << endl;
		cout << "     ======================" << endl;
		cout << "Enter quantity: ";
		cin >> sides.quantity;
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cin.ignore();
			cout << "\nPlease enter a Valid Selection." << endl;
		}
		sides.itemName += " (A)";
		sides.price = sides.alaCarte * sides.quantity;
		orderList.push_back(sides);  //add ordered items to vector
		cout << "\nOrder has been added to checkout list ~ ~";
	}
}


/*                    PAYMENT MODULE USER-DECLARED FUNCTION                   */
void payment(int dine) {
	struct Members {
		string memberids;
		string names;
		string contact;
		int age = 0;
		double topupvalue = 0.0;
		double memberPoints = 0.0;

	};
	
	//declare variable
	int payDecicion = 5, topupDecision = 0, linecounter = 0, i = 0;
	double total = 0, itemsPrice = 0.0, serviceCharge = 0.0, subtotal = 0.0, convertMemberPoint = 0.0;
	string line = " ", memberidInput = " a ", serviceType = " ";
	fstream idFile;
	ofstream temp;
	vector<string>lines;
	Members members;

	cout << "===========================================================" << endl;
	cout << "                       Payment                             " << endl;
	cout << "===========================================================" << endl;

	// Step 2: Calculate subtotal and total
	//loop through the vector for all the food all calculate the total
	for (const menu& item : orderList) {

		total = total + item.price;

	}
	if (dine == 1) {
		//dine in calculation
		serviceCharge = total * 0.1;
		subtotal = total + serviceCharge;
		serviceType = "Dine In 10%";
	}
	else if (dine == 2) {
		//take away calculation
		serviceCharge = 2;
		subtotal = total + serviceCharge;
		serviceType = "Take Away (RM2)";
	}

	// Step 3: Prompt staff to enter a valid card number
	do {
		cout << "Enter the card number: ";
		getline(cin, memberidInput);
		transform(memberidInput.begin(), memberidInput.end(), memberidInput.begin(), ::toupper);// convert lower case to upper case

		linecounter = 0;//reset counter
		idFile.open("customer_data.txt", ios::in);
		if (idFile.fail()) {
			cout << "Error Reading File" << endl;// if file cannot open print Error Reading File
		}
		else if (!idFile.eof()) {
			while (getline(idFile, line)) {
				linecounter++; //counter for the line number or customer info
				istringstream iss(line); // store line in iss
				getline(iss, members.memberids, ',');
				getline(iss, members.names, ',');  // Read name until comma
				getline(iss, members.contact, ',');
				iss >> members.age;
				iss >> members.topupvalue; //read data from iss
				iss >> members.memberPoints;
				iss.ignore();//ignore the buffer
				//print customer info
				if (memberidInput == members.memberids) {
					cout << "-----------------------------------------------------------" << endl;
					cout << setfill(' ') << setw(35) << "Customer Info" << endl;
					cout << "Name                     : " << members.names << endl;
					cout << "MemberID                 : " << members.memberids << endl;
					cout << "Contact                  : " << members.contact << endl;
					cout << "Age                      : " << members.age << endl;
					cout << "Card Balance(RM)         : " << members.topupvalue << endl;
					cout << "Member Point(RM1 = 100)  : " << fixed << setprecision(2) << members.memberPoints << endl;
					cout << "-----------------------------------------------------------" << endl;
					break;
				}
			}
			idFile.close();
			if (memberidInput != members.memberids) { //if the id is not at file then will print Enter a valid member id
				cout << "Enter a valid member id" << endl;
			}
		}

	} while (memberidInput != members.memberids);

	convertMemberPoint = members.memberPoints / 100;

	// Step 4: Check card balance or member point and proceed with payment
	// Check if card number exists and balance is sufficient for the total payment

	if (members.topupvalue >= subtotal || convertMemberPoint + members.topupvalue >= subtotal) {
		//print summary of all ordered food
		cout << "-----------------------------------------------------------" << endl;
		cout << setfill(' ') << setw(30) << "Summary" << endl;
		cout << "-----------------------------------------------------------" << endl;
		cout << setfill(' ') << setw(35) << left << "Name" << setw(10) << right << "Quantity" << setw(13) << "Price(RM)" << endl;
		//loop through the vector for all the food
		for (const menu& item : orderList) {
			cout << setfill(' ') << left << setw(35) << item.itemName << right << setw(10) << item.quantity << setw(13) << item.price << endl;
			cout << endl;
		}
		cout << setfill('-') << setw(60) << endl;
		cout << "\n";
		cout << left << setw(40) << setfill(' ') << "Total: " << setw(18) << right << total << endl;
		cout << left << setw(16) << setfill(' ') << "Service Charge: " << setw(24) << serviceType << setw(18) << showpos << right << serviceCharge << endl;
		cout << left << setw(40) << setfill(' ') << "Subtotal: " << setw(18) << noshowpos << right << subtotal << endl;

		cout << "\n";
		if (members.memberPoints <= 0) {
			cout << " 0. Pay with Card Balance ";;
			cout << " 2. Cancel Payment ";
			cout << "\n";
			cout << "Option : \n";
			cin >> payDecicion;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				payDecicion = 5;
			}
			while (payDecicion != 0 && payDecicion != 2) {
				cout << "Please Enter a Valid Number" << endl;
				cin >> payDecicion;
				if (cin.fail()) {
					cin.clear();
					cin.sync();
					cin.ignore();
					payDecicion = 5;
				}
			}
		}
		else if (members.topupvalue < subtotal) {
			cout << " 1. Pay with Member Point ";
			cout << " 2. Cancel Payment ";
			cout << "\n";
			cout << "Option : ";
			cin >> payDecicion;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				payDecicion = 5;
			}
			while (payDecicion != 1 && payDecicion != 2) {
				cout << "Please Enter a Valid Number" << endl;
				cin >> payDecicion;
				if (cin.fail()) {
					cin.clear();
					cin.sync();
					cin.ignore();
					payDecicion = 5;
				}
			}
		}
		else {
			cout << " 0. Pay with Card Balance ";
			cout << " 1. Pay with Member Point ";
			cout << " 2. Cancel Payment ";
			cout << "\n";
			cout << "Option : ";
			cin >> payDecicion;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				payDecicion = 5;
			}
			while (payDecicion != 0 && payDecicion != 1 && payDecicion != 2) {
				cout << "Please Enter a Valid Number" << endl;
				cin >> payDecicion;
				if (cin.fail()) {
					cin.clear();
					cin.sync();
					cin.ignore();
					payDecicion = 5;
				}
			}
		}

		if (payDecicion == 0) {
			// Step 5: Display payment status and updated card balance
			members.memberPoints = memberpointadd(subtotal, members.memberPoints);
			cout << "\nPayment Successful, Thank You\n" << endl;
			members.topupvalue = members.topupvalue - subtotal;
			cout << "New Card Balance : RM " << fixed << setprecision(2) << members.topupvalue << endl;
			cout << "New Member Point : " << fixed << setprecision(2) << members.memberPoints << endl;

			// Step 6: Process payment and deduct the amount from the card balance
			idFile.open("customer_data.txt", ios::in);
			if (idFile.fail()) { // if file fail to open will print error message
				cout << "Error Reading File" << endl;
			}
			else if (idFile.is_open()) {
				while (getline(idFile, line)) {
					lines.push_back(line); //read all the data line by line and store it in vector
				}
			}idFile.close();

			temp.open("customer_data.txt");
			if (temp.is_open()) {
				linecounter--;//vector count lines from 0 so the line counter must minus one to get the correct line number
				for (i = 0; i < lines.size(); i++) { //if i greater than lines which store by vector then the loop will stop
					if (i != linecounter) //if i not equal to the line counter the program will write the same things back to the file
						temp << lines[i] << endl;
					else// if i is equal to the line counter it will write the updated point in to it
						temp << members.memberids << "," << members.names << "," << members.contact << "," << members.age << " " << fixed << setprecision(2) << members.topupvalue << " " << members.memberPoints << endl;
				}
			}temp.close();

			orderList.clear(); //cancels order selection
			cout << "\nPress any key to return main menu -->";
			cin.ignore();
			cin.get();
			home();
		}
		else if (payDecicion == 1) {
			//when member point is sufficient
			if (convertMemberPoint >= subtotal) {
				members.memberPoints = memberpointsub1(subtotal, convertMemberPoint);
			}
			//when member point is insufficient
			else if (convertMemberPoint < subtotal) {
				members.topupvalue = memberpointsub2(subtotal, &convertMemberPoint, members.topupvalue);
				members.memberPoints = convertMemberPoint;
			}
			members.memberPoints = memberpointadd(subtotal, members.memberPoints);
			// Step 5: Display payment status and updated card balance
			cout << "\nPayment Successful, Thank You\n" << endl;
			cout << "New Card Balance : RM " << fixed << setprecision(2) << members.topupvalue << endl;
			cout << "New Member Point : " << fixed << setprecision(2) << members.memberPoints << endl;

			// Step 6: Process payment and deduct the amount from the card balance
			idFile.open("customer_data.txt", ios::in);
			if (idFile.fail()) { // if file fail to open will print error message
				cout << "Error Reading File" << endl;
			}
			else if (idFile.is_open()) {
				while (getline(idFile, line)) {
					lines.push_back(line); //read all the data line by line and store it in vector
				}
			}idFile.close();

			temp.open("customer_data.txt");
			if (temp.is_open()) {
				linecounter--;//vector count lines from 0 so the line counter must minus one to get the correct line number
				for (i = 0; i < lines.size(); i++) { //if i greater than lines which store by vector then the loop will stop
					if (i != linecounter) //if i not equal to the line counter the program will write the same things back to the file
						temp << lines[i] << endl;
					else// if i is equal to the line counter it will write the updated point in to it
						temp << members.memberids << "," << members.names << "," << members.contact << "," << members.age << " " << fixed << setprecision(2) << members.topupvalue << " " << members.memberPoints<< endl;
				}
			}temp.close();
			orderList.clear(); //cancels order selection
			cout << "\nPress any key to return main menu -->";
			cin.ignore();
			cin.get();
			home();

		}
		else if (payDecicion == 2) {
			orderList.clear(); //cancels order selection
			cout << "Thank You" << endl;
			cout << "\nPress any key to return main menu -->";
			cin.ignore();
			cin.get();
			home();
		}
	}

	else {
		// If balance is insufficient, provide the option to top-up or cancel the order
		do {
			cout << setw(38) << "Insufficient Point" << endl;
			cout << " 1. Top Up ";
			cout << " 2. Cancel ";
			cout << "\n";
			cout << "Option : ";
			cin >> topupDecision;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				cout << "Invalid Selection" << endl;
				continue;
			}
			else if (topupDecision == 1) {
				cout << "Proceed to top up module" << endl;
				topup();
			}
			else if (topupDecision == 2) {
				orderList.clear(); //cancels order selection
				cout << "\nThank You" << endl;
				cout << "\nPress any key to return main menu -->";
				cin.ignore();
				cin.get();
				home();
			}
			else {
				cout << "Invalid Selection" << endl;;
			}
		} while (topupDecision != 1 && topupDecision != 2);

	}


}

//member point module
//add member point
double memberpointadd(double subtotal, double memberpoint) {
	memberpoint = memberpoint + subtotal;
	return memberpoint;
}

//when member point is sufficient
double memberpointsub1(double subtotal, double convertmemberpoint) {
	convertmemberpoint = convertmemberpoint - subtotal;
	convertmemberpoint = convertmemberpoint * 100;
	return convertmemberpoint;
}

//when member point is insufficient
double memberpointsub2(double subtotal, double* convert, double topupvalue) {
	topupvalue = topupvalue + *convert - subtotal; //all point will use for payment and the insufficient part will be pay by the card balance
	*convert = 0; //pointer for changing the converted member point value
	return topupvalue;
}

/*						     EXIT PROGRAM LOGO FUNCTION				         */
void exitProgram() {
	cout << "  _______   _    _              _   _   _  __   __     __   ____    _    _     _ " << endl;
	cout << " |__   __| | |  | |     /\\     | \\ | | | |/ /   \\ \\   / /  / __ \\  | |  | |   | |" << endl;
	cout << "    | |    | |__| |    /  \\    |  \\| | | ' /     \\ \\_/ /  | |  | | | |  | |   | |" << endl;
	cout << "    | |    |  __  |   / /\\ \\   | . ` | |  <       \\   /   | |  | | | |  | |   | |" << endl;
	cout << "    | |    | |  | |  / ____ \\  | |\\  | | . \\       | |    | |__| | | |__| |   |_|" << endl;
	cout << "    |_|    |_|  |_| /_/    \\_\\ |_| \\_| |_|\\_\\      |_|     \\____/   \\____/    (_)" << endl;
	cout << "\n\n";
	cout << "           _____    ____     ____    _____    ____   __     __  ______           " << endl;
	cout << "          / ____|  / __ \\   / __ \\  |  __ \\  |  _ \\  \\ \\   / / |  ____|          " << endl;
	cout << "         | |  __  | |  | | | |  | | | |  | | | |_) |  \\ \\_/ /  | |__             " << endl;
	cout << "         | | |_ | | |  | | | |  | | | |  | | |  _ <    \\   /   |  __|            " << endl;
	cout << "         | |__| | | |__| | | |__| | | |__| | | |_) |    | |    | |____           " << endl;	
	cout << "          \\_____|  \\____/   \\____/  |_____/  |____/     |_|    |______|          " << endl;

	exit(0); //forces an exit code 0 (ends without error)
}