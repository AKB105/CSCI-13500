//This file contains the class declaration for the Sudoku Boaard along with the definitions

//1-Define SUDOKUBOARD_HPP and create the SudokuBoard class
#ifndef SUDOKUBOARD_HPP
#define SUDOKUBOARD_HPP

#include <string> 

class SudokuBoard {
    public: 
        // Member functions for Sudoku BOARD generation
        SudokuBoard();

        void DisplayBoard() const;

        void SetCell(int row, int column, int number);

        int GetCell(int row, int column) const;

        bool IsRowValid(int row, int number) const;

        bool IsColumnValid(int column, int number) const;

        bool IsBoxValid(int row, int column, int number) const;

        bool IsMoveValid(int row, int column, int number) const;

        bool IsFull() const;

        //Member functions for Sudoku PUZZLE generation:
        void ClearCell(int row, int col);

        void GenerateBoard();

        void SaveToFile(const std::string& filename) const;

        bool HasUniqueSolution();
    
    private:
        //Note: A sudoku board is always fixed to be 9x9, 
        //so an array is more efficient than a vector for this specific scenario.
        int board_[9][9]; //Note: Since the size is fixed, we don't need a destructor for the class as well, another victory for arrays!!

        bool FillBoard(); //Note: Private helper function that the board uses to generate itself with actual numbers

        int CountSolutions (int limit);
};

#endif