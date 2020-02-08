#include <cstring>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <math.h>

#include <PCalc.h>
#include <PCalc_SP.h>

PCalc_SP::PCalc_SP(unsigned int array_size):PCalc(array_size){
    std::cout << "PCalc_SP() consructor called with array_size: " << array_size << std::endl;
    //remember, no access to parents classes' private members... so why are they there?
    
}

PCalc_SP::~PCalc_SP(){}

void PCalc_SP::markNonPrimes() {
    
    //WHY WERE PRIVATE VARIABLES CREATED IN PCALC IF I CANT ACCESS THEM?
    //std::cout << "Array Size in markNonPrimes() is: " << asize << std::endl;
     //std::cout << "PCalc_SP::markNonPrimes() where array_size is: " << array_size << std::endl;
     //std::cout << "PCalc_SP::markNonPrimes() where this->array_size is: " << this->array_size << std::endl;
    //std::cout << "using this: " << this->at(0) << std::endl;
    //std::cout << "using this: " << this->at(1) << std::endl;
    //std::cout << "using this: " << this->at(2) << std::endl;
    //std::cout << "using this: " << this->at(3) << std::endl;
    //this->at(8)=false;
    //std::cout << "using this: " << this->at(10) << std::endl;
    //this->[103]=false; //DONT KNOW HOW TO USE THIS


    //algorithm Sieve of Eratosthenes is
    //input: an integer n > 1.
    //output: all prime numbers from 2 through n.

    //let A be an array of Boolean values, indexed by integers 2 to n,
    //initially all set to true.
    unsigned int maxloopingforarray = sqrt(array_size());
    unsigned int i, j, isquared;
    for (i = 2; i < maxloopingforarray; i++){
        //std::cout << i << ",";
        //std::cout << "for i =: " << i << " nixing: ";
        if(this->at(i) == true){
            std::cout << i << ",";
            isquared = i*i;
            for (int j=0; isquared+(i*j)<maxloopingforarray; j++) {
                //std::cout << (i*i)+(i*j) << ",";
                this->at(isquared+(i*j))=false;
                //j+=i;                
            }
            //std::cout << std::endl;
        }
        //std::cout << std::endl;
    }
    
    //for i = 2, 3, 4, ..., not exceeding √n do
    //    if A[i] is true
    //        for j = i2, i2+i, i2+2i, i2+3i, ..., not exceeding n do
    //            A[j] := false

    //return all i such that A[i] is true.

    
    
}

//void PCalc_SP::cleanup(){}

//bool &PCalc_SP::operator [] (unsigned int x){}

//bool &PCalc_SP::at(unsigned int x){}

//void PCalc_SP::printPrimes(const char *filename){}