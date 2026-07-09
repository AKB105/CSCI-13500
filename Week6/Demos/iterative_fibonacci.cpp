#include <iostream> 

int main(){

    int num = 0;
    int first_fibo = 0;
    int second_fibo = 1;
    int result = 0;
    std::cout << "Enter a number:";
    std::cin >> num;

    for (int i = 0; i < num; i++){
        if (num <= 1){
            std::cout << num;
        }

        //fibonacci = F(num - 1) + F(num -2)
        result = first_fibo + second_fibo; 
        first_fibo = second_fibo;
        second_fibo = result;

        std::cout << i+1 << "-) " << result << ", ";
    }

    return 0;
}
