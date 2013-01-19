/****************************************************************************
 * log2.h
 *
 * Computer Science 50x
 * Paul Reiners
 *
 * An implementation of the Bailey–Borwein–Plouffe (BBP) formula for log(2) 
 * in binary.
 ***************************************************************************/

#ifndef LOG2_H
#define LOG2_H

char* log_2_binary(int first_place, int num_places);
int log_2_binary_p(int k);

#endif // LOG2_H

