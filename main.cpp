#include <iostream>
#include <string.h>
#include <cstdlib>
#include <algorithm>

using namespace std;


char board[3][3] = {{' ', ' ' , ' '}, { ' ', ' ', ' '},{' ', ' ', ' '}};


void clearScreen()
{
    // Windows-specific (works for both 32-bit and 64-bit)
	#if defined(_WIN32) || defined(_WIN64)
    system("cls");

    // If the OS is not Windows
	#else
    system("clear");
	#endif
}



void displayBoard()
{
    cout<<"\n\n\tTic-Tac-Toe\n\n";
    for (int i=0;i<3;i++)
    {
        cout<<"\t";
        for (int j=0;j<3;j++)
        {
            cout<<" "<<board[i][j];
            if (j!=2)
            {
                cout<<" |";
            }
        }
        cout<<"\n";


        if(i!=2)
        {
            cout<<"\t";
            for (int k=1;k<12;k++)
            {
                cout<<"-";
            }
        cout<<"\n";

        }
    }
}



bool input(int row, int column, char player)
{
    if (board[row][column] == ' ')
    {
        board[row][column] = player;
        return true;
    }
    else
    {
        return false;
    }
}

// Check if the either x or o has won
bool checkWin(char player)
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
        {
            return true;

        }
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
        {
            return true;
        }
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
    {
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
    {
        return true;
    }

    return false;
}


bool isDraw()
{
    // Check if the board is full and no one has won
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')  // If there is an empty space, it's not a draw
                return false;
        }
    }
    return true;  // If the board is full and no one has won, it's a draw
}


void resetBoard()
{
    // Reset the board to an empty state
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}


// Main function
int main()
{
    int row, column, xScore, oScore;
    char CurrentPLR= 'X';
    string playAgain = "yes";

    cout<<"\n  Hey, welcome to Tic Tac Toe";



    while(playAgain == "yes")
    {
        clearScreen();
        resetBoard();


        bool gameOver = false;
        while (!gameOver)
        {
            clearScreen();
            displayBoard();
            cout<<"\n   Enter row and column:  ";
            while (true)
            {
                cin >> row;
                if (cin.fail() || row < 1 || row > 3)
                {
                    cin.clear(); // Clear input buffer
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                    cout << "Invalid input! Please enter a row number between 1 and 3: ";
                    clearScreen();
                    displayBoard();
                    cout<<"\n   Enter row and column:  ";
                }
                else
                {
                    break; // Exit loop if valid input
                }
            }

            // Validate column input
            while (true)
            {
                cin >> column;
                if (cin.fail() || column < 1 || column > 3)
                {
                    cin.clear(); // Clear input buffer
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                    cout << "Invalid input! Please enter a column number between 1 and 3: ";
                    clearScreen();
                    displayBoard();
                    cout<<"\n   Enter row and column:  ";
                }
                else
                {
                    break; // Exit loop if valid input
                }
            }



            row--;  // Adjust to 0-based index
            column--;  // Adjust to 0-based index

            // Ensure that the spot is available
            if (!input(row, column, CurrentPLR))
            {
                cout << "This spot is already taken! Try again.\n";
                continue;
            }

            // Check for win or draw after each move
            if (checkWin(CurrentPLR))
            {
                clearScreen();
                displayBoard();
                cout << "\n      Player " << CurrentPLR << " wins!\n";
                if (CurrentPLR == 'X') xScore++;
                else oScore++;
                gameOver = true;
            }
            else if (isDraw())
            {
                clearScreen();
                displayBoard();
                cout << "It's a draw!\n";
                gameOver = true;
            }
            else
            {
                // Switch player turn
                CurrentPLR = (CurrentPLR == 'X') ? 'O' : 'X';
            }
        }

        // Display scores and prompt for new game
        cout << "\t    Wins: \n\n\t    X = " << xScore << "\n\t    O = " << oScore << "\n";
        cout << "\n\n  Would you like to play again? (Yes/No): ";
        cin >> playAgain;
        transform(playAgain.begin(), playAgain.end(), playAgain.begin(), ::tolower);
    }

    cout << "Thanks for playing!\n";
    return 0;
}

