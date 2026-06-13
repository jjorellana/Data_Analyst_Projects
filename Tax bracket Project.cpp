// Tax bracket Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Julio Orellana
Program 7 Tax Bracket Challenge
Programming fundamentals
04 / 11 / 2025 
*/

/* This Program Calculates a simple paycheck as well as identifies
a workers tax bracket to correct withold federal income tax and
deliver a proper net paycheck. */

// We will include a main menu screen and a paycheck input/output screen 


#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


// Declaration & Housekeeping

const double SS_RATE = .062,
				MED_RATE = .0145;

double GROSSPAY,
		NET_PAY,
		FEDERAL_INCOME_TAX;

int PAYPERIOD,
	DECISION;

string FILING_STATUS;

//Function Prototypes

void Paycheckcalc();
double Tax_Bracket(string status, int period, double pay, double& FIT);
void netPayProcess(double socialrate, double medrate, double pay, double FIT);


// Input opportunity and options 

int main()// main menu
{
	cout << endl;
	cout << "          Main Menu     " << endl;
	cout << "------------------------------" << endl;
	cout << "   1. Calculate a Paycheck" << endl;
	cout << "   2. Exit Program" << endl;

	cout << "\nPlease enter menu option : ";
		cin >> DECISION;
		cout << endl;

	while (DECISION <1 || DECISION > 2)
		{
			cout << "Please only input 1 or 2 as they are the only option!" << endl;
			cout << "Please enter menu option: ";
			cin >> DECISION;
		}

	if (DECISION == 1)
		Paycheckcalc(); // calls funtion 
	else if (DECISION == 2)
		exit(0); // exits funtion and ends program

	return(0);
}
// Function to input gross pay , pay period, and filing status
void Paycheckcalc()
{
	// Function Houskeeping and declaration
	bool Checkmark = false;

	cout << endl;
	cout << endl;
	cout << endl;
	cout << "       Calculate Paycheck    " << endl;
	cout << " =============================" << endl<< endl;
	cout << "Enter gross pay : $";
	cin >> GROSSPAY;
	cout << endl;
	cout << "\nWhich of the following is your Pay period ? \n";
	cout << "\n    1->Biweekly(Every 2 weeks)\n";
	cout << "    2->Semimonthly(Twice a month)\n";
	cout << "    3->Monthly(One a month)\n";
	cout << "\n\nPlease Enter your pay period:";
	cin >> PAYPERIOD;


	while (PAYPERIOD < 1 || PAYPERIOD >3)
		{
			cout << "\nPlease enter an option between 1 - 3 as shown!\n";
			cout << "What is your Pay period: ";
			cin >> PAYPERIOD;
		}
	cout << "\n What is your filing status ?\n";
	cout << "	SIN->Single or Separate(Not Joint)\n";
	cout << "	JNT->Joint(Married or in a partnership)\n";
	cout << "\nEnter your Filing Status :";
	while(Checkmark == false)
		{
			cin >> FILING_STATUS;
			if (FILING_STATUS == "SIN" || FILING_STATUS == "JNT")
				Checkmark = true;
			else 
				cout << "\n\nPlease enter an option as shown above!";
		}

	Tax_Bracket(FILING_STATUS, PAYPERIOD, GROSSPAY, FEDERAL_INCOME_TAX); // calls tax bracket Function for Federal Income Tax

	netPayProcess(SS_RATE, MED_RATE, GROSSPAY, FEDERAL_INCOME_TAX); // calls net pay calculation

}


