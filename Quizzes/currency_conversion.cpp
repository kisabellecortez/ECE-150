#include <iostream>

int main(); 

main(){
    double cad{}; 

    std::cout << "Enter the currency in CAD: "; 
    std::cin >> cad; 
    std::cout << std::endl;  

    std::cout << "There are " << cad/1.30 << " USD." << std::endl; 
    std::cout << "There are " << (cad/1.30)/0.86 << " Pound sterling." << std::endl;
    std::cout << "There are " << ((cad/1.30)/0.86) * 0.87 << " Euro." << std::endl;
    std::cout << "There are " << (cad/1.30) * 100 << " US penny." << std::endl;

    return 0; 

}