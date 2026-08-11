#include <iostream>
#include <string>

int main(){
    //Create storage for the name and age.    
    std::string name = "";
    int age = 0;

    //Ask user for their name and age.
    std::cout << "Please write down your name:";
    std::cin >> name;
    std::cout << "Please write down your age:";
    std::cin >> age;

    //Print out user info: theri name and age.

    std::cout << "The user name is " << name << " and their age is " << age;

    return 0;

}
