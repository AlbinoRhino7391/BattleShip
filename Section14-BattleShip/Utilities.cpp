//This is my utilities source file to save my commonly used functions such as the error checking loops for user input.
// Every header file needs an accompaning src file to define the functions that are declared in the Header.


#include <iostream> // basic input/output functions such as cin.get and other nice little error checking functions.
#include <cstring> //This lib is for the use of functions with cstrings, such as string length to create an array from input into an array with a null at the end of the array.
#include <cctype> // this lib is used for functions that can be used to check user input, such as the function isalpha to see if the input is a valid letter. or the function tolower to change input to lowercase.
#include "Utilities.h"

using namespace std;



char GetCharacter(const char* prompt, const char* error)
{

    const int IGNORE_CHAR = 256;

    char input;
    bool failure;

    do
    {
        failure = false;

        cout << prompt;
        cin >> input;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(IGNORE_CHAR, '\n');
            cout << error << endl;
            failure = true;
        }
        else
        {
            cin.ignore(IGNORE_CHAR, '\n');

            if (isalpha(input))
            {
                input = tolower(input);
            }
            else
            {
                cout << error << endl;
                failure = true;
            }
        }

    } while (failure);

    return input;
}

char GetCharacterFull(const char* prompt, const char* error, const char validInput[], int validInputLength, CharacterCaseType charCase)
{
    char input;
    bool failure;
    const int IGNORE_CHAR = 256;

    do
    {
        failure = false;

        cout << prompt;
        cin >> input;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(IGNORE_CHAR, '\n');
            cout << error << endl;
            failure = true;
        }
        else
        {
            cin.ignore(IGNORE_CHAR, '\n');
            if (isalpha(input))
            {
                if (charCase == CC_UPPER_CASE)
                {
                    input = toupper(input);
                }
                else if (charCase == CC_LOWER_CASE)
                {
                    input = tolower(input);
                }
                
                for (int i = 0; i < validInputLength; i++)
                {
                    if (input == validInput[i])
                    {
                        return input;
                    }
                }
            }


            cout << error << endl;
            failure = true;

        }
    } while (failure);
    return input;
}

int Getinteger(const char* prompt, const char* error, const int validInput[], int validInputLength)
{
    int input;
    bool failure;

    const int IGNORE_CHAR = 256;

    do
    {
        failure = false;

        cout << prompt;
        cin >> input;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(IGNORE_CHAR, '\n');
            cout << error << endl;
            failure = true;
        }
        else
        {
            for (int i = 0; validInputLength; i++)
            {
                if (input == validInput[i])
                {
                    return input;
                }
            }

            cout << error << endl;
            failure = true;
        }
    } while (failure);

    return -1;
}


void WaitForKeyPress()
{
    system("read -n 1 -s -p \"Press any key to continue...\";echo");
}

