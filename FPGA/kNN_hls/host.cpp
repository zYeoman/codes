#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <assert.h>

#include <iostream>
#include <fstream>

#include "typedefs.h"
#include "timer.h"
#include "testing_data.h"

//--------------------------------------
// main function
//--------------------------------------
int main()
{
  // Open channels to the FPGA board.
  // These channels appear as files to the Linux OS
  int fdr = open("/dev/xillybus_read_32", O_RDONLY);
  int fdw = open("/dev/xillybus_write_32", O_WRONLY);

  // Check that the channels are correctly opened
  if ((fdr < 0) || (fdw < 0))
  {
    fprintf(stderr, "Failed to open Xillybus device channels\n");
    exit(-1);
  }

  // Number of test instances
  const int N = 180;

  // Timer
  Timer timer("digitrec FPGA");

  int nbytes;
  int error = 0;
  int interpreted_digit;

  timer.start();

  for (int i = 0; i < N; i++)
  {
    uint64_t input_t = testing_data[i];
    nbytes = write(fdw, (void *)&input_t, sizeof(input_t));
    // std::cout<<"i =\t"<<i<<"\tinput size=\t"<<sizeof(input_t)<<"\tnbytes=\t"<<nbytes<<"\n";
    assert(nbytes == sizeof(input_t));
  }

  for (int i = 0; i < N; i++)
  {

    int32_t recvd_i;
    nbytes = read(fdr, (void *)&recvd_i, sizeof(recvd_i));
    // std::cout<<"i =\t"<<i<<"\trecvd size=\t"<<sizeof(recvd_i)<<"\tnbytes=\t"<<nbytes<<"\n\n";
    assert(nbytes == sizeof(recvd_i));

    if (testing_label[i] != recvd_i)
    {
      error = error + 1;
    }
  }

  timer.stop();

  // Report overall error out of all testing instances
  std::cout << "Number of test instances = " << N << std::endl;
  std::cout << "Overall Error Rate = "
            << ((double)error / N) * 100
            << "%" << std::endl;

  return 0;
}
