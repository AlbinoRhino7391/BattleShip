// Section14-BattleShip.cpp : This file contains the 'main' function. Program execution begins and ends there.
//  Eric Phelps
// Learning C++ programming by making games
// Self study courses

/*
    Game Breakdown: Battleship

The game is played on a 10x10 grid by 2 players, each player has 2 boards (ship/guess).
Each grid is broke down with the rows(A-J) and the coloumns (1-10).
Each player has 5 ships to arrange on thier own bottom board before the game starts.
each ship occupies a respective consecutive number of spaces in the grid.
ships can only be arranged vertically or horizontally.
the number of spaces taken by the ship is determined by the type of ship.
ships cannot over lap.

    Ship Information:

Type                Size
-------------------+-------
Aircraft carrier   | 5
Battleship         | 4
Cruiser            | 3
Destroyer          | 3
Submarine          | 2

After all ships are placed, The game can start in terms of rounds.
    
    Player 1 Round:
- player 1 declaring which grid square to shoot at on the opposing board.
- player 2 announces if that square is occupied by a ship. (HIT/MISS)
- Player 1 will mark his guess board whether or not his declaration was a hit or miss.
- Player 2 will mark his ship board with a hit or a miss.
-----------------END Player 1 ROUND, START PLAYER 2 ROUND-----------------------------

when all squares of a ship have been hit, the ship is sunk and there should be an output of which ship was sunk.
when all ships of a player have been sunk, that player loses, and the game is over.

*/

/*

     Mental Model of Programs
        +---------------+
 Input  |               |
--------+               | Output
        |     xform     +---------
--------+               |
        |               |
        +---------------+

        We know what the outcome should be as the previously stated breakdown
        Now we can deduce what imput is needed to make that outcome possible
        Once we have the input, then we can create the algoritm to transform the input into output.
*/

/*
Needs based off the breakdown:
    - Ships
        - 5 types (enum)
        - size (dot function to set within the structure)
        - position on board (row, column)
        - orientation (horizontal/ vertical)
        - can be damaged (bool?)
    - Boards
        - 2 types (Guess board/ Ship board)
        - guess board spots have 3 states (HIT/ MISS/ NotGuessed)
        - ship board, holds the ships within their arrays
        - pins markers (H/M)
    - Players
        - name
        - all ships
        - guess board
        - ship board
    - Position Guess
        - position on boards
        - position on board (row, column)
*/

