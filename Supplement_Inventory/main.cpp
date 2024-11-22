#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "main.h"

using namespace std;

int main()
{
	cout << "Welcome! Type 'help' to see all commands." << endl;
	cmd();
	return 0;
}

void cmd()
{
	while (true)
	{
		bool t = false; // testosterone pellets
		bool e = false; // estradiol pellets
		bool a = false; // arimidex pellets
		bool m = false; // male kits
		bool f = false; // female kits
		bool plus = false;
		bool minus = false;

		string dose = "";
		string amount = "";
		string line = "";
		string cmd = "";
		string num = "";

		cout << ">>> ";
		getline(cin, line);
		if (line == "help")
		{
			help();
		}
		else if (line == "quit")
		{
			cout << endl << "You have quit the program. Have a great day!" << endl;
			exit(0);
		}
		else if (line == "inv")
		{
			ifstream iFile;
			string fLine = "";
			iFile.open("supplement_data.txt");
			if (!iFile)
			{
				cout << "Error";
			}
			cout << endl;
			while (getline(iFile, fLine))
			{
				 cout << fLine << endl;
			}
			iFile.close();
			cout << endl;
		}
		else
		{
			int count = 0;
			for (int i = 0; i < line.size(); i++) // Finds command and argument if any
			{
				if (count == 2) //checks dose amount
				{
					while (i < line.size())
					{
						amount += line[i];
						i++;
					}
					
					if (amount[0] == '+')
					{
						plus = true;
					}
					else if (amount[0] == '-')
					{
						minus = true;
					}
					else error();

					for (int j = 1; j < amount.size(); j++)
					{
						if (!isdigit(amount[j]))
						{
							error();
						}
						else num += amount[j];
					}
					count++;
				}

				if (count == 1) //checks dose supplement size
				{
					if (m == true || f == true)
					{
						count++;
						i--;
						continue;
					}
					else
					{
						while (!isspace(line[i]))
						{
							dose += line[i];
							i++;
						}
						if (t == true)
						{
							if (dose != "12.5" && dose != "25" && dose != "100" && dose != "200")
							{
								error();
							}
							else count++;
						}
						else if (e == true)
						{
							if (dose != "12.5" && dose != "25")
							{
								error();
							}
							else count++;
						}
						else if (a == true)
						{
							if (dose != "10")
							{
								error();
							}
							else count++;
						}
						else error();
					}
				}

				if (count == 0) // Checks dose type
				{
					if (line[i] == 'T' || line[i] == 't' && i == 0)
					{
						t = true;
					}
					else if (line[i] == 'E' || line[i] == 'e' && i == 0)
					{
						e = true;
					}
					else if (line[i] == 'A' || line[i] == 'a' && i == 0)
					{
						a = true;
					}
					else if (line[i] == 'M' || line[i] == 'm' && i == 0)
					{
						m = true;
					}
					else if (line[i] == 'F' || line[i] == 'f' && i == 0)
					{
						f = true;
					}
					else if (isspace(line[i]) && i != 0)
					{
						count++;
					}
					else error();
				}
			}
			if (count == 3) // Valid entry to be saved
			{

				int Number = stoi(num);
				int lineNum = 0;
				fstream file;
				string fileLine;
				vector<string> fileLines; 
				
				file.open("supplement_data.txt", ios::in);
				while (getline(file, fileLine))
				{
					fileLines.push_back(fileLine);
				}
				file.close();

				if (t == true) //get the right line number to update
				{
					if (dose == "12.5")
					{
						lineNum = 2;
					}
					else if (dose == "25")
					{
						lineNum = 4;
					}
					else if (dose == "100")
					{
						lineNum = 6;
					}
					else lineNum = 8;
				}
				else if (e == true)
				{
					if (dose == "12.5")
					{
						lineNum = 11;
					}
					else lineNum = 13;
				}
				else if (a == true)
				{
					lineNum = 16;
				}
				else if (m == true)
				{
					lineNum = 19;
				}
				else lineNum = 21;

				if (minus == true)
				{
					Number = Number * -1;
				}
				
				string prevNumS = fileLines[lineNum - 1];
				int prevNum = stoi(prevNumS);

				Number = Number + prevNum;
				string res = to_string(Number);
				fileLines[lineNum - 1] = res;

				file.open("supplement_data.txt", ios::out);
				for (auto v : fileLines)
				{
					file << v << endl;
				}
				file.close();
				cout << endl << "Inventory Updated" << endl << endl;
			}
		}
	}
}

void help()
{
	cout << endl << "List of Commands: "
		<< endl << "--------------------------------------------"
		<< endl << "'help' - shows the list of commands"
		<< endl << "'inv' - shows the supplement inventory"
		<< endl << "'quit' - quits the program"
		<< endl << "--------------------------------------------"
		<< endl << endl
		<< endl << "Adding/Subtracting Supplements: "
		<< endl << "---------------------------------------------------------------------------------------------"
		<< endl << "#1 - Identify the supplement (T for Testosterone, E for Estradiol, A for Arimidex)"
		<< endl << "#2 - Identify the dose amount in mg (12.5, 25, 100, or 200 for T; 12.5 or 25 for E; 10 for A)"
		<< endl << "#3 - Identify the amount of doses used or gained (-3, +2, -5, +1, etc.)"
		<< endl << "Example 1 (E 12.5 +2): Adds 2 doses of 12.5mg Estradiol to inventory"
		<< endl << "Example 2 (T 100 -3): Subtracts 3 doses of 100mg Testosterone from invetory"
		<< endl << "---------------------------------------------------------------------------------------------"
		<< endl << endl
		<< endl << "Adding/Subtracting Kits: "
		<< endl << "--------------------------------------------------------------"
		<< endl << "#1 - Identify the kit type (M for male, F for female)"
		<< endl << "#2 - Identify the amount of kits used or gained (-3, +2, etc.)"
		<< endl << "Example (M +12): Adds 12 male kits to inventory"
		<< endl << "--------------------------------------------------------------"
		<< endl << endl;
}

void error()
{
	cout << endl << "Error: Invalid Command" << endl << endl;
	cmd();
}