/*
AUTHORS: J. Robillard, C. Suggs, A. Thomas, J. Vasseur, K. Washington
PROGRAM: Symbol Table
CLASS: CSI465-01SC
Professor: Dr. Pokorny
DATE CODED: 2 / 4 / 2017
------------------------------------------------------------------------------
USE: This program which serves the purpose of a symbol table
will eventually become a class or function for our compiler that will work
in unison with the other parts of the compiler to produce target code into Python
from our source code (SJL).

NOTES: None
-----------------------------------------------------------------------------
*/


//INCLUDES//
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
//#include <locale>               //don't believe we need this, going to comment out for now to ensure it isn't broken
//-------//


using namespace std;


//TABLE STRUCTURE//
struct TABLE
{
	string name;                   //string to hold the name of the ID
	string type;                   //string to save the type of symbol
	string kind;                   //string to save the kind of the symbol
	int scope;
};
//-----------------//


//ADD NEW ENTRY FUNCTION//
void add_symbol(vector<TABLE>& symbols)
{
	static bool first_time = true;                                 //bool to determine if the user is entering their first symbol
	static int current_scope = 0;                                  //variable to track where we are in the scope
	static int number_symbols = 0;                                 //may need a counter of how many symbols eventually														 
	string ans_string;                                             //variable to save the user's input if string
	TABLE new_entry;                                              //creating a new variable of type TABLE, this will be pushed into our vector     

	if (first_time == true)                                                                     //checking if this our first entry into the table                                 
	{
		//statement to gather name of the new entry//
		cout << "\nEnter the name of the entry (must start with a lowercase letter): ";
		cin >> ans_string;

		//checking if the first character is lowercase//
		char c = ans_string[0];
		if (!(islower(c)))
		{
			cout << "\n--Invalid naming convention, sending user back to main menu--\n";
			return;
		}

		new_entry.name = ans_string;                                                            //setting the name of the new entry

																								//statement to gather the type of the new entry//
		cout << "\nEnter the type (char,int,void,float,bool,string): ";
		cin >> ans_string;
		transform(ans_string.begin(), ans_string.end(), ans_string.begin(), &::toupper);       //making the string uppercase to facilitate for easier coding

		if (!(ans_string == "CHAR" || ans_string == "INT" || ans_string == "VOID" || ans_string == "FLOAT" || ans_string == "BOOL" || ans_string == "STRING")) //if statement to check if the type is allowable
		{
			cout << "\n--Invalid type, sending user back to main menu--\n";
			return;
		}
		new_entry.type = ans_string;                                                          //inputing the type in the new entry

																							  //---------------------------------------------//

																							  //statement to gather the kind of the new entry//
		cout << "\nEnter the kind (var,func): ";
		cin >> ans_string;                                                                     //taking in the user's input

		transform(ans_string.begin(), ans_string.end(), ans_string.begin(), &::toupper);       //making the string uppercase to facilitate for easier coding

		if (!(ans_string == "VAR" || ans_string == "FUNC"))                                    //if statement to check if the kind is allowable
		{
			cout << "\n--Invalid kind, sending user back to main menu--\n";
			return;
		}

		new_entry.kind = ans_string;                                                          //setting the new entry kind


																							  //statement to set scope//
		new_entry.scope = 0;
		if (ans_string == "FUNC")                                                                 //if to check if the kind was a function. Will force string to upper eventually, this will due for now
		{
			current_scope++;                                                                     //if the new entry is a function increment the scope
		}

		symbols.push_back(new_entry);                                                           //pushing the new entry to the table

		number_symbols++;                                                                          //counter for how many symbols have been entered
		first_time = false;                                                                          //setting this bool to false to indicate that the first entry has been made
		cout << "\n--Symbol has been inserted into the table--\n";
	}


	//else if that runs if the entry is not the first//
	else if (first_time == false)                                                                                      //checking if this is our first iteration
	{
		//statement to gather name of the new entry//
		cout << "\nEnter the name of the entry (must start with a lowercase letter): ";
		cin >> ans_string;

		//checking if the first character is lowercase//
		char c = ans_string[0];                                                                                        //saving the character of the first position in the string
		if (!(islower(c)))                                                                                             //if the first character isn't a lowercase letter return an error
		{
			cout << "\n--Invalid naming convention, sending user back to main menu--\n";
			return;
		}
		//---------------------------------//

		//for loop to check if name already exist in the scope
		for (int i = 0; i < symbols.size(); i++)                                                                      //iterating through our table
		{
			if ((symbols.at(i).scope == current_scope) && (symbols.at(i).name == ans_string))                         //checking if this name already exist at the current scope
			{
				cout << "\n--This entry already exist at this scope, sending the user back to the main menu--\n";
				return;
			}
		}

		new_entry.name = ans_string;                                  //name checked out, assigning the entries name to the new_entry
																	  //------------------------------------------//


																	  //statement to gather the type of the new entry//
		cout << "\nEnter the type (char,int,void,float,bool): ";
		cin >> ans_string;                                                                      //accepting user input
		transform(ans_string.begin(), ans_string.end(), ans_string.begin(), &::toupper);        //making the string uppercase to facilitate for easier coding

		if (!(ans_string == "CHAR" || ans_string == "INT" || ans_string == "VOID" || ans_string == "FLOAT" || ans_string == "BOOL" || ans_string == "STRING")) //if statement to check if the type is allowable
		{
			cout << "\n--Invalid type, sending user back to main menu--\n";
			return;
		}

		new_entry.type = ans_string;                                                           //setting the type of the new entry
																							   //---------------------------------------------//

																							   //statement to gather the kind of the new entry//
		cout << "\nEnter the kind (var,func): ";
		cin >> ans_string;                                                                     //saving use input
		transform(ans_string.begin(), ans_string.end(), ans_string.begin(), &::toupper);       //making the string uppercase to facilitate for easier coding

		if (!(ans_string == "VAR" || ans_string == "FUNC"))                                    //if statement to check if the kind is allowable
		{
			cout << "\n--Invalid kind, sending user back to main menu--\n";
			return;
		}

		new_entry.kind = ans_string;                               //saving the kind of the new entry
																   //--------------------------------------------//

																   //statement to set scope//
		new_entry.scope = current_scope;                          //setting the scope of the new entry                

		if (ans_string == "FUNC")                                 //if the new entry is a function we need to increment our scope by 1
		{
			current_scope++;
		}
		//---------------------//


		symbols.push_back(new_entry);                            //placing the new symbol into the table

		number_symbols++;                                        //counter for how many symbols have been entered
		cout << "\n--Symbol has been inserted into the table--\n";
	}

}
//----------------------------//