/*  Top Down breakdown// This was done after the design section, I have it placed at the top for organizational reasons
    Psuedo Code:

Step 1: Highest Level (what to put in Main)
    
    Initialize Player (Player1, "Player1");
    Initialize Player (Player2, "Player2");

    do
    {
        PlayGame(Player1, Player2)

    }while(PlayAgain());
------------------------------------------------------------------------
Step 2: Break down step 1 functions

    PlayGame:

    SetupBoard(Player1);
    SetupBoard(Player2);

    do
    {
        DrawBoards(currentPlayer);

        do
        {
            prompt player for a guess
            guess = getGuess();

        }while(!validGuess(guess, current player)

        UpdateBoards(guess, currentPlayer, otherPlayer);
        DrawBoards(currentPlayer);

        if(shipSunk on currentPlayers turn)
        {
            output that player has sunk a ship
        }
        WaitForKeyPress();

        switchPlayer();

    }while(!GameOver);

    Display Winner();
-------------------------------------------------------------------------------------------------
Step 3: Further Brakdown of Step 2 functions

SetupBoard(player):
    ClearBoard(player);

    for(allShips)
    {
        DrawBoard(player);

        currentShip = Get the current ship;

        do
        {
            postion = GetBoardPosition starting with the bow
            orient = GetShipOrient

            validPlacement = valid placement(currentShip, position, orient, player)

            if(!validPlacement)
            {
                output to player, not valid placement.
            }
        }while(!validPlacement)

        PlaceShip(player, currentShip, position, orientation)
    }

validPlacement(player, currentShip, position, orientation):
    if(orient == HORIZONTAL)
    {
        for(all cols the current ship would take up)
        {
            if(ship will overlap another ||  be off board horizontally)
            {
                return false
            }
        }
    }
    else
    {
        for(all the rows of the current ship would take up)
        {
            if(ship will overlap || will be off vertically)
            {
                return false;
            }
        }
    }

    return true;

PlaceShipOnBoard(Player, ship, position, orient)
    
    ship.position = postion
    ship.orientation = orient
    
    if(orientation == HORIZONTAL)
    {
        for(all the cols the ship will take up)
        {
            set the ship part on the board at position.row at current column
        }
    }
    else
    {
        for(all the rows the ship will take up)
        {
            set the ship part on the board at the position.row and postion.col
        }
    }

UpdateBoards(guess, currentplayer, otherplayer)
    
    if(other players ship board at guess is ship part)
    {
        hit
        *set hit on current players guess board
        *set hit on other players ship board
        * apply damage to ship
        * return ship type to check if sunk
    }
    else
    {
        set miss on current player guess board
        return ST_NONE.
    }

GameOver(Player1, Player2)

    return AllShipsSunk(player1) || AllShipsSunk(player2)

AllShipsSunk(player)

    for(allPlayerShips)
    {
        if(!sunk(player, currentShip))
        {
            return false
        }

    }
    return true

sunk(player,ship)

    if(shipOrientation == HORIZONTAL)
    {   
        for(cols ship takes up)
        {
            if(current positionon the ship is not hit)
            {   
                return false
            }
        }
    }
    else
    {
        for(rows ship takes up)
        {
            if(current position of ship is not hit)
            {   
                return false
            }
        }
    }

    return true

*/
#include <iostream>
#include <cstring>
#include "Utilities.h"

using namespace std;

//designing the data, as functions are used to design a program. Structures are used to design user defined data.

// cool thing about enums is you can have an anonymous enum to store constants, I created this open enum after designing the rest of the game to remove magic numbers.
enum
{
    CARRIER_SIZE = 5,
    BATTLESHIP_SIZE = 4,
    CRUISER_SIZE = 3,
    DESTROYER_SIZE = 3,
    SUBMARINE_SIZE = 2,

    BOARD_SIZE = 10,
    NUM_OF_SHIPS = 5,
    PLAYER_NAME_SIZE = 8, // I chose the number 8 because Player1 is 7 characters + 1 for the null character that gets added to the end of cstrings.
    MAX_SHIP_SIZE = CARRIER_SIZE,
};

//---------------------------------------------------- SHIP DESIGN---------------------------------------------------------------------------------------------

// use enumeration for type and orientation, as there can only be a certain type and a certain orientation.
enum ShipType
{
    ST_NONE = 0,
    ST_AIRCRAFT_CARRIER,
    ST_BATTLESHIP,
    ST_CRUISER,
    ST_DESTROYER,
    ST_SUBMARINE,
};
enum ShipOrientationType
{
    SO_VERTICAL = 0,
    SO_HORIZONTAL,
};
// we utilize struc for the position because it take in 2 segments of information to form the position.
struct ShipPositionType
{
    int row;
    int col;
};
// we utilize struc for the ship itself because it take in multiple segments of information to create the ship.
struct Ship
{
    ShipType shipType;
    int shipSize;
    ShipOrientationType orientation;
    ShipPositionType position;
};

//----------------------------------------------------BOARDS DESIGN--------------------------------------------------------------------------------------------------------------

// this enum is used to create the 3 different states that a board position can be in.
enum GuessType
{
    GT_NONE = 0,
    GT_MISSED,
    GT_HIT,
};
//This will only represent one section of a board that contains part of the ship
struct ShipPartType
{
    ShipType shipType;
    bool isHit;
};

