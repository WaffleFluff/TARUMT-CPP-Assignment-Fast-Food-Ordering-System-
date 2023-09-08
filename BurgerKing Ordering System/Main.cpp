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
/****************************************************/

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


/*                      Menu Module                  */
void MENU();
void BREAKFAST_MENU();
void CHICKEN_MENU();
void BEEF_MENU();
void PREMIUM_MENU();
void DRINKS_MENU();
void DESSERT_MENU();
void SIDES_MENU();
/*Payment and Member Point module*/
void payment(int dine);
double memberpointadd(double subtotal, double memberpoint);
double memberpointsub1(double subtotal, double convertmemberpoint);
double memberpointsub2(double subtotal, double* convert, double topupvalue);

int main() {

	home();

	return 0;
}

/*                REGISRATION MODULE USER-DECLARED FUNCTIONS               */
//homepage 
void home() {
	vector<Customer> customers;


	int choice = 0;

	do
	{
#ifdef _WIN32
		system("cls");
#else
		system("clear");
#endif

		logo();
		cout << "Your Choice Here: ";
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cin.ignore();
			cout << "Please Enter a Valid Number" << endl;
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
			MENU();
			break;
		}

		case 4:
		{
			cout << "Thank you, Goodbye!" << endl;
			break;
		}

		default:
			break;
		}

		cout << "\nPress Enter to continue...";
		cin.get();


	} while (choice != 3);
}

//function display logo
void logo()
{
	int choice = 0;
	cout << " __          __  ______   _         _____    ____    __  __   ______     _______    ____    " << endl;
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

	cout << " ************************************************* \n";
	cout << " ************************************************* \n";
	cout << "|*| How Can I Help You? \n\n";
	cout << "       1.Register - Make a new Account\n";
	cout << "       2.Check Member Account info\n";
	cout << "       3.Menu\n";
	cout << "       4.Exit\n\n";
	cout << " ************************************************* \n";
	cout << " ************************************************* \n";

}


// Function to validate the customer name
bool validateName(const string& name)
{
	if (name.empty() || name.length() < 3 || name.length() > 30) //check the name  

	{
		return false;
	}
	for (char i : name)
	{
		if (!isalpha(i) && i != ' ')
		{
			return false;
		}
	}
	return true;
}


// Function to validate the contact number
bool validateContact(const string& contact)
{
	if (contact.empty() || contact.length() < 5)
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
	if (ageString.empty())
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

	cout << "====================REGISTER====================\n\n";

	while (true) // Validate the name
	{
		cout << "Full Name---------->";
		cin.ignore();
		getline(cin, newCustomer.name);

		if (validateName(newCustomer.name))
		{
			// The name is valid
			break;
		}
		else
		{
			cout << "Please enter a valid name, Thank You\n";
		}
	}

	while (true) // Validate the contact number
	{
		cout << "Contact Number ---->";
		getline(cin, newCustomer.contact);

		if (validateContact(newCustomer.contact))
		{
			// The contact number is valid
			break;
		}
		else
		{
			cout << "Please enter a valid contact number, Thank You\n";
		}
	}

	while (true) // Validate the age
	{
		cout << "Age --------------->";
		getline(cin, newCustomer.ageString);

		if (validateAge(newCustomer.ageString))
		{
			// The age is valid
			newCustomer.age = stoi(newCustomer.ageString);
			break;
		}
		else
		{
			cout << "Invalid age. Please enter a valid age,Thank You\n";
		}
	}

	// Generate random memberID
	srand(static_cast<unsigned int>(time(0)));
	newCustomer.memberID = "ABC" + to_string(rand() % 900000 + 100000);

	newCustomer.balance = 0;
	newCustomer.memberPoint = 0;

	cout << "Congratulations Registration successful!\n" << endl;

	cout << "============Customer Details============\n\n";
	cout << "---------------------------------------\n";
	cout << "Full Name      : " << newCustomer.name << endl;
	cout << "Contact Number : " << newCustomer.contact << endl;
	cout << "Age            : " << newCustomer.ageString << endl;
	cout << "Member Number  : " << newCustomer.memberID << endl;
	cout << "Balance        : " << newCustomer.balance << endl;
	cout << "Member Point   : " << newCustomer.memberPoint << endl;
	cout << "---------------------------------------\n";

	writeToFile(newCustomer);
}