//PRINT SYMBOL TABLE FUNCTION//
void print_symbol(vector<TABLE>& symbols)
{
	const char seperator = ' ';                                                                     //variable used for tabular printing
	const int nameWidth = 13;																		//variable used for tabular printing
	const int numWidth = 20;																		//variable used for tabular printing

	if (symbols.size() > 0)                                                                       //if our table isn't empty do this
	{
		cout << "|   NAME   |   TYPE   |   SCOPE   |    KIND    |\n";
		cout << "________________________________________________\n";

		for (int i = 0; i < symbols.size(); i++)                                                   //iterate through the table
		{
			cout << left << " " << setw(nameWidth) << setfill(seperator) << symbols.at(i).name;   //print ith position name
			cout << left << setw(nameWidth) << setfill(seperator) << symbols.at(i).type;          //print ith position type
			cout << left << setw(nameWidth) << setfill(seperator) << symbols.at(i).scope;         //print ith position scope
			cout << left << setw(nameWidth) << setfill(seperator) << symbols.at(i).kind << "\n";    //print ith position kind
		}
		cout << "________________________________________________\n";
	}
	else {
		cout << "\n-The table is empty-\n";
	}
}
//----------------------------------------------------------------------//


//PRINT CURRENT SCOPE FUNCTION//
void print_scope(vector<TABLE>& symbols)
{
	const char seperator = ' ';                                                                      //variable used for tabular printing
	const int nameWidth = 13;                                                                        //variable used for tabular printing
	const int numWidth = 20;                                                                         //variable used for tabular printing
	int current_scope;                                                                               //saving the current scope

	if (symbols.size() <= 0)                                                                         //if our table is empty print a notification
	{
		cout << "\nThe are no symbols in the table\n";
		return;
	}

	else
	{
		current_scope = symbols.back().scope;                                                          //saving our current scope
	}

	cout << "|   NAME   |   TYPE   |   SCOPE   |    KIND    |\n";
	cout << "________________________________________________\n";

	for (int i = 0; i < symbols.size(); i++)                                                           //incrementing through our table
	{
		if (symbols.at(i).scope == current_scope)                                                      //if the ith position in the vector matches the current scope, do this
		{
			cout << left << " " << setw(nameWidth) << setfill(seperator) << symbols.at(i).name;        //print ith position name         
			cout << left << setw(nameWidth) << setfill(seperator) << symbols.at(i).type;               //print ith position type
			cout << left << setw(nameWidth) << setfill(seperator) << symbols.at(i).scope;              //print ith position scope
			cout << left << setw(nameWidth) << setfill(seperator) << symbols.at(i).kind << "\n";       //print ith position kind
		}
	}
	cout << "________________________________________________\n";
}
//----------------------------------------------------------------------//


