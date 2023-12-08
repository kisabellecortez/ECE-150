#include "geesespotter_lib.h"

char *createBoard(std::size_t xdim, std::size_t ydim){
    char *array_board{new char[xdim * ydim]}; 

    for(int i = 0; i < (xdim * ydim); ++i){
        array_board[i] = 0; 

    }

    return array_board; 

}

void cleanBoard(char *board){
    delete[] board; 
    board = nullptr;

}

void printBoard(char *board, std::size_t xdim, std::size_t ydim){
    for(int i = 0; i < ydim; ++i){
        for(int k = 0; k < xdim; ++k){
            if((board[(xdim * i) + k] & markedBit()) && (board[(xdim * i) + k] & hiddenBit())){
                std::cout << 'M'; 
            }

            else if(board[(xdim * i) + k] & hiddenBit()){
                std::cout << '*';  

            }

            else{
                std::cout << (board[(xdim * i) + k] & valueMask()); 
            }

        }
        std::cout << std::endl; 

    }

}

void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim){
    for(int i = 0; i < (xdim * ydim); ++i){
        if((board[i] & valueMask()) == 9){
            for(int a = 0; a < 3; ++a){
                int yloc = i / xdim; 
                int xloc = i % xdim;    

                --yloc; 
                xloc = xloc - 1 + a;             

                if((yloc >= 0 && yloc <= ydim - 1) && (xloc >= 0 && xloc <= xdim - 1) && ((board[xdim * yloc + xloc] & valueMask()) != 9)){
                    board[xdim * yloc + xloc] = (board[xdim * yloc + xloc] & valueMask()) + 1; 

                }
            }

            for(int b = 0; b < 3; ++b){
                int yloc = i / xdim; 
                int xloc = i % xdim; 

                ++yloc; 
                xloc = xloc + 1 - b;                   

                if((yloc >= 0 && yloc <= ydim - 1) && (xloc >= 0 && xloc <= xdim - 1) && ((board[xdim * yloc + xloc] & valueMask()) != 9)){
                    board[xdim * yloc + xloc] = (board[xdim * yloc + xloc] & valueMask()) + 1;
                }
            }

            int yloc = i / xdim; 
            int xloc = i % xdim; 

            if((yloc >= 0 && yloc <= ydim - 1) && (xloc + 1 >= 0 && xloc + 1<= xdim - 1) && ((board[xdim * yloc + (xloc + 1)] & valueMask()) != 9)){
                board[xdim * yloc + (xloc + 1)] = (board[xdim * yloc + (xloc + 1)] & valueMask()) + 1;

            }

            if((yloc >= 0 && yloc <= ydim - 1) && (xloc - 1 >= 0 && xloc - 1 <= xdim - 1) && ((board[xdim * yloc + (xloc - 1)] & valueMask()) != 9)){
                board[xdim * yloc + (xloc - 1)] = (board[xdim * yloc + (xloc - 1)] & valueMask()) + 1;

            }            
    
        }

    }

}

void hideBoard(char *board, std::size_t xdim, std::size_t ydim){
    for(int i = 0; i < (xdim * ydim); i++){
        board[i] |= hiddenBit(); 
        
    }

}

int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    if((board[(xdim * yloc) + xloc] & hiddenBit()) && !((board[(xdim * yloc) + xloc] & markedBit()))){ 
        board[(xdim * yloc) + xloc] ^= hiddenBit();

        if((board[(xdim * yloc) + xloc] & valueMask()) != 9){
            if((board[(xdim * yloc) + xloc] & valueMask()) == 0){

                --yloc; 
                --xloc; 

                for(int k = 0; k < 3; ++k){
                    int temp = xloc + k; 

                    if((yloc >= 0 && yloc <= ydim - 1) && (temp >= 0 && temp <= xdim - 1)){
                        board[(xdim * yloc) + temp] &= ~hiddenBit();

                    }
                
                }

                ++yloc; 
                ++xloc; 

                if((yloc >= 0 && yloc <= ydim - 1) && (xloc - 1 >= 0 && xloc - 1 <= xdim - 1)){
                    board[((xdim * yloc) + xloc) - 1] &= ~hiddenBit(); 

                } 
            
                if((yloc >= 0 && yloc <= ydim - 1) && (xloc + 1 >= 0 && xloc + 1 <= xdim - 1)){
                    board[((xdim * yloc) + xloc) + 1] &= ~hiddenBit(); 

                }   

                ++yloc; 
                ++xloc; 

                for(int j = 0; j < 3; ++j){
                    int temp = xloc - j; 
                    if((yloc >= 0 && yloc <= ydim - 1) && (temp >= 0 && temp <= xdim - 1)){
                        board[(xdim * yloc) + temp] &= ~hiddenBit(); 

                    }                
                
                }
                             
            }

            return 0; 

        }

        else{
            return 9; 
        }
   
    }

    else if(board[(xdim * yloc) + xloc] & markedBit()){
        return 1; 
    }

    else if(!(board[(xdim * yloc) + xloc] & hiddenBit())){
        return 2; 

    }

    else{
        return 0; 
    }

}

int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){

    if(!(board[(xdim * yloc) + xloc] & hiddenBit())){
        return 2; 

    }

    else{
        board[(xdim * yloc) + xloc] ^= markedBit(); 
        return 0; 

    }


}

bool isGameWon(char *board, std::size_t xdim, std::size_t ydim){

    int goose{}; 
    int found{}; 

    for(int i = 0; i < xdim * ydim; ++i){
        if(((board[i]) & valueMask()) == 9){
            ++goose; 

        }

        else if((((board[i] & markedBit())) && ((board[i] & valueMask()) == 9)) || !(board[i] & hiddenBit())){
            ++found; 

        }
    }

    if(goose == xdim * ydim || found == xdim * ydim - goose){
        return true; 
    }

    else{
        return false; 
    }

}

