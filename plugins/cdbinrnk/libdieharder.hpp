/**
* @file   libdieharder.hpp
* @Author ATetiukhin
* @date   January, 2015
* @brief  Method cdbinrnk.
*/

#ifndef LIBDIEHARDER_HPP_INCLUDE
#define LIBDIEHARDER_HPP_INCLUDE

#include <QVector>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
#include <gsl/gsl_sf.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_heapsort.h>
#include <gsl/gsl_sort.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_eigen.h>

typedef unsigned int uint;

const unsigned int rmax_bits = 32;   /* Number of valid bits in rng */

double diehard_rank_6x8(QVector<double> const &sample);

uint get_rand_bits_uint(uint nbits, uint mask, gsl_rng *rng);

int binary_rank(unsigned int **mtx, int mrows, int ncols);

#endif