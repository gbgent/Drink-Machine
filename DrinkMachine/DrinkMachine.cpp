// Course Project
// Drink Machine Simulation

//Author: Gerald Glass
// Version: 05/05/2018

//Files to Include
#include <iostream>
#include <iomanip>

//Namespaces used
using namespace std;

// Global Variables
const int MAX_DRINK_CHOICES	= 5;	// This is the max differant drinks the
									//	Machine will hold.  5 per simulation
//Structures
struct Drink					// Data structure for each Drink
{	
	string name;
	float price;
	int	quantityOnHand;
};

//Function Prototypes
void loadDrinkSelections(Drink *);	
int mainDrinkMenu(Drink []);
double saleSoda(Drink&);
double receivePayment(double);
void makeChange(double, double);
void exitSimulation (double);


int main()
{
	// Local Variables
	Drink drinks[MAX_DRINK_CHOICES];
	double totalRevenue=0.0;
	int choice=0;
	bool isRunning = true;
	
	cout << fixed << showpoint << setprecision(2);
	
	//Load Soda Machine information
	loadDrinkSelections(drinks);
	
	//Start Machine
	while (isRunning)
	{
		choice = mainDrinkMenu(drinks);
		if (choice != 8)
			totalRevenue += saleSoda(drinks[choice]);
		else
			isRunning = false;
		
	}
	
	cout << "Total Revenue Earned $ " << totalRevenue << endl;
}

/***************
	loadDrinkSelections
	
	This function will load 5 drinks types
	along with price and quantity in machine
	In this simulation drinks are preselected though
	in a real model, this would be loaded from a file
	
	@param Drink  array of by reference
	@return nothing
*********************/

void loadDrinkSelections(Drink * array)
{
	array[0].name = "Cola";
	array[0].price = 0.75;
	array[0].quantityOnHand = 20;
	
	array[1].name = "Root Beer";
	array[1].price = 0.75;
	array[1].quantityOnHand = 1;
	
	array[2].name = "Lemon-Lime";
	array[2].price = 0.75;
	array[2].quantityOnHand = 20;
	
	array[3].name = "Grape Soda";
	array[3].price = 0.80;
	array[3].quantityOnHand = 20;
	
	array[4].name = "Cream Soda";
	array[4].price = 0.80;
	array[4].quantityOnHand = 20;
}


/***************
	mainDrinkMenu
	
	This function is the main menu
	it will validate selection and
	check that there is enough of the
	selected choice to proceed
	
	@param Drink  array of by reference
	@return int choice
*********************/

int mainDrinkMenu(Drink array[])
{
	int ch;
	bool exitFlag = false;
	do
	{	cout << "\nDrink Menu\n";
		cout <<"-----------------------------\n";
		for (int x = 0; x < MAX_DRINK_CHOICES; x++)
		{
			int count = x +1;
			cout << count <<" - " << array[x].name << endl;
		}
		cout <<"9 - to exit simulation.\n";
		cout <<"-----------------------------\n";
		cout << "Enter choice: ";
		cin >>	ch;
		if ((ch > 0 && ch < 6) || ch == 9)
			exitFlag = true;
		else
			cout << "Invalid Selection Try again!\n";
	} while (!exitFlag);
	
	return (ch-1);
}

/***************
	saleSoda
	
	This function process the soda.
	If quantity on hand is > 0 it will
	sale the soda, otherwise it will
	display a message that selection is out.
	
	@param Drink  array of by reference
	@return int choice
*********************/

double saleSoda(Drink &soda)
{
	double output = 0.0, payment=0.0;
	
	if(soda.quantityOnHand > 0)
	{
		// sale soda
		payment = receivePayment(soda.price);
		makeChange(payment, soda.price);
		soda.quantityOnHand -=1;
		output = soda.price;
	}
	else
	{
		cout <<"Your selection is empty.\n PLease make a new Selection\n";
		output = 0.0;	
	}
	
	return output;
}


double receivePayment(double cost)
{
	double payment=0.0;
	double newpayment=0.0;

	cout << "\nPrice $ " << cost << endl;
	do
	{
		cout << "Amount paid: " << payment << endl;
		cout << "Please enter payment amount: ";
		cin >> newpayment;
		if (newpayment+payment > 1.00)
			cout <<" Can not accept more than $1.00. \nYour payment of " 
				 << newpayment << " has been refunded.\n";
		else
			payment += newpayment;
		
	}while (cost > payment);
	
	return payment;
}

void makeChange(double paid, double cost)
{

	if (paid > cost)
		cout << "Your Change is " << (paid-cost) << endl;
}
