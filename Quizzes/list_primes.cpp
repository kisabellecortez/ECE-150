#include <iostream>

int main(); 

main(){
    int num1{}; 
    int num2{}; 

    std::cout << "Enter first number: "; 
    std::cin >> num1; 
    std::cout << "Enter second number: "; 
    std::cin >> num2; 

    bool has_prime{false}; 

    for(int i = num1; i <= num2; i++){ 
        bool is_prime{true}; 

        for(int j = 2; j < i; j++){
            if(i%j == 0){
                is_prime = false; 
            }

        }

        if(is_prime){

            if(!has_prime){
                std::cout << "Primes in range: " << i << " "; 
                has_prime = true; 
            }

            else{
                std::cout << i << " "; 
            }

        }
        
    }

    if(!has_prime){
        std::cout << "No primes in range."; 
    }

    return 0; 
}