//Here's where the Sudoku will be played
#include "SudokuGame.hpp"
#include <iostream>
#include <string>
#include <cctype>

int main(){
    bool running = true;
    std::string play_Again = " ";
    
    //ADDON: Allow the user to start a new game after winning or losing
    while(running){

        SudokuGame game;
        game.PlayGame();

        do {
            std::cout << "\nDo you want to play again? [yes/no or y/n]: ";
            std::getline(std::cin, play_Again);

            for (int i = 0; i < play_Again.length(); i++) {
                play_Again[i] = std::tolower(play_Again[i]);
            }

            if (play_Again == "y") {
                play_Again = "yes";
            } else if (play_Again == "n") {
                play_Again = "no";
            }

            if (play_Again != "yes" && play_Again != "no") {
                std::cout << "Please only respond with [yes or no], [y or n].\n";
            }

        } while (play_Again != "yes" && play_Again != "no");

        if (play_Again == "no") {
            running = false;
        }
    }
    
    std::cout << "Thank you for playing Sudoku with us, bye!! :D" << std::endl;

    return 0;
}