# ConnectN Game Implementation

This program implements the ConnectN game, a strategic board game with simple rules. The game is played on an M x M board, where M is a value between 8 and 25. Each player takes turns placing their game pieces (red or black) on the board, aiming to create a row, column, or diagonal line of N pieces before their opponent does.

## Instructions

1. **Compile and Run**: Compile the program and run the executable. The program will prompt you to enter the size of the board (number of squares along each edge) and the number of pieces needed to form a line to win.
   
2. **Gameplay**:
   - Red moves first, followed by black.
   - Players take turns choosing a column to place their game piece. The piece is placed in the lowest available row in that column.
   - The game continues until one player wins or the board is filled.

3. **Winning**: To win, a player must form a row, column, or diagonal line of N pieces.

## File Structure

- `connectN.c`: The main C program containing the implementation of the ConnectN game.
  
### Functions

1. **main**: The main function orchestrating the game flow.
2. **CheckWinner**: Function to check if a player has won after making a move.
3. **MakeMove**: Function to place a player's game piece on the board.
4. **InitializeBoard**: Function to initialize the game board.
5. **DisplayBoard**: Function to display the current state of the game board.

### Usage

```bash
gcc connectN.c -o connectN
./connectN
