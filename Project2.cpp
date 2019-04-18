#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <chrono>
#include <queue>        /* Queue */

using namespace std;
using namespace std::chrono;

//Function to allocate memory. Returns the amount of memory that is free
int my_malloc(int memoryToStore, int totalMemorySize);

//Function to deallocate memory. Returns the amount of memory that is free
int my_free(int storedMemorySize, int totalMemorySize);

void question1(int processes[][2]);//Function for standard malloc and free
void question2(int processes[][2]);//Function for self-made my_malloc and my_free
void question3a(int processes[][2]);//Function for 50% memory
void question3b(int processes[][2]);//Function for 10% memory

int main()
{
  high_resolution_clock::time_point startTime, endTime;
  int processes[50][2];//Array to hold 50 processes, with processes burst time and memory
  int averageTime = 0, averageTime2 = 0, averageTime3a = 0, averageTime3b = 0;//Holds average time
  int specialMemorySize = 0;//Variable to hold the special mem size for questions 3

  for(int j = 0; j < 12000; j++)//Go through 4000 times, to get a good average
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
  if(j < 3000)//First question
    {
      startTime = high_resolution_clock::now();

      question1(processes);

      endTime = high_resolution_clock::now();//Get the elapsed time, in ticks
      auto duration = duration_cast<microseconds>( endTime - startTime ).count();
      averageTime += duration;
    }
   else if(j < 6000 && j > 2999)//Second question
    {
      startTime = high_resolution_clock::now();

      question2(processes);

      endTime = high_resolution_clock::now();//Get the elapsed time, in ticks
      auto duration2 = duration_cast<microseconds>( endTime - startTime ).count();
      //cout << duration2 << endl;
      averageTime2 += duration2;
    }
	else if(j < 9000 && j > 5999)//Third question, first option
    {
      startTime = high_resolution_clock::now();
      specialMemorySize = (specialMemorySize * 0.5);//Only 50% memory

      question3a(processes);

      endTime = high_resolution_clock::now();//Get the elapsed time, in ticks
      auto duration3 = duration_cast<microseconds>( endTime - startTime ).count();
      averageTime3a += duration3;

      specialMemorySize = 0;//Reset the memory size for the next program to run
    }
    else if(j < 12000 && j > 8999)//Third question, second option
    {
      startTime = high_resolution_clock::now();
      specialMemorySize = (specialMemorySize * 0.1);//Only 10% memory

      question3b(processes);

      endTime = high_resolution_clock::now();//Get the elapsed time, in ticks
      auto duration4 = duration_cast<microseconds>( endTime - startTime ).count();
      averageTime3b += duration4;

      specialMemorySize = 0;//Reset the memory size for the next program to run
    }
  }
	cout << "\n--------Question 1--------\n";
	cout <<"Average Time of question 1 (in microseconds): " << (averageTime / 3000) << endl;
	cout << "\n--------Question 2--------\n";
    cout <<"Average Time of question 2 (in microseconds): " << (averageTime2 / 3000) << endl;
	cout << "\n--------Question 3a--------\n";
    cout <<"Average Time of question 3a (in microseconds): " << (averageTime3a / 3000) << endl;
	cout << "\n--------Question 3b--------\n";
    cout <<"Average Time of question 3b (in microseconds): " << (averageTime3b / 3000) << endl;
	return 0;
  }
