#include <iostream>
#include <random>

int main(){

    //start game (declare variable)
    int player_score = 0;
    int bot_score = 0;
    int bot_move = 0;
    std::string bot_pick = "";
    std::string player_move = "";
    std::string winner = "";

    //game loop
    for (int rounds = 0; rounds < 3; rounds++){
        //check for early winner
        if(player_score >= 2){
            winner = "Player";
            break;
        } else if (bot_score >= 2) {
            winner = "Bot";

        }
    }

        
        //ask for user input
        std::cout << "Choose rock, paper or scissor: ";
        std::cin >> player_move;

        //generate bot input
        bot_move = rand() % 3;

        if(bot_move == 0){
            bot_pick = "Rock";
        } else if (bot_move = 1){
            bot_pick = "Paper";
        } else{
            bot_pick = "Scissors";
        }

        // figure out the score
        if(player_move == bot_pick){
            player_score += 0;
            bot_score += 0;
        } else if(player_move == "rock" && bot_pick == "scissors"){
            player_score++;
        } else if(player_move=="paper" && bot_pick == "rock"){
            player_score++
        }

    //declare a winner or a tie
}