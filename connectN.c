//This program was created by Kuan Ting (Tim) Chou. Completed on July 8th 2023
//This program is meant to replicate the game connect 4 where the two players try to connect
//their pieces together to reach at 4 in a row or N in a row for this program.
//They can win by either having N in a row horizontally, vertically, and or diagonally. 

#include <stdio.h>
#include <stdlib.h>

int InitializeBoard(int** connectNBoard, int numRowsInBoard );
int MakeMove(int** connectNBoard, int numRowsInBoard, int playerID, int columnChosen);
int DisplayBoard( int** connectNBoard, int numRowsInBoard);
int CheckWinner( int** connectNBoard, int numRowsInBoard, int numConnect, int columnChosen, int playerID );
int GetChoice(int** connectNBoard, int numRowsInBoard, int playerID, int numConnect);
void clearInputBuffer();


const int MAXSIZE = 25;
const int MINSIZE = 8;
const int MINCONNECTNUM = 4;

int main()
{
    int numRows = 0;
    while (1)
    {
        printf("Enter the number of squares along each edge of board\n");
        
        if (scanf("%d", &numRows) != 1)
        {
            printf("ERROR: The value provided was not an integer\n");
        }
        else if (numRows > MAXSIZE)
        {
            printf("ERROR: Board size too large (>%d)\n", MAXSIZE);
        }
        else if (numRows < MINSIZE)
        {
            printf("ERROR: Board size too small (<%d)\n", MINSIZE);
        }
        else
        {
            break;
        }
        clearInputBuffer();
    }

    int numToConnect = 0;
    while (1)
    {
        printf("Enter the number of pieces that must form a line to win\n");
        
        if (scanf("%d", &numToConnect) != 1)
        {
            printf("ERROR: The value provided was not an integer\n");
        }
        else if (numToConnect < MINCONNECTNUM)
        {
            printf("ERROR: Number to connect is too small (<%d)\n", MINCONNECTNUM);
        }
        else if (numToConnect > numRows - MINCONNECTNUM)
        {
            printf("ERROR: Number to connect is too large (>%d)\n", numRows - MINCONNECTNUM);
        }
        else
        {
            break;
        }
        clearInputBuffer();
    }

    int** myConnectNBoard = (int**)malloc(numRows * sizeof(int*));
    //Test if memory has been allocated properly
    if (myConnectNBoard == NULL)
    {
        printf("Error failed to allocate memory\n");
        return 1;
    }

    for (int i = 0; i < numRows; i++)
    {
        myConnectNBoard[i] = (int*)malloc(numRows * sizeof(int));
    }

    //Test if memory has been allocated properly
    for (int i = 0; i < numRows; i++)
    {
        if (myConnectNBoard[i] == NULL)
        {
            printf("Error failed to allocate memory\n");
            free(myConnectNBoard);
            return 1;
        }
    }

    //Test InitializeBoard function
    if (InitializeBoard(myConnectNBoard, numRows) == 0)
    {
        printf("ERROR: Could not initialize the game board\n");
        exit(1);
    }

    printf("\n\n");
    if (DisplayBoard(myConnectNBoard, numRows) == 0)
    {
        printf("ERROR: Could not display the game board\n");
    }

    int numTurns = 1;
    int playerTurn = 1;
    
    while (1)
    {
        //this if and else statement are responsible for determining whose turn it is
        if (numTurns % 2 == 0)
        {
            playerTurn = 2;
        }
        else
        {
            playerTurn = 1;
        }
        //check if winner has been found. if there is winner test will have the value 2 otherwise test will have value 1
        int test = GetChoice(myConnectNBoard, numRows, playerTurn, numToConnect);
        if (test == 2)
        {
            DisplayBoard(myConnectNBoard, numRows);
            break;
        }
        else if (test == 1 || test == 3)
        {
            printf("\n\n");
            DisplayBoard(myConnectNBoard, numRows);
        }
        numTurns++;     
    }

    //frees dynamically allocated memory for myConnectNBoard
    for (int i = 0; i < numRows; i++)
    {
        free(myConnectNBoard[i]);
    }

    free(myConnectNBoard);

    return 0;
}

//helper function to clear buffer
void clearInputBuffer() 
{
    int c;
    while((c = getchar()) != '\n')
    {
    
    }
}

