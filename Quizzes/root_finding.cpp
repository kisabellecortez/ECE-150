#include <iostream>

int main(); 
double function_value(double a, double b, double c, double d); 
double root(double a, double b, double c, double d, double low, double high);
double abs(double x); 


main(){

    while(true){

        double a{}; 
        double b{};
        double c{};
        double d{};
        double low{}; 
        double high{}; 
        char answer{}; 

        std::cout << "Enter the coefficients (a, b, c, d): ";
        std::cin >> a;
        std::cin >> b;
        std::cin >> c;
        std::cin >> d; 
        std::cout << "Enter the lower and upper bound of the search interval: "; 
        std::cin >> low;
        std::cin >> high; 

        std::cout << std::endl << "The root found was x = " << root(a, b, c, d, low, high);
        std::cout << std::endl; 

        std::cout << "Would you like to find another root (Y/N): "; 
        std::cin >> answer; 

        if(answer == 'n' || answer == 'N'){
            std::cout << "Program terminated."; 
            break;  
        }

    }

    return 0; 
}

double function_value(double a, double b, double c, double d, double x){
        return (a * (x * x * x)) + (b * (x * x)) + (c * x) + d; 
}

double root(double a, double b, double c, double d, double low, double high){
    double closest_zero{function_value(a, b, c, d, high)}; 
    double check_root{}; 
    double increment{(high - low)/1000000};

    if(increment > 0.0001){
        increment = 0.0001; 
    }

    for(double i = high; i >= low; i -= increment){
        check_root = function_value(a, b, c, d, i);

        if(abs(closest_zero) > abs(check_root)){
            closest_zero = check_root; 
        }
    }

    return closest_zero; 

}

double abs(double x){
    if(x >= 0){
        return x; 
    }

    else{
        return -x; 
    }

}



