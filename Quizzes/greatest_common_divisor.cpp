#include <iostream>

int main(); 

main(){
    int num1{}; 
    int num2{}; 
    int num3{}; 
    int gcd{}; 

    std::cout << "Enter the first number: "; 
    std::cin >> num1;
    std::cout << "Enter the second number: "; 
    std::cin >> num2;
    std::cout << "Enter the third number: "; 
    std::cin >> num3;

    int lowest{}; 

    if(num1 < num2 && num1 < num3){
        lowest = num1; 
    }

    else if(num2 < num3){
        lowest = num2; 
    }

    else{
        lowest = num3; 
    }

    while(true){
        if(num1%lowest == 0 && num2%lowest == 0 && num3%lowest == 0){
            gcd = lowest; 
            break; 
        }

        else{
            --lowest; 
        }
    }

    std::cout << "The GCD of the three numbers is " << gcd << "."; 

    return 0; 
}