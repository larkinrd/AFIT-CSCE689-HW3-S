#ifndef PCALC_SP_H
#define PCALC_SP_H

#include "PCalc.h"

// Add your PCalc_SP class definition here as a child class of PCalc
// Be sure to overload the right methods from PCalc or it won't compile

// This class should manage the single process implementation of the prime number generator. I'd recommend
// getting this working first, then tackling multithreaded

class PCalc_SP : public PCalc { 
    public:

        PCalc_SP(unsigned int array_size);

        ~PCalc_SP();

        void markNonPrimes();

        //void PCalc_SP::cleanup(); 

        //bool &PCalc_SP::operator [] (unsigned int x);

        //bool &PCalc_SP::at(unsigned int x); 

        //void printPrimes(const char *filename); 

    protected:

    private:

};

#endif
