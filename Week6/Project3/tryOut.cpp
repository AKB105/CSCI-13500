//This file is created to try out each function created within the custom data type.
#include "linkedlist.hpp"
#include <iostream>

int main(){
    LinkedList myList;

    myList.InsertNode(20);
    myList.InsertNodeFront(10);
    myList.InsertNode(30);


    myList.PrintValues();

    myList.Remove(2);
    myList.GetValueAtPosition(1);
    myList.InsertNodeFront(40);

    myList.PrintValues();
    myList.PrintAddresses();

    myList.MergeIntertwine()

    return 0;
}