#include <iostream>

int main(); 

main(){
    double mph{}; 

    std::cout << "Enter the speed in miles per hour: "; 
    std::cin >> mph; 
    std::cout << std::endl; 

    std::cout << "The speed is " << mph << " Miles per hour." << std::endl; 
    std::cout << "The speed is " << (mph * 5280)/3600 << " Feet per second." << std::endl; 
    std::cout << "The speed is " << ((mph * 5280)/3600)/3.28084 << " Meters per second." << std::endl; 
    std::cout << "The speed is " << ((mph * 5280)/3.28084)/1000 << " Kilometers per hour." << std::endl; 
    std::cout << "The speed is " << ((((mph * 5280))/3.28084)/201.168) * 336<< " Furlongs per fortnight." << std::endl; 

    return 0; 
}