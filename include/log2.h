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

/*
 * Function:  log_2_binary 
 * --------------------
 * Computes the log(2) binary BBP formula.
 * It is the responsibility of the calling function to free the returned string.
 *
 *  d: binary digit to be calculated
 *  num_places: how many binary places to calculate
 *
 *  returns: the dth binary digit of log(2) (plus num_places - 1 more places)
 */
char* log_2_binary(int d, int num_places);

/*
 * Function:  log_2_binary_p 
 * --------------------
 * The polynomial p used for the log(2) BBP formula
 *
 *  k: input to the polynomial p
 *
 *  returns: p(k)
 */
int log_2_binary_p(int k);

#endif // LOG2_H

