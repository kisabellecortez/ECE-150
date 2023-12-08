#include <iostream>
#include <climits>

unsigned int add_checksum( unsigned int n ); 
void add_checksum( unsigned int array[], std::size_t capacity ); 
bool verify_checksum( unsigned int n ); 
unsigned int remove_checksum( unsigned int n ); 
void remove_checksum( unsigned int array[], std::size_t capacity ); 

#ifndef MARMOSET_TESTING
int main();
#endif

#ifndef MARMOSET_TESTING
int main() {

    const std::size_t QTY_VALUES {4}; 
    unsigned int array[QTY_VALUES]{0, 99999999, 5843, 4000000000}; 
    add_checksum(array, QTY_VALUES); 

    for(int i = 0; i < 4; i++){
        std::cout << array[i] << std::endl; 
    }

    std::cout << verify_checksum(123456782) << std::endl; 
    std::cout << verify_checksum(123456789) << std::endl;

    std::cout << verify_checksum(999999998) << std::endl;
    std::cout << verify_checksum(999999999) << std::endl;

    std::cout << verify_checksum(58438) << std::endl;
    std::cout << verify_checksum(58437) << std::endl;

    unsigned int array2[QTY_VALUES]{0, 999999998, 58438, 4000000000}; 
    remove_checksum(array2, QTY_VALUES); 

    for(int i = 0; i < 4; i++){
        std::cout << array2[i] << std::endl; 
    }

    /*
	unsigned int value_to_protect{21352411};
	unsigned int protected_value = add_checksum(value_to_protect);
	std::cout << "The value " << value_to_protect
		<< " with the checksum added is " << protected_value
		<< "." << std::endl;
	
	if (verify_checksum(protected_value))
	{
		std::cout << "The checksum is valid." << std::endl;
	}
	else   {
		std::cout << "The checksum is invalid." << std::endl;
	} 
	const std::size_t QTY_VALUES {3};
	unsigned int value_series[QTY_VALUES] {20201122, 20209913, 20224012};
	
	add_checksum(value_series, QTY_VALUES);
	
	std::cout << "Series with checksums added: ";
	for (std::size_t series_index {0};
		series_index < QTY_VALUES; series_index++)
	{
		std::cout << value_series[series_index] << " ";
	}
    */

    return 0;
}

#endif

unsigned int add_checksum( unsigned int n ) { 
	if ( 0 <= n && n <= 99999999) {  
		int calculate[9]{}; 
        int divisor{1}; 
        int checksum{};
        int add_num{};
        int d_value{}; 

		for( int i = 7; i >= 0; i--){ 
			calculate[i] = (n / divisor) % 10;

			divisor *= 10;
		}

        for( int i = 7; i >= 0; i -=2){ 
            int mult_num{}; 

            mult_num = calculate[i] * 2; 
            
            if( mult_num > 9 ){

                mult_num = (mult_num % 10) + (mult_num / 10); 

            }

            calculate[i] = mult_num; 

        }

        for(int i = 0; i < 8; i++){ 
            add_num += calculate[i]; 

        }

        d_value = ( add_num * 9 ) % 10; 
        calculate[8] = d_value; 
        checksum = ( n * 10 ) + d_value; 

        return checksum; 

	}

	else { 
        return UINT_MAX; 

	}

}

void add_checksum( unsigned int array[], std::size_t capacity ){
    for( int i = 0; i < capacity; i++ ){

        array[i] = add_checksum(array[i]); 

    }

}

bool verify_checksum( unsigned int n ) {

    if( n <= 999999999) {
        int d_value = n % 10; 
        int check_d_value = (add_checksum( n / 10 )) % 10; 

        if( d_value == check_d_value){
            return true; 

        }

        else{
            return false; 

        }
    }

    else {
        return false; 

    }

}

unsigned int remove_checksum( unsigned int n ){
        bool flag = false; 

        flag = verify_checksum( n ); 

        if( flag == true ){
            return n / 10; 
        }

        else{
            return UINT_MAX; 

        }

    }


void remove_checksum( unsigned int array[], std::size_t capacity ){
    for( int i = 0; i < capacity; i++ ){
        array[i] = remove_checksum( array[i] ); 

    }

}