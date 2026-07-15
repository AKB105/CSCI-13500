#include "linkedlist.hpp"
#include <iostream>
#include <stdexcept> //Note: library for the throw cases. Some compilers might work without it, but some may not. I'm not taking the risk.

//Define constructor for Node struct.
Node::Node(int passed_value){
    value = passed_value;
    next = nullptr;
}

//Defube constructor for LinkedList class.
LinkedList::LinkedList(){
    size_ = 0;
    //Note: An empty list starts with no first node, so head_ must point to nullptr until a node is inserted.
    head_ = nullptr;
}

//3.3: InsertNode
//Insert the provided value as a new node at the end of the list.
//Ensure that the list's tracking variables are updated accordingly.
void LinkedList::InsertNode(const int value){
    Node* new_node = new Node(value);

    //Note: Special case handler, as inserting into an empty list means there is no last node to attach to yet.
    if(head_ == nullptr){
        head_ = new_node;
    } else{
        Node* current = head_;

        //Note: Walk until the final node, then attach the new node to the end of the chain.
        while (current->next != nullptr){
            current = current->next;
        }
        current->next = new_node;
    }
    size_++;
}

//3.4: InsertNodeFront()
//Insert the provided value as a new node at the BEGINNING of the list.
//Ensure thatt the list's tracking variables are updated accordingly.
void LinkedList::InsertNodeFront(const int value){
    Node* new_node = new Node(value);
    new_node->next = head_; // The new node points to the current first node before head_ is moved, preserving the rest of the list.
    head_ = new_node;

    size_++;
}

//3.5: Contains()
// Return true if the target value exists within any node in the list.
// Otherwise, return false.
bool LinkedList::Contains(const int value) const {
    Node* current = head_;

    while(current != nullptr){
        if (current->value == value){
            return true;
        }

        current = current->next;
    }

    return false;
}

//3.6: Remove()
//Validate the position. If valid, remove the node at that 1-based position,
//carefully bypassing it in the chain. Prevent memory leaks by freeing
//the removed node, update the list's size, and return true.
bool LinkedList::Remove(const int position) {
    if (position < 1 || position > size_){
        return false;
    }

    //Note: Removing the first node is handled separately because head_ must move to the next node.
    if (position == 1){
        Node* node_to_delete = head_;
        head_ = head_->next;
        delete node_to_delete;
        size_--;

        return true;
    }

    Node* previous = head_;
    
    //Note: Stop at the node before the target so its next pointer can bypass the removed node.
    for(int i = 1; i < position - 1; i++){
        previous = previous->next;
    }

    Node* node_to_delete = previous->next;
    //Notes: Reconnect the list before deleting the node so no remaining nodes are lost.
    previous->next = node_to_delete->next;

    delete node_to_delete;
    size_--;

    return true;

}

//3.7: PrintValues() and Print Addresses()
// Print all values sequentially, separated by "-> ",
// and terminate the output with "nullptr" and a newline.
void LinkedList::PrintValues() const {
    Node* current = head_;

    while(current != nullptr){
        std::cout << current->value << " -> ";
        current = current->next;
    }
    
    std::cout << "nullptr\n";
}

// Print the 1-based position, a space, and the node's memory address
// for every node in the list.
void LinkedList::PrintAddresses() const {
    Node* current = head_;
    int position = 1;

    while (current != nullptr) {
        std::cout << position << " " << current << "\n";
        current = current->next;
        position++;
    }
}

//3.8: GetValueAtPosition()
// Validate the position, throwing an exception if it is out of bounds.
// Otherwise, navigate to the correct node and return its value.
int LinkedList::GetValueAtPosition(const int position) const {
    if (position < 1 || position > size_){
        throw std::out_of_range("Position is outside the list.");
    }

    Node* current = head_;
    //Note: Positions are 1-based, so the loop advances position - 1 times from the head.
    for(int i = 1; i < position; i++){
        current = current->next;
    }
    return current->value;
}

//3.9: ReverseList()
// Reverse the nodes of the current list.
// Allocate a new LinkedList dynamically, give it ownership of the reversed nodes,
// and reset the current (original) list to an empty state.
// Return the pointer to the newly created list.
LinkedList* LinkedList::ReverseList() {
    LinkedList* reversed_list = new LinkedList();

    //Note: Three pointers are needed so each link can be reversed without losing access to the rest of the original list.
    Node* current = head_;
    Node* previous = nullptr;
    Node* next_node = nullptr;

    while (current != nullptr) {
        // Save the next node before changing current->next, otherwise the unreversed portion would be lost.
        next_node = current->next;
        current->next = previous;
        previous = current;
        current = next_node;
    }

    reversed_list->head_ = previous;
    reversed_list->size_ = size_;
    // Ownership of the nodes has moved to reversed_list, so the original list must be reset to empty.
    head_ = nullptr;
    size_ = 0;

    return reversed_list;
}

//3.10: InsertNodeAt()
// Check if the position is valid (allowing insertions at the very end).
// If invalid, throw std::out_of_range.
// Otherwise, insert the new node at the correct spot and update list properties.
void LinkedList::InsertNodeAt(const int value, const int position) {
    if (position < 1 || position > size_ + 1) {
        throw std::out_of_range("Position is outside the list.");
    }

    //Note: Reuse the front insertion function for position 1 to avoid duplicating pointer logic.
    if (position == 1) {
        InsertNodeFront(value);
        return;
    }

    //Note: Position size_ + 1 means inserting after the current last node, so this is the same as appending.
    if (position == size_ + 1) {
        InsertNode(value);
        return;
    }

    Node* new_node = new Node(value);
    Node* previous = head_;

    for (int i = 1; i < position - 1; i++) {
        previous = previous->next;
    }

    //Note: Link the new node to the following node first, then connect the previous node to the new node.
    new_node->next = previous->next;
    previous->next = new_node;

    size_++;
}

//3.11: GetSize()
// Return the appropriate member variable.
int LinkedList::GetSize() const {
    return size_;
}

//3.12: MergeIntertwine
// Create a new LinkedList on the heap.
// Populate it by alternating nodes from THIS list and the second_list.
// If one list is longer, append the remaining nodes from the longer list.
// Do not alter the original lists. Return the new merged list.
LinkedList* LinkedList::MergeIntertwine(const LinkedList& second_list) const {
    LinkedList* merged_list = new LinkedList();

    Node* current_first = head_;
    Node* current_second = second_list.head_;

    //Note: Continue until both lists are exhausted so extra nodes from the longer list are still copied.
    while ((current_first != nullptr) || (current_second != nullptr)) {
        if (current_first != nullptr) {
            merged_list->InsertNode(current_first->value); // Copy values into a new list instead of reusing nodes so the original lists remain unchanged.
            current_first = current_first->next;
        }

        if (current_second != nullptr) {
            merged_list->InsertNode(current_second->value);
            current_second = current_second->next;
        }
    }

    return merged_list;
}

//3.13: The destructor: ~ LinkedList()
// Free all dynamically allocated memory used by the list's nodes.
// Ensure no orphaned memory is left behind upon object destruction.
LinkedList::~LinkedList() {

    //Note: Delete nodes one at a time from the front so every dynamically allocated node is freed safely
    while(head_ != nullptr){
        Node* node_to_delete = head_;
        //Note: Move head_ forward before deleting the old node, since deleted memory can no longer be accessed.
        head_ = head_->next;
        delete node_to_delete;
    }

    size_ = 0;
}