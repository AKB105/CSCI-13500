//Objective: Given an array of students grades, determine how many students passed on how many failed

#include <iostream>

int main(){
//variables for the array, students that passed and failed and variable for the passing grade minimum.
    int passing_grade = 70;
    int student_passed = 0;
    int student_failed = 0;
    int grades[5] = {95, 72, 68, 88, 100};

//For-loop to pass through the array.
    for (int i =0; i < 5; i++){
        if (grades[i] >= 70){
            student_passed++ ;
        } else {
            student_failed++ ;
        }
    }

//Final output stating how many failed and how many passed.
    std:: cout << "Student passed: " << student_passed << '\n' << "Student failed: " << student_failed << std::endl;

    return 0;
}
//#CoolioFORLIFE