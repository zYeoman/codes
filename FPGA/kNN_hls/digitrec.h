//===========================================================================
// digitrec.h
//===========================================================================
// @brief: This header file defines the interface for the core functions.

#ifndef DIGITREC_H
#define DIGITREC_H

#include "typedefs.h"
#include "training_data.h"

// The K_CONST value: number of nearest neighbors
#define K_CONST 3

// Design under test
void dut( uint32_t * data_in, int * data_out);

// Top function for digit recognition
int digitrec( uint64_t input );

// Given the testing instance and a (new) training instance,
// this function is expected to maintain/update an array of
// K minimum distances per training set
void update_knn( uint64_t test_inst, uint64_t train_inst, int min_distances[K_CONST] );

// Among 10xK minimum distance values, this function finds 
// the actual K nearest neighbors and determine the final 
// output based on the most common digit represented by these
// nearest neighbors (i.e., a vote among KNNs). 
int knn_vote( int min_distances[10][K_CONST] );

#endif
