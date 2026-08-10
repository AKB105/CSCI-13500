/*
    Operator Overloading Review

    Operator overloading lets a class define what built-in operators mean
    when they are used with objects of that class.

    Common examples:
    - operator+= modifies the current object.
    - operator+ returns a new combined object.
    - operator<< lets cout print the object nicely.
*/

#include <iostream>
#include <string>

class Score {
public:
    Score(const std::string& name, int points) {
        name_ = name;
        points_ = points;
    }

    Score& operator+=(int extra_points) {
        points_ += extra_points;
        return *this;
    }

    Score operator+(const Score& other) const {
        return Score(name_ + " + " + other.name_, points_ + other.points_);
    }

    friend std::ostream& operator<<(std::ostream& output, const Score& score);

private:
    std::string name_;
    int points_;
};

std::ostream& operator<<(std::ostream& output, const Score& score) {
    output << score.name_ << ": " << score.points_;
    return output;
}

int main() {
    Score player("Player", 10);
    Score bonus("Bonus", 5);

    player += 3;

    Score total = player + bonus;

    std::cout << player << "\n";
    std::cout << total << "\n";

    return 0;
}
