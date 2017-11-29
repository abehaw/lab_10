#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
 
using namespace std;
 
class Account {
private:
              long acctNum;
              double balance;
public:
              //Description:
              //Pre-condition:
              //Post-condition:
              Account(long acct, double balance) {
                           acctNum = acct;
                           balance = balance;
              }
              //Description:
              //Pre-condition:
              //Post-condition:
              long getAcct() {
                           return acctNum;
              }
              //Description:
              //Pre-condition:
              //Post-condition:
              double getBalance()
              {
                           return balance;
              }
              //Description:
              //Pre-condition:
              //Post-condition:
              void setAcct(long acct)
              {
                           acctNum = acct;
              }
              //Description:
              //Pre-condition:
              //Post-condition:
              void setBalance(double balance)
              {
                           balance = balance;
              }
 
              //Description:
              //Pre-condition:
              //Post-condition:
              virtual string toString() {
                           stringstream ss;
                           ss << "Account # = " << acctNum << " Balance = $" << balance << endl;
                           return ss.str();
              }
              //Description:
              //Pre-condition:
              //Post-condition:
              virtual double computeIntr(int years) {
                           return 0;
              }
};
 
class Checking :public Account {
private:
      int minIntrBalance;
      int intRate;
public:
      //Description:
      //Pre-condition:
      //Post-condition:
      Checking(long acct, double bal) : Account(acct, bal)
      {
                   minIntrBalance = bal;
                   //intRate = rate;
      }

      //Description:
      //Pre-condition:
      //Post-condition:
      void setMinIntrBalence(int bal)
      {
                   minIntrBalance = bal;
      }

      //Description:
      //Pre-condition:
      //Post-condition:
      void setRate(int rate)
      {
                   intRate = rate;
      }

      //Description:
      //Pre-condition:
      //Post-condition:
      int getMinIntrBalence()
      {
                   return minIntrBalance;
      }

      //Description:
      //Pre-condition:
      //Post-condition:
      int getRate()
      {
                   return intRate;
      }

      string toString() {
                   stringstream ss;
                   ss << "Checking Account # = " << getAcct() << " Balance = $" << getBalance() << endl;
                   return ss.str();
      }
      double computeIntr(int years) {
                   if (getBalance() > 700) {
                                 return (getBalance() - 700) * 0.02 * years;
                   }
                   else {
                                 return 0;
                   }
      }
};
 
class Savings :public Account {
private:
              double intRate;
public:
              //Description:
              //Pre-condition:
              //Post-condition:
              Savings(long acct, double bal, double rate) :Account(acct, bal)
              {
                           intRate = rate;
              }
 
              //Description:
              //Pre-condition:
              //Post-condition:
              double getRate()
              {
                           return intRate;
              }
 
              //Description:
              //Pre-condition:
              //Post-condition:
              void setRate(double rate)
              {
                           intRate = rate;
              }
              string toString()
              {
                           stringstream ss;
                           ss << "Savings Account # = " << getAcct() << " Balance = $" << getBalance() << " Rate = " << intRate * 100 << "%";
                           return ss.str();
              }
              double computeIntr(int years)
              {
                           //return (pow(1 + intRate, years) * getBalance()) - getBalance();
              }
};
 
int main() 
{
	cout << setprecision(2) << fixed;
	Account *accounts[100];
	for (int i = 0; i < 10; ++i) 
	{
		long acct = 0;
		double balance = 0;
		if (i < 5) 
		{
			acct = 100 + i;
			balance = 1000 + (10 * acct);
			accounts[i] = new Checking(acct, balance);
		}
		else 
		{
			acct = 200 + (i - 5);
			balance = 1000 + (10 * acct);
			accounts[i] = new Savings(acct, balance, 0.03);
		}
	}
	Account *account;
	long acct;
	int years;
	double balance;
	cout << "a) Add Acount" << endl;
	cout << "b) set balance" << endl;
	cout << "d) display using the toString function" << endl;
	cout << "i) display interest" << endl;
	cout << "q) quit processing the account" << endl;
	while (true) 
	{
		cout << "Account# : ";
		cin >> acct;
		if ((acct >= 100 && acct <= 104) || (acct >= 200 && acct <= 204)) 
		{
			bool loop = true;
			if (acct < 200) 
			{
				account = accounts[acct % 100];
			}
			else 
			{
				account = accounts[5 + (acct % 100)];
			}
			while (loop) 
			{
				char ch;
				cin >> ch;
				switch (ch) 
				{
					/*case 'a':
					case 'A':
					return 0;
					break;
					case 'r':
					case 'R':
					break;
					case 'g':
					case 'G':
					break;*/
					case 'b':
					case 'B':
						cout << "Please set a balance: ";
						cin >> balance;
						account->setBalance(balance);
						break;
					case 'i':
					case 'I':
						cin >> years;
						cout << "$" << account->computeIntr(years) << endl;
						break;
					case 'd':
					case 'D':
						cout << "Your interest is " << account->toString() << endl;
						break;
					case 'c':
					case 'C':
						cin >> years;
						cout << "$" << account->computeIntr(years) << endl;
						break;
					case 'q':
					case 'Q':
						loop = false;
						break;
					default:
						break;
				}
			}
		}
		else if (acct == 0) {
			return 0;
		}
	}
	return 0;
}
