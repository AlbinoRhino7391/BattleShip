//This is my utilities header file to save my commonly used functions such as the error checking loops for user input.
// headers are used to store the function prototypes or the declarations of functions.

#ifndef __UTILITIES_H__  //think of this as a copy and paste funciton for a library, if not defined in program, then define it with this.
#define __UTILITIES_H__  //This is telling a program that everything after this line up until the end statement is what needs to be copy and pasted.

enum CharacterCaseType
{
    CC_UPPER_CASE = 0,
    CC_LOWER_CASE,
    CC_EITHER,
}; 


char GetCharacter(const char* prompt, const char* error);
char GetCharacterFull(const char* prompt, const char* error, const char validInput[], int validInputLength, CharacterCaseType charCase);
int Getinteger(const char* prompt, const char* error, const int validInput[], int validInputLength);

void WaitForKeyPress();

#endif // this is the closing end word for the copy paste library function used above.
