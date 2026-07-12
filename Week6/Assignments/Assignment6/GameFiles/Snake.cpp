#include "Snake.h"
#include <iostream>
// TODO: Constructor
// - Build a snake with STARTING_LENGTH segments using `new`.
// - head should point to segment id 0 (or 1, your choice - just be consistent),
//   tail should point to the last segment created.
// - Set length and nextId appropriately.
Snake::Snake(int starting_length, int max_length) {
    head_ = nullptr;
    tail_ = nullptr;
    length_ = 0;
    id_ = 0;
    max_length_ = max_length;
    // TODO: allocate STARTING_LENGTH nodes and link them together
    Regenerate(starting_length);
}
// TODO: Destructor
// - Walk the list and delete every remaining node.
// - If you don't do this, running under valgrind/ASan will report a leak.
Snake::~Snake() {
    // TODO
    while (head_ != nullptr){
        Node* old_head = head_;
        head_ = head_ -> next_;
        delete old_head;
    }

    tail_ = nullptr;
    length_ = 0;
}
// TODO: kill()
// - Remove up to `count` nodes from the FRONT of the list, deleting each one.
// - Handle the edge case where the snake has fewer than `count` nodes left:
//   kill all remaining nodes and stop. Do not crash.
// - Update `length` (and `tail`/`head` if the snake becomes empty!).
// - Return the number of segments ACTUALLY killed.
int Snake::Kill(int count) {
    // TODO
    int killed = 0;

    while (killed < count && head_ != nullptr){
        Node* old_head = head_;
        head_ = head_ -> next_;
        delete old_head;

        length_--;
        killed++;
    }

    if (head_ == nullptr){
        tail_ = nullptr;
    }

    return killed;
}

// TODO: regenerate()
// - Append `count` new nodes to the BACK of the list using `new`.
// - Use `nextId` to assign each new node a unique, increasing id, and
//   increment `nextId` each time.
// - Update `tail` (and `head` if the snake was empty!) and `length`.
void Snake::Regenerate(int count) {
    // TODO
    for (int i = 0; i < count; i++){
        if (max_length_ != NO_MAX_LENGTH && length_ >= max_length_) {
            return;
        }

        Node* new_node = new Node;
        new_node -> body_part_ = id_;
        new_node -> next_ = nullptr;
        id_++;

        if(head_ == nullptr){
            head_ = new_node;
            tail_ = new_node;
        } else {
            tail_ ->next_ = new_node;
            tail_ = new_node;
        }
        length_++;
    }
}

// TODO: print()
// - Walk the list from head to tail and print in the format:
//   Snake: [12] -> [13] -> [14] -> [15]
// - If the snake is empty, print something sensible like "Snake: (dead)".
// - This function must not modify the snake - use a `const Node*` to walk it.
void Snake::PrintSnake() const {
    // TODO
    if (head_ == nullptr) {
        std::cout << "The Snake has died!!\n";
        return;
    }

    const Node* current = head_;

    std::cout << "Behold!! The Snake: ";

    while (current != nullptr){
        std::cout << "[" << current -> body_part_ << "]";
        
        if (current -> next_ != nullptr){
            std::cout << " -> ";
        }

        current = current -> next_;
    }

    std::cout << "\n";
}

int Snake::GetLength() const {
    // TODO
    //Note: Length is already updated by Regenerate() and Kill(), so the function doesn't need to count manually.
    return length_;
}
