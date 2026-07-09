#include <iostream>
using namespace std;

int Fibonacci(int n){

    if (n <= 1){
        return n;
    }
    /*Returns the simpler version of the function. If n = 4, then it goes like this:
    fibo(4-1) + fibo(4-2) = fibo(3) + fibo(2). 
    Neither of those is equal to 1, so it keeps going:
    (fibo (3-1) + fibo (3-2)) + (fibo(2-1) + fibo(2-2)) = (fibo(2) + fibo(1) + fibo(1) + fibo(0))
    Now:
    fibo(2) = fibo(2-1) + fibo(2-2) = fibo(1) + fibo(0);
    Whole thing becomes: 

    */
    return Fibonacci(n - 1) + Fibonacci(n - 2);
}

int main(){
    int num;
    cout << "Enter a number: ";
    cin >> num;
    
    for (int i = 0; i < num; i++){
        cout << i+1 << "-) " << Fibonacci(i) << ", ";
    }

    return 0;
}

/*#include <iostream>
using namespace std;

int fibo(int n){

    if (n <= 1){
        return n;
    }
    return (n - 1) + (n - 2);
}

int main(){
    int num;
    cout << "Enter a number: ";
    cin >> num;
    
    for (int i = 0; i < num; i++){
        cout << fibo(i) << " ";
    }

    return 0;
}*/