//Function to locate which Tax Bracket Employee is in. 
double Tax_Bracket(string FILING_STATUS, int PAYPERIOD, double GROSSPAY, double& FEDERAL_INCOME_TAX)
{

	// Array houskeeping for bracket ranges
	const int TaxBracket = 8;
	double BIWFederalJNT[TaxBracket] = { 0, 1065, 1912, 4506, 8402, 15073, 18854, 27748 };
	double UpperBIWFederalJNT[TaxBracket] = { 1065, 1912, 4506, 8402, 15073, 18854, 27748, 27748 };

	double BIWFederalSIN[TaxBracket] = { 0, 533, 956, 2253, 4201, 7537, 9427, 22768 };
	double UpperBIWFederalSIN[TaxBracket] = { 533, 956, 2253, 4201, 7537, 9427, 22768, 22768 };

	double SEMIFederalJNT[TaxBracket] = { 0, 1154, 2071, 4881, 9102, 16329, 20425, 30600 };
	double UpperSEMIFederalJNT[TaxBracket] = { 1154, 2071, 4881, 9102, 16329, 20425, 30600, 30600 };

	double SEMIFederalSIN[TaxBracket] = { 0, 577, 1035, 2441, 4551, 8165, 10213, 24666 };
	double UpperSEMIFederalSIN[TaxBracket] = { 577, 1035, 2441, 4551, 8165, 10213, 24666, 24666 };

	double MONFederalJNT[TaxBracket] = { 0, 2308, 4142, 9763, 18204, 32658, 40850, 60121 };
	double UpperMONFederalJNT[TaxBracket] = { 2308, 4142, 9763, 18204, 32658, 40850, 60121, 60121 };

	double MONFederalSIN[TaxBracket] = { 0, 1154, 2071, 4881, 9102, 16329, 20425, 49331 };
	double UpperMONFederalSIN[TaxBracket] = { 1154, 2071, 4881, 9102, 16329, 20425, 49331, 49331 };

	double ColumnC = 0;
	const int COL_C = 8;
	double BIColumnCJNT[COL_C] = { 0.00, 0.00, 84.70, 395.98, 1253.10, 2854.14, 4064.06, 7176.96 };
	double BIColumnCSIN[COL_C] = { 0.00, 0.00, 42.30, 197.94, 626.50, 1427.14, 2031.94, 6701.29 };
	double SEMIColumnCJNT[COL_C] = { 0.00, 0.00, 91.70, 428.90, 1357.52, 3092.00, 4402.72, 7774.97 };
	double SEMIColumnCSIN[COL_C] = { 0.00, 0.00, 45.80, 214.52, 678.72, 1546.08, 2201.44, 7259.99 };
	double MONColumnCJNT[COL_C] = { 0.00, 0.00, 183.40, 857.92, 2714.94, 6183.90, 8805.34, 15550.19 };
		double MONColumnCSIN[COL_C] = { 0.00, 0.00, 91.70, 428.90, 1357.52, 3092.00, 4402.75, 14519.82 };

	double ColumnE = 0;
	const int COL_E = 8;
	double BIColumnEJNT[COL_E] = { 0, 1065, 1912, 4506, 8402, 15073, 18854, 27748 };
	double BIColumnESIN[COL_E] = { 0, 533, 956, 2253, 4201, 7537, 9427, 22768 };
	double SEMIColumnEJNT[COL_E] = { 0, 1154, 2071, 4881, 9102, 16329, 20425, 30060 };
	double SEMIColumnESIN[COL_E] = { 0, 577, 1035, 2441, 4551, 8165, 10213, 24666 };
	double MONColumnEJNT[COL_E] = { 0, 2308, 4142, 9763, 18204, 32658, 40850, 60121 };
		double MONColumnESIN[COL_E] = { 0, 1154, 2071, 4881, 9102, 16329, 20425, 49331 };
	
	const int TaxPercentage = 8;
		double Taxrate[TaxPercentage] = { 0.0, .10, .12, .22, .24, .32, .35, .37 };
	
		int count = 0;


	//Processing and program for paycheckcalc
			if (PAYPERIOD == 1)
				if (FILING_STATUS == "SIN")
				{
					cout << "You are in the Single / Married seperate filing Tax Bracket \n";
					for (int count = 0; count < TaxBracket; count++)
					{
						if (GROSSPAY >= BIWFederalSIN[count] && GROSSPAY <= UpperBIWFederalSIN[count])
						{
							ColumnC = BIColumnCSIN[count];
							ColumnE = BIColumnESIN[count];
							Taxrate[count];
							FEDERAL_INCOME_TAX = ColumnC + (Taxrate[count] * (GROSSPAY - ColumnE));
							break;
						}



						else if (count == 7)
						{
							ColumnC = BIColumnCSIN[count];
							ColumnE = BIColumnESIN[count];
							Taxrate[count];
							FEDERAL_INCOME_TAX = ColumnC + (Taxrate[count] * (GROSSPAY - ColumnE));
							break;
						}
					}
				}
				else if (FILING_STATUS == "JNT")
				{
					cout << "You are in the Married Joint filing Tax Bracket \n";
					for (int count = 0; count < TaxBracket; count++)
						if (GROSSPAY >= BIWFederalJNT[count] && GROSSPAY <= UpperBIWFederalJNT[count])
						{
							ColumnC = BIColumnCJNT[count];
							ColumnE = BIColumnEJNT[count];
							Taxrate[count];
							FEDERAL_INCOME_TAX = ColumnC + (Taxrate[count] * (GROSSPAY - ColumnE));
							break;

						}

						else if (count == 7)
						{
							ColumnC = BIColumnCJNT[count];
							ColumnE = BIColumnEJNT[count];
							Taxrate[count];
							FEDERAL_INCOME_TAX = ColumnC + (Taxrate[count] * (GROSSPAY - ColumnE));
							break;
						}
				}
									
			if (PAYPERIOD == 2)
				if (FILING_STATUS == "SIN")
				{
					cout << "You are in the Single / Married seperate filing Tax Bracket\n";
						for (int count = 0; count < TaxBracket; count++)
							if (GROSSPAY >= SEMIFederalSIN[count] && GROSSPAY <= UpperSEMIFederalSIN[count])
							{
								ColumnC = SEMIColumnCSIN[count];
								ColumnE = SEMIColumnESIN[count];
								Taxrate[count];
								FEDERAL_INCOME_TAX = ColumnC + (Taxrate[count] * (GROSSPAY - ColumnE));
								break;
							}
							else if (count == 7)
							{
								ColumnC = SEMIColumnCSIN[count];
								ColumnE = SEMIColumnESIN[count];
								Taxrate[count];
								FEDERAL_INCOME_TAX = ColumnC + (Taxrate[count] * (GROSSPAY - ColumnE));
								break;
							}
				}
				else if (FILING_STATUS == "JNT")
				{
					cout << "You are in the Married Joint filing Tax Bracket\n";
						for (int count = 0; count < TaxBracket; count++)
							if (GROSSPAY >= SEMIFederalJNT[count] && GROSSPAY <= UpperSEMIFederalJNT[count])
							{
								ColumnC = SEMIColumnCJNT[count];
								ColumnE = SEMIColumnEJNT[count];
								Taxrate[count];
								FEDERAL_INCOME_TAX = ColumnC + (Taxrate[count] * (GROSSPAY - ColumnE));
								break;
							}
							else if (count == 7)
							{
								ColumnC = SEMIColumnCJNT[count];
								ColumnE = SEMIColumnEJNT[count];
								Taxrate[count];
								FEDERAL_INCOME_TAX = ColumnC + (Taxrate[count] * (GROSSPAY - ColumnE));
								break;
							}
				}														
			if (PAYPERIOD == 3)
				if (FILING_STATUS == "SIN")
				{
					cout << "You are in the Single / Married seperate filing Tax Bracket\n";
					for (int count = 0; count < TaxBracket; count++)
						if (GROSSPAY >= MONFederalSIN[count] && GROSSPAY <= UpperMONFederalSIN[count])
						{
							ColumnC = MONColumnCSIN[count];
							ColumnE = MONColumnESIN[count];
							Taxrate[count];
							FEDERAL_INCOME_TAX = ColumnC + (Taxrate[count] * (GROSSPAY - ColumnE));
							break;
						}
						else if (count == 7)
						{
							ColumnC = MONColumnCSIN[count];
							ColumnE = MONColumnESIN[count];
							Taxrate[count];
							FEDERAL_INCOME_TAX = ColumnC + (Taxrate[count] * (GROSSPAY - ColumnE));
							break;
						}
				}
				else if (FILING_STATUS == "JNT")
				{
					cout << "You are in the Married Joint filing Tax Bracket\n";
					for (int count = 0; count < TaxBracket; count++)
						if (GROSSPAY >= MONFederalJNT[count] && GROSSPAY <= UpperMONFederalJNT[count])
						{
							ColumnC = MONColumnCJNT[count];
							ColumnE = MONColumnEJNT[count];
							Taxrate[count];
							FEDERAL_INCOME_TAX = ColumnC + (Taxrate[count] * (GROSSPAY - ColumnE));
							break;
						}
						else if (count == 7)
						{
							ColumnC = MONColumnCJNT[count];
							ColumnE = MONColumnEJNT[count];
							Taxrate[count];
							FEDERAL_INCOME_TAX = ColumnC + (Taxrate[count] * (GROSSPAY - ColumnE));
							break;
						}
				}
				//FEDERAL_INCOME_TAX = ColumnC + (Taxrate[count] * (GROSSPAY - ColumnE));
			return FEDERAL_INCOME_TAX;
}	



