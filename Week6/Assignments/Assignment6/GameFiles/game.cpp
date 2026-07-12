// This is the game loop. Your job is to implement the functions/methods
// it calls: RollDice() in Dice.cpp, and the Snake methods (functions) in Snake.cpp.
 
#include <iostream>
#include "Dice.h"
#include "Snake.h"
 
const int MAX_ROUNDS = 20;
 
int main() {
    std::cout << "=== KILL THE SNAKE ===\n\n";

    std::string difficulty = "";
    int starting_length = 10;
    int max_length = -1;
    bool regenerate_every_round = false; //ADDON: Change the snake's skill to regenerate so that it can do it every round instead of 2.

    //ADDON: Let's the user decide the difficulty of the game
    std::cout << "Choose your difficulty:\n";
    std::cout << "1. Easy:\nSnake's 5 segments long. It cannot grow bigger than 5. You can one-shot it, right? \n";
    std::cout << "2. Medium:\nSnake's 10 segments long. It's your average kill the snake game, go for it!!\n";
    std::cout << "3. Hard\nSnake's 20 segments long. It mihgt grow bigger than that tho. A challenge for those know their luck with dices!!\n";
    std::cout << "Enter difficulty: ";
    std::getline(std::cin, difficulty);

    //Note: Since now the user is able to interact with the game, some edge cases must be handled.
    while (difficulty != "1" && difficulty != "2" && difficulty != "3") {
        std::cout << "Please choose 1, 2, or 3: ";
        std::getline(std::cin, difficulty);
    }

    if (difficulty == "1") {
        starting_length = 5;
        max_length = 5;
    } else if (difficulty == "2") {
        starting_length = 10;
        max_length = -1;
    } else if (difficulty == "3") {
        starting_length = 20;
        max_length = -1;
        regenerate_every_round = true;
    } 
 
    Snake mySnake(starting_length, max_length);
    std::cout << "The snake has awaken...\n";
    mySnake.PrintSnake();
    std::cout << "\n";
 
    int round = 1;
    bool snake_is_dead = false;
 
    while (round <= MAX_ROUNDS) {
        std::cout << "--- Round " << round << " ---\n";
 
        int roll = RollDice();
        std::cout << "You rolled a " << roll << "!\n";
 
        int killedCount = mySnake.Kill(roll);
        std::cout << "You killed " << killedCount << " segment(s).\n";
        mySnake.PrintSnake();
 
        if (mySnake.GetLength() == 0) {
            snake_is_dead = true;
            break;
        }
 
        if (regenerate_every_round || round % 2 == 0) {
            int regenRoll = RollDice();
            int length_before_regen = mySnake.GetLength();
            mySnake.Regenerate(regenRoll);
            int regenerated_count = mySnake.GetLength() - length_before_regen;
            std::cout << "The snake regenerates " << regenerated_count
                      << " segment(s)!\n";
            mySnake.PrintSnake();
        }
 
        std::cout << "\n";
        round++;
    }
 
    std::cout << "\n=== GAME OVER ===\n";
    if (snake_is_dead) {
        std::cout << "You killed the snake in " << round << " round(s)! You win!\n";
    } else {
        std::cout << "The snake survived " << MAX_ROUNDS
                  << " rounds. It wins this time.\n";
    }
 
    return 0;
}
 
