/*
    Week 5 and Week 6 Review: Pointers and Dynamic Memory

    Good cheat-sheet ideas:
    - &variable gets an address.
    - pointer stores an address.
    - *pointer dereferences the address and accesses the real object.
    - nullptr means the pointer points to nothing.
    - Every successful new should have a matching delete unless ownership is transferred.
*/

#include <iostream>
#include <string>

struct Node {
    std::string name;
    Node* next;

    Node(const std::string& given_name) {
        name = given_name;
        next = nullptr;
    }
};

void DoubleIfPresent(int* evidence) {
    if (evidence != nullptr) {
        *evidence *= 2;
    }
}

void Append(Node*& head, const std::string& name) {
    Node* new_node = new Node(name);

    if (head == nullptr) {
        head = new_node;
        return;
    }

    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = new_node;
}

void PrintAndDelete(Node*& head) {
    while (head != nullptr) {
        std::cout << head->name << " -> ";

        Node* next_node = head->next;
        delete head;
        head = next_node;
    }

    std::cout << "nullptr\n";
}

int main() {
    int clue = 7;
    int* pointer = &clue;

    std::cout << "Value: " << clue << "\n";
    std::cout << "Address stored in pointer: " << pointer << "\n";
    std::cout << "Value through pointer: " << *pointer << "\n";

    DoubleIfPresent(&clue);
    DoubleIfPresent(nullptr);
    std::cout << "After pointer function: " << clue << "\n";

    Node* head = nullptr;
    Append(head, "start");
    Append(head, "middle");
    Append(head, "end");

    PrintAndDelete(head);
    std::cout << "Head after cleanup is nullptr: " << std::boolalpha
              << (head == nullptr) << "\n";

    return 0;
}
