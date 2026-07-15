#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>

int main() {

    //1- Declare and initialize arrays and variables.
    std::string valid_grades[] = {"A+", "A", "A-", "B+", "B", "B-", "C+", "C", "D", "F", "WU", "FIN", "FAB"};
    double credit_points[] = {4.0, 4.0, 3.7, 3.3, 3.0, 2.7, 2.3, 2.0, 1.0, 0.0, 0.0, 0.0, 0.0};
    double total_credits = 0;
    double total_points = 0;
    double gpa = 0;
    int class_counter = 0;
    std::string answer;
    bool running = true;
    double user_course_credit = 0;
    std::string user_letter_grade;
    double grade_point = 0;
    bool valid_course = false;
    std::string ask_another_course = "yes";
    bool grade_found = false;

    //2- Greets the user and provides instructions.
    std::cout << "=========================================\n";
    std::cout << "              Welcome to\n";
    std::cout << "    Hunter College GPA Calculator\n";
    std::cout << "=========================================\n";
    std::cout << "This program calculates your semester GPA.\n\n";

    std::cout << "How to use:\n";
    std::cout << "1. Enter the number of credits followed by the letter grade.\n";
    std::cout << "2. You may enter the input with or without a space, such as 3A or 3 A.\n";
    std::cout << "3. Valid grades are: A+, A, A-, B+, B, B-, C+, C, D, F, WU, FIN, FAB.\n";
    std::cout << "4. Credit values must be greater than 0 and less than 10.\n\n";

    std::cout << "Examples:\n";
    std::cout << "3A = 3 credit course with an A grade\n";
    std::cout << "4b+ = 4 credit course with a B+ grade\n";
    std::cout << "2wu = 2 credit course with a WU grade\n\n";

    //3- Prompts the user to enter their course credit and their grades.
    //3.1- Program keeps running until user chooses to stop.
    while (running) {
        total_credits = 0;
        total_points= 0;
        gpa= 0;
        class_counter= 0;
        ask_another_course= "yes";
        //3.2- Second while-loop that accept courses until user declines to continue.
        while (ask_another_course == "yes") {
            user_course_credit = 0;
            user_letter_grade = "";
            grade_point = 0;
            valid_course = false;

            //3.3- Third while-loop to alert the user they have enter an invalid course
            while (!valid_course) {
                //NOTE: Validates letter grade, should be set back to false with each loop-attempt.
                grade_found = false;

                std::cout << "Enter credits and letter grade: ";

                //3.4- Handles non-numeric credit input and prevents infinite loops
                if (!(std::cin >> user_course_credit >> user_letter_grade)) {
                    std::cout << "Invalid input. Enter a number followed by a valid grade.\n";
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    continue;
                }

                //3.5- Converts letter grade to uppercase to make input case-insensitive
                for (int i = 0; i < user_letter_grade.length(); i++) {
                    user_letter_grade[i] = std::toupper(user_letter_grade[i]);
                }

                //3.6- Handles edge-case of user entering credit value out of range from 1 to 9.
                if (user_course_credit <= 0 || user_course_credit >= 10) {
                    std::cout << "Invalid credits. Credits must be greater than 0 and less than 10.\n";
                    continue;
                }

                //3.7- Compares the letter grade to a valid grade, matching GPA point value
                for (int j = 0; j < 13; j++) {
                    if (user_letter_grade == valid_grades[j]) {
                        grade_point = credit_points[j];
                        grade_found = true;
                        break;
                    }
                }

                if (!grade_found) {
                    std::cout << "Invalid grade. Valid grades are: A+, A, A-, B+, B, B-, C+, C, D, F, WU, FIN, FAB.\n";
                    continue;
                }

                valid_course = true;
            }

            //4- Add valid course to GPA calculation
            total_points += user_course_credit * grade_point;
            total_credits += user_course_credit;
            class_counter++;

            //5- Ask user if they want to enter another course for easy input track.
            do {
                std::cout << "Do you wish to enter another course? [yes/no or y/n]: ";
                std::cin >> ask_another_course;

                for (int i = 0; i < ask_another_course.length(); i++) {
                    ask_another_course[i] = std::tolower(ask_another_course[i]);
                }

                if (ask_another_course == "y") {
                    ask_another_course = "yes";
                } else if (ask_another_course == "n") {
                    ask_another_course = "no";
                }

                if (ask_another_course != "yes" && ask_another_course != "no") {
                    std::cout << "Please answer only yes, no, y, or n.\n";
                }

            } while (ask_another_course != "yes" && ask_another_course != "no");
        }
        
        //6- Final division for GPA to be stored and displayed.
        //NOTE: Over-protecting if-statement to avoid any possible case of 0 divisiion.
        if (total_credits > 0) {
            gpa = total_points / total_credits;

            std::cout << "\n=========================================\n";
            std::cout << "Classes taken: " << class_counter << std::endl;
            std::cout << "Cumulative GPA: " << std::fixed << std::setprecision(2) << gpa << std::endl;
            std::cout << "=========================================\n\n";
        } else {
            std::cout << "No valid classes were entered. GPA cannot be calculated.\n";
        }

        //7- Ask if user wants to run another GPA calculation
        //Note: Updated to allow yes/no and y/n answers alike!!
        do {
            std::cout << "Do you want to keep using the GPA Calculator? [yes/no or y/n]: ";
            std::cin >> answer;

            for (int i = 0; i < answer.length(); i++) {
                answer[i] = std::tolower(answer[i]);
            }

            if (answer == "y") {
                answer = "yes";
            } else if (answer == "n") {
                answer = "no";
            }

            if (answer != "yes" && answer != "no") {
                std::cout << "Please only respond with yes, no, y, or n.\n";
            }

        } while (answer != "yes" && answer != "no");

        if (answer == "no") {
            running = false;
        }
    }
    

    //8- Bid the user good-bye in their way out. Close program.
    std::cout << "Thank you for using the GPA Calculator. Goodbye!\n";

    return 0;
}
