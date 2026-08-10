#ifndef FINAL_REVIEW_PLAYER_HPP
#define FINAL_REVIEW_PLAYER_HPP

#include <string>

enum Move {
    ROCK = 1,
    PAPER = 2,
    SCISSORS = 3
};

class Player {
public:
    Player(const std::string& chosen_name = "John Player", int starting_score = 0);
    ~Player();

    std::string GetName() const;
    Move GetMove() const;
    int GetScore() const;

    void SetMove(Move chosen_move);
    void AddPoints(int points);

    bool Beats(const Player& opponent) const;

    Player& operator+=(int points);

private:
    std::string name_;
    Move move_;
    int score_;
};

#endif