void login(vector<Customer>& customers)
{
	string MemberID;
	cout << "====================LOGIN====================\n\n";
	cout << "Enter Member ID: ";
	cin.ignore();
	getline(cin, MemberID);
	transform(MemberID.begin(), MemberID.end(), MemberID.begin(), ::toupper);

	ifstream inFile("customer_data.txt");
	if (inFile.is_open())
	{
		string line;
		bool found = false;

		while (getline(inFile, line))
		{
			istringstream iss(line);
			Customer customer; //create a customer object to store data

			getline(iss, customer.memberID, ',');
			getline(iss, customer.name, ',');
			getline(iss, customer.contact, ',');
			iss >> customer.age;
			iss >> customer.balance;
			iss >> customer.memberPoint;

			if (MemberID == customer.memberID)
			{
				found = true;
				cout << "--------------------------------------------" << endl;
				cout << setw(27) << "Customer Info" << endl;
				cout << "Name          : " << customer.name << endl;
				cout << "MemberID      : " << customer.memberID << endl;
				cout << "Balance       : " << fixed << setprecision(2) << customer.balance << endl;
				cout << "Member Point  : " << fixed << setprecision(2) << customer.memberPoint << endl;
				cout << "Member Age    : " << customer.age << endl;
				cout << "Member Contact: " << customer.contact << endl;
				cout << "--------------------------------------------" << endl;
				break;
			}
		}

		if (!found)
		{
			cout << "Member not found." << endl;
		}

		inFile.close();
	}
	else
	{
		cout << "Unable to open file for reading." << endl;
	}
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
			cout << "\nEnter selection: ";
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
			cout << "CHECKOUT:" << endl;



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
			cout << "Press 0 to return to order menu, 1 to edit orders, 2 to remove an order, or 9 to proceed." << endl;
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
				cout << "Enter the order number to edit: ";
				cin >> editNum;
				if (editNum >= 1 && editNum <= orderList.size()) { //check if order number is valid using vector size, checking starts from i=1
					cout << "Enter the new quantity: ";			//if valid, prompt user to enter new quantity
					cin >> newQuantity;
					orderList[editNum - 1].quantity = newQuantity;
				}
				else {
					cout << "Please enter a Valid Selection.";
					cout << "\n";
					continue;
				}
			}
			else if (checkoutChoice == 2) {
				//remove an order
				cout << "Enter the order number to remove: ";
				cin >> editNum;
				if (editNum >= 1 && editNum <= orderList.size()) {
					orderList.erase(orderList.begin() + editNum - 1);
				}
				else {
					cout << "Invalid selection.";
					cout << "\n";
					continue;
				}
			}
			else if (checkoutChoice == 9) {
				//proceed to payment
				break;
			}
			else {
				cout << "Invalid selection.";
				cout << "\n";
				continue;
			}
		} while (checkoutChoice != 9);

		if (checkoutChoice == 9)
		{
			cout << setw(65) << setfill('=') << endl;
			cout << "\n";
			cout << "Dine-in or Take-away?" << endl;
			cout << "Press 1 for dine-in, 2 for take-away." << endl;
			cout << setw(65) << setfill('=') << endl;
			cout << "\n";

			cout << fixed << setprecision(2) << endl; //to ensure display for price has two decimal points (RM x.xx)

			cin >> diningMethod;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				diningMethod = 5; //set to invalid number to continue loop
			}
			if (diningMethod == 1) {
				break;
			}
			else if (diningMethod == 2) {
				break;
			}
			else {
				cout << "Please enter a Valid Selection." << endl;
				continue;
			}
		}
		else
			continue;
	} while (categoryChoice != 9 || checkoutChoice != 9);
	payment(diningMethod);
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
		cout << "BREAKFAST MENU";
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
		cout << "Press 0 to return to main menu" << endl;
		cout << '\n';
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
			cout << "Please enter a Valid Selection.";
			cout << "\n";
			return;
		}
		else
		{
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
					cout << "Ala Carte:	RM " << breakfast.alaCarte << endl;
					cout << "Set Meal:	RM " << breakfast.setMeal << endl;
					break;
				}
			}
			inBreakfast.close();
		}

		cout << "\n";
		cout << "Ala Carte or Set Meal?" << endl;
		cout << "Press 1 for ala carte, 2 for set meal." << endl;
		cin >> meal_selection;
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cin.ignore();
		}
		switch (meal_selection) {
		case 1:
		{
			cout << "Enter quantity: ";
			cin >> breakfast.quantity;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				cout << "Please enter a Valid Selection." << endl;
				break;
			}
			breakfast.itemName += " (A)";
			breakfast.price = breakfast.alaCarte * breakfast.quantity;
			orderList.push_back(breakfast);  //add ordered items to vector
			break;
		}
		case 2:
		{
			cout << "Enter quantity: ";
			cin >> breakfast.quantity;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				cout << "Please enter a Valid Selection." << endl;
				break;
			}
			breakfast.itemName += " (SET)";
			breakfast.price = breakfast.setMeal * breakfast.quantity;
			orderList.push_back(breakfast);
			break;
		}
		default:
			cout << "Please enter a Valid Selection." << endl;
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
		cout << "CHICKEN BURGERS MENU";
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
		else if (listChoice > chicken.list) { //checks for user input error (selection num greater than listed)
			cout << "Please Enter a Valid Selection.";
			cout << "\n";
			return;
		}
		else
		{
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
					cout << "Ala Carte:	RM " << chicken.alaCarte << endl;
					cout << "Medium Set:	RM " << chicken.medium << endl;
					cout << "Large Set:	RM " << chicken.large << endl;
					break;
				}
			}
			inChicken.close();
		}

		cout << "\n";
		cout << "Ala Carte, Medium or Large set?" << endl;
		cout << "Press 1 for ala carte, 2 for medium set, 3 for large set." << endl;
		cin >> meal_selection;
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cin.ignore();
		}
		switch (meal_selection) {
		case 1:
		{
			cout << "Enter quantity: ";
			cin >> chicken.quantity;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				cout << "Please enter a Valid Selection." << endl;
				break;
			}
			chicken.itemName += " (A)";
			chicken.price = chicken.alaCarte * chicken.quantity;
			orderList.push_back(chicken); //add ordered items to vector
			break;
		}
		case 2:
		{
			cout << "Enter quantity: ";
			cin >> chicken.quantity;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				cout << "Please enter a Valid Selection." << endl;
				break;
			}
			chicken.itemName += " (M)";
			chicken.price = chicken.medium * chicken.quantity;
			orderList.push_back(chicken);
			break;
		}
		case 3:
		{
			cout << "Enter quantity: ";
			cin >> chicken.quantity;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				cout << "Please enter a Valid Selection." << endl;
				break;
			}
			chicken.itemName += " (L)";
			chicken.price = chicken.large * chicken.quantity;
			orderList.push_back(chicken);
			break;
		}
		default:
			cout << "Please Enter a Valid Selection." << endl;
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
		cout << "BEEF BURGERS MENU";
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
		cout << "Press 0 to return to main menu" << endl;
		cout << '\n';
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
			cout << "Please Enter a Valid Selection.";
			cout << "\n";
			return;
		}
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
				cout << "Ala Carte:	RM " << beef.alaCarte << endl;
				cout << "Medium Set:	RM " << beef.medium << endl;
				cout << "Large Set:	RM " << beef.large << endl;
				break;
			}
		}
		inBeef.close();

		cout << "\n";
		cout << "Ala Carte, Medium or Large set?" << endl;
		cout << "Press 1 for ala carte, 2 for medium set, 3 for large set." << endl;
		cin >> meal_selection;
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cin.ignore();
		}
		switch (meal_selection) {
		case 1:
		{
			cout << "Enter quantity: ";
			cin >> beef.quantity;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				cout << "Please enter a Valid Selection." << endl;
				break;
			}
			beef.itemName += " (A)";
			beef.price = beef.alaCarte * beef.quantity;
			orderList.push_back(beef); //add ordered items to vector
			break;
		}
		case 2:
		{
			cout << "Enter quantity: ";
			cin >> beef.quantity;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				cout << "Please enter a Valid Selection." << endl;
				break;
			}
			beef.itemName += " (M)";
			beef.price = beef.medium * beef.quantity;
			orderList.push_back(beef);
			break;
		}
		case 3:
		{
			cout << "Enter quantity: ";
			cin >> beef.quantity;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				cout << "Please enter a Valid Selection." << endl;
				break;
			}
			beef.itemName += " (L)";
			beef.price = beef.large * beef.quantity;
			orderList.push_back(beef);
			break;
		}
		default:
			cout << "Please Enter a Valid Selection." << endl;
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
		cout << "PREMIUM BURGERS MENU";
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
		cout << "Press 0 to return to main menu" << endl;
		cout << '\n';
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
			cout << "Please Enter a Valid Selection.";
			cout << "\n";
			return;
		}
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
				cout << "Ala Carte:	RM " << premium.alaCarte << endl;
				cout << "Medium Set:	RM " << premium.medium << endl;
				cout << "Large Set:	RM " << premium.large << endl;
				break;
			}
		}
		inPremium.close();

		cout << "\n";
		cout << "Ala Carte, Medium or Large set?" << endl;
		cout << "Press 1 for ala carte, 2 for medium set, 3 for large set." << endl;
		cin >> meal_selection;
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cin.ignore();
		}
		switch (meal_selection) {
		case 1:
		{
			cout << "Enter quantity: ";
			cin >> premium.quantity;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				cout << "Please enter a Valid Selection." << endl;
				break;
			}
			premium.itemName += " (A)";
			premium.price = premium.alaCarte * premium.quantity;
			orderList.push_back(premium); //add ordered items to vector
			break;
		}
		case 2:
		{
			cout << "Enter quantity: ";
			cin >> premium.quantity;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				cout << "Please enter a Valid Selection." << endl;
				break;
			}
			premium.itemName += " (M)";
			premium.price = premium.medium * premium.quantity;
			orderList.push_back(premium);
			break;
		}
		case 3:
		{
			cout << "Enter quantity: ";
			cin >> premium.quantity;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				cout << "Please enter a Valid Selection." << endl;
				break;
			}
			premium.itemName += " (L)";
			premium.price = premium.large * premium.quantity;
			orderList.push_back(premium);
			break;
		}
		default:
			cout << "Please Enter a Valid Selection." << endl;
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
		cout << "DRINKS MENU";
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
		else if (listChoice > drinks.list) { //checks for user input error (selection num greater than listed)
			cout << "Please Enter a Valid Selection.";
			cout << "\n";
			return;
		}
		else
		{
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
					cout << "Ala Carte:	RM " << drinks.alaCarte << endl;
					break;
				}
			}
			inDrinks.close();
		}

		cout << "Only ala carte available for drinks." << endl;
		cout << "\n";
		cout << "Enter quantity: ";
		cin >> drinks.quantity;
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cin.ignore();
			cout << "Please enter a Valid Selection." << endl;
		}
		drinks.itemName += " (A)";
		drinks.price = drinks.alaCarte * drinks.quantity;
		orderList.push_back(drinks);  //add ordered items to vector
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
		cout << "DESSERT MENU";
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
			cout << "Please Enter a Valid Selection.";
			cout << "\n";
			return;
		}
		else
		{
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
					cout << "Ala Carte:	RM " << dessert.alaCarte << endl;
					break;
				}
			}
			inDessert.close();
		}
		cout << "Only ala carte available for dessert." << endl;
		cout << "\n";
		cout << "Enter quantity: ";
		cin >> dessert.quantity;
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cin.ignore();
			cout << "Please enter a Valid Selection." << endl;
		}
		dessert.itemName += " (A)";
		dessert.price = dessert.alaCarte * dessert.quantity;
		orderList.push_back(dessert);  //add ordered items to vector
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
		cout << "SIDES MENU";
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
		else if (listChoice > sides.list) { //checks for user input error (selection num greater than listed)
			cout << "Please Enter a Valid Selection.";
			cout << "\n";
			return;
		}
		else
		{
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
		cout << "Only ala carte available for sides." << endl;
		cout << "\n";
		cout << "Enter quantity: ";
		cin >> sides.quantity;
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cin.ignore();
			cout << "Please enter a Valid Selection." << endl;
		}
		sides.itemName += " (A)";
		sides.price = sides.alaCarte * sides.quantity;
		orderList.push_back(sides);  //add ordered items to vector
	}
}


