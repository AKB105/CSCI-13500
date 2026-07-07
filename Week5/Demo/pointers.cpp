#include <iostream>
using namespace std;

int main(){

    int number = 42;

    int* pointer = &number;

    cout << "Value of number: " << number << endl;
    cout << "Address of number: " << pointer << endl;
    cout << "value through pointer: " << *pointer << endl;

    return 0;

}