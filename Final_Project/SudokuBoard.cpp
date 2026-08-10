//The class SudokuBoard made on SudokuBoard.hpp is now expanded in this file, where the constructor and destructor are actually defined.

#include "SudokuBoard.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

//1- Define the constructor of the class SudokuBoard so that it makes a 9x9 board of 0s.
SudokuBoard::SudokuBoard() {
    //1.1- Create the board
    for (int row = 0; row < 9; row++){
        for (int col = 0; col < 9; col++){
            board_[row][col] = 0;
        }
    }
}

//2- Definition for member function DisplayBoard. It display the board to terminal with spaces in it
void SudokuBoard::DisplayBoard() const {
    std::cout << "     1 2 3    4 5 6    7 8 9" << std::endl;
    std::cout << "  ++-------++-------++-------++" << std::endl;
    for (int row = 0; row < 9; row++){
        std::cout << row+1 << " || ";

        for (int col = 0; col < 9; col++){
            if (board_[row][col] == 0) {
                std::cout << "  ";
            } else{
                std::cout << board_[row][col] << " ";
            }
             
            if(col == 2 || col == 5){
                std::cout << "|| ";
            }
        }
        std::cout << "||";

        std::cout << std::endl;

        if(row == 2 || row == 5){
            std::cout << "  ++-------++-------++-------++" << std::endl;
        }
    }

    std::cout << "  ++-------++-------++-------++" << std::endl;
}

//3- Takes user's values to set the row and column where a value should be placed in board.
void SudokuBoard::SetCell(int row, int column, int number){
    board_[row][column] = number;
}

//4- Member function GetCell returns the current cell the user is in based on the row and column values.
int SudokuBoard::GetCell(int row, int column) const {
    return board_[row][column];

}

//5- Function checks for a determined row in each column to see if the number is already present in the row or not.
bool SudokuBoard::IsRowValid(int row, int number) const {
    for (int col = 0; col < 9; col++){
        if (board_[row][col] == number){
            return false;
        }
    }

    return true;
}

//6- Similar to its sister function above, IsColumnValid will check for every row in a determined column to report if a number is already present.
bool SudokuBoard::IsColumnValid(int column, int number) const {
    for (int row = 0; row < 9; row++){
        if(board_[row][column] == number){
            return false;
        }
    }

    return true;
}

//7- Member function to verify that the number is not repeated within a box of the sudoku.
//Note: We ask for row and column to know which 3x3 box is the user currently in.
bool SudokuBoard::IsBoxValid(int row, int column, int number) const {

    //Note: Since each box starts from a row and colum at 0 (0-2), 3 (3-5) and 6 (6-8)
    //We declare two variables that divide the rows and columns by groups of 3 so that is easier to check
    int startRow = (row / 3) * 3; //i.e: (5/3) * 3 = 1 * 3 = 3, so now the program looks for the box which starting row is 3.
    int startCol = (column / 3) * 3;

    for (int r = startRow; r < startRow + 3; r++){
        for (int c = startCol; c < startCol + 3; c++){
            if(board_[r][c] == number){
                return false;
            }
        }
    }

    return true;
}

//8- Checks if the user move can be done by checking the current box, column and row the user is in.
bool SudokuBoard::IsMoveValid(int row, int column, int number) const{
    if ((IsRowValid(row, number)) && (IsColumnValid(column, number)) && (IsBoxValid(row, column, number))){
        return true;
    }

    return false;
}

//9- Member function IsFull search the entire sudoku to see if a cell remains empty (assigned to 0).
bool SudokuBoard::IsFull() const {    
    for (int row = 0; row < 9; row++){
        for (int col = 0; col < 9; col++){
            if (board_[row][col] == 0){
                return false;
            }
        }
    }

    return true;
}

//!README: The functions below will generate a solved puzzle that will be, eventually, partially erased, 
//!which will make the player figure out what the missing values will be

//10- As its name gives away, the function will place cero in the called cell. 
//This is a part of the process to create the puzzle, making missing pieces that the user needs to place back
void SudokuBoard::ClearCell(int row, int column) {
    board_[row][column] = 0;
}

