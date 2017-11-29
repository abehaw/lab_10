#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <sstream>
#include <string>

using namespace std;

struct clientData
{
       int acountNumber;
       char lastName[15];
       char firstName[10];
       double balance;
};


int main()
{
	string usrLine = "";
	int usrOpn;
	
    ofstream outCredit("credit.dat", ios::out);
    clientData blankClient = {0, "", "", 0.0};
    
    for(int i = 0; i < 100; i++)
    {
    	outCredit.write(reinterpret_cast<const char*>(&blankClient), sizeof(clientData));
	}
	
	cout << "Your options are: " << endl;
	cout << "1 write data to the file" << endl;
	cout << "2 print requested data from a file" << endl;
	cout << "3 print out all records that do not have account # 0" << endl;
    
    while (cin >> usrLine)
	{
		//checking to make sure that the value provided is an integer
		stringstream ss(usrLine);
		if (ss >> usrOpn)
		{
			if (ss.eof())
			{
				//validating year value
				if(usrOpn >= 1 && usrOpn <= 3)
				break;
			}
		}
		//if the user entered an invalid entry this will prompt the user for a new value
		cout << "Invalid value. Please enter an integer value: ";
	}
	
	switch(usrOpn)
	{
		case 1:
			
			break;
		case 2:
			break;
		case 3:
			break;
	}
    
    return 0;
}





