/*
    Week 6 Review: Linked Lists and OOP

    This file blends the Snake assignment and Project3 linked-list project:
    - struct Node
    - class LinkedList
    - constructor and destructor
    - private data members
    - const member functions
    - dynamic memory allocation
    - returning a heap-allocated object
    - exception throwing
*/

#include <iostream>
#include <stdexcept>

struct Node {
    int value;
    Node* next;

    Node(int given_value) {
        value = given_value;
        next = nullptr;
    }
};

class LinkedList {
public:
    LinkedList() {
        head_ = nullptr;
        size_ = 0;
    }

    ~LinkedList() {
        while (head_ != nullptr) {
            Node* node_to_delete = head_;
            head_ = head_->next;
            delete node_to_delete;
        }
        size_ = 0;
    }

    void InsertBack(const int value) {
        Node* new_node = new Node(value);

        if (head_ == nullptr) {
            head_ = new_node;
        } else {
            Node* current = head_;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new_node;
        }

        size_++;
    }

    void InsertFront(const int value) {
        Node* new_node = new Node(value);
        new_node->next = head_;
        head_ = new_node;
        size_++;
    }

    bool Contains(const int value) const {
        const Node* current = head_;
        while (current != nullptr) {
            if (current->value == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    int GetValueAtPosition(const int position) const {
        if (position < 1 || position > size_) {
            throw std::out_of_range("Position is outside the list.");
        }

        const Node* current = head_;
        for (int i = 1; i < position; i++) {
            current = current->next;
        }
        return current->value;
    }

    bool Remove(const int position) {
        if (position < 1 || position > size_) {
            return false;
        }

        if (position == 1) {
            Node* old_head = head_;
            head_ = head_->next;
            delete old_head;
            size_--;
            return true;
        }

        Node* previous = head_;
        for (int i = 1; i < position - 1; i++) {
            previous = previous->next;
        }

        Node* node_to_delete = previous->next;
        previous->next = node_to_delete->next;
        delete node_to_delete;
        size_--;

        return true;
    }

    LinkedList* ReverseIntoNewList() {
        LinkedList* reversed = new LinkedList();

        Node* current = head_;
        Node* previous = nullptr;
        Node* next_node = nullptr;

        while (current != nullptr) {
            next_node = current->next;
            current->next = previous;
            previous = current;
            current = next_node;
        }

        reversed->head_ = previous;
        reversed->size_ = size_;

        head_ = nullptr;
        size_ = 0;

        return reversed;
    }

    void PrintValues() const {
        const Node* current = head_;
        while (current != nullptr) {
            std::cout << current->value << " -> ";
            current = current->next;
        }
        std::cout << "nullptr\n";
    }

    int GetSize() const {
        return size_;
    }

private:
    Node* head_;
    int size_;
};

int main() {
    LinkedList list;
    list.InsertBack(20);
    list.InsertFront(10);
    list.InsertBack(30);

    list.PrintValues();
    std::cout << "Contains 20: " << std::boolalpha << list.Contains(20) << "\n";
    std::cout << "Value at position 2: " << list.GetValueAtPosition(2) << "\n";

    list.Remove(2);
    list.PrintValues();

    LinkedList* reversed = list.ReverseIntoNewList();
    reversed->PrintValues();

    delete reversed;
    reversed = nullptr;

    return 0;
}
