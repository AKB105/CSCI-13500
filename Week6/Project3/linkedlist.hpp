#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP
#include <iostream>

//3.1: Create Node Struct
struct Node{
    int value;
    Node* next;

    Node(int passed_value);
};

//3.2: Create the LinkedList Class
class LinkedList{

    public:
        LinkedList();

        //3.3: InsertNode
        void InsertNode(const int value);

        //3.4: InsertNodeFront()
        void InsertNodeFront(const int value);

        //3.5: Contains()
        bool Contains(const int value) const;
        
        //3.6: Remove()
        bool Remove(const int position);
        
        //3.7: PrintValues() and Print Addresses()
        void PrintValues() const;

        void PrintAddresses() const;
        
        //3.8: GetValueAtPosition()
        int GetValueAtPosition(const int position) const;
        
        //3.9: ReverseList()
        LinkedList* ReverseList();
        
        //3.10: InsertNodeAt()
        void InsertNodeAt(const int value, const int position);        
        
        //3.11: GetSize()
        int GetSize() const;
        
        //3.12: MergeIntertwine
        LinkedList* MergeIntertwine(const LinkedList& second_list) const;
        
        //3.13: The destructor: ~ LinkedList()
        ~LinkedList();

    private:
        int size_;
        Node* head_;
};

#endif