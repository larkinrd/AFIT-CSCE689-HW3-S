
#include <cstring>
#include <stdexcept>
#include <fstream>
#include <iostream>

#include <thread>
#include <vector>
#include <algorithm>
#include <math.h>
#include <mutex>

#include <PCalc.h>
#include <PCalc_T.h>


//https://www.bogotobogo.com/cplusplus/C11/3_C11_Threading_Lambda_Functions.php
//https://www.acodersjourney.com/top-20-cplusplus-multithreading-mistakes/
//https://www.acodersjourney.com/c11-multithreading-tutorial-via-faq-thread-management-basics/#q20

//static const int num_of_threads = 10; //do this for now

PCalc_T::PCalc_T(unsigned int array_size, unsigned int num_threads):PCalc(array_size) {
   bobsnumthreads = num_threads;
   //num_of_threads = num_threads;
}


/************************************************************************************************
 * PCalc (destructor) - deletes the primelist array
 ************************************************************************************************/

PCalc_T::~PCalc_T() {
   cleanup();
}

/* USED THIS FOR ATTEMPTS #1 AND #2 BELOW
void PCalc_T::multithreadedfunction(){
   std::cout << "Function running in multithreadedfunction " << std::endl;
}
*/

void PCalc_T::markNonPrimes(){

//******
// ATTEMPT #1 FROM https://www.go4expert.com/articles/writing-multithreaded-program-cpp-t29980/
// 
// I GET ERROR:  error: invalid use of non-static member function ‘void PCalc_T::multithreadedfunction()’
//  std::thread t(multithreadedfunction);
//
//	//This statement will launch thread in parallel to main function
//	std::thread t(multithreadedfunction);
//	std::cout << "\nThe main function execution\n";
//	//This is how we join the new thread with main
//	t.join();
//	getchar();
//**********

//******
// ATTEMPT #2 FROM https://www.go4expert.com/articles/writing-multithreaded-program-cpp-t29980/
// 
// I GET SAME ERROR:  error: invalid use of non-static member function ‘void PCalc_T::multithreadedfunction()’
//  std::thread t(multithreadedfunction);std::cout << "num_of_threads is " << num_of_threads << std::endl;
/****
 * 
 * 
 * 
 * 
 * std::thread threads[num_of_threads];
 * 	//This statement will launch multiple threads in loop
 * 	for (int i = 0; i < num_of_threads; ++i) {
 * 		threads[i] = std::thread(multithreadedfunction, i);
 * 	}
 * 	std::cout << "The main function execution\n";
 * 	//This is how we join the new thread with main
 * 	for (int i = 0; i < num_of_threads; ++i) {
 * 		threads[i].join();
 * 	}
 * 	getchar();





/* JUST SOME NOTES FROM FELLOW CLASSMATES
unsigned int i = 0
std::thread ([&]()){lambda... insert code using i}
*/

/****** ATTEMPT NUMBER 3 USING LAMBDA ******
//
// MAIN ERROR: The variable b in the inner loop does not work correctly

*/

unsigned int maxloopingforarray = sqrt(array_size());
unsigned int myarraysize = array_size();
         

// vector container stores threads
    std::vector<std::thread> workers;
    for (int i = 0; i < bobsnumthreads; i++) {
        workers.push_back(std::thread([i,this,maxloopingforarray,myarraysize]() {
            
            //FROM TUTORIAL
         
            //std::cout << "num for this thread function is " << i << "\n";
            //std::cout << "print unique identifier for thread " << std::this_thread::get_id() << "\n";
            //std::cout << "bobsnumthreads variable is " << bobsnumthreads << "\n";
            //std::cout << "array_size() is " << array_size() << "\n";
            //std::cout << "sqrt(array_size()) is " << (1/(i+1))*sqrt(myarraysize) << "\n";
            //std::cout << "1/(i+1) is: " << maxloopingforarray/(i+1) << "\n";
            
            
         unsigned int a=2, b, asquared;
         //if (i == 0) { a = 2; } else { a = maxloopingforarray/(i+1);}
         //if (i == 0) { a = 2; } else { a = 2+i;}
         //std::cout << "Thread INT i is: " << i << " with INT a starting at: " << a << std::endl;
       
        
        for (a ; a < maxloopingforarray; a++){
          //std::cout << i << ",";
        //std::cout << "for i =: " << i << " nixing: ";
        if(this->at(a) == true){
            std::cout << "Thread,"<<i<<",IS AT PRIME," << a << "\n";
            asquared = a*a;
            for (int b=0; asquared+(a*b)<myarraysize; b++) {
                //std::cout << (i*i)+(i*j) << ",";
                //std::cout << "i is: " << i << "::";
                //std::cout << "j is: " << j << "::";;
                //std::cout << "myarraysize is: " << myarraysize  << "::";
                //std::cout << "isquared is: " << isquared << "::";
                //std::cout << "isquared+(i*j) is: " << isquared+(i*j);
                mu.lock();
                this->at(asquared+(a*b))=false;
                //std::cout << "Thread,"<<i<<",modifying position,"<< (asquared+(a*b)) << ",to false\n";
                //std::cout << "Next position is: " << ((asquared+(a*b))+1) << " with value " << this->at((asquared+(a*b))+1) << "\n";
                mu.unlock();
                //std::cout << std::endl;
                //j+=i;                
            }
            //std::cout << std::endl;
        }
        //std::cout << std::endl;
    }
            
        
     
            //std::cout << "\nDONE WITH CALCS... OUTPUT PRIMEARRAY\n";
            //for (int checkprimesarray = 0; checkprimesarray < array_size(); checkprimesarray++){
            //   std::cout << this->at(checkprimesarray) << ".";
            //}
            
        }));
    }
    //mu.lock();
    std::cout << "main thread\n";
   //mu.unlock();

    // Looping every thread via for_each
    // The 3rd argument assigns a task
    // It tells the compiler we're using lambda ([])
    // The lambda function takes its argument as a reference to a thread, t
    // Then, joins one by one, and this works like barrier
    std::for_each(workers.begin(), workers.end(), [](std::thread &t) 
    {
        t.join();
    });


}

/************************************************************************************************
 * cleanup - cleans up memory from this object
 ************************************************************************************************/
/*
void PCalc_T::cleanup() {
   if (primelist != NULL)
      delete[] primelist;
   primelist = NULL;
}
*/
/************************************************************************************************
 * operator [] - retrieves a reference (can be modified) to the prime boolean at index x
 *                      
 ************************************************************************************************/
/*
bool &PCalc_T::operator [] (unsigned int x){
   if (x > asize) {
      throw std::range_error("primelist array index out of bounds");
   }

   return primelist[x];
}*/

/************************************************************************************************
 * at - retrieves a reference (can be modified) to the prime boolean at index x
 *
 ************************************************************************************************/
/*
bool &PCalc_T::at(unsigned int x) {
   if (x > asize) 
      throw std::range_error("primelist array index out of bounds");

   return primelist[x];
}
*/
/************************************************************************************************
 * printPrimes - outputs the prime values to the file specified
 *
 *    Params:  filename - the path/filename of the output file
 *
 ************************************************************************************************/
/*
void PCalc_T::printPrimes(const char *filename) {

}*/


