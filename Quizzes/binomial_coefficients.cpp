#include <iostream>
#include <limits>

int main(); 
int factorial(int n); 

main(){
    int n{}; 
    int k{}; 
    int nCk{}; 

    std::cout << "Binomial Coefficients Calculator"; 

    std::cout << "Enter the value for n: "; 
    std::cin >> n;
    std::cout << "Enter the value for k: "; 
    std::cin >> k;

    if(n >= k && k >= 0){
        nCk = factorial(n)/factorial(k)/factorial(n-k);
        std::cout << "The value of nCk is " << nCk << "."; 

    }

    else{
        std::cout << "Cannot calculate nCk because condition n >= k >= 0 was not met.";
    }

    return 0; 
}

int factorial(int n){
    int result{1}; 

    if(n < 0){
        return 0; 
    }

    else{
        for(int i = n; i >= 2; --i){
            result *= i; 
        }

        return result; 
    
    }

}


