#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

//Structs
struct Item{
	string name;
	double price;
	};

//Function Prototypes
void mainMenu();
void selection(int selection);
void menuSelection();
vector<Item> getMenu();
void printMenu(vector<Item> menu);
void printBill(vector<Item> totals);
void printDailyTotal();
void managerTools();

double dailyTotal = 0;

//Main function
int main() {
	
	mainMenu();
	
	return 0;
}

//Prints the main menu to the console for the user
void mainMenu() {
	int choice = 0;
	cout << "Please select which option you would like to choose" << endl << endl;
	cout << "1. Menu Selection" << endl;
	cout << "2. Daily Total" << endl;
	cout << "3. Manager Tools" << endl;
	cout << "4. Exit" << endl;
	cin >> choice;
	cout << endl;
	
	selection(choice);
}

//Will take the input of a selection and branch off from there
void selection(int selection){
	if(selection == 1) {
		menuSelection();			
	} else if(selection == 2) {
		printDailyTotal();
	} else if(selection == 3) {
		managerTools();
	}else if(selection == 4){
		cout << "Thank you, have a nice day!" << endl;
		exit(0);
	}else{
		cout << "That is not a valid selection!" << endl << endl;
		mainMenu();
	}
}

//Call for the menu to print and takes the user's input for menu items and stores it in a vector
void menuSelection(){
	int selection = 1;
	vector<Item> ticket;
	vector<Item> menu;
	
	menu = getMenu();
	printMenu(menu);
	
	while(selection != 0) {	
	
		cout << "Please select which menu item is to be added to the total" << endl;
		cout << "Enter 0 to print the bill" << endl;
		cin >> selection;
		cout << endl;
	//If the user selects an item off the menu, it will be inserted into the totals vector
	
		if(selection > 0 && selection <= menu.size()){
			ticket.push_back(menu[(selection - 1)]);
			cout << menu[(selection - 1)].name << " has been added to the menu" << endl << endl;
		//If the users enters 0, it will print the bill
		}else if(selection == 0){
			printBill(ticket);
		//If they enter somehting other than a menu selection or 0
		}else{
			cout << "Incorrect input. Please enter 0 or a selection from the menu" << endl << endl;
		}
	}
}

//Reads the text files and populates the menu vector with menui items and prices
vector<Item> getMenu() {
	string iName;
	double iPrice;
	Item i;
	ifstream inFile;
	vector<Item> menu;
	
	inFile.open("Menu.txt");
	
	if (!inFile) {
    	cerr << "Unable to open file datafile.txt";
    	exit(1);   // call system to stop
	}
	
	while(inFile >> iName >> iPrice){
		i.name = iName;
		i.price = iPrice;
		
		menu.push_back(i);
	}
	
	inFile.close();
	
	return menu;
}

//Prints the menu to the console
void printMenu(vector<Item> menu){
	
	//Prints out the menu, separated by menu headers
	for(int x; x < menu.size(); x++) {
		if(x == 0){
			cout << endl;
			cout << "Appetizers ---------------------------" << endl;
			cout << endl;
			cout << right << setw(2) << x+1 << ". " << left << setw(22) << menu[x].name << " $" << menu[x].price << endl;
		}else if(x == 6){
			cout << endl;
			cout << "Soups and Salads ---------------------------" << endl;
			cout << endl;
			cout << right << setw(2) << x+1 << ". " << left << setw(22) << menu[x].name << " $" << menu[x].price << endl;
		}else if(x == 15){
			cout << endl;
			cout << "Entrees ---------------------------" << endl;
			cout << endl;
			cout << right << setw(2) << x+1 << ". " << left << setw(22) << menu[x].name << " $" << menu[x].price << endl;
		}else if(x ==22){
			cout << endl;
			cout << "Desserts ---------------------------" << endl;
			cout << endl;
			cout << right << setw(2) << x+1 << ". " << left << setw(22) << menu[x].name << " $" << menu[x].price << endl;
		}else{
			cout << right << setw(2) << x+1 << ". " << left << setw(22) << menu[x].name << " $" << menu[x].price << endl;
		}
	}
	cout << endl;
}

//Prints the bill, including items ordered, subtotal, tax, and total including tax
void printBill(vector<Item> ticket) {
	const double TAX_AMT = .06;
	double subTotal = 0;
	double tax = 0;
	double total = 0;
	
	cout << endl;
	cout << "----- Bill -----" << endl;
	cout << endl;
	
	for(int i = 0; i < ticket.size(); i++){
		cout << left << setw(22) << ticket[i].name << " $" << ticket[i].price << endl;
		subTotal += ticket[i].price;
	}
	
	cout << endl;
	cout << "-------------------------------" << endl;
	cout << endl;
	
	cout << left << setw(22) << "Sub Total: " << " $" << subTotal << endl;
	
	tax = subTotal * TAX_AMT;
	cout << left << setw(22) << "Tax: " << " $" << tax << endl;
	
	total = subTotal + tax;
	cout << left << setw(22) << "Total: " << " $" << total << endl;
	
	cout << endl << endl;
	
	dailyTotal += subTotal;
	
	mainMenu();
}

