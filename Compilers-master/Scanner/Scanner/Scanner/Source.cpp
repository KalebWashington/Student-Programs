/*
Initial notes:
If we decide to read in entire words at a time we need to change chars to strings in the load code function, along with the initial vector build in the main function, in addition to changing char word to string word.
I'm not sure which will be the best approach as of now.

*/


#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

struct TOKENS
{
	string token_name;
};

/*build tokens notes: I believe we should keep track of how many characters we use to build a token, then delete those elements from the vector and recursively call the build function again with the new size. IE)

for loop to build the first token it comes up with
  push that token into the tokens vector
   call function to delete the elements used to make the token from the vector
      call build function again
*/




//TOKEN PRINT FUNCTION//
void print_tokens(vector<TOKENS> tokens);

//VODE VECTOR DELETE FUNCTION//
void elements_delete(vector<char>code, vector<TOKENS> tokens, int counter);


//TOKEN BUILDER FUNCTION//
void build_tokens(vector<char> code, vector<TOKENS> tokens);


//LOAD CHARACTERS FROM FILE TOKEN//
void load_code(vector<char> code, vector<TOKENS> tokens);

//----------------------------------------//


//INITIAL FUNCTION//
void initial();



//MAIN FUNCTION//
int main()
{
	initial();
}
//----------------//



//VODE VECTOR DELETE FUNCTION//
void elements_delete(vector<char>code, vector<TOKENS> tokens, int counter)
{
	code.erase(code.begin(), code.begin() + counter);
	if (code.size() == 0)
	{
		cin.get();
		exit;
	}
	build_tokens(code, tokens);
}

//LOAD FUNCTION
void load_code(vector<char> code, vector<TOKENS> tokens)
{
	int count = 0;
	char word;
	ifstream file("code.txt");

	if (!file)                                                                  //if we can't open the file print a warning and exit
	{
		cout << "\n--Could not open file--\n--Press Enter to exit--\n";
		cin.get();
		exit(EXIT_FAILURE);
	}

	while (file >> word)                                                         //while to read file into vector
	{
		code.push_back(word);                                                 //pushing the character into the vector
		count++;                                                             //increment count, we may need this later on
	}

	cout << "The gathered data is: ";
	for (int i = 0; i < code.size(); i++)
	{
		cout << code[i];
	}
	cout << "\n\nTest to see if we are getting all chars: " << count;  //for testing
	cin.get();
	file.close();

	build_tokens(code, tokens);
}
//----------------------------------------//



//PRINT FUNCTION
void print_tokens(vector<TOKENS> tokens)
{
	cout << "\nThese are your tokens: \n";
	for (int i = 0; i < tokens.size(); i++)
	{
		cout << tokens.at(i).token_name << " ";
	}
	cin.get();
}
//----------------------------------------//




