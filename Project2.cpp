#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <chrono>


using namespace std;
using namespace std::chrono;


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
}
//void question2(int processes[][2]);//Function for self-made my_malloc and my_free
//void question3a(int processes[][2]);//Function for 50% memory
//void question3b(int processes[][2]);//Function for 10% memory

int main()
{
  high_resolution_clock::time_point startTime, endTime;
  int processes[50][2];//Array to hold 50 processes, with processes burst time and memory
  int averageTime = 0, averageTime2, averageTime3a, averageTime3b;//Holds average time

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
    }
    if(j < 1000)
    {
      if(j == 0)
      {
        cout << "\n--------Question 1--------\n";
      }

      startTime = high_resolution_clock::now();

      question1(processes);

      endTime = high_resolution_clock::now();//Get the elapsed time, in ticks
      auto duration = duration_cast<microseconds>( endTime - startTime ).count();
      averageTime += duration;
    }
    else if(j < 2000 && j > 999)
    {
      if(j == 0)
      {
        cout << "\n--------Question 2--------\n";
      }

      startTime = high_resolution_clock::now();

      //question2(processes);

      endTime = high_resolution_clock::now();//Get the elapsed time, in ticks
      auto duration = duration_cast<microseconds>( endTime - startTime ).count();
      averageTime2 += duration;
    }
    else if(j < 3000 && j > 1999)
    {
      if(j == 0)
      {
        cout << "\n--------Question 3a--------\n";
      }

      startTime = high_resolution_clock::now();

      //question3a(processes);

      endTime = high_resolution_clock::now();//Get the elapsed time, in ticks
      auto duration = duration_cast<microseconds>( endTime - startTime ).count();
      averageTime3a += duration;
    }
    else if(j < 4000 && j > 2999)
    {
      if(j == 0)
      {
        cout << "\n--------Question 3b--------\n";
      }

      startTime = high_resolution_clock::now();

      //question3b(processes);

      endTime = high_resolution_clock::now();//Get the elapsed time, in ticks
      auto duration = duration_cast<microseconds>( endTime - startTime ).count();
      averageTime3b += duration;
    }
  }

  cout <<"Average Time of question 1 (in microseconds): " << (averageTime / 800) << endl;

  return 0;
}