int InitializeBoard(int** connectNBoard, int numRowsInBoard )
{
    if (connectNBoard == NULL)
    {
        printf("ERROR: cannot initialize the board because the pointer to the board is NULL\n");
        return 0;
    }

    if (numRowsInBoard > MAXSIZE || numRowsInBoard < MINSIZE)
    {
        printf("ERROR: illegal number of rows in board\n");
        return 0;
    }

    for (int i = 0; i < numRowsInBoard; i++)
    {
        for (int j = 0; j < numRowsInBoard; j++)
        {
            connectNBoard[i][j] = 0;
        }
    }
    return 1;
}

int DisplayBoard( int** connectNBoard, int numRowsInBoard)
{
    if (connectNBoard == NULL || numRowsInBoard > MAXSIZE || numRowsInBoard < MINSIZE)
    {
        return 0;
    }
    
    //Prints the top row numbers 
    for (int i = 0; i < numRowsInBoard; i++)
    {
        if (i == 0)
        {
            printf("%6d", i);
        }
        else
        {
            printf("%3d", i);
        } 
    }
    printf("\n");

    char empty = 'o';
    char red = 'R';
    char black = 'B';

    for (int i = 0; i < numRowsInBoard; i++)
    {
        for (int j = 0; j < numRowsInBoard; j++)
        {
            //prints the column numbers on the left
            if (j == 0)
            {
                printf("%3d", i);
            }
            //prints the 'o's
            if (connectNBoard[i][j] == 0)
            {    
                printf("%3c", empty);
            }
            //prints the 'R's
            else if (connectNBoard[i][j] == 1)
            {
                printf("%3c", red);
            }
            //prints the 'B's
            else
            {
                printf("%3c", black);
            }
        }
        printf("\n");
    }
    return 1;
}

int MakeMove(int** connectNBoard, int numRowsInBoard, int playerID, int columnChosen)
{
    if (connectNBoard == NULL)
    {
        return 0;
    }
    //checks if column number is within the range and if column is full
    if (columnChosen > numRowsInBoard - 1 || columnChosen < 0 || connectNBoard[0][columnChosen] != 0)
    {
        printf("Illegal move\n");
        return 0;
    }
    //checks if a position is empty if it is keep incrementing if it isnt take the previous position that was empty
    for (int i = 0; i < numRowsInBoard; i++)
    {
        if (connectNBoard[i][columnChosen] != 0)
        {
            connectNBoard[i-1][columnChosen] = playerID;
            printf("%s has moved\n", (playerID == 1 ? "Red" : "Black"));
            return 1;
        }
    }
    //checks the final row because the previous for loop does not check it
    if (connectNBoard[numRowsInBoard-1][columnChosen] == 0)
    {
        connectNBoard[numRowsInBoard-1][columnChosen] = playerID;
        printf("%s has moved\n", (playerID == 1 ? "Red" : "Black"));
        return 1;
    }
    return 0;
}

//helper function to get the user's input for where they want to place the piece
//it will return different values based on what the user inputs
int GetChoice(int** connectNBoard, int numRowsInBoard, int playerID, int numConnect)
{
    int numTries = 0;
    int chosenColumn = 0;
    
    printf("%s moves\n", (playerID == 1 ? "Red" : "Black"));

    while (1)
    {
        //check number of tries
        if (numTries == 3)
        {
            printf("TOO MANY ILLEGAL MOVES\n");
            printf("%s has forfeited a turn\n", (playerID == 1 ? "Red" : "Black"));
            return 3;
        }
        numTries++;

        printf("Enter the column number where you want to put your piece\n");
        clearInputBuffer();
        //check if the value entered is not a number
        if (scanf("%d", &chosenColumn) != 1)
        {
            printf("ERROR: The value provided was not a number\n");
            continue;
        }
        //check if it is within the range
        else if (chosenColumn > numRowsInBoard - 1 || chosenColumn < 0)
        {
            printf("ERROR: Column %d is not on the board: try again\n", chosenColumn);
            printf("ERROR: Column number should be >= 0 and <= %d\n", numRowsInBoard);
            continue;
        }
        //check if the first row of their chosen column is occupied
        else if (connectNBoard[0][chosenColumn] != 0)
        {
            printf("ERROR: Column %d is already completely full try again\n", chosenColumn);
            continue;
        }
        else
        {
            break;
        }
    }
    if (MakeMove(connectNBoard, numRowsInBoard, playerID, chosenColumn)) 
    {
        if (CheckWinner(connectNBoard, numRowsInBoard, numConnect, chosenColumn, playerID))
        {
            return 2;
        }
        return 1;
    }
    return 0;   
}

