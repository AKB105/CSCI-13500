Hi Angelo,

Building an entire Sudoku game requires a lot more time than what you are given. I suggest: 

Minimum Requirements:

Use a predefined Sudoku puzzle (hardcoded in the program or read from a text file). [You can build a sudoku solver later in the summer after this ends!] 

Display the board in the console.

Let the player:
- Enter a row, column, and number.

- Reject moves into fixed (original) cells.

- Check whether the move follows Sudoku rules (row, column, and subgrid).

- Update the board if the move is valid.

- End the game when the board is completely filled.

I do expect this to be done using classes. 

Stretch Goals (Optional)
If you finish early: 
- Difficulty selection (different predefined boards) `(DONE!!)`

- A hint system `(DONE)`

- Save/load the game `(... No.)`

- A timer `(DONE!!)`

- Limited lives (e.g., lose after 3 invalid moves) `(DONE!!)`

- Score based on time or mistakes `(DONE!!)`

Let me know if you need any help! Cheering you on!
Syeda

# Angelo's notes:
On a rough, unpolished basis, every program should be as follow:

**1- `SudokuBoard.hpp`**
Defines the `board class` interface: size, grid storage, getting/setting values, checking whether a move is legal, printing the board, clearing editable cells, etc.

**2- `SudokuBoard.cpp`**
Implements the board logic. This is where the 9x9 grid lives and where Sudoku rules are checked: row, column, and 3x3 box validation.

   - (Go to MainPlay.cpp to run a quick test to ensure the board is working)

**3- `SudokuGame.hpp`**
Defines the game controller: starting the game, reading user input, checking win/loss state, managing turns, maybe tracking mistakes.

**4- `SudokuGame.cpp`**
Implements the gameplay loop. This is where we ask the user for row/col/value, call the board to validate the move, update the board, and refresh the screen.

**5- Play.cpp**
Very small. It should just create a `SudokuGame object` and start it.

`Example:`
```Text:
    #include "SudokuGame.hpp"

    int main() {
        SudokuGame game;
        game.start();
        return 0;
    }
```
# Compilation command:
```g++ MainPlay.cpp SudokuBoard.cpp SudokuGame.cpp -o SudokuGame.exe```

List of edge cases and things to fix: 
- ClearScreen works, but it erases way too much. It's erasing welcoming message before user can even read it.
  Also, user doesn't receive any form of confirmation that their move was correct. 
  Likewise, user can't see the warning messages of invalid move or to not change locked cells 
  (although the cells do stay unchanged, so we can confirm that works. Sweet!!)

- Sudoku Board could look cleaner by adding lines to at least separate each subgrid and border the whole board.

- Empty cells should appear as empty spaces, not 0 (However, behind courtains, program should still see them as 0s)

- Obvious edge case: If user enters a letter or word, the program enters an infinite loop

- Sudoku solved puzzle still needs to be printed in a .txt file so that I don't have to solve each Sudoku by myself... 
  (Actually, let's turn this into a feature for the user too. Instead of not allowing the user to see the .txt file, 
  let them see the fixed solution once they've lost the game. 
  This needs to be added alongside the limited lives extra feature tho, so we can worry about that later)

- Would be nice to mark a way to distinguish which numbers were placed by user and which numbers were already there.

- If user enters an invalid row (out of 1 to 9 range), the program allows them to continue despite the invalid row and 
  never informs them about the invalid row placement. At least the board doesn't modifies a non-existant value, but still, 
  a message should stop the user from entering the columns if their rows are bad (and viceversa).