// Net pay check calculator that deducts taxes and retrieves Federal Income tax amount
void netPayProcess(const double  SS_RATE, const double MED_RATE, double GROSSPAY, double FEDERAL_INCOME_TAX)
{
	//Declarations
	double SStax = 0,
		MEDtax = 0,
		NET_PAY = 0;

		// Process and set equations for taxes 
	
		SStax = GROSSPAY * SS_RATE;
		MEDtax = GROSSPAY * MED_RATE;
		NET_PAY = GROSSPAY - (FEDERAL_INCOME_TAX + SStax + MEDtax );

		//Output Results
		cout << fixed << setprecision(2);
		cout << "           Your Pay Stub\n";
		cout << " ========================================\n";
		cout << "\n   Your gross pay is : $";
		cout << GROSSPAY;
		cout << "\n\n - Your Medicare Tax is : $";
		cout << MEDtax;
		cout << "\n\n - Your Social Security Tax is : $";
		cout << SStax;
		cout << "\n\n - Your Federal Income Tax is : $";
		cout << FEDERAL_INCOME_TAX;
		cout << "\n\n=========================================\n";
		cout << "\nYour net pay is : $";
		cout << NET_PAY;
		cout << "\n\n";
			//return (FEDERAL_INCOME_TAX, NET_PAY, SStax, MEDtax)
}