//----------------------------------------------------Player Design--------------------------------------------------------------------------------------------------------------
// What does each player have?
struct Player
{
    char playerName[PLAYER_NAME_SIZE];
    Ship ships[NUM_OF_SHIPS];
    GuessType guessBoard[BOARD_SIZE][BOARD_SIZE];
    //For this game we make the ships out of the individual parts to correlate with the spot on the board.
    ShipPartType shipBoard[BOARD_SIZE][BOARD_SIZE];

};

//Global Variables
const char* INPUT_ERROR_STRING = "Invalid input, please try again.";

//Function Prototypes
void InitializePlayer(Player& player, const char* playerName);
void InitializeShip(Ship& ship, int shipSize, ShipType shipType);
void PlayGame(Player& player1, Player& player2);
bool PlayAgain();
void SetupBoards(Player& player);
const char* GetShipNameForType(ShipType shipType);
void ClearBoards(Player& player);
void DrawBoards(const Player& player); // we put a const on the draw boards because the specifications of the boeard will always remain constant.
void SwitchPlayer(Player** currentPlayer, Player** otherPlayer); // we need a pointer to a pointer in order to preperly utilize a multidiminsional array with pointers.
bool IsGameOver(const Player& player1, const Player& player2);
void DisplayWinner(const Player& player1, const Player& player2);

//The following Functions are needed to complete an iteration of DrawBoards()
void DrawSeperationLine();
void DrawColumnsRow();
char GetShipRepresentationAt(const Player& player, int row, int col);
char GetGuessRepresentationAt(const Player& player, int row, int col);
void DrawShipBoardRow(const Player& player, int row);
void DrawGuessBoardRow(const Player& player, int row);

//functions needed to place the ships on the boards.
ShipPositionType GetBoardPosition();
ShipOrientationType GetShipOrientation();
bool isValidPlacement(const Player& player, const Ship& currentShip, const ShipPositionType& shipPosition, ShipOrientationType orientation);
void PlaceShipOnBoard(Player& player, Ship& currentShip, const ShipPositionType& shipPosition, ShipOrientationType orientation);

//this funciton is to update the game board after every round.
ShipType UpdateBoards(ShipPositionType guess, Player& currentPlayer, Player& otherPlayer);

//functions to see if the game is over
bool IsSunk(const Player& player, const Ship& ship);
bool AreAllShipsSunk(const Player& player);

int main()
{
    Player player1;
    Player player2;

    InitializePlayer(player1, "Player1");
    InitializePlayer(player2, "Player2");

    do
    {
        PlayGame(player1, player2);
    } while (PlayAgain());
}

//function descriptions

//What does a player consist of and how do we give it to them at the start of the game.
void InitializePlayer(Player& player, const char* playerName)
{
    if (playerName != nullptr && strlen(playerName) > 0)
    {
        strcpy_s(player.playerName, playerName);
    }

    InitializeShip(player.ships[0], CARRIER_SIZE, ST_AIRCRAFT_CARRIER);
    InitializeShip(player.ships[1], BATTLESHIP_SIZE, ST_BATTLESHIP);
    InitializeShip(player.ships[2], CRUISER_SIZE, ST_CRUISER);
    InitializeShip(player.ships[3], DESTROYER_SIZE, ST_DESTROYER);
    InitializeShip(player.ships[4], SUBMARINE_SIZE, ST_SUBMARINE);

}
// this function was created after initialize player to save myself from writing an additional 5 lines of code per ship type.
void InitializeShip(Ship& ship, int shipSize, ShipType shipType)
{
    ship.shipType = shipType;
    ship.shipSize = shipSize;
    ship.position.row = 0;
    ship.position.col = 0;
    ship.orientation = SO_HORIZONTAL;
}

