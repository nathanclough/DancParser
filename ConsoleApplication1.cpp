#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include<sstream>
#include <list>
#include <ctype.h>

/// <summary>
/// This program analyzes .danc and displays the lexeme/token pairs used in the file  
/// </summary>
/// <param name="argc"> number of arguments </param>
/// <param name="argv"> List of arguments as a string </param>
/// <returns> N/A </returns>

using namespace std;


const  string KEYWORDS[] = { "read","write","while","do","od" };
const string KWTOKENS[] = { "KEY_READ", "KEY_WRITE", "KEY_WHILE", "KEY_DO", "KEY_OD", "IDENT", "UNKNOWN" };

const char OPERATOR_CHARACTERS [] =  {'+','-','*','/','(',')',';',':','=','<','>' };
const string OPERATORS[] = { ":=","<",">","=","<>","<=",">=","+","-","*","/","(",")",";" };
const string OPTOKENS[] = { "ASSIGN_OP", "LESSER_OP", "GREATER_OP", "EQUAL_OP", "NEQUAL_OP", "LEQUAL_OP",
                        "GEQUAL_OP","ADD_OP","SUB_OP","MULT_OP", "DIV_OP","LEFT_PAREN","RIGHT_PAREN","SEMICOLON","UNKNOWN"  };

void PrintPair(string s1, string s2);
int IsKeyword(string lexeme);
void Analyze(string fileContents);
int IsOperatorLexeme(string lexeme);
int isoperator(char c);

int main(int argc, char* argv[])
{
    // Check if number arguments are valid 
    if (argc < 2) {
        cout << "Error::Not Enough Arguments (" << argc -1 << " Arguments were supplied)";
    }
    else if (argc > 2) {
        cout << "Error::Too Many Arguments(" << argc << " Arguments were supplied)";

    }
    else {
        ifstream  f(argv[1]);
        string fileContents;
        ostringstream ss;

        // Make sure file exists 
        if (f) {
            ss << f.rdbuf();
            fileContents = ss.str();
            cout << "DanC Analyzer :: R11568824\n";
            Analyze(fileContents);
        }
        else {
            cout << "Error::File doesnt exist";
        }

    }
}
/// <summary>
/// Analyzes the file as string and prints the lexeme token pair 
/// </summary>
/// <param name="filePath"> Path to the input .danc file </param>
void Analyze(string fileContents) {

    int length = fileContents.length();
    int index = 0;
    int endOfTokenIndex = 0;

    // while ! end of string 
    while (index < length) {
        char c = fileContents[index];

        // case c is alphabetical
        if (isalpha(c)) {
            int endOfTokenIndex = index + 1;

            // find end of the lexeme 
            while (isalpha(fileContents[endOfTokenIndex]) and endOfTokenIndex < length) {
                endOfTokenIndex++;
            }

            string temp = fileContents.substr(index, endOfTokenIndex - index);

            int tokenIndex = IsKeyword(temp);
            PrintPair(temp, KWTOKENS[tokenIndex]);
        
            index = endOfTokenIndex - 1;
                
        }

        // case c is numeric 
        else if (isdigit(c)) {
            int endOfTokenIndex = index;

            while (isdigit(fileContents[endOfTokenIndex]) and endOfTokenIndex < length) {
                endOfTokenIndex++;
            }
            string temp = fileContents.substr(index, endOfTokenIndex - index);
            PrintPair(temp, "INT_LIT");

            index = endOfTokenIndex-1;
        }

        // case is operator 
        else if (isoperator(c)>-1){
            int endOfTokenIndex = index + 1;

            while (isoperator(fileContents[endOfTokenIndex]) >6
                                    and !(fileContents[endOfTokenIndex] == ';')
                                    and endOfTokenIndex < index+2) {
                endOfTokenIndex++;
            }
            string temp = fileContents.substr(index, endOfTokenIndex - index);
            int TokenIndex = IsOperatorLexeme(temp);
            PrintPair(temp, OPTOKENS[TokenIndex]);

            index = endOfTokenIndex-1;
        }
        else if (isspace(c)) {
            index++;
            continue;
        }
        else {
            // unknown
            string temp = fileContents.substr(index,1);
            PrintPair(temp, "UNKNOWN");

        }
        index++;
    }
 }
    
// given a lexeme returns the matching index in KEYWORDS and -1 if no matches 
// IDENT = 5 AND UNKNOWN = 6
int IsKeyword(string lexeme){
    for (int x = 0; x < sizeof(KEYWORDS)/sizeof(KEYWORDS[0]); x++) {
        if (lexeme.compare(KEYWORDS[x]) == 0) {
            return x;
        }
    }
    for (int i = 0; i < lexeme.length(); i++)
    {
        if (isupper(lexeme[i]))
            return 6; // this is KEYWORD for UNKNOWN since uppercase is not allowed  
    }
    return 5; // this is KEYWORD for IDENT
}

int IsOperatorLexeme(string lexeme) {
    for (int x = 0; x < sizeof(OPERATORS) / sizeof(OPERATORS[0]); x++) {
        if (lexeme.compare(OPERATORS[x]) == 0) {
            return x;
        }
    }
    return 14; // this is UNKNOWN
}
int isoperator(char c) {
    for (int i = 0; i < sizeof(OPERATOR_CHARACTERS) / sizeof(OPERATOR_CHARACTERS[0]); i++)
    {
        if (c == OPERATOR_CHARACTERS[i]) {
            return i;
        }
    }
    return -1;
}

// Prints the lexeme Token Pair 
void PrintPair(string Lexeme,string Token) {
    cout << Lexeme;
    for (int x = 20 - Lexeme.length(); x > 0; x--) {
        cout << " ";
    }
    cout << " " << Token << "\n";


}
