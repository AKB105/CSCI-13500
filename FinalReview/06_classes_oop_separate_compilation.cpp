/*
    Week 7 Review: OOP and Separate Compilation

    In a real project, the class declaration lives in the .hpp file and the
    member function definitions live in the .cpp file.

    Compile this file by itself:
    g++ -std=c++17 -Wall 06_classes_oop_separate_compilation.cpp -o oop_demo.exe
*/

#include "06_classes_oop_separate_compilation.hpp"

#include <iostream>

Player::Player(const std::string& chosen_name, int starting_score)
    : name_(chosen_name), move_(ROCK), score_(starting_score) {
}

Player::~Player() {
}

std::string Player::GetName() const {
    return name_;
}

Move Player::GetMove() const {
    return move_;
}

int Player::GetScore() const {
    return score_;
}

void Player::SetMove(Move chosen_move) {
    move_ = chosen_move;
}

void Player::AddPoints(int points) {
    score_ += points;
}

bool Player::Beats(const Player& opponent) const {
    return (move_ == ROCK && opponent.move_ == SCISSORS) ||
           (move_ == PAPER && opponent.move_ == ROCK) ||
           (move_ == SCISSORS && opponent.move_ == PAPER);
}

Player& Player::operator+=(int points) {
    AddPoints(points);
    return *this;
}

int main() {
    Player human("Human");
    Player bot("Bot");

    human.SetMove(PAPER);
    bot.SetMove(ROCK);

    if (human.Beats(bot)) {
        human += 1;
    }

    std::cout << human.GetName() << " score: " << human.GetScore() << "\n";
    std::cout << bot.GetName() << " score: " << bot.GetScore() << "\n";

    return 0;
}