void PlayGame(Player& player1, Player& player2)
{
    SetupBoards(player1);
    SetupBoards(player2);

    Player* currentPlayer = &player1;
    Player* otherPlayer = &player2;

    ShipPositionType guess;

    do
    {
        DrawBoards(*currentPlayer);

        bool isValidGuess;

        do
        {
            cout << currentPlayer->playerName << " what is your guess? " << endl;
            guess = GetBoardPosition();

            isValidGuess = currentPlayer->guessBoard[guess.row][guess.col] == GT_NONE;

            if (!isValidGuess)
            {
                cout << "That was not a valid Guess, please try again." << endl;
            }


        } while (!isValidGuess);

        ShipType type = UpdateBoards(guess, *currentPlayer, *otherPlayer);
        DrawBoards(*currentPlayer);

        if (type != ST_NONE && IsSunk(*otherPlayer, otherPlayer->ships[type - 1]))
        {
            cout << "you sunk " << otherPlayer->playerName << "'s " << GetShipNameForType(type) << endl;
        }

        WaitForKeyPress();

        SwitchPlayer(&currentPlayer, &otherPlayer);



    } while (!IsGameOver(player1, player2));

    DisplayWinner(player1, player2);

}

ShipType UpdateBoards(ShipPositionType guess, Player& currentPlayer, Player& otherPlayer)
{
       //This Function is to update the game boards after a guess with either a hit or a miss.
    if (otherPlayer.shipBoard[guess.row][guess.col].shipType != ST_NONE)
    {
        currentPlayer.guessBoard[guess.row][guess.col] = GT_HIT;
        otherPlayer.shipBoard[guess.row][guess.col].isHit = true;
    }
    else
    {
        currentPlayer.guessBoard[guess.row][guess.col] = GT_MISSED;
    }
    return otherPlayer.shipBoard[guess.row][guess.col].shipType;
}

void SwitchPlayer(Player** currentPlayer, Player** otherPlayer)
{
    //exact same as we did in the swap by pointer assignment. think round robin.
    Player* temp = *currentPlayer;
    *currentPlayer = *otherPlayer;
    *otherPlayer = temp;
}

void DisplayWinner(const Player& player1, const Player& player2)
{
    if (AreAllShipsSunk(player1))
    {
        cout << "Congrats " << player2.playerName << ", wins" << endl;
    }
    else
    {
        cout << "Congrats " << player1.playerName << ", wins" << endl;
    }
}

bool IsSunk(const Player& player, const Ship& ship)
{
    if (ship.orientation == SO_HORIZONTAL)
    {
        for (int col = ship.position.col; col < (ship.position.col + ship.shipSize); col++)
        {
            if (!player.shipBoard[ship.position.row][col].isHit)
            {
                return false;
            }
        }
    }
    else
    {
        for (int row = ship.position.row; row < (ship.position.row + ship.shipSize); row++)
        {
            if (!player.shipBoard[row][ship.position.col].isHit)
            {
                return false;
            }
        }
    }

    return true;
}


bool AreAllShipsSunk(const Player& player)
{
    for (int i = 0; i < NUM_OF_SHIPS; i++)
    {
        if (!IsSunk(player, player.ships[i]))
        {
            return false;
        }
    }
    return true;
}

bool IsGameOver(const Player& player1, const Player& player2)
{
    return AreAllShipsSunk(player1) || AreAllShipsSunk(player2);
}

bool PlayAgain()
{
    char input;

    const char validInput[2] = { 'y', 'n' };

    input = GetCharacterFull("Would you like to play again? (y/n)", INPUT_ERROR_STRING, validInput, 2, CC_LOWER_CASE);

    return input == 'y';
}

const char* GetShipNameForType(ShipType shipType)
{
    if (shipType == ST_AIRCRAFT_CARRIER)
    {
        return "Aircraft Carrier";
    }
    else if (shipType == ST_BATTLESHIP)
    {
        return "Battleship";
    }
    else if (shipType == ST_CRUISER)
    {
        return "Cruiser";
    }
    else if (shipType == ST_DESTROYER)
    {
        return "Destroyer";
    }
    else if (shipType == ST_SUBMARINE)
    {
        return "Submarine";
    }

    return "None";
}

