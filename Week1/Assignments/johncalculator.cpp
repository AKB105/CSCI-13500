#include <iostream>
#include <string>

int main(){
    // using double for larger values and decimals.
    double Num1 = 0;
    double Num2 = 0;
    char choiceOP; // char to use characters as operators(+, -, x, *, /, %)

    std::cout << "Enter an expression to calculate (example: 3 x 3)" << std::endl;
    
    // Check the input order. user wont be able to type two nums and then the operator
    while(std::cin >> Num1 >> choiceOP >> Num2) {

    if (choiceOP != 'x' && choiceOP != '*' && choiceOP != '+' && choiceOP != '-' && choiceOP != '/' && choiceOP != '%') {
        std::cout << "Error, use a valid operator (+, -, x, *, /, %)" << std::endl;
        continue;
    }
    // User wont be able to divide by 0
    if ((choiceOP == '/' || choiceOP == '%') && Num2 == 0) {
        std::cout << "Cannot divide by zero (0)" << std::endl;
        continue;
    }
    //new double called result to be able to perform the operations
    double result = 0;
    // Using switch to perform the operation based on each operational symbol
    switch (choiceOP) {
        case '+':
        result = Num1 + Num2;
        break;
        
        case '-':
        result = Num1 - Num2;
        break;

        case 'x':
        case '*':
        case 'X':
        result = Num1 * Num2;
        break;

        case '/':
        result = Num1 / Num2;
        break;

        case '%':
        result = (int)Num1 % (int)Num2;
        break;
    }

    // print the result
    std::cout << "Your result is: " << Num1 << " " << choiceOP << " " << Num2 << " = " << result << std::endl;

}
    //Prints only if the user enters an invalid input such as letters or words, or other symbols.
    
    std:: cout << "Do not enter letters instead of numbers for the expression " << std::endl;

    return 0;
}