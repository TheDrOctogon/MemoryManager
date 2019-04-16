#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <chrono>
#include <queue>        /* Queue */

using namespace std;
using namespace std::chrono;

//Function to allocate memory. Returns the amount of memory that is free
int my_malloc(int memoryToStore, int *totalMemorySize);

//Function to deallocate memory. Returns the amount of memory that is free
int my_free(int storedMemorySize, int *totalMemorySize);

void question1(int processes[][2]);//Function for standard malloc and free
//void question2(int processes[][2]);//Function for self-made my_malloc and my_free
//void question3a(int processes[][2], int specialMemorySize);//Function for 50% memory
//void question3b(int processes[][2], int specialMemorySize);//Function for 10% memory

int main()
{
  high_resolution_clock::time_point startTime, endTime;
  int processes[50][2];//Array to hold 50 processes, with processes burst time and memory
  int averageTime = 0, averageTime2 = 0, averageTime3a = 0, averageTime3b = 0;//Holds average time
  int specialMemorySize = 0;//Variable to hold the special mem size for questions 3

  for(int j = 0; j < 4000; j++)//Go through 4000 times, to get a good average
  {
    /* initialize random seed: */
    srand(time(NULL));

    for(int i = 0; i < 50; i++)//Generate 50 processes
    {
      //Generate random num between 10000000 and 50000000000000, for burst time
      processes[i][0] = rand() % 50000000000000 + 10000000;

      //Generate random num for memory requirement for each process.
      //Each can have a max memory requirement of 209715 bytes (10 MB / 50 processes),
      //so that is the upperbound.
      processes[i][1] = rand() % 209715 + 1;
      specialMemorySize += processes[i][1];
      
	
	}
  if(j < 1000)//First question
    {
      startTime = high_resolution_clock::now();

      question1(processes);

      endTime = high_resolution_clock::now();//Get the elapsed time, in ticks
      auto duration = duration_cast<microseconds>( endTime - startTime ).count();
      averageTime += duration;
    }
	cout << "\n--------Question 1--------\n";
	cout <<"Average Time of question 1 (in microseconds): " << (averageTime / 1000) << endl;
  }
	
  }
void question1(int processes[][2])//Function for standard malloc and free
{
  int counter = 0;
  int loop = 1;
  int* buff;
  int* buff2;
  queue <int> cycle;
  queue <int> mem;
  queue <int> p1;
  queue <int> p2;
  
  for(int k = 0; k < 50; k++)//Go through all of the processes
  {
	cycle.push(processes[k][0]);
	mem.push(processes[k][1]);
  }
  
  while(loop==1)//Go through all of the processes
  {
    //Allocate the memory for the process
    //buff = (int*) malloc(processes[k][1] * sizeof(int));
	if (p1.empty() && !cycle.empty() && !mem.empty()){
		p1.push(cycle.front());
		cycle.pop();
		buff = (int*) malloc(mem.front() * sizeof(int)); 
		mem.pop();
	}
	
	if (p2.empty() && !cycle.empty() && !mem.empty()){
		p2.push(cycle.front());
		cycle.pop();
		buff2 = (int*) malloc(mem.front() * sizeof(int)); 
		mem.pop();
	}
	
    if((counter % 50) == 0)//New process arrives every 50
    {
     if(!p1.empty())
	 {
		p1.front()-= 1000000000000;
		if(p1.front()>=0){
		 p1.pop();
		 free(buff);
		}
	 }
	 if(!p2.empty())
	 {
		p2.front()-= 1000000000000;
		if(p2.front()>=0){
		 p2.pop();
		 free(buff2);
        }
     }
	
	}
	if(p1.empty() && p2.empty() &&cycle.empty())
	{
		loop=0;
	}
		
	counter++;//Increment the counter, as a new process comes every 50
    //Free the memory from the process
    //free(buff);
  }
}; 
 
  
int my_malloc(int memoryToStore, int totalMemorySize)
{
  return (totalMemorySize - memoryToStore);
}

//Function to deallocate memory. Returns the amount of memory that is free
int my_free(int storedMemorySize, int totalMemorySize)
{
  return (totalMemorySize + storedMemorySize);
}