//TOKEN BUILDER FUNCTION//
/*
Function notes: We'll need to decide what we want to do if we find syntax that isn't correct. IE) #L@#
More than likely we can implement else statements that will throw and error and let the user know that
there's error in their code. We can go back and implement this once we have completed the if statements.
*/
void build_tokens(vector<char> code, vector<TOKENS> tokens)
{
	int counter = 0;
	char test;
	auto list = code.begin();                                                  //iterator
	TOKENS new_entry;

	
	//begin looking through the characters in the vector//
	if (code.size() > 0)
	{
		cout << "\nCurrent vector size: " << code.size() << "\n";


		//GRAPH 1 START//
		//Assign/Decrement/Increment generator//
		if (code[0] == '-')
		{
			counter++;
			advance(list, 1);                                            //iterator & lookahead
			if (*list == '-')
			{
				counter++;
				cout << "\nAssignToken found\n";
				new_entry.token_name = "AssignToken";            //printing for testing purposes
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);

			}
			else if (*list == ')')
			{
				counter++;
				cout << "\nDecrToken found\n";
				new_entry.token_name = "DecrToken";            //printing for testing purposes
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);

			}
			else if (*list == '(')
			{
				counter++;
				cout << "\nIncrToken found\n";
				new_entry.token_name = "IncrToken";            //printing for testing purposes
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);

			}
		}
		//-----------------//


	//left/right parenth. token//
		else if (code[0] == '#')
		{
			counter++;
			advance(list, 1);                                            //iterator & lookahead
			if (*list == 'L')
			{
				counter++;
				advance(list, 1);
				if (*list == '#')
				{
					counter++;
					cout << "\nLParenToken found\n";
					new_entry.token_name = "LParenToken";            //printing for testing purposes
					tokens.push_back(new_entry);
					elements_delete(code, tokens, counter);
				}

			}
			else if (*list == 'R')
			{
				counter++;
				advance(list, 1);
				if (*list == '#')
				{
					counter++;
					cout << "\nRParenToken found\n";
					new_entry.token_name = "RParenToken";            //printing for testing purposes
					tokens.push_back(new_entry);
					elements_delete(code, tokens, counter);
				}
			}
		}
		//-----------------//


		//subtoken//
		else if (code[0] == ')')
		{
			counter++;
			cout << "\nSubToken found\n";
			new_entry.token_name = "SubToken";            //printing for testing purposes
			tokens.push_back(new_entry);
			elements_delete(code, tokens, counter);
		}
		//-----------------//


		//AndToken//
		else if (code[0] == '*')
		{
			counter++;
			advance(list, 1);                                            //iterator & lookahead
			if (*list == 'N')
			{
				counter++;
				cout << "\nAndToken found\n";
				new_entry.token_name = "AndToken";            //printing for testing purposes
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
			}

		}
		//-----------------//

		//NegateToken//
		else if (code[0] == '=')
		{
			counter++;
			advance(list, 1);                                            //iterator & lookahead
			if (*list == '*')
			{
				counter++;
				cout << "\nNegateToken found\n";
				new_entry.token_name = "NegateToken";            //printing for testing purposes
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
			}

		}
		//-----------------//

		//AddToken/StringEscToken//
		else if (code[0] == '\\')
		{
			counter++;
			advance(list, 1);                                            //iterator & lookahead
			if (*list == ')')
			{
				counter++;
				cout << "\nAddToken found\n";
				new_entry.token_name = "AddToken";            //printing for testing purposes
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
			}

			else if (*list == 'M')
			{
				counter++;
				cout << "\nStringEscToken found\n";
				new_entry.token_name = "StringEscToken";            //printing for testing purposes
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
			}

		}
		//-----------------//

		//ArrayToken//
		else if (code[0] == ']')
		{
			counter++;
			advance(list, 1);                                            //iterator & lookahead
			if (*list == '[')
			{
				counter++;
				cout << "\nArrayDefToken found\n";
				new_entry.token_name = "ArrayDefToken";            //printing for testing purposes
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
			}

		}
		//-----------------//
		//GRAPH 1 END//

		//GRAPH 2 START//
		//HexToken//
		else if (code[0] == 'X')
		{
			counter++;
			advance(list, 1);                                            //iterator & lookahead
			if (*list == 'O')
			{
				counter++;
				advance(list, 1);
				if ((*list >= 'A' && *list <= 'F') || (*list >= '0' && *list <= '9'))
				{
					counter++;
					advance(list, 1);
					if ((*list >= 'A' && *list <= 'F') || (*list >= '0' && *list <= '9'))
					{
						counter++;
						advance(list, 1);
						if ((*list >= 'A' && *list <= 'F') || (*list >= '0' && *list <= '9'))
						{
							counter++;
							advance(list, 1);
							if ((*list >= 'A' && *list <= 'F') || (*list >= '0' && *list <= '9'))
							{
								counter++;
								cout << "\nHexToken found\n";
								new_entry.token_name = "HexToken";            //printing for testing purposes
								tokens.push_back(new_entry);
								elements_delete(code, tokens, counter);
							}
						}
					}
				}
			}

		}
		//-----------------//



		//CharLitToken / StringLitToken//
		else if (code[0] == '[')
		{
			counter++;
			advance(list, 1);                                            //iterator & lookahead
			if (*list == '[')
			{
				counter++;
				advance(list, 1);
				if (isalpha(*list) || isalnum(*list))                  //can a characterlit be a number?
				{
					counter++;
					advance(list, 1);
					if (*list == ']')
					{
						counter++;
						advance(list, 1);
						if (*list == ']')
						{
							counter++;
							cout << "\nCharLitToken found\n";
							new_entry.token_name = "CharLitToken";            //printing for testing purposes
							tokens.push_back(new_entry);
							elements_delete(code, tokens, counter);

						}
					}
				}
			}

			else if (isalpha(*list) || isalnum(*list))                  //stringlit portion
			{
				counter++;
				while (*list != ']')
				{
					counter++;
					advance(list, 1);
				}
				cout << "\nStringLitToken found\n";
				new_entry.token_name = "StringLitToken";            //printing for testing purposes
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
			}
		}
		//-----------------//


		
		//IntToken//
		else if (isdigit(code[0]))
		{
			counter++;
			
			
			while (isdigit(*list) && code.size() > counter)
			{
				counter++;
				advance(list, 1);
			}
			
			if (!(*list == 'E' || *list == 'e' || *list == '-' || *list == '.'))      //int portion
			{
				cout << "\IntToken found\n";
				new_entry.token_name = "IntToken";            //printing for testing purposes
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
			}
			
			else if (*list == 'E' || *list == 'e' || *list == '-' || *list == '.')   //real portion
			{
				//counter++;
				//advance(list, 1);
				if (*list == '.')
				{
					//counter++;
					advance(list, 1);
					while (isdigit(*list) && code.size() > counter)
					{
						counter++;
						advance(list, 1);
					}

					cout << "\nRealLitToken found\n";
					new_entry.token_name = "RealLitToken";            //printing for testing purposes
					tokens.push_back(new_entry);
					elements_delete(code, tokens, counter);
				}

			}
				
			
		}
		//-----------------//