//CHECK FOR ID AT SCOPE FUNCTION//
void check_id_scope(vector<TABLE>& symbols)
{
	const char seperator = ' ';                                                                              //variable used for tabular printing
	const int nameWidth = 13;                                                                                //variable used for tabular printing
	const int numWidth = 20;                                                                                 //variable used for tabular printing
	int current_scope;                                                                                       //variables used to hold the value of the current scope
	string ans;                                                                                              //variable used to save the user's input
	bool found = false;

	if (symbols.size() <= 0)                                                                                 //if our table is empty print the below code
	{
		cout << "\nThe are no symbols in the table\n";
		return;
	}
	else
	{
		current_scope = symbols.back().scope;                                                                //getting out current scope from the last element in the vector
	}

	cout << "You are currently at scope: " << current_scope << "\nEnter a symbol to search for: ";           //notifying the user to the current scope and promping them for their input
	cin >> ans;                                                                                              //saving the user's input int the ans variable


	for (int i = 0; i < symbols.size(); i++)                                                                 //iterating through the symbol table
	{
		if (symbols.at(i).scope == current_scope && symbols.at(i).name == ans)                               //if the ith position in the vector matches the scope and name print the below                      
		{
			found = true;
		}
	}

	if (found == true)
	{
		cout << "\nYes, " << ans << " was found at the current scope.\n";
	}

	else
	{
		cout << "\nNo, " << ans << " was not found at the current scope.\n";
	}


}
//----------------------------------------------------------------------//


//CHECK FOR ID IN TABLE//
void check_id_table(vector<TABLE>& symbols)
{
	const char seperator = ' ';                                                                      //variable to use for tabulated printing
	const int nameWidth = 13;                                                                        //variable to use for tabulated printing
	const int numWidth = 20;                                                                         //variable to use for tabulated printing
	int current_scope;                                                                               //variable to save our current position in the scope
	string ans;                                                                                      //variable to save the user's input
	bool found = false;

	if (symbols.size() <= 0)                                                                         //checking if our table is empty
	{
		cout << "\nThe are no symbols in the table\n";
		return;
	}

	else                                                                                            //if our table has entries do this
	{
		current_scope = symbols.back().scope;                                                       //saving the current scope that we are at
	}

	cout << "\nEnter a symbol to search for in the table: ";
	cin >> ans;

	for (int i = 0; i < symbols.size(); i++)                                                         //iterate through the symbols in our table
	{
		if (symbols.at(i).name == ans)                                                               //if statement to check if the name matches the user's input
		{
			found = true;
		}
	}

	if (found == true)
	{
		cout << "\nYes, " << ans << " exist in the symbol table.\n";
	}

	else
	{
		cout << "\nNo, " << ans << " was not found in the table.\n";
	}
}
//----------------------------------------------------------------------//



//EXAMINE ATTRIBUTES//
void look_at_attrib(vector<TABLE>& symbols)
{
	const char seperator = ' ';                                                                      //variable to use for tabulated printing
	const int nameWidth = 13;                                                                        //variable to use for tabulated printing
	const int numWidth = 20;                                                                         //variable to use for tabulated printing
	int current_scope;                                                                               //variable to save our current position in the scope
	string ans;                                                                                      //variable to save the user's input

	if (symbols.size() <= 0)                                                                         //checking if our table is empty
	{
		cout << "\nThe are no symbols in the table\n";
		return;
	}

	else                                                                                            //if our table has entries do this
	{
		current_scope = symbols.back().scope;                                                       //saving the current scope that we are at
	}

	cout << "\nEnter a symbol to search for in the table: ";
	cin >> ans;
	cout << "|   NAME   |   TYPE   |   SCOPE   |    KIND    |\n";
	cout << "________________________________________________\n";
	for (int i = 0; i < symbols.size(); i++)                                                         //iterate through the symbols in our table
	{
		if (symbols.at(i).name == ans)                                                               //if statement to check if the name matches the user's input
		{
			cout << left << " " << setw(nameWidth) << setfill(seperator) << symbols.at(i).name;      //print current index name
			cout << left << setw(nameWidth) << setfill(seperator) << symbols.at(i).type;             //print current index type
			cout << left << setw(nameWidth) << setfill(seperator) << symbols.at(i).scope;            //print current index scope
			cout << left << setw(nameWidth) << setfill(seperator) << symbols.at(i).kind << "\n";     //print current index kind
		}
	}
	cout << "________________________________________________\n";
}
//----------------------------------------------------------------------//



