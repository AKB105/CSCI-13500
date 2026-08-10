//In this file, the objects of the board class, and what will make the game run, will be displayed.

#ifndef SUDOKUGAME_HPP
#define SUDOKUGAME_HPP

#include "SudokuBoard.hpp"

//ADDON: Let the user choose how hard the puzzle will be
enum Difficulty{
    EASY = 1,
    MEDIUM = 2,
    HARD = 3
};


class SudokuGame {
    public:
        SudokuGame();
        
        void PlayGame();

    private:
        Difficulty ChooseDifficulty();

        SudokuBoard board_; //Note: This makes that every SudokuGame object has its own 
        //Sudoku with setted rules and boundaries.
        
        SudokuBoard solved_board_; //Note: This one keeps the actual solution to the puzzle, 
        //which will not be revealed to the user, but the program must have it to check answers.
        
        void CreatePuzzle(int cells_To_Remove);
        
        void ClearScreen();
        
        bool locked_[9][9];
        
        void MarkLockedCells();
        
        int ValidateInput(const std::string& prompt);
        
        int mistakes_; //ADDON: Give the user 5 lives for 5 mistakes. 

        int hints_; //ADDON: Allows the user hints to solve the game.
        
        void GiveHints();

        int score_; //ADDON: Provide the user with a score system based on their rights and wrongs moves
};

#endif