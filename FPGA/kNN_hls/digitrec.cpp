//==========================================================================
//digitrec.cpp
//==========================================================================
// @brief: A k-nearest-neighbor implementation for digit recognition (k=1)

#include "digitrec.h"
#include "ap_int.h"

//----------------------------------------------------------
// Digitrec
//----------------------------------------------------------
// @param[in] : input - the testing instance
// @return : the recognized digit (0~9)

void dut( uint32_t * data_in, int32_t * data_out) {
#pragma HLS interface axis port=data_in
#pragma HLS interface axis port=data_out
#pragma HLS interface ap_ctrl_none port=return

  uint64_t image;
  int32_t digit;
  uint32_t tmp;

  // Handle input data
  tmp = *data_in++; // L
  image = *data_in++; // H
  image = image << 32;
  image |= tmp;

  digit = digitrec(image);
  *data_out++ = digit;
}

int digitrec( uint64_t input )
{
  #include "training_data.h"

  // This array stores K minimum distances per training set
  int knn_set[10][K_CONST];

  // Initialize the knn set
  for ( ap_uint<4> i = 0; i < 10; i++ )
    for ( ap_uint<2> k = 0; k < K_CONST; k++ )
      // Note that the max distance is 49
      knn_set[i][k] = 50;

  for ( ap_uint<11> i = 0; i < TRAINING_SIZE; i++ ) {
#pragma HLS PIPELINE II=1
    for ( ap_uint<4> j = 0; j < 10; j++ ) {
      // Read a new instance from the training set
      uint64_t training_instance = training_data[j][i];
      // Update the KNN set
      update_knn( input, training_instance, knn_set[j] );
    }
  }

  // Compute the final output
  return knn_vote( knn_set );
}

//-----------------------------------------------------------------------
// update_knn function
//-----------------------------------------------------------------------
// Given the test instance and a (new) training instance, this
// function maintains/updates an array of K minimum
// distances per training set.

// @param[in] : test_inst - the testing instance
// @param[in] : train_inst - the training instance
// @param[in/out] : min_distances[K_CONST] - the array that stores the current
//                  K_CONST minimum distance values per training set

void update_knn( uint64_t test_inst, uint64_t train_inst, int min_distances[K_CONST] )
{
  // Compute the Manhattan distance
  uint64_t diff = test_inst ^ train_inst;

  int dist = 0;
  // Count the number of set bits
  for ( ap_uint<6> i = 0; i < 49; i++ ) {
	  dist += diff & 0x0000000000000001;
	  diff = diff >> 1;
  }

  // -----------------------------
  // YOUR CODE GOES HERE
  // -----------------------------
  //brute-force
  int maximum_dist = 0;
  int maximum_pos = 0;
  for (ap_uint<2> i = 0; i < K_CONST; i++) {
    if (min_distances[i] >= maximum_dist) {
      maximum_dist = min_distances[i];
      maximum_pos = i;
    }
  }
  if (dist < maximum_dist) {
    min_distances[maximum_pos] = dist;
  }

}


//-----------------------------------------------------------------------
// knn_vote function
//-----------------------------------------------------------------------
// Given 10xK minimum distance values, this function
// finds the actual K nearest neighbors and determines the
// final output based on the most common digit represented by
// these nearest neighbors (i.e., a vote among KNNs).
//
// @param[in] : knn_set - 10xK_CONST min distance values
// @return : the recognized digit
//

int knn_vote( int knn_set[10][K_CONST] )
{
  // -----------------------------
  // YOUR CODE GOES HERE
  // -----------------------------
	  //brute-force
	  int maximum_dist = 50;
	  int maximum_pos = 0;
	  int knn[K_CONST];
	  int vote[K_CONST];
	  for (ap_uint<2> i = 0; i < K_CONST; i++) {
	    knn[i] = 50;
	    vote[i] = -1;
	  }
	  for (ap_uint<4> i = 0; i < 10; i++) {
	    for (ap_uint<2> j = 0; j < K_CONST; j++) {
	      if (knn_set[i][j] < maximum_dist) {
	        knn[maximum_pos] = knn_set[i][j];
	        vote[maximum_pos] = i;
	        maximum_dist = knn_set[i][j];
	        for (int k = 0; k < K_CONST; k++) {
	          if (knn[k] >= maximum_dist) {
	            maximum_dist = knn[k];
	            maximum_pos = k;
	          }
	        }
	      }
	    }
	  }
	  int major[10];
	  int distance_sum[10];
	  for (int i = 0; i < 10; i++) {
	    major[i] = 0;
	    distance_sum[i] = 0;
	  }
	  int maximum = 0;
	  int result = -1;
	  for (ap_uint<2> i = 0; i < K_CONST; i++) {
	    major[vote[i]]++;
	    distance_sum[vote[i]] += knn[i];
	    if (major[vote[i]] > maximum) {
	      maximum = major[vote[i]];
	      result = vote[i];
	    } else if (major[vote[i]] == maximum &&
	       distance_sum[vote[i]] < distance_sum[result]) {
	      maximum = major[vote[i]];
	      result = vote[i];
	    }
	  }
	  return result;

}

