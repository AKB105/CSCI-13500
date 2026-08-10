//The procedure and logic for the game are in this file. User input, board changed, display in console, win and losing conditions
#include "SudokuGame.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>

//ADDON: Define the Enumerator Difficulty so that it checks the user's decissions on regard of difficulty.
Difficulty SudokuGame::ChooseDifficulty(){
    int user_choice = 0;
    
    std::cout << "Select difficulty:\n";
    std::cout << "1- Easy\n";
    std::cout << "2- Medium\n";
    std::cout << "3- Hard\n";


    while(true){
        user_choice = ValidateInput("Choose difficulty (1-3): ");
        //Note: We call ValidateInput to invalid words or sentences right away.
        //ValidateInput can still accept numbers from 4 to 9 tho, so we need to handle it through an if-statement.
        if (user_choice >= 1 && user_choice <= 3) {
            return static_cast<Difficulty>(user_choice);
        }
        
        std::cout << "Invalid difficulty. Enter 1, 2, or 3.\n";
    }
}

//1- Define constructor to generate a completed Sudoku Board, then save a copy in solved_board_ 
//so that the program can later modify board_ to erase numbers from it to create an incomplete puzzle by erasing a number of randoms cells.
//Afterwards, it marks which cells still contains numbers in then, which will be the clues for the user to finish the game.
SudokuGame::SudokuGame(){
    board_.GenerateBoard();
    solved_board_ = board_;
    solved_board_.SaveToFile("solved_Sudoku_Puzzle.txt");
    mistakes_ = 0;
    hints_ = 3;
    score_ = 0;
}

//2- Member function that elimates random cells from random rows and columns so that a real puzzle is presented to the user
void SudokuGame::CreatePuzzle(int cells_To_Remove){
    int blank_cells = 0;
    int creation_Attempts = 0;
    const int max_Attempts = 1000;

    while ((blank_cells < cells_To_Remove) && (creation_Attempts < max_Attempts)){

        //Note: Keeps tracks of the attempts the board has to create a randomized unique solution and avoid a long or infinite loop.
        creation_Attempts++;

        int row = rand() % 9;
        int col = rand() % 9;

        //Note: The if- ensure that the program doesn't erase a cell already empty and counts it twice
        if(board_.GetCell(row, col) != 0){
            int original_Values = board_.GetCell(row, col);

            board_.ClearCell(row, col);

            //Note: If the puzzle still has only one solutionn, cell remains blank. Otherwise, the cell returns to its previous original value.
            if (board_.HasUniqueSolution()){
                blank_cells++;
            } else {
                board_.SetCell(row, col, original_Values);
            }
        }
    }
}

//3- Member function to check which cells are a given part of the solution so that the user cannot touch them.
void SudokuGame::MarkLockedCells(){
    for (int row = 0; row < 9; row++){
        for (int col = 0; col < 9; col++){

            //Note: Check if the current cell is empty before games starts.
            //If it is not empty, it means its part of the given out values user can see but cannot modify.
            if (board_.GetCell(row, col) != 0){    
                locked_[row][col] = true;
            } else{
                locked_[row][col] = false;
            }
        }
    }
}

//ADDON: Member function for hints system. It will look at the solved version of the puzzle, 
//pick a random cell, then it will grab the number in there and place it in the incompleted board.
void SudokuGame::GiveHints(){
    int hinted_row;
    int hinted_column;

    do{
        hinted_row = rand() % 9;
        hinted_column = rand() % 9;
    } while (board_.GetCell(hinted_row, hinted_column) != 0);


    int hinted_number = solved_board_.GetCell(hinted_row, hinted_column);

    board_.SetCell(hinted_row, hinted_column, hinted_number);

    hints_--;
}

//4- Member helper function, invalidates user input such as words, characters, sentences or numbers out of range (1 to 9)
int SudokuGame::ValidateInput(const std::string& prompt){
    std::string user_input; 

    while(true){
        std::cout << prompt;
        std::getline(std::cin, user_input);

        if(user_input.length() == 1 && user_input[0] >= '0' && user_input[0] <= '9'){
            return user_input[0] - '0';
        }

        std::cout << "Invalid input. Please try again.\n";
    }
}