//Print the total for the day
void printDailyTotal() {
	cout << "Total for the Day is: $" << dailyTotal << endl << endl;
	mainMenu();
}

void managerTools(){
int selection = 3;
double CustoToTable = 60; // Average taken if 100 customer compacity > 20$ per customer on average > 3 Customers per table> where 60 comes from
int Cooks;
int Servers;
int Managers;
double MPay = 15.50; // Base Pay For All Managers
double CPay = 10.10; // Base Pay For All Cooks
double SPay = 8.20; //Base Pay For All Servers
double Labor;
double HoursWorked = 7; // Base Hours Worked 4 to 11 can be changed to calculate weekly > Monthly if weekly/ Monthly Totals are available;
double FoodCost;
double FoodCostPercent = .60; // Assumed Average Margin of 60% for Food Cost;
double Rent = 1500;
double TotalCosts;
double RentTimePeriod = 30; // Rent is due every 30 days
double RentPerDay = Rent / RentTimePeriod; // Calcs rent needed for each day to hit total Rent needed over time period
double TableAvg = dailyTotal / CustoToTable;
{
	if (TableAvg <= 48) // 48 per night is Minimum Tables Needed to Break Even With Minimum Labor Needed
	{
		Cooks = 2; // Minimum Cooks Needed
		Servers = 3; // Minimum Servers Needed
		Managers = 1; // Minimum Managers Needed
		
		Labor = ((Cooks * CPay * HoursWorked)+(Servers * SPay* HoursWorked)+(Managers * MPay* HoursWorked));
	}
	if (TableAvg <= 68 && TableAvg > 48) // Need an Extra Cook
	{
		Cooks = 3; // Minimum Cooks Needed
		Servers = 4; // Minimum Servers Needed
		Managers = 1; // Minimum Managers Needed
		
		Labor = ((Cooks * CPay * HoursWorked)+(Servers * SPay* HoursWorked)+(Managers * MPay* HoursWorked));
	}
	if (TableAvg <= 120 && TableAvg > 68) // Need Extra cook and server and Manager
	{
		Cooks = 4; // Minimum Cooks Needed
		Servers = 5; // Minimum Servers Needed
		Managers = 2; // Minimum Managers Needed
		
		Labor = ((Cooks * CPay * HoursWorked)+(Servers * SPay* HoursWorked)+(Managers * MPay* HoursWorked));
	}
	if (TableAvg <= 144 && TableAvg > 120)// Need Extra cook and server
	{
		Cooks = 5; // Minimum Cooks Needed
		Servers = 6; // Minimum Servers Needed
		Managers = 2; // Minimum Managers Needed
		
		Labor = ((Cooks * CPay * HoursWorked)+(Servers * SPay* HoursWorked)+(Managers * MPay* HoursWorked));
	}
	if (TableAvg <= 168 && TableAvg > 144)// Need Extra server
	{
		Cooks = 5; // Minimum Cooks Needed
		Servers = 7; // Minimum Servers Needed
		Managers = 2; // Minimum Managers Needed
		
		Labor = ((Cooks * CPay * HoursWorked)+(Servers * SPay* HoursWorked)+(Managers * MPay* HoursWorked));
	}
	if (TableAvg <= 192 && TableAvg > 168) // // Need Extra cook and server
	{
		Cooks = 6; // Minimum Cooks Needed
		Servers = 8; // Minimum Servers Needed
		Managers = 2; // Minimum Managers Needed
		
		Labor = ((Cooks * CPay * HoursWorked)+(Servers * SPay* HoursWorked)+(Managers * MPay* HoursWorked));
	}
		if (TableAvg > 192 && TableAvg <= 250) // Need Extra cook and server 204 is Max tables on average but just incase i made it extra
	{
		Cooks = 6; // Minimum Cooks Needed
		Servers = 8; // Minimum Servers Needed
		Managers = 2; // Minimum Managers Needed
		
		Labor = ((Cooks * CPay * HoursWorked)+(Servers * SPay* HoursWorked)+(Managers * MPay* HoursWorked));
	}

	double FoodCost = dailyTotal * FoodCostPercent;
	double TotalCosts = FoodCost + Labor + RentPerDay;
	double DailyOverhead = dailyTotal - TotalCosts;
	cout << endl;
	cout << endl;
	cout << "    Total Labor Needed" << endl;
	cout << "Number of Cooks Needed: " << Cooks << endl;
	cout << "Number of Servers Needed: " << Servers << endl;
	cout << "Number of Managers Needed: " << Managers << endl;
	cout << endl;
	cout << endl;
	cout << "    Food Cost" << endl;
	cout << "Nightly Food Cost: " << FoodCost << "$" << endl;
	cout << endl;
	cout << endl;
	cout << "    Labor Cost" << endl;
	cout << "Nightly Labor Cost: " << Labor << "$" << endl;
	cout << endl;
	cout << endl;
	cout << "    Overhead" << endl;
	cout << "Nightly Overhead: " << DailyOverhead <<"$" << endl;
	cout << endl;
	cout << endl;
	
	mainMenu();

}
}





