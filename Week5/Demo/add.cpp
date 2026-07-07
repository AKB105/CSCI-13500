#include <iostream>

int SumTwoNumbers(int first_num, int second_num){
    first_num = 4;
    return first_num + second_num;
}

int main(){

    int first_num = 3;
    int second_num = 4;

    std::cout << first_num << std::end;

    int result = SumTwoNumbers(first_num, second_num);

    std::cout << result << std::endl;

}