void question1(int processes[][2])//Function for standard malloc and free
{
  int counter = 0;
  int loop = 1;
  int buffDude;
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
		buffDude=mem.front();
		buff = (int*) malloc(buffDude * sizeof(int)); 
		mem.pop();
	}
	
	if (p2.empty() && !cycle.empty() && !mem.empty()){
		p2.push(cycle.front());
		cycle.pop();
		buffDude=mem.front();
		buff2 = (int*) malloc(buffDude * sizeof(int)); 
		mem.pop();
	}
	
    if((counter % 50) == 0)//New process arrives every 50
    {
     if(!p1.empty())
	 {
		p1.front()-= 1000000000000;
		if(p1.front()<=0){
		 p1.pop();
		 free(buff);
		}
	 }
	 if(!p2.empty())
	 {
		p2.front()-= 1000000000000;
		if(p2.front()<=0){
		 p2.pop();
		 free(buff2);
        }
     }
	
	}
	if(p1.empty() && p2.empty() && cycle.empty())
	{
		loop=0;
	}
		
	counter++;//Increment the counter, as a new process comes every 50
    //Free the memory from the process
    //free(buff);
  }
  
 }; 
 
 void question2(int processes[][2])//Function for self-made my_malloc and my_free
{
  int counter = 0;
  int loop = 1;
  int storedMemorySize = 0;
  int totalMemorySize = 10485750;//Total size, 10MB
  int buff = 0;
  int buff2 = 0;
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
		buff=mem.front();
		storedMemorySize += my_malloc(buff, totalMemorySize);
		mem.pop();
	}
	
	if (p2.empty() && !cycle.empty() && !mem.empty()){
		p2.push(cycle.front());
		cycle.pop();
		buff2=mem.front();
		storedMemorySize += my_malloc(buff2, totalMemorySize);
		mem.pop();
	}
	
    if((counter % 50) == 0)//New process arrives every 50
    {
     if(!p1.empty())
	 {
		p1.front()-= 1000000000000;
		if(p1.front()<=0){
		 p1.pop();
		 my_free(buff, totalMemorySize);
		}
	 }
	 if(!p2.empty())
	 {
		p2.front()-= 1000000000000;
		if(p2.front()<=0){
		 p2.pop();
		 my_free(buff2, totalMemorySize);
        }
     }
	
	}
	if(p1.empty() && p2.empty() && cycle.empty())
	{
		loop=0;
	}
		
	counter++;//Increment the counter, as a new process comes every 50
    //Free the memory from the process
    //free(buff);
  }
  
  }
 
 void question3a(int processes[][2])//Function for 50% memory
{
  int counter = 0;
  int loop = 1;
  int storedMemorySize = 0;
  int totalMemorySize = 10485750*.5;
  int buff = 0;
  int buff2 = 0;
  int buffDude = 0;
  int allocatedMem = 0;
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
    
	buffDude=mem.front();
	if((buffDude+allocatedMem)<=totalMemorySize)
	{
		if (p1.empty() && !cycle.empty() && !mem.empty()){
			p1.push(cycle.front());
			cycle.pop();
			buff=mem.front();
			storedMemorySize += my_malloc(buff, totalMemorySize);
			mem.pop();
			allocatedMem += buff;
		}
	}
	buffDude=mem.front();
	if((buffDude+allocatedMem)<=totalMemorySize)
	{
			if (p2.empty() && !cycle.empty() && !mem.empty()){
			p2.push(cycle.front());
			cycle.pop();
			buff2=mem.front();
			storedMemorySize += my_malloc(buff2, totalMemorySize);
			mem.pop();
			allocatedMem += buff2;
		}
	}
	
    if((counter % 50) == 0)//New process arrives every 50
    {
     if(!p1.empty())
	 {
		
		p1.front()-= 1000000000000;
		if(p1.front()<=0){
			p1.pop();
			my_free(buff, totalMemorySize);
			allocatedMem-=buff;
			
		}
	 }
	 if(!p2.empty())
	 {
		
		p2.front()-= 1000000000000;
		if(p2.front()<=0){
			p2.pop();
			my_free(buff2, totalMemorySize);
			allocatedMem-=buff2;
        }
     }
	
	}
	if(p1.empty() && p2.empty() && cycle.empty())
	{
		loop=0;
	}
		
	counter++;//Increment the counter, as a new process comes every 50
    //Free the memory from the process
    //free(buff);
  }
  
  }

 void question3b(int processes[][2])//Function for 50% memory
{
  int counter = 0;
  int loop = 1;
  int storedMemorySize = 0;
  int totalMemorySize = 10485750*.10;
  int buff = 0;
  int buff2 = 0;
  int buffDude = 0;
  int allocatedMem = 0;
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
    
	buffDude=mem.front();
	if((buffDude+allocatedMem)<=totalMemorySize)
	{
		if (p1.empty() && !cycle.empty() && !mem.empty()){
			p1.push(cycle.front());
			cycle.pop();
			buff=mem.front();
			storedMemorySize += my_malloc(buff, totalMemorySize);
			mem.pop();
			allocatedMem += buff;
		}
	}
	buffDude=mem.front();
	if((buffDude+allocatedMem)<=totalMemorySize)
	{
			if (p2.empty() && !cycle.empty() && !mem.empty()){
			p2.push(cycle.front());
			cycle.pop();
			buff2=mem.front();
			storedMemorySize += my_malloc(buff2, totalMemorySize);
			mem.pop();
			allocatedMem += buff2;
		}
	}
	
    if((counter % 50) == 0)//New process arrives every 50
    {
     if(!p1.empty())
	 {
		
		p1.front()-= 1000000000000;
		if(p1.front()<=0){
			p1.pop();
			my_free(buff, totalMemorySize);
			allocatedMem-=buff;
			
		}
	 }
	 if(!p2.empty())
	 {
		
		p2.front()-= 1000000000000;
		if(p2.front()<=0){
			p2.pop();
			my_free(buff2, totalMemorySize);
			allocatedMem-=buff2;
        }
     }
	
	}
	if(p1.empty() && p2.empty() && cycle.empty())
	{
		loop=0;
	}
		
	counter++;//Increment the counter, as a new process comes every 50
    //Free the memory from the process
    //free(buff);
  }
  
  }  

int my_malloc(int memoryToStore, int totalMemorySize)
{
  return (totalMemorySize - memoryToStore);
}

//Function to deallocate memory. Returns the amount of memory that is free
int my_free(int storedMemorySize, int totalMemorySize)
{
  return (totalMemorySize + storedMemorySize);
}