//END GRAPH 2//



//GRAPH 3 STARTS//
//True/False Token//
		else if (code[0] == '^')
		{
			counter++;
			advance(list, 1);
			if (*list == 'G')
			{
				counter++;
				cout << "\nTrueToken found\n";
				new_entry.token_name = "TrueToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);

			}
			else if (*list == 'N')
			{
				counter++;
				advance(list, 1);
				if (*list == 'G')
				{
					counter++;
					cout << "\nFalseToken found \n";
					new_entry.token_name = "FalseToken";
					tokens.push_back(new_entry);
					elements_delete(code, tokens, counter);
				}
			}
		}

		//--------------------//



		

		//Division Token//
		else if (code[0] == '_')
		{
			counter++;
			advance(list, 1);
			if (*list == '^')
			{
				counter++;
				advance(list, 1);
				if (*list == '_')
				{
					counter++;
					cout << "\nDivToken found \n";
					new_entry.token_name = "DivToken";
					tokens.push_back(new_entry);
					elements_delete(code, tokens, counter);
				}
			}
		}

		//--------------------//

		
		
		//EOL/RBLOCK Token//
		else if (code[0] == '|')
		{
			counter++;
			advance(list, 1);
			if (*list == 'P')
			{
				counter++;
				cout << "\nEOL found \n";
				new_entry.token_name = "EOLToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
			}

			else if (*list == '-')
			{
				counter++;
				advance(list, 1);
				if (*list == '-')
				{
					counter++;
					advance(list, 1);
					if (*list == '%')
					{
						counter++;
						cout << "\nRBlockToken found \n";
						new_entry.token_name = "RBlockToken";
						tokens.push_back(new_entry);
						elements_delete(code, tokens, counter);
					}
				}
			}
		}

		//-------------------//



		//LBlockToken//
		else if (code[0] == '%')
		{
			counter++;
			advance(list, 1);
			if (*list == '-')
			{
				counter++;
				advance(list, 1);
				if (*list == '-')
				{
					counter++;
					advance(list, 1);
					if (*list == '|')
					{
						counter++;
						cout << "\nLBlockToken found \n";
						new_entry.token_name = "LBlockToken";
						tokens.push_back(new_entry);
						elements_delete(code, tokens, counter);
					}
				}
			}
		}


		//-------------------//



		//Pointer Token//
		else if (code[0] == '~')
		{
			counter++;
			advance(list, 1);
			if (*list == '>')
			{
				counter++;
				cout << "\nPointerToken found \n";
				new_entry.token_name = "PointerToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
			}
		}


		//-----------------------//


		//Equality/Less/LessThanOrEq Token//
		else if (code[0] == '<')
		{
			counter++;
			advance(list, 1);
			if (*list == '>')
			{
				counter++;
				cout << "\nEqToken found \n";
				new_entry.token_name = "EqToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
			}

			else if (*list == 'L')
			{
				counter++;
				cout << "\nLessToken found \n";
				new_entry.token_name = "LessToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
			}

			else if (*list == 'E')
			{
				counter++;
				cout << "\nLessThanOrEqToken found \n";
				new_entry.token_name = "LessThanOrEqToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
			}
		}


		//-----------------------//




		//Greater/GreaterThanOrEq Token//
		else if (code[0] == '>')
		{
			counter++;
			advance(list, 1);
			if (*list == 'G')
			{
				counter++;
				cout << "\nGreaterThanOrEqToken found \n";
				new_entry.token_name = "GreaterThanOrEqToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
			}

			else if (*list == 'W')
			{
				counter++;
				cout << "\nGreaterToken found \n";
				new_entry.token_name = "GreaterToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
			}
		}


		//------------------------------//


		// Graph 3 ends, start Graph 4//

		//LMultiLineComment/Or Token//
		else if (code[0] == '/')
		{
			counter++;
			advance(list, 1);
			if (*list == '@')
			{
				counter++;
				cout << "\nLMultiLineCommentToken found \n";
				new_entry.token_name = "LMultiLineCommentToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
			}

			else if (*list == 'B')
			{
				counter++;
				advance(list, 1);
				if (*list == '/')
				{
					counter++;
					cout << "\nOrToken found \n";
					new_entry.token_name = "OrToken";
					tokens.push_back(new_entry);
					elements_delete(code, tokens, counter);
				}
			}
		}


		//------------------------//



		//SingleLineComment/RMultiLineComment//
		else if (code[0] == '@')
		{
			counter++;
			cout << "\nSingleLineToken found \n";
			new_entry.token_name = "SingleLineToken";
			//tokens.push_back(new_entry);
			//elements_delete(code, tokens, counter);

			advance(list, 1);
			if (*list == '/')
			{
				counter++;
				cout << "\nOrToken found \n";
				new_entry.token_name = "OrToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
			}
		}


		//------------------------//





		//While Token//
		else if (code[0] == 'R')
		{
			counter++;
			advance(list, 1);
			if (*list == 'E')
			{
				counter++;
				advance(list, 1);
				if (*list == 'V')
				{
					counter++;
					cout << "\nWhileToken found \n";
					new_entry.token_name = "WhileToken";
					tokens.push_back(new_entry);
					elements_delete(code, tokens, counter);
				}
			}
		}


		//-------------------------------//




		//Case Token//
		else if (code[0] == 'S')
		{
			counter++;
			advance(list, 1);
			if (*list == 'U')
			{
				counter++;
				advance(list, 1);
				if (*list == 'B')
				{
					counter++;
					cout << "\nCaseToken found \n";
					new_entry.token_name = "CaseToken";
					tokens.push_back(new_entry);
					elements_delete(code, tokens, counter);
				}
			}
		}


		//--------------------------//




		//Multi Token//
		else if (code[0] == 'T')
		{
			counter++;
			advance(list, 1);
			if (*list == 'D')
			{
				counter++;
				cout << "\nMultiToken found \n";
				new_entry.token_name = "MultiToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
			}
		}


		// Graph 5 begins //

		//Else Token//
		else if (code[0] == 'A')
		{
			counter++;
			advance(list, 1);
			if (*list == 'U')
			{
				counter++;
				advance(list, 1);
				if (*list == 'D')
				{
					counter++;
					cout << "\nElseToken found\n";
					new_entry.token_name = "ElseToken";
					tokens.push_back(new_entry);
					elements_delete(code, tokens, counter);
				}
			}
		}


		//------------------------//


		//RealDec/VoidDec Token//
		else if (code[0] == 'B')
		{
			counter++;
			advance(list, 1);
			if (*list == 'B')
			{
				counter++;
				cout << "\nRealDecToken found\n";
				new_entry.token_name = "RealDecToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
			}

			else if (*list == 'R')
			{
				counter++;
				advance(list, 1);
				if (*list == 'W')
				{
					counter++;
					advance(list, 1);
					if (*list == 'N')
					{
						counter++;
						advance(list, 1);
						if (*list == 'S')
						{
							counter++;
							cout << "\nVoidDecToken found\n";
							new_entry.token_name = "VoidDecToken";
							tokens.push_back(new_entry);
							elements_delete(code, tokens, counter);
						}
					}
				}
			}
		}


		//----------------------//




		//IntDec/StringDec/BoolDec Token//
		else if (code[0] == 'C')
		{
			counter++;
			advance(list, 1);
			if (*list == 'H')
			{
				counter++;
				advance(list, 1);
				if (*list == 'A')
				{
					counter++;
					advance(list, 1);
					if (*list == 'I')
					{
						counter++;
						advance(list, 1);
						if (*list == 'N')
						{
							counter++;
							advance(list, 1);
							if (*list == 'S')
							{
								counter++;
								cout << "\nIntDecToken found\n";
								new_entry.token_name = "IntDecToken";
								tokens.push_back(new_entry);
								elements_delete(code, tokens, counter);
							}
						}
					}
				}
			}

			else if (*list == 'L')
			{
				counter++;
				advance(list, 1);
				if (*list == 'E')
				{
					counter++;
					advance(list, 1);
					if (*list == 'A')
					{
						counter++;
						advance(list, 1);
						if (*list == 'T')
						{
							counter++;
							advance(list, 1);
							if (*list == 'S')
							{
								counter++;
								cout << "\nStringDecToken found\n";
								new_entry.token_name = "StringDecToken";
								tokens.push_back(new_entry);
								elements_delete(code, tokens, counter);
							}
						}
					}
				}
			}

			else if (*list == 'O')
			{
				counter++;
				advance(list, 1);
				if (*list == 'I')
				{
					counter++;
					advance(list, 1);
					if (*list == 'N')
					{
						counter++;
						cout << "\nBoolDecToken found\n";
						new_entry.token_name = "BoolDecToken";
						tokens.push_back(new_entry);
						elements_delete(code, tokens, counter);
					}
				}
			}
		}


		//-----------------------------//




		//For/CharDec Token//
		else if (code[0] == 'G')
		{
			counter++;
			advance(list, 1);
			if (*list == 'O')
			{
				counter++;
				advance(list, 1);
				if (*list == 'L')
				{
					counter++;
					advance(list, 1);
					if (*list == 'F')
					{
						counter++;
						cout << "\nForToken found\n";
						new_entry.token_name = "ForToken";
						tokens.push_back(new_entry);
						elements_delete(code, tokens, counter);
					}
				}

				else if (*list == 'O')
				{
					counter++;
					advance(list, 1);
					if (*list == 'N')
					{
						counter++;
						cout << "\nCharDecToken found\n";
						new_entry.token_name = "CharDecToken";
						tokens.push_back(new_entry);
						elements_delete(code, tokens, counter);
					}
				}
			}
		}


		//-------------------------//




		//Deref Token//
		else if (code[0] == 'K')
		{
			counter++;
			advance(list, 1);
			if (*list == '0')
			{
				counter++;
				cout << "\nDerefToken found\n";
				new_entry.token_name = "DerefToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
			}
		}


		//---------------------------//




		//Switch Token//
		else if (code[0] == 'M')
		{
			counter++;
			advance(list, 1);
			if (*list == 'O')
			{
				counter++;
				advance(list, 1);
				if (*list == 'T')
				{
					counter++;
					advance(list, 1);
					if (*list == 'I')
					{
						counter++;
						advance(list, 1);
						if (*list == 'O')
						{
							counter++;
							advance(list, 1);
							if (*list == 'N')
							{
								counter++;
								cout << "\nSwitchToken found\n";
								new_entry.token_name = "SwitchToken";
								tokens.push_back(new_entry);
								elements_delete(code, tokens, counter);
							}
						}
					}
				}
			}
		}


		//----------------------------------//



		//Graph 5 ends//

	



	}

	else
	{
		print_tokens(tokens);
	}
	//return;
}


void initial()
{
	cout << "This program will handle the scanner functions of our compiler.\n--PRESS ENTER TO CONTINUE--\n";
	cin.get();
	vector<char> working_code;             //vector to hold the characters read in from the input file
	vector<TOKENS> tokens;                 //vector to hold the tokens that we generate
	load_code(working_code, tokens);        //call load_code function to begin reading in the code
}