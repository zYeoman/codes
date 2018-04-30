#include <stdio.h>
#include <stdlib.h>
//#include<unistd.h>
#include <fcntl.h>
#include <math.h>
#include <assert.h>

#include <iostream>
#include <fstream>

#include "typedefs.h"
#include "timer.h"
#include "testing_data.h"
#include "digitrec.h"

//--------------------------------------
// main function
//--------------------------------------
int main()
{
  // Number of test instances
  const int N = 180;

  int nbytes;
  int error = 0;
  int interpreted_digit;

  for (int i = 0; i < N; i++)
  {
    dut((uint32_t *)&testing_data[i], &interpreted_digit);
    if (testing_label[i] != interpreted_digit)
    {
      error = error + 1;
    }
  }

  // Report overall error out of all testing instances
  std::cout << "Number of test instances = " << N << std::endl;
  std::cout << "Overall Error Rate = "
            << ((double)error / N) * 100
            << "%" << std::endl;

  return 0;
}