//DELETE ID IN TABLE//
void delete_id_table(vector<TABLE>& symbols)
{
	int current_scope;                                        //variable to store the current scope
	int save_position;                                        //if we need to delete a function we'll store it's position in the vector/array
	string ans;                                              //store the name of the ID that the user wants to delete



	if (symbols.size() <= 0)                                 //if table is empty let the user know
	{
		cout << "\nThe are no symbols in the table\n";
		return;
	}
	else
	{
		current_scope = symbols.back().scope;                //determining the scope that we are currently at
	}

	cout << "\nEnter a symbol to delete at the current scope: ";
	cin >> ans;                                              //get ID to be deleted

															 //for loop to iterate through our symbol table
	for (int i = 0; i < symbols.size(); i++)
	{

		//checking the previous scope in case the element to be deleted is a function (the scope would be different than the current working one)
		if (symbols.at(i).name == ans && symbols.at(i).scope == current_scope - 1 && symbols.at(i).kind == "FUNC")  //if name&scope-1&kind match do this              
		{
			save_position = i;                                                                                 //saving the position of our element in the vector.
			for (int j = 0; j < symbols.size(); j++)                                                           //incrementing through the symbol table
			{
				if (symbols.at(j).scope > symbols.at(save_position).scope)                                     //if statement to check scopes below the function we deleted. This is accounting for nesting.
				{
					symbols.erase(symbols.begin() + j);                                                        //deleting entries in the vector
				}
			}
			symbols.erase(symbols.begin() + save_position);                                                    //Finally deleting the function that the user wanted to be deleted.
		}

		else if (symbols.at(i).name == ans && symbols.at(i).scope == current_scope)                            //if statement checking if scope and name are the same
		{
			symbols.erase(symbols.begin() + i);                                                               //deleting the symbol at the ith position
		}
	}
	cout << "________________________________________________\n";
}
//----------------------------------------------------------------------//



//SYMBOL TABLE MENU FUNCTION//
void symbol_table_menu()
{
	vector<TABLE> symbol_table;

	//BEGIN EXECUTION//
	int menuchoice;                                            //char to hold user's menu anwer

															   //do statement for user input
	do {
		//printing menu
		cout << "\n\n--Symbol Table--\n";
		cout << "(1) Add an ID\n";
		cout << "(2) Check for ID in table\n";
		cout << "(3) Check for ID at current scope\n";
		cout << "(4) Remove symbol from current scope\n";
		cout << "(5) Examine attributes \n";
		cout << "(6) Return all IDs from current scope \n";
		cout << "(7) Print entire symbol table \n";
		cout << "(8) to exit\n";

		cout << "\nEnter selection: ";
		cin >> menuchoice;                                 //accepting the user's input

		while (cin.fail())                                 //checking if user's cin is valid
		{
			cin.clear();                                   //clearing cin buffer to accept next user input
			cin.ignore();
			cout << "-Invalid input-\n";
			cout << "\nEnter selection: ";
			cin >> menuchoice;                            //asking for user input
		}

		//switch statement for the menu//
		switch (menuchoice)
		{
		case 1:                                  //case to insert a new symbol
			add_symbol(symbol_table);
			break;
		case 2:                                  //check for ID at current scope
			check_id_table(symbol_table);
			break;
		case 3:                                  //check for ID in symbol table
			check_id_scope(symbol_table);
			break;
		case 4:                                  //case to remove a symbol
			delete_id_table(symbol_table);
			break;
		case 5:                                  //case to examine attributes
			look_at_attrib(symbol_table);
			break;
		case 6:                                  //case to print the current scope
			print_scope(symbol_table);
			break;
		case 7:                                  //case to print the entire symbole table
			print_symbol(symbol_table);
			break;
		default:
			cout << "\nInvalid input\n\n";
			break;
		}
	} while (menuchoice != 8);                  //if q is entered exit the program					
}
//-------------------------------------------------------//


//MAIN FUNCTION//
int main()
{
	cout << "This is the main function, all of the symbol table functions have been placed outside of this to make implementation into the larger whole easier.\n\n--PRESS ENTER TO CONTINUE--\n\n";
	cin.get();
	symbol_table_menu();
}
//-----------//
