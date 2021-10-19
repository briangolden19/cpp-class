#ifndef BANKING_H
#define BANKING_H
//Created by Brian Golden brian.golden@snhu.edu on 10/2/2021
using namespace std;

class Banking {
public:
	bool GetUserInput();
	void DisplayYearlyReportNoMon();
	void DisplayYearlyReportMon();

private:
	int userYears;
	double openingAmount;
	double monthlyDeposit;
	double interestRate;
};
#endif
