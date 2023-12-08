#include <iostream>

int main(); 

main(){
    double joules{}; 

    std::cout << "Enter the energy in Joules: "; 
    std::cin >> joules; 
    std::cout << std::endl; 

    std::cout << "There are " << joules << " Joules of energy." << std::endl; 
    std::cout << "There are " << ((joules/1055)/3.966)/ 860.4 << " kWh of energy." << std::endl; 
    std::cout << "There are " << (joules/1055)/3.966<< " kcal of energy." << std::endl; 
    std::cout << "There are " << joules/1055 << " BTU of energy." << std::endl; 
    std::cout << "There are " << (((joules/1055)/3.966)/ 860.4)/1.162 << " kg-TNT of energy." << std::endl; 

    return 0; 
}