int CheckWinner( int** connectNBoard, int numRowsInBoard, int numConnect, int columnChosen, int playerID )
{
    if (columnChosen < 0 || columnChosen > numRowsInBoard - 1)
    {
        printf("ERROR: invalid column chosen, cannot check for winner\n");
        return 0;
    }
    if (connectNBoard == NULL)
    {
        return 0;
    }

    //Get row number
    int rowNum = 0;
    for (int i = 0; i < numRowsInBoard; i++)
    {
        if (connectNBoard[i][columnChosen] != 0 && connectNBoard[i][columnChosen] == playerID)
        {
            rowNum = i;
            break;
        }
    }
    int afterCount = 0;
    int beforeCount = 0;

    //Count Horizontal
    //count the number of the player's pieces to the right of their most recent piece.
    for (int i = columnChosen + 1; i < numRowsInBoard; i++)
    {
        if (connectNBoard[rowNum][i] == playerID)
        {
            afterCount++;
        }
        else
        {
            break;
        }
    }
    //count the number of the player's pieces to the left of their most recent piece. 
    for (int i = columnChosen - 1; i > 0; i--)
    {
        if (connectNBoard[rowNum][i] == playerID)
        {
            beforeCount++;
        }
        else
        {
            break;
        }
    }
    int horizTotal; 
    horizTotal = afterCount + beforeCount + 1;
    if (horizTotal >= numConnect)
    {
        printf("%s has won\n", (playerID == 1 ? "Red" : "Black"));
        return 1;
    }

    //Vertical count
    
    afterCount = 0;
    beforeCount = 0;
    //count the number of the player's pieces to the under their most recent piece.
    for (int i = rowNum - 1; i > 0; i--)
    {
        if (connectNBoard[i][columnChosen] == playerID)
        {
            afterCount++;
        }
        else
        {
            break;
        }
    }
    //count the number of the player's pieces to the above their most recent piece.
    for (int i = rowNum + 1; i < numRowsInBoard; i++)
    {
        if (connectNBoard[i][columnChosen] == playerID)
        {
            beforeCount++;
        }
        else
        {
            break;
        }
    }

    int verticalCheck;
    verticalCheck = afterCount + beforeCount + 1;
    if (verticalCheck >= numConnect)
    {
        printf("%s has won\n", (playerID == 1 ? "Red" : "Black"));
        return 1;
    }
    
    //Diagonal check from upper left to lower right
    afterCount = 0;
    beforeCount = 0;
    
    for (int i = 1; i < numRowsInBoard - 1; i++)
    {
        if (i + rowNum > numRowsInBoard - 1 || i + columnChosen > numRowsInBoard - 1)
        {
            break;
        }
        else if (connectNBoard[i + rowNum][i + columnChosen] == playerID)
        {
            afterCount++;
        }
        else
        {
            break;
        }
    }

    for (int i = 1; i < numRowsInBoard; i++)
    {
        if (rowNum - i < 0 || columnChosen - i < 0)
        {
            break;
        }
        else if (connectNBoard[rowNum - i][columnChosen - i] == playerID)
        {
            beforeCount++;
        }
        else
        {
            break;
        }
    }

    int diagonal1;
    diagonal1 = afterCount + beforeCount + 1;

    if (diagonal1 >= numConnect)
    {
        printf("%s has won\n", (playerID == 1 ? "Red" : "Black"));
        return 1;
    }
    
    
    //Check diagonal from lower left to upper right
    afterCount = 0;
    beforeCount = 0;

    for (int i = 1; i < numRowsInBoard - 1; i++)
    {
        if (rowNum - i < 0 || i + columnChosen > numRowsInBoard - 1)
        {
            break;
        }
        else if (connectNBoard[rowNum - i][i + columnChosen] == playerID)
        {
            afterCount++;
        }
        else
        {
            break;
        }
    }

    for (int i = 1; i < numRowsInBoard - 1; i++)
    {
        if (rowNum + i > numRowsInBoard - 1 || columnChosen - i < 0)
        {
            break;
        }
        else if (connectNBoard[rowNum + i][columnChosen - i] == playerID)
        {
            beforeCount++;
        }
        else
        {
            break;
        }
    }

    int diagonal2;
    diagonal2 = afterCount + beforeCount + 1;

    if (diagonal2 >= numConnect)
    {
        printf("%s has won\n", (playerID == 1 ? "Red" : "Black"));
        return 1;
    }
    return 0;
}