//11- Private member function that will find empty cells in the board to place numbers from 1 to 9 in them without repetition in row, column or box
bool SudokuBoard::FillBoard(){
    //11.1- Find an empty cell
    int empty_Cell_Row = -1;
    int empty_Cell_Col = -1;

    for (int row = 0; row < 9; row++){
        for (int col = 0; col < 9; col++){
            if (board_[row][col] == 0){
                empty_Cell_Row = row;
                empty_Cell_Col = col;
                break;
            }
        }
        if (empty_Cell_Row != -1){
            break;
        }
    }

    //11.2- Try filling up with random numbers from 1 to 9
    //Note: Start recursive method here. Base case implemented
    if (empty_Cell_Row == -1){
        return true;
    }

    //11.2.1- Declare an array of numbers from 1 to 9 to possibly be placed in sudoku cell
    int sudokuNum [9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    //11.2.2- Randomize the order in which numbers can be placed
    for (int i = 8; i > 0; i--){
        int random_Index = rand() % (i + 1);

        int temp = sudokuNum[i];
        sudokuNum[i] = sudokuNum[random_Index];
        sudokuNum[random_Index] = temp;
    }

    for (int i = 0; i < 9; i++){
       int value = sudokuNum[i];

       //11.3- Check IsMoveValid()
        if (IsMoveValid(empty_Cell_Row, empty_Cell_Col, value)){
            //11.4- Place a number
            SetCell(empty_Cell_Row, empty_Cell_Col, value);

            //11.5- Keep filling by recursion, for this will allow a backtracking system
            if(FillBoard()){
                return true;
            }
            //11.5.1- The program needs to erase and change its action if a dead end is reached in number placement.
            ClearCell(empty_Cell_Row, empty_Cell_Col);
        }
    }
    //Note: Not a single number worked, so the board is filled.
    return false;
}

//12- Function that will generate the Sudoku in puzzle structure
void SudokuBoard::GenerateBoard(){
    //12.1- Reset board to 0
    for (int row = 0; row < 9; row++){
        for (int col = 0; col < 9; col++){
            board_[row][col] = 0;
        }
    }

    //12.2- Seed a random number generator to avoid patterns
    srand(time(0));

    //12.3- Call FillBoard() to make a solved Sudoku board puzzle
    FillBoard();
}

//13- Opposite purpose to FillBoard(). Instead of filling each cell, it erases random cells and checks if 
//the puzzle still has a unique solution (two or more solutions for a Sudoku puzzle shouldn't be allowed)
int SudokuBoard::CountSolutions(int limit){
    //13.1- Find an empty cell
    int empty_Cell_Row = -1;
    int empty_Cell_Col = -1;

    for (int row = 0; row < 9; row++){
        for (int col = 0; col < 9; col++){
            if (board_[row][col] == 0){
                empty_Cell_Row = row;
                empty_Cell_Col = col;
                break;
            }
        }
        if (empty_Cell_Row != -1){
            break;
        }
    }

    //13.2- If no empty cells in row, then one complete solution was found
    if (empty_Cell_Row == -1){
        return 1;
    }

    int solution_Counter = 0;

    //13.3- Try to place every possible number from 1 to 9 
    for(int val = 1; val <= 9; val++){
        //Note: This follows a similar recursive backtracking procedure from FillBoard(), 
        //but it keeps looking for other possible solutions until no other can be found. I like to think of it as a constant checker for edge cases, 
        //as if a user was constantly trying to look for ways to mess up the logic and report back if it was successful or not in doing so. 
        if (IsMoveValid(empty_Cell_Row, empty_Cell_Col, val)){
            SetCell(empty_Cell_Row, empty_Cell_Col, val);
            solution_Counter += CountSolutions(limit - solution_Counter);

            //Undo the move before trying another possibility
            ClearCell(empty_Cell_Row, empty_Cell_Col);

            //We must assume there is more than one solution
            if (solution_Counter >= limit){
                return solution_Counter;
            } 
        }
    }

    return solution_Counter;
}

//14- Member function of class SudokuBoard. Returns false if Sudoku's puzzle has more than one solution
bool SudokuBoard::HasUniqueSolution(){
    return CountSolutions(2) == 1;
}

//15- Member function to save a copy of the Sudoku fully solved into a file.
void SudokuBoard::SaveToFile(const std::string& filename) const{
    std::ofstream solutionFile(filename);

    if(!solutionFile){
        return;
    }
    solutionFile << "     1 2 3    4 5 6    7 8 9" << std::endl;
    solutionFile << "  ++-------++-------++-------++" << std::endl;
    for (int row = 0; row < 9; row++){
        solutionFile << row+1 << " || ";

        for (int col = 0; col < 9; col++){
            solutionFile << board_[row][col] << " ";

            if(col == 2 || col == 5){
                solutionFile << "|| ";
            }
        }

        solutionFile << "||";
        solutionFile << std::endl;
        if(row == 2 || row == 5){
            solutionFile << "  ++-------++-------++-------++" << std::endl;
        }
    }
    solutionFile << "  ++-------++-------++-------++";
    
    solutionFile.close();
}