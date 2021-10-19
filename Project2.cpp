//Created by Brian Golden brian.golden@snhu.edu on 10/2/2021


#include <iostream>
#include "Banking.h"
using namespace std;

int main()
{
    char keepGoing = 'y'; // a char to keep track if we want to keep running
    while (keepGoing == 'y') { // the loop to keep checking if we want
        Banking bank; // our bank variable
        bool noErrors = bank.GetUserInput(); // get input returns true if no errors were thrown in user input, false if an error was thrown
        if (noErrors) { // if there were no errors we run the breakdown of interest
            system("cls"); // clear the screen before displaying
            bank.DisplayYearlyReportNoMon(); // run the report with no monthly deposit
            bank.DisplayYearlyReportMon(); // run the report with monthly deposit
        }
        cout << "Do you want to continue? y or n" << endl; // ask to continue
        cin >> keepGoing; //get the input
        while (cin.fail() || (keepGoing != 'n' && keepGoing != 'y')) { //my favorite basic input checker
            cin.clear(); //this clears the input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //A quick google showed that this clears the input buffer and is necessary for this to work
            cout << "Please enter correct input!" << endl; //output an error
            cin >> keepGoing;
        }
        cin.clear(); // clear the input 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // and input buffer, it just helps
        system("cls"); //clear screen even if quitting or repeating
    }
    
}