void SetupBoards(Player& player)
{
    ClearBoards(player);

    for (int i = 0; i < NUM_OF_SHIPS; i++)
    {
        DrawBoards(player);

        Ship& currentShip = player.ships[i];

        ShipPositionType shipPosition;
        ShipOrientationType orientation;

        bool validPlacement = false;

        do
        {
            cout << player.playerName << " Please set the position and orientation for your " << GetShipNameForType(currentShip.shipType) << endl;

            shipPosition = GetBoardPosition();
            orientation = GetShipOrientation();

            validPlacement = isValidPlacement(player, currentShip, shipPosition, orientation);

            if (!validPlacement)
            {
                cout << "That was not a valid ship placement, please try again" << endl;
                WaitForKeyPress();
            }

        } while (!validPlacement);


        PlaceShipOnBoard(player, currentShip, shipPosition, orientation);
    }  
    DrawBoards(player);
    WaitForKeyPress();
}

bool isValidPlacement(const Player& player, const Ship& currentShip, const ShipPositionType& shipPosition, ShipOrientationType orientation)
{
    if (orientation == SO_HORIZONTAL)
    {   //this for is to add the starting postion of the ship + the ship size and check the if statements
        for (int c = shipPosition.col; c < (shipPosition.col + currentShip.shipSize); c++)
        {
            //if where the ship is being placed does not equal an empty space or if the overall length exceeds board length, it is not valid.
            if (player.shipBoard[shipPosition.row][c].shipType != ST_NONE || c >= BOARD_SIZE)
            {
                return false;
            }
        }
    }
    else
    {
        for (int r = shipPosition.row; r < (shipPosition.row + currentShip.shipSize); r++)
        {
            if (player.shipBoard[r][shipPosition.col].shipType != ST_NONE || r >= BOARD_SIZE)
            {
                return false;
            }
        }
    }
    return true;
}

void PlaceShipOnBoard(Player& player, Ship& currentShip, const ShipPositionType& shipPosition, ShipOrientationType orientation)
{
    currentShip.position = shipPosition;
    currentShip.orientation = orientation;

    if (orientation == SO_HORIZONTAL)
    {
        for (int c = shipPosition.col; c < (shipPosition.col + currentShip.shipSize); c++)
        {
            player.shipBoard[shipPosition.row][c].shipType = currentShip.shipType; 
            player.shipBoard[shipPosition.row][c].isHit = false;
        }
    }
    else
    {
        for (int r = shipPosition.row; r < (shipPosition.row + currentShip.shipSize); r++)
        {
            player.shipBoard[r][shipPosition.col].shipType = currentShip.shipType;
            player.shipBoard[r][shipPosition.col].isHit = false;
        }
    }
}

ShipPositionType MapBoardPosition(char rowInput, int colInput)
{
    // this function is to adjust inputs to work with the idexes of our arrays to fit on the map.
    int realRow = rowInput - 'A';
    int realCol = colInput - 1;

    ShipPositionType boardPosition;

    boardPosition.row = realRow;
    boardPosition.col = realCol;

    return boardPosition;
}

