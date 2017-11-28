//Program Name: Client Data header file
//Programmer Name: Chris Josebalan
//Description: Header file for client Data
//Date Created: 11/22/17
#ifndef ClientData_H
#define ClientData_H
 
struct clientData {
              int accountNumber;
              char lastName[15];
              char firstName[10];
              float balance;
};
#endif
 
//Program Name: Account Number
//Programmer Name: Chris Josebalan
//Description: Updating and mofifying client credit data inside account number
//Date Created: 11/22/17
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
 
int menu();
void creditFile(fstream&);
void updateRecord(fstream&);
void newRecord(fstream&);
void deleteRecord(fstream&);
void outputLine(ostream&, const clientData &);
int getAccount(const char *);
 
enum Choices { CREDITFILE = 1, UPDATE, NEW, DELETE, END };
 
 
int main()
{
              ofstream outCredit("credit.dat", ios::out);
              clientData blankClient = { 0, "", "", 0.0 };
              for (int i = 0; i < 100; i++)
              outCredit.write(reinterpret_cast<const char *>(&blankClient), sizeof(clientData));
 
              fstream ins("credit.dat", ios::in | ios::out);
              if (!ins) {
                           cout << "File does not exist" << endl;
                           system("pause");
                           return 0;
              }
              else
              {
                           cout << "File exists!" << endl;
              }
              int choice;
              while ((choice = menu())) {
                           switch (choice) {
                           case CREDITFILE:
                                         creditFile(ins);
                                         cout << "Stored into print.txt!" << endl;
                                         break;
                           case UPDATE:
                                         updateRecord(ins);
                                         break;
                           case NEW:
                                         newRecord(ins);
                                         break;
                           case DELETE:
                                         deleteRecord(ins);
                                         break;
                           case END:
                                         cout << "Thank you for using this program!" << endl;
                                         system("pause");
                                         return 0;
                           default:
                                         cout << "Error! Please Choose listed option from the menu" << endl;
                                         break;
                           }
                           ins.clear();
              }
              return 0;
}
 
int menu()
{
              cout << "*****************Enter your choice*****************" << endl;
              cout << "1 - Store formatted account info and data into output file (print.txt)" << endl;
              cout << "2 - Update an account" << endl;
              cout << "3 - Add a new account" << endl;
              cout << "4 - Delete an account" << endl;
              cout << "5 - Exit program" << endl;
              int menuChoice;
              cin >> menuChoice;
              return menuChoice;
}
// Create formatted text file for printing
void creditFile(fstream &readFromFile)
{
              ofstream outPrintFile("print.txt", ios::out);
              if (!outPrintFile) {
                           cout << "File could not be opened." << endl;
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
 
                           float transaction;   
                           cin >> transaction;  
                           client.balance += transaction;
                           outputLine(cout, client);
                           updateFile.seekp((account - 1) * sizeof(clientData));
                           updateFile.write(
                                         reinterpret_cast<const char *>(&client),
                                         sizeof(clientData));
              }
              else cout << "Account #" << account
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
                           cout << "Enter lastname, firstname, balance ";
                           cin >> client.lastName >> client.firstName
                                         >> client.balance;
                           client.accountNumber = account;
                           insertInFile.seekp((account - 1) *
                                         sizeof(clientData));
                           insertInFile.write(
                                         reinterpret_cast<const char *>(&client),
                                         sizeof(clientData));
              }
              else cout << "Account number " << account
                           << " already has information" << endl;
}
 
//delets account data
void deleteRecord(fstream &deleteFromFile)
{
              int account = getAccount("Enter account number to delete");
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
                           cout << "Account number " << account << " is deleted." << endl;
              }
              else cout << "Account number" << account << " is empty." << endl;
}
//Outuputs client data
void outputLine(ostream &output, const clientData &c)
{
              output << setiosflags(ios::left) << setw(10)
                           << c.accountNumber << setw(16) << c.lastName
                           << setw(11) << c.firstName << setw(10)
                           << setprecision(2) << resetiosflags(ios::left)
                           << setiosflags(ios::fixed | ios::showpoint)
                           << c.balance << endl;
}
 
//Asking user to type in the account information
int getAccount(const char *prompt)
{
              int account;
              do {
                           cout << prompt << " (1 - 100): ";
                           cin >> account;
              } while (account < 1 || account > 100);
              return account;
}
