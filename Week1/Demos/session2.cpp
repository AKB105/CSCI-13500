#include <iostream>

int main(){

    // enter age
    int age = 0;
    std::cout << "Enter age: ";
    // validate input 

    while(std::cin >> age){
        if (std::cin.fail()){
            std::cout << "Invalid input!" << std::endl;
            break;
        }

        if (age < 0){
            std::cout << "Cannot input negative numbers!" << std::endl;
        }

        // print out what they are legally allowed to do at that age
        if (age >= 18){
            std::cout << "You can vote!" << std::endl;
        }

        if ( age >= 21){
            std::cout << "You can drink!" << std::endl;
        }

        if (age < 18 && age >= 0){
            std::cout << "You are a minor!" << std::endl;
        }
    }


}