//5- Define member function PlayGame, which handles the player's movement and the game process.
void SudokuGame::PlayGame() {
    std::cout << "||Welcome to Sudoku!!||\n=======================" << std::endl; //Note: this message will be deleted eventually by clearScreen, is just to introduce the user
    
    //ADDON: Switch-case to set up the removed pieces from the puzzle.
    Difficulty chosen_difficulty = ChooseDifficulty();
    
    switch (chosen_difficulty){
        case EASY:
        CreatePuzzle(35);
        break;
        
        case MEDIUM:
        CreatePuzzle(45);
        break;
        
        case HARD:
        CreatePuzzle(55);
        break;
    }
    
    MarkLockedCells();

    auto start_Time = std::chrono::steady_clock::now(); //ADDON: Add a timer to the game that will start right when the puzzle starts
    int total_Seconds = 0;
    int minutes = 0;
    int seconds = 0;

    std::string messages = " ";

    while ((!board_.IsFull()) && mistakes_ < 5){
        
        //5.1- Before everything, the function should erase previous boards
        ClearScreen();

        //ADDON: Calculates the time in game.
        auto current_Time = std::chrono::steady_clock::now();
        total_Seconds = std::chrono::duration_cast<std::chrono::seconds>(current_Time - start_Time).count();
        minutes = total_Seconds / 60;
        seconds = total_Seconds % 60;
        
        std::cout << "||Welcome to Sudoku!!||\n=======================" << std::endl;
        std::cout << "Complete the game by filling in the missing numbers.\n\n";
        
        //5.2- Display the board 
        board_.DisplayBoard();

        //ADDON: Display lives, available hints, score and time 
        std::cout << "|| Score: " << score_ << " ";
        std::cout << "|| Mistakes: " << mistakes_ << "/5 ||";
        std::cout << " Hints: " << hints_ << "/3 ||";
        std::cout << " Time: " << minutes <<"m " << seconds << "s ||" << std::endl;
        
        //Note: Since ClearScreen will update the screen each time, the messages are structured this way to print them after update
        if(messages != " "){
            std::cout << "\n" << messages << std::endl;
        }

        //5.3 Declare the variables the user will use for playing and call the helper function to valdiate user input
        int row = ValidateInput("\nEnter row from 1 to 9 (Press 0 for instant hint): ");
        if (row == 0){
            if (hints_ > 0){
                GiveHints();
                messages = "Hint used!! You have " + std::to_string(hints_) + " hints remaining.";
            } else {
                messages = "You have no hints remaining.";
            }
            continue;
        }

        int column = ValidateInput("Enter column from 1 to 9 (Press 0 for instant hint): ");
        if (column == 0){
           if (hints_ > 0){
                GiveHints();
                messages = "Hint used!! You have " + std::to_string(hints_) + " hints remaining.";
            } else {
                messages = "You have no hints remaining.";
            }
            continue;
        }

        int number = ValidateInput("Enter value to place from 1 to 9 in row " + std::to_string(row) + " and col " + std::to_string(column) + " (Press 0 for instant hint): ");
        if (number == 0){
            if (hints_ > 0){
                GiveHints();
                messages = "Hint used!! You have " + std::to_string(hints_) + " hints remaining.";
            } else {
                messages = "You have no hints remaining.";
            }
            continue;
        }
        

        //Note: Sudoku rows and columns go from 1 to 9, however, the program reads the index from 0 to 8. 
        //By substracting the value, we match the indexes.
        row --;
        column --;

        //5.4- Check player's move. If valid to both board's rule of valid board and the solved board positions, place it in a cell.
        if(locked_[row][column]){

            messages = "The cell in row " + std::to_string(row+1) + ", column " + std::to_string(column+1) + " already has a number. Try again.";

        }else if (board_.GetCell(row, column) != 0){
            messages = "The cell in row " + std::to_string(row+1) + ", column " + std::to_string(column+1) + " already has a number. Try again.";

        }else if ((board_.IsMoveValid(row, column, number)) && (number == solved_board_.GetCell(row, column))){
            board_.SetCell(row, column, number);

            messages = "Correct move!!\n+ 1000 POINTS!!";
            score_ += 1000;

        } else{
            mistakes_ ++;
            score_ -= 360;

            if (score_ < 0){
                score_ = 0;
            }

            messages = "Number entered in cell is incorrect. Try again.\n- 360 points...";
        }
    }

    //Note: We must call these functions again in case the user finishes the Sudoku and board_.IsFull() returns true
    ClearScreen();
    board_.DisplayBoard();

    //ADDON: Re-calculate the final time since the while loop will not mark it
    auto end_Time = std::chrono::steady_clock::now();
    total_Seconds = std::chrono::duration_cast<std::chrono::seconds>(end_Time - start_Time).count();
    minutes = total_Seconds / 60;
    seconds = total_Seconds % 60;

    //5.5- Let the user know if the game ended because they won or lost.
        if (board_.IsFull()){
            std::cout << "Congratulations!! You've completed a Sudoku!!" << std::endl;
            std::cout << "Mistakes: " << mistakes_ << "/5" << std::endl;
            std::cout << "Total Score: " << score_ << std::endl;
            std::cout << "Total Time: " << minutes << " minutes and " << seconds << " seconds." << std::endl;
        }
        if (mistakes_ == 5){
            std::cout << "GAME OVER!\nYou have made 5 mistakes and lost this game." << std::endl;
            std::cout << "Mistakes: " << mistakes_ << "/5" << std::endl;
            std::cout << "Total Score: " << score_ << std::endl;
            std::cout << "Total Time: " << minutes << " minutes and " << seconds << " seconds" << std::endl;

            std::cout << "The solution for this Sudoku puzzle was:\n" << std::endl;
            solved_board_.DisplayBoard();
        }
}

//6- Void Function that will erase the last Sudoku board message in terminal so that a new, updated one can be printed.
//This avoids having an annoying ration of repeated Sudoku board messages by just showing one that is constantly
//updating, like a real Sudoku game.
void SudokuGame::ClearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear"); //Note: This is for Linux/macOS 
    #endif
}