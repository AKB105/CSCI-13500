#pragma once
#include "Node.h"

class Snake {
public:
    Snake(int starting_length, int max_length);                    // To build a snake with a starting number of segments
                                                                  // ADDON: For the purpose of the difficulty addon, the snake construct now needs parameter to customize its size.
    ~Snake();                   //Prevent memory leaks. deallocate the space

    // Kills up to `count` segments from the FRONT of the snake.
    // If the snake has fewer than `count` segments left, kill all of them
    // and stop (do not go out of bounds / do not crash).
    // Returns the number of segments ACTUALLY killed.
    int Kill(int count);

    // Adds `count` new body parts (nodes) to the BACK (tail) of the snake.
    void Regenerate(int count);

    // Prints the snake's segments from head to tail, e.g.:
    // Snake: [12] -> [13] -> [14] -> [15]
    // Must not modify the snake in any way.
    void PrintSnake() const;

    int GetLength() const;


private:
    Node* head_;
    Node* tail_;   // think about why keeping a tail pointer is useful here
    int length_;
    int id_;      // used to give each new node a unique, increasing id
    int max_length_; //ADDON: Sets the maximum length the snake can reach so that it doesn't surpass it on easy mode.

    //static const int STARTING_LENGTH = 10; Is no longer needed since the size will be set through difficulty, but I'll keep the line for clarification purposes.
    static const int NO_MAX_LENGTH = -1; //ADDON: If the user chooses the hard mode, the snake would grow without limits... Or until the rounds are over.
};
