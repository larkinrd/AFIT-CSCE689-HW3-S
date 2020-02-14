
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

#include <strings.h>
#include <iomanip>


//https://www.bogotobogo.com/cplusplus/C11/3_C11_Threading_Lambda_Functions.php
//https://www.acodersjourney.com/top-20-cplusplus-multithreading-mistakes/
//https://www.acodersjourney.com/c11-multithreading-tutorial-via-faq-thread-management-basics/#q20

                                       //threadslot,    maxthreads,       primesearchmax,      &threadarray[threadslot],     this);
// My Thread Function 
void mythreadfunction(unsigned int id, int totalthreads, unsigned int lastnum, unsigned int* arrayofthreads, PCalc_T *updateprimearray){
     // critical section (exclusive access to std::cout signaled by locking mtx):
  //WAS USED TO TEST MY LAZY THREAD LOGIC!
  //std::this_thread::sleep_for (std::chrono::milliseconds(5000));

  int primesquared = (*arrayofthreads)*(*arrayofthreads);
  unsigned int startpt = *arrayofthreads;
  for (unsigned int k=0; (primesquared + (startpt * k)) < lastnum; k++) {
    *arrayofthreads = (primesquared + (startpt * k));
    //mtx.lock(); // REALLY SLOWS DOWN THE CODE, BUT IS CORRECT LOGIC TO LOCK AND UNLOCK SHARED RESOURCE
    updateprimearray->at(*arrayofthreads)=0;
    //mtx.unlock();
    //WAS USED TO TEST MY LAZY THREAD LOGIC!
    //std::this_thread::sleep_for (std::chrono::milliseconds(250));
  }
  
  //make the thread available to main
  *arrayofthreads = 0;
}

PCalc_T::PCalc_T(unsigned int array_size, unsigned int num_threads):PCalc(array_size) {
  
  maxthreads = num_threads;
  primesearchmax = array_size; 

  //std::cout << "maxthreads is " << maxthreads << "and primesearchmax is " << primesearchmax << std::endl;
}


/************************************************************************************************
 * PCalc (destructor) - deletes the primelist array
 ************************************************************************************************/

PCalc_T::~PCalc_T() {
   cleanup();
}




void PCalc_T::markNonPrimes(){
   unsigned int psqrt = sqrt(primesearchmax);
   unsigned int threadarray[maxthreads];
   bzero(threadarray, maxthreads * sizeof(int));
   std::thread threads[maxthreads];
   unsigned int threadslot = 0;

   //std::cout << "IS THIS EXECUTING" << std::endl;
   //std::cout << "maxthreads is " << maxthreads << "and primesearchmax is " << primesearchmax << std::endl;


 //Begin outer loop of Seive of Erathosnese starting at prime number 2
  for(unsigned int primesearch =2; primesearch<psqrt; primesearch++) {
    
    //Print to screen current 'potential' prime number and status of running threads
    //std::cout << "primesearch value is: " << primesearch << " :: ";    
    //std::cout << "threadarray[]={"; for (int z=0; z<maxthreads; z++ ) {std::cout << threadarray[z] << ",";} std::cout << "}\n";

/*********SEE BELOW******I'M EMARRASSED AND I CANNOT FIGURE THIS OUT**************************/   
    //Check for a lazy thread (i.e. I think the number 3 or 4 is prime, but a thread is still on number 2)
    //To say another, ensure all threads are evaluating a number greater than the potential prime number in order
    //to prevent RACE CONDITION
    for (int lazythread = 0; lazythread < maxthreads;){
      if (threadarray[lazythread] <= primesearch && threadarray[lazythread] > 0 ){
        //std::cout << "Threadslot is LAZY in threadarray[" << lazythread << "]=" <<threadarray[lazythread] << "... sleeping and resetting lazythread loop counter\n";
        //std::cout << "threadarray[]={"; for (int z=0; z<maxthreads; z++ ) {std::cout << threadarray[z] << ",";} std::cout << "}\n";
        std::this_thread::sleep_for (std::chrono::milliseconds(100));
        lazythread =0;
      } else {
        //std::cout << "Threadslot is NOT LAZY with threadarray[" << lazythread << "]=" <<threadarray[lazythread] << "\n";
        lazythread++;
        continue;
      }
    }
/*********************PLEASE CHECK LOGIC ABOVE HERE AND LETS DISCUSS**************************/       

    //check if value primesearch in the primearray is true
    if (this->at(primesearch) == true) {

       //initeloop until a thread becomes available
      for (;;) {
        if (threadarray[threadslot] == 0) {
          break; //a thread became availealbe, break out of the loop
        } else {
        threadslot++;
        threadslot = threadslot % (maxthreads); //just keeping looping over the number of threads
        }
      }

      //A thread become availale, set it to the prime number to spawn the thread and start crossing off multiples of it 
      threadarray[threadslot] = primesearch; 

      
/*********************HAD ISSUES HERE**************************/      
      // Join the thread object to main, first check to see if it is joinable
      if(threads[threadslot].joinable() == true) {
        threads[threadslot].join(); 
        std::cout << "threadarray["<<threadslot<<"] has been JOINED TO main()";
      }
/*********************HAD ISSUES HERE**************************/    

      // Spawn the thread and save it in a threads object array... however, std::thread() doesn't return reliable information
      //  SEE https://en.cppreference.com/w/cpp/thread/thread ... "turn value of the top-level function is ignored"
      // OH GOD! Programming the pass by reference for the threadarray[threadnum] hurt... VIEW DEITEL BOOK PG 322 Bubble Sort 
      threads[threadslot] = std::thread(mythreadfunction, threadslot, maxthreads, primesearchmax, &threadarray[threadslot], this);

/**************CODE HERE FIXES MY ISSUES**************************/  
      //detach the thread and let it run
      //threads[threadslot].detach(); 
      //std::cout << "threadarray["<<threadslot<<"] has been detached from main()::";
      //this prints out the status of the threads and their current number
      std::cout << "threadarray[]={"; for (int z=0; z<maxthreads; z++ ) {std::cout << threadarray[z] << ",";} std::cout << "}\n";
/**************CODE HERE FIXES MY ISSUES**************************/  
      
      threadslot++;
      threadslot = threadslot % (maxthreads);

    } //END if (primearray.at(primesearch) == 1 
      
      //GOOD CODE TO KEEP FOR DETACHING THREADS IN THE FUTURE
      //for (int z = 0; z < maxthreads; z++){
      //  if(threads[z].joinable() == true) {threads[z].detach(); std::cout << "threadarray["<<z<<"] has been detached from main()";}
      //}
  
  }//END for(unsigned int primesearch =2; primesearch<psqrt; primesearch++) 

for (int z = 0; z<maxthreads; z++){
 // Join the thread object to main, first check to see if it is joinable
      if(threads[threadslot].joinable() == true) {
        threads[threadslot].join(); 
        //std::cout << "threadarray["<<threadslot<<"] has been JOINED TO main()";
      }
}


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


