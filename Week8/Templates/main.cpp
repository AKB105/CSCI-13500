#include <iostream>

template <typename T, typename U, typename V>
T AddThreeNumbers(T a, T b, T c);

int main(){

    std::cout << AddThreeNumbers(6.32, 9.0, 7.0);

    return 0;
}

template <typename T, typename U, typename V>
T AddThreeNumbers(T a, U b, V c){
    return a + b + c;
}