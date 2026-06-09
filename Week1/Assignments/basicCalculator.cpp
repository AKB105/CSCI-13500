//Libraries
#include <iostream>
#include <string>
#include <cmath>

int main(){
    //1- User inputs the numbers and the operation they wanna do with them.
    double num1 = 0;
    char operation = ' ';
    double num2 = 0;
    //1.1- Extra variable for diverse purposes
    //1.2- Double result displays the total of the calulation, bool running deetermines if the program is on or off.
    //1.3- Finally, answer holds the respond of the user to whether they wanna turn on or off the calculator.
    double result = 0;
    bool running = true;
    std::string answer = "";

    while (running){
        bool validResult = true;

        std::cout << "Enter a number: ";
        while(!(std::cin>> num1)){
            std::cout << "Letters and/or symbols are not recognized as numbers. Please, try again.\nEnter a number: ";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }

        do{
            std::cout << "Enter intended operation (ONLY [+] [-] [x] [*] [/] [%]): ";
            std::cin >> operation;
            std::cin.ignore(1000, '\n');
        }while(operation != '+' && 
                operation != '-' && 
                operation != '*' && 
                operation != 'x' && 
                operation != 'X' && 
                operation != '/' && 
                operation != '%');

        std::cout << "Enter another number: ";
        while(!(std::cin>> num2)){
            std::cout << "Letters and/or symbols are not recognized as numbers. Please try again.\nEnter another number: ";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }

        //2- The program reads user inputs and do the intended operation.
        //Note: "case 'X':" covers for the scneario of user inputing capitalized x
            switch (operation){
                case '+':
                    result = num1 + num2;
                    break;
                case '-':
                    result = num1 - num2;
                    break;
                case 'x':
                case '*':
                case 'X':
                    result = num1 * num2;
                    break;
                case '/':
                //2.1- BONUS: The if-statement handles division by zero, telling the user that is undefined and 
                //skipping the line intended to show the result, since there is no result to display.
                    if (num2 == 0){
                        std::cout << "Sorry, division by 0 is undefined.\n";
                        validResult = false;
                        break;
                    }
                    result = num1 / num2;
                    break;
                case '%':
                //2.2- Since the modulo operator does not work with doubles, we use the fmod function from the cmath library.
                    result = std::fmod(num1, num2);
                    break;
                default:
                    std::cout << "Invalid operation. Only use real numbers and the valid operators ([+] [-] [x] [*] [/] [%]).\n";
                    validResult = false;
                    break;
            }

        //3- The program outputs the final result and ask the user if they wanna do another operation or close the program.
        if (validResult){
            std::cout << "The operation result is: " << result << std::endl;
        }

        //3.1- The do-while runs once with what is stored in answer. If it not the expected response, it will ask the user to only respond with Y or N endlessly.
        do{    
            std::cout << "Please only respond with Y or N. Would you like to do another operation? [Y / N]: " << std::endl;
            std::cin >> answer;
            std::cin.ignore(1000, '\n');
        }  while ((answer != "Y") && (answer != "y") && (answer != "N") && (answer != "n"));
        
        //3.2- The OR condition handles the scenario where the user may input a lower-case or capitalized Y or N.  
        if ((answer == "N") || (answer == "n")){
            running = false;
            } else if ((answer == "Y") || (answer == "y")){
                running = true;
                }
    }
}