ShipPositionType GetBoardPosition()
{
    //This function is to take user input at the begining of the game to decide where to place ships.
    char rowInput;
    int colInput;

    const char validRowInput[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
    const int validColInput[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    rowInput = GetCharacterFull("Please input a row (A - J): ", INPUT_ERROR_STRING, validRowInput, BOARD_SIZE, CC_UPPER_CASE);
    colInput = Getinteger("Please input a column (1 - 10):", INPUT_ERROR_STRING, validColInput, BOARD_SIZE);

    // we need to work in another function because as you can see above the valid inputs wouldnt work well with the 2D array, so we need a function to accomadate that.
    return MapBoardPosition(rowInput, colInput);
}

ShipOrientationType GetShipOrientation()
{
    //much like the function above, we are taking user input to determine if a ship is vertical or horizontal when placed.
    ShipOrientationType orientation;
     
    const char validInput[2] = { 'H', 'V' };
    char input = GetCharacterFull("Please Choose the orientation of this ship vertical(V)/horizantal(H): ", INPUT_ERROR_STRING, validInput, 2, CC_UPPER_CASE);

    if (input == validInput[0])// being the input is H
    {
        return SO_HORIZONTAL;
    }
    else
    {
        return SO_VERTICAL;
    }

}

void ClearBoards(Player& player)
{
    for (int r = 0; r < BOARD_SIZE; r++)
    {
        for (int c = 0; c < BOARD_SIZE; c++)
        {
            player.guessBoard[r][c] = GT_NONE; // for rows as they go through the columns, set each space to guess type none there for they have not been guessed yet.
            player.shipBoard[r][c].shipType = ST_NONE; // this resets the ship board to say there are no ships placed here.
            player.shipBoard[r][c].isHit = false; // this line effectively resets all hit statuses as a double measure.
        }
    }
}

void DrawSeperationLine()
{
    cout << " ";
    // this will esecially make all of the cells for the columns.
    // These are the horizontal lines that look like +---+---+---+
    for (int c = 0; c < BOARD_SIZE; c++)
    {
        cout << "+---";
    }

    cout << "+";
}

void DrawColumnsRow()
{
    cout << "  ";
    //THis function is to name all of the columns 1-10 and give the proper spacing on the boards.
    for (int c = 0; c < BOARD_SIZE; c++)
    {
        int columnName = c + 1;

        cout << " " << columnName << "  ";
    }
}

char GetShipRepresentationAt(const Player& player, int row, int col)
{
    //THis is to be able to show where the ships are on the ship board with the appropriate letter, a blank space if nothing is there, and a * if the ship has been hit.
    if (player.shipBoard[row][col].isHit)
    {
        return '*'; 
    }
    if (player.shipBoard[row][col].shipType == ST_AIRCRAFT_CARRIER)
    {
        return 'A';
    }
    else if (player.shipBoard[row][col].shipType == ST_BATTLESHIP)
    {
        return 'B';
    }
    else if (player.shipBoard[row][col].shipType == ST_CRUISER)
    {
        return 'C';
    }
    else if (player.shipBoard[row][col].shipType == ST_DESTROYER)
    {
        return 'D';
    }
    else if (player.shipBoard[row][col].shipType == ST_SUBMARINE)
    {
        return 'S';
    }
    else
    {
        return ' ';
    }
}

char GetGuessRepresentationAt(const Player& player, int row, int col)
{
    //this function is to draw on the guess board with a * for hit, o for miss, and a blank space for not guessed.
    if (player.guessBoard[row][col] == GT_HIT)
    {
        return '*';
    }
    else if (player.guessBoard[row][col] == GT_MISSED)
    {
        return 'o';
    }
    else
    {
        return ' ';
    }
}

void DrawShipBoardRow(const Player& player, int row)
{
    //This function is to fill in the rows with the vertical bars |   |   |   | 
    char rowName = row + 'A';
    cout << rowName << "|";

    for (int c = 0; c < BOARD_SIZE; c++)
    {
        cout << " " << GetShipRepresentationAt(player, row, c) << " |";
    }
}

void DrawGuessBoardRow(const Player& player, int row)
{
    char rowName = row + 'A';
    cout << rowName << "|";

    for (int c = 0; c < BOARD_SIZE; c++)
    {
        cout << " " << GetGuessRepresentationAt(player, row, c) << " |";
    }
}

void DrawBoards(const Player& player)
{
    // function to draw the entirety of the boards.
    DrawColumnsRow();
    DrawColumnsRow();
    
    cout << endl;

    for (int r = 0; r < BOARD_SIZE; r++)
    {
        DrawSeperationLine();

        cout << " ";

        DrawSeperationLine();
        
        cout << endl;

        DrawShipBoardRow(player, r);

        cout << " ";

        DrawGuessBoardRow(player, r);

        cout << endl;
    }

    DrawSeperationLine();

    cout << " ";

    DrawSeperationLine();

    cout << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