/*                    PAYMENT MODULE USER-DECLARED FUNCTIONS                   */
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

#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif


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
					cout << setfill(' ') << setw(35) << "Customer Info" << endl;
					cout << "Name                     : " << members.names << endl;
					cout << "MemberID                 : " << members.memberids << endl;
					cout << "Contact                  : " << members.contact << endl;
					cout << "Age                      : " << members.age << endl;
					cout << "Top Up Value(RM)         : " << members.topupvalue << endl;
					cout << "Member Point(RM1 = 100)  : " << fixed << setprecision(2) << members.memberPoints << endl;
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

	if (members.topupvalue >= total || convertMemberPoint + members.topupvalue >= total) {
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
		else if (members.topupvalue < total) {
			cout << " 1. Pay with Member Point ";
			cout << " 2. Cancel Payment ";
			cout << "\n";
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
			cout << "Payment Successful, Thank You" << endl;
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
						temp << members.memberids << "," << members.names << "," << members.contact << "," << members.age << " " << fixed << setprecision(2) << members.topupvalue << " " << members.memberPoints << " " << endl;
				}
			}temp.close();

			cout << "Press anykey to return main menu -->";
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
			cout << "Payment Successful, Thank You" << endl;
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
						temp << members.memberids << "," << members.names << "," << members.contact << "," << members.age << " " << fixed << setprecision(2) << members.topupvalue << " " << members.memberPoints << " " << endl;
				}
			}temp.close();
			cout << "Press anykey to return main menu -->";
			cin.ignore();
			cin.get();
			home();

		}
		else if (payDecicion == 2) {
			cout << "Thank You" << endl;
			cout << "Press anykey to return main menu -->";
			cin.ignore();
			cin.get();
			home();
		}
	}

	else {
		// If balance is insufficient, provide the option to top-up or cancel the order
		do {
			cout << setw(29) << "Insufficient Point" << endl;
			cout << " 1. Top Up ";
			cout << " 2. Cancel ";
			cout << "\n";
			cin >> topupDecision;
			if (cin.fail()) {
				cin.clear();
				cin.sync();
				cin.ignore();
				cout << "Press anykey to return main menu -->" << endl;
				continue;
			}
			else if (topupDecision == 1) {
				cout << "Proceed to top up module";
			}
			else if (topupDecision == 2) {
				cout << "Thank You" << endl;
				cout << "Press anykey to return main menu -->";
				cin.ignore();
				cin.get();
				home();
			}
			else {
				cout << "Invalid Input" << endl;;
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