#ifndef PCALC_T_H
#define PCALC_T_H

#include "PCalc.h"
#include <mutex>

// Your implementation of PCalc_T class should go here. 
// Make sure your constructor takes in two parameters:

// PCalc_T::PCalc_T(unsigned int array_size, unsigned int num_threads);

// Call the parent constructor when initializing your constructor and pass in array_size. Then
// use num_threads to cap off how many threads you use to calculate all prime numbers

class PCalc_T : public PCalc {
    public:
        PCalc_T(unsigned int array_size, unsigned int num_threads);

        ~PCalc_T();

        void markNonPrimes();

        //void PCalc_SP::cleanup(); 

        //bool &PCalc_SP::operator [] (unsigned int x);

        //bool &PCalc_SP::at(unsigned int x); 

        //void printPrimes(const char *filename); 

        unsigned int bobsnumthreads;
        std::mutex mu;


  //ALL MY VARIABLES
  //unsinged int maximum is: 	0 to 4294967295
  int maxthreads = 0; 
  unsigned int primesearchmax = 0;
  
  
  //std::vector<unsigned int> primearray(primesearchmax,1);
 
   
        
    protected:
    
    private:

};
#endif
