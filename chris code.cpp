#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
//#include "clntdata.h"
using namespace std;
int enterChoice();
void textFile(fstream&);
void updateRecord(fstream&);
void newRecord(fstream&);
void deleteRecord(fstream&);
void outputLine(ostream&, const clientData &);
int getAccount(const char *);
 
enum Choices { TEXTFILE = 1, UPDATE, NEW, DELETE, END };
 
 
struct clientData {
              int accountNumber;
              char lastName[15];
              char firstName[10];
              float balance;
};
 
int main()
{
              fstream inOutCredit("credit.dat", ios::in | ios::out);
              if (!inOutCredit) {
                           cerr << "File could not be opened." << endl;
                           exit(1);
              }
              int choice;
              while ((choice = enterChoice()) != END) {
                           switch (choice) {
                           case TEXTFILE:
                                         textFile(inOutCredit); break;
                           case UPDATE:
                                         updateRecord(inOutCredit); break;
                           case NEW:
                                         newRecord(inOutCredit); break;
                           case DELETE:
                                         deleteRecord(inOutCredit); break;
                           default:
                                         cerr << "Incorrect choice\n"; break;
                           }
                           inOutCredit.clear(); // resets end-of-file indicator
              }
              return 0;
}
// Prompt for and input menu choice
int enterChoice()
{
              cout << "\nEnter your choice" << endl
                           << "1 - store a formatted text file of accounts\n"
                           << "    called \"print.txt\" for printing\n"
                           << "2 - update an account\n"
                           << "3 - add a new account\n"
                           << "4 - delete an account\n"
                           << "5 - end program\n? ";
              int menuChoice;
              cin >> menuChoice;
              return menuChoice;
}
// Create formatted text file for printing
void textFile(fstream &readFromFile)
{
              ofstream outPrintFile("print.txt", ios::out);
              if (!outPrintFile) {
                           cerr << "File could not be opened." << endl;
                           exit(1);
              }
              outPrintFile << setiosflags(ios::left) << setw(10)
                           << "Account" << setw(16) << "Last Name" << setw(11)
                           << "First Name" << resetiosflags(ios::left)
                           << setw(10) << "Balance" << endl;
              readFromFile.seekg(0);
 
              clientData client;
              readFromFile.read(reinterpret_cast<char *>(&client),
                           sizeof(clientData));
 
              while (!readFromFile.eof()) {
                            if (client.accountNumber != 0)
                                         outputLine(outPrintFile, client);
 
                           readFromFile.read(reinterpret_cast<char *>(&client),
                                         sizeof(clientData));
              }
}
// Update an account's balance
void updateRecord(fstream &updateFile)
{
              int account = getAccount("Enter account to update");
              updateFile.seekg((account - 1) * sizeof(clientData));
 
              clientData client;
              updateFile.read(reinterpret_cast<char *>(&client),
                           sizeof(clientData));
              if (client.accountNumber != 0) {
                           outputLine(cout, client);
                           cout << "\nEnter charge (+) or payment (-): ";
 
                           float transaction;    // charge or payment
                           cin >> transaction;   // should validate
                           client.balance += transaction;
                           outputLine(cout, client);
                           updateFile.seekp((account - 1) * sizeof(clientData));
                           updateFile.write(
                                         reinterpret_cast<const char *>(&client),
                                         sizeof(clientData));
              }
              else cerr << "Account #" << account
                           << " has no information." << endl;
}
// Create and insert new record
void newRecord(fstream &insertInFile)
{
              int account = getAccount("Enter new account number");
              insertInFile.seekg((account - 1) * sizeof(clientData));
 
              clientData client;
              insertInFile.read(reinterpret_cast<char *>(&client),
                           sizeof(clientData));
              if (client.accountNumber == 0) {
                           cout << "Enter lastname, firstname, balance\n? ";
                           cin >> client.lastName >> client.firstName
                                         >> client.balance;
                           client.accountNumber = account;
                           insertInFile.seekp((account - 1) *
                                         sizeof(clientData));
                           insertInFile.write(
                                         reinterpret_cast<const char *>(&client),
                                         sizeof(clientData));
              }
              else cerr << "Account #" << account
                           << " already contains information." << endl;
}
// Delete an existing record
void deleteRecord(fstream &deleteFromFile)
{
              int account = getAccount("Enter account to delete");
              deleteFromFile.seekg((account - 1) * sizeof(clientData));
 
              clientData client;
              deleteFromFile.read(reinterpret_cast<char *>(&client),
                           sizeof(clientData));
              if (client.accountNumber != 0) {
                           clientData blankClient = { 0, "", "", 0.0 };
 
                           deleteFromFile.seekp((account - 1) *
                                         sizeof(clientData));
                           deleteFromFile.write(
                                         reinterpret_cast<const char *>(&blankClient),
                                         sizeof(clientData));
                           cout << "Account #" << account << " deleted." << endl;
              }
              else cerr << "Account #" << account << " is empty." << endl;
}
// Output a line of client information
void outputLine(ostream &output, const clientData &c)
{
              output << setiosflags(ios::left) << setw(10)
                           << c.accountNumber << setw(16) << c.lastName
                           << setw(11) << c.firstName << setw(10)
                           << setprecision(2) << resetiosflags(ios::left)
                           << setiosflags(ios::fixed | ios::showpoint)
                           << c.balance << '\n';
}
// Get an account number from the keyboard
int getAccount(const char *prompt)
{
              int account;
              do {
                           cout << prompt << " (1 - 100): ";
                           cin >> account;
              } while (account < 1 || account > 100);
              return account;
}
