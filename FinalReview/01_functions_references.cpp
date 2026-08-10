/*
    Week 5 Review: Functions, Parameters, References, const

    Good cheat-sheet ideas:
    - Pass by copy protects the original variable.
    - Pass by reference lets the function modify the original variable.
    - const reference avoids a copy but prevents modification.
    - Arrays passed to functions decay into pointers, so the size must be passed separately.
*/

#include <cctype>
#include <iostream>
#include <string>

std::string ToLowercase(std::string text) {
    for (int i = 0; i < static_cast<int>(text.length()); i++) {
        text[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(text[i])));
    }
    return text;
}

// Pass by copy: original is not modified.
int AddFiveCopy(int number) {
    number += 5;
    return number;
}

// Pass by reference: original is modified.
void AddBonusReference(int& score, const int& bonus) {
    score += bonus;
    // bonus += 1; // compile error: bonus is const
}

// Array parameter: moves[] is really a pointer to the first string.
bool IsValidMove(const std::string moves[], int move_count, const std::string& user_move) {
    for (int i = 0; i < move_count; i++) {
        if (user_move == moves[i]) {
            return true;
        }
    }
    return false;
}

void UpdateScore(const std::string& player_name,
                 const std::string& bot_name,
                 const std::string& player_move,
                 const std::string& bot_move,
                 int& player_score,
                 int& bot_score) {
    if (player_move == bot_move) {
        return;
    }

    const bool player_wins =
        (player_move == "rock" && bot_move == "scissors") ||
        (player_move == "paper" && bot_move == "rock") ||
        (player_move == "scissors" && bot_move == "paper");

    if (player_wins) {
        std::cout << "+1 for " << player_name << "\n";
        player_score++;
    } else {
        std::cout << "+1 for " << bot_name << "\n";
        bot_score++;
    }
}

int main() {
    int value = 10;
    int changed_copy = AddFiveCopy(value);

    std::cout << "Original value: " << value << "\n";
    std::cout << "Returned copy: " << changed_copy << "\n";

    int score = 10;
    const int bonus = 5;
    AddBonusReference(score, bonus);
    std::cout << "Score after reference function: " << score << "\n";

    const std::string moves[3] = {"rock", "paper", "scissors"};
    std::string input = "Scissors";
    input = ToLowercase(input);

    std::cout << "Move is valid: " << std::boolalpha
              << IsValidMove(moves, 3, input) << "\n";

    int player_score = 0;
    int bot_score = 0;
    UpdateScore("Human", "Bot", "paper", "rock", player_score, bot_score);

    std::cout << "Human: " << player_score << ", Bot: " << bot_score << "\n";
    return 0;
}
