#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <chrono>


using namespace std;
using namespace std::chrono;

//Function to allocate memory. Returns the amount of memory that is free
int my_malloc(int memoryToStore, int *totalMemorySize);

//Function to deallocate memory. Returns the amount of memory that is free
int my_free(int storedMemorySize, int *totalMemorySize);

void question1(int processes[][2]);//Function for standard malloc and free
void question2(int processes[][2]);//Function for self-made my_malloc and my_free
void question3a(int processes[][2], int specialMemorySize);//Function for 50% memory
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
    else if(j < 2000 && j > 999)//Second question
    {
      startTime = high_resolution_clock::now();

      question2(processes);

      endTime = high_resolution_clock::now();//Get the elapsed time, in ticks
      auto duration2 = duration_cast<microseconds>( endTime - startTime ).count();
      cout << duration2 << endl;
      averageTime2 += duration2;
    }
    else if(j < 3000 && j > 1999)//Third question, first option
    {
      startTime = high_resolution_clock::now();
      specialMemorySize = (specialMemorySize * 0.5);//Only 50% memory

      //question3a(processes, specialMemorySize);

      endTime = high_resolution_clock::now();//Get the elapsed time, in ticks
      auto duration3 = duration_cast<microseconds>( endTime - startTime ).count();
      averageTime3a += duration3;

      specialMemorySize = 0;//Reset the memory size for the next program to run
    }
    else if(j < 4000 && j > 2999)//Third question, second option
    {
      startTime = high_resolution_clock::now();
      specialMemorySize = (specialMemorySize * 0.1);//Only 10% memory

      //question3b(processes, specialMemorySize);

      endTime = high_resolution_clock::now();//Get the elapsed time, in ticks
      auto duration4 = duration_cast<microseconds>( endTime - startTime ).count();
      averageTime3b += duration4;

      specialMemorySize = 0;//Reset the memory size for the next program to run
    }
  }


  //-------------------Output the average runtime ------------------------------
  cout << "\n--------Question 1--------\n";
  cout <<"Average Time of question 1 (in microseconds): " << (averageTime / 1000) << endl;
  cout << "\n--------Question 2--------\n";
  cout <<"Average Time of question 2 (in microseconds): " << (averageTime2 / 1000) << endl;
  cout << "\n--------Question 3a--------\n";
  cout <<"Average Time of question 3a (in microseconds): " << (averageTime3a / 1000) << endl;
  cout << "\n--------Question 3b--------\n";
  cout <<"Average Time of question 3b (in microseconds): " << (averageTime3b / 1000) << endl;


  return 0;
}

//Function to allocate memory. Returns the amount of memory that is stored
int my_malloc(int memoryToStore, int totalMemorySize)
{
  return (totalMemorySize - memoryToStore);
}

//Function to deallocate memory. Returns the amount of memory that is free
int my_free(int storedMemorySize, int totalMemorySize)
{
  return (totalMemorySize + storedMemorySize);
}

void question1(int processes[][2])//Function for standard malloc and free
{
  int counter = 0;
  int* buff;

  for(int k = 0; k < 50; k++)//Go through all of the processes
  {
    //Allocate the memory for the process
    buff = (int*) malloc(processes[k][1] * sizeof(int));

    if((counter % 50) == 0)//New process arrives every 50
    {
      for(int j = 0; j < 50; j++)//Go through process at 1,000,000,000,000 Hz/cycle
      {
        if(processes[k][0] <= 0)//If the process has finished
        {
          break;//get out of the cycle
        }
        else//If the process still has burst time, subtract 1000000000000
        {
          processes[k][0] -= 1000000000000;
        }
      }

      counter++;//Increment the counter, as a new process comes every 50
    }

    //Free the memory from the process
    free(buff);
  }
};

void question2(int processes[][2])//Function for self-made my_malloc and my_free
{
  int counter = 0;
  int storedMemorySize;
  int totalMemorySize = 10485750;//Total size, 10MB
  int memoryToStore = 0;

  for(int k = 0; k < 50; k++)//Go through all of the processes
  {
    //Allocate the memory for the process
    memoryToStore = processes[k][1];
    storedMemorySize = my_malloc(memoryToStore, totalMemorySize);

    if((counter % 50) == 0)//New process arrives every 50
    {
      for(int j = 0; j < 50; j++)//Go through process at 1,000,000,000,000 Hz/cycle
      {
        if(processes[k][0] <= 0)//If the process has finished
        {
          break;//get out of the cycle
        }
        else//If the process still has burst time, subtract 1000000000000
        {
          processes[k][0] -= 1000000000000;
        }
      }

      counter++;//Increment the counter, as a new process comes every 50
    }

    //Free the memory from the process
    my_free(storedMemorySize, totalMemorySize);
  }
}

void question3a(int processes[][2], int specialMemorySize)//Function for 50% memory
{
  int counter = 0;
  int storedMemorySize;
  int totalMemorySize = specialMemorySize;//Total size, 50%
  int memoryToStore = 0;

  for(int k = 0; k < 50; k++)//Go through all of the processes
  {
    //Allocate the memory for the process
    memoryToStore = processes[k][1];
    storedMemorySize = my_malloc(memoryToStore, totalMemorySize);

    if((counter % 50) == 0)//New process arrives every 50
    {
      for(int j = 0; j < 50; j++)//Go through process at 1,000,000,000,000 Hz/cycle
      {
        if(processes[k][0] <= 0)//If the process has finished
        {
          break;//get out of the cycle
        }
        else//If the process still has burst time, subtract 1000000000000
        {
          if((totalMemorySize - processes[k][1]) <= 0)//If the process would go over the memory threshold
          {

          }
          processes[k][0] -= 1000000000000;
        }
      }

      counter++;//Increment the counter, as a new process comes every 50
    }

    //Free the memory from the process
    my_free(storedMemorySize, totalMemorySize);
  }
}
