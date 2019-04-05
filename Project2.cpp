#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>

using namespace std;

void question1(int processes[][2]);//Function for standard malloc and free
void question2(int processes[][2]);//Function for self-made my_malloc and my_free
void question3a(int processes[][2]);//Function for 50% memory
void question3b(int processes[][2]);//Function for 10% memory

int main()
{
  int processes = [50][2];//Array to hold 50 processes, with processes burst time and memory

  for(int j = 0; j < 200; j++)//Go through 200 times, to get an average
  {
    /* initialize random seed: */
    srand(time(NULL));

    for(int i = 0; i < 50; i++)
    {
      //Generate random num between 10000000 and 50000000000000, for burst time
      processes[i][0] = rand() % 50000000000000 + 10000000;

      //Generate random num for memory requirement for each process.
      //Each can have a max memory requirement of 204, so that is the upperbound.
      processes[i][1] = rand() % 204 + 1
    }

    question1(processes);
    question2(processes);
    question3a(processes);
    question3b(processes);
  }

  return 0;
}

void question1(int processes[][2])//Function for standard malloc and free
{
  for(k = 0; k < 50; k++)//Go through all of the processes
  {
    if((counter % 50) == 0)//New process arrives every 50
    {


    }
  }
}
