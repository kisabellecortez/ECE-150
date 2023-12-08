#include <iostream>

int main();

int main() {
	double x{};
	
	std::cout << "Enter value of x: ";
	std::cin >> x;
	
	// This local variable should hold the result of stair( x )
	int stair{};
	
	// TASK: write code that calculates an integer value
	// corresponding to the value of the function stair( x ) here

    if (x > 0)
        {
            for (int i = 0; i >= 0; i++)
			{
				if (i <= x && i + 1 > x)
				{ 
					stair = i;
					break;
				}

				else
				{

				}
			}

        }

    else if (x < 0)
        {
            for (int i = 0; i <= 0; i--)
			{
				if (i > x && i - 1 < x)
				{
					stair = i-1; 
					break; 
				}

				else if (i == x)
				{
					stair = i; 
				}
			}
        }

	else
	{
		stair = 0;
	}
	
	std::cout << "The value of stair(x) is: ";
	std::cout << stair;
	std::cout << std::endl;
	
	return 0;
}