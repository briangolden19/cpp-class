
#include "Banking.h"
#include <iostream>
#include <iomanip>               //For setprecision
#include <string>
#include <cmath>
#include <stdexcept>
//Created by Brian Golden brian.golden@snhu.edu on 10/2/2021

using namespace std;

bool Banking::GetUserInput() { // this is our method of getting user input

	for (int i = 0; i < 32; i++) { // print some stars
		cout << "*";
	}
	cout << endl;
	for (int i = 0; i < 10; i++) { 
		cout << "*";
	}
	cout << " Data Input "; //print our top part
	for (int i = 0; i < 10; i++) {
		cout << "*";
	}
	cout << endl;
	string tempInput; // string to get temp input
	try {
		cout << "Initial Investment Amount: ";
		cin >> tempInput; // get user input
		if (tempInput.find('$') == string::npos) { // if no $ was found we throw an error
			throw runtime_error("Needs to start with $");
		}
		tempInput = tempInput.substr(1); // we get everything after the $
		double tempNum = atof(tempInput.c_str()); // we make that string a number
		if (tempNum <= 0) { // if it was not greater than 0 we fail out. This also catches this not being a number
			throw runtime_error("Needs to be Number or greater than 0!");
		}
		this->openingAmount = tempNum; // since no error was thrown yet we set the opening amount
		cout << "Monthly Deposit: ";
		cin >> tempInput;
		if (tempInput.find('$') == string::npos) { // this follows the same idea as above
			throw runtime_error("Needs to start with $");
		}
		tempInput = tempInput.substr(1);
		tempNum = atof(tempInput.c_str());
		if (tempNum <= 0) { // with all input it follows the same format as above
			throw runtime_error("Needs to be Number or greater than 0!");
		}
		this->monthlyDeposit = tempNum;
		cout << "Annual Interest: ";
		cin >> tempInput;
		if (tempInput.find('%') == string::npos) { // the only difference here is we check if it is a % sign not a $ sign
			throw runtime_error("Needs to start with %");
		}
		tempInput = tempInput.substr(1);
		tempNum = atof(tempInput.c_str());
		if (tempNum <= 0) { //same error check for this part though
			throw runtime_error("Needs to be Number or greater than 0!");
		}
		this->interestRate = tempNum;
		cout << "Number of years: ";
		cin >> tempNum;
		if (tempNum <= 0) { //same error check for this part though
			throw runtime_error("Needs to be Number or greater than 0!");
		}
		this->userYears = tempNum;
	}
	catch (runtime_error& excpt) { //this is our catch
		cout << excpt.what() << endl; //it prints the error message
		cout << "Cannot Compute Interest!!" << endl; // and a generic cannot compute
		cin.clear(); // clear the input
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // and input buffer, it just helps
		return false; //returns false since there was an error
	}
	system("pause"); // waits as requested in the instructions
	return true; //no errors returns true
}

void Banking::DisplayYearlyReportNoMon() {
	cout << "    Balance and Interest Without Additional Monthly Deposits" << endl;
	for (int i = 0; i < 65; i++) {
		cout << "=";
	}
	cout << endl;
	cout << "  Year          Year End Balance         Year End Earned Interest" << endl;
	for (int i = 0; i < 65; i++) {
		cout << "-";
	}
	cout << endl; // the above just prints the banner
	double tempEOY = this->openingAmount; // set the temp to the initial investment
	for (int i = 1; i <= this->userYears; i++) { // run a loop for however many years the user wanted
		double interestEarned = tempEOY * (this->interestRate / 100.0); // gets our interest for the year
		tempEOY += interestEarned; // adds it to total for end of year amount

		string outputEOY = to_string(ceil(tempEOY * 100.0) / 100.0); // so this gets the first two decimal places of the EOY and then makes it a string
																	 // I use this to make the formatting of the chart work. I ran into a lot of issues before I figured this out
		string tempSub = outputEOY.substr(0, outputEOY.find('.')); // then we get what is before the decimal
		outputEOY = outputEOY.substr(outputEOY.find('.'), 3); // then get what is after the decimal
		outputEOY = "$" + tempSub + outputEOY; // and make our final output. This had to be done as strings kept displaying like 5.000000000

		string outputInterest = to_string(ceil(interestEarned * 100.0) / 100.0); // we follow the same process for the interest
		tempSub = outputInterest.substr(0, outputInterest.find('.'));
		outputInterest = outputInterest.substr(outputInterest.find('.'), 3);
		outputInterest = "$" + tempSub + outputInterest; //here is our nicely formatted string

		cout << setw(6) << right << i << " ";
		cout << setw(25) << right << outputEOY;
		cout << setw(33) << right << outputInterest << endl; //now we just output and it is nice and pretty
	}
}

void Banking::DisplayYearlyReportMon() {
	cout << "      Balance and Interest With Additional Monthly Deposits" << endl;
	for (int i = 0; i < 65; i++) {
		cout << "=";
	}
	cout << endl;
	cout << "  Year          Year End Balance         Year End Earned Interest" << endl;
	for (int i = 0; i < 65; i++) {
		cout << "-";
	}
	cout << endl; // display our banner
	double tempEOY = this->openingAmount; // get the inital investment
	for (int i = 1; i <= this->userYears; i++) { //we loop the correct amount of years
		double totalInterestEarned = 0; // this is to keep track of the yearly interest
		for (int j = 0; j < 12; j++) {  // we loop for 12 months to get the monthly deposits and interest each month
			double tempInterest = (tempEOY + this->monthlyDeposit) * ((this->interestRate / 100.0) / 12.0); // get the interest per month
			tempEOY += (this->monthlyDeposit + tempInterest); // add the deposit and interest to the EOY data
			totalInterestEarned += tempInterest; // add the temp interest to the total
		}

		string outputEOY = to_string(ceil(tempEOY * 100.0) / 100.0);
		string tempSub = outputEOY.substr(0, outputEOY.find('.'));
		outputEOY = outputEOY.substr(outputEOY.find('.'), 3);
		outputEOY = "$" + tempSub + outputEOY; // the above lines are the exact same process I used in the without monthly method just to make formatting work right

		string outputInterest = to_string(ceil(totalInterestEarned * 100.0) / 100.0);
		tempSub = outputInterest.substr(0, outputInterest.find('.'));
		outputInterest = outputInterest.substr(outputInterest.find('.'), 3);
		outputInterest = "$" + tempSub + outputInterest; // we do that same process again 

		cout << setw(6) << right << i << " ";
		cout << setw(25) << right << outputEOY;
		cout << setw(33) << right << outputInterest << endl; // then output nicely
	}
}