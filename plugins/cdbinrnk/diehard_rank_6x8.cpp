/*
* This is the BINARY RANK TEST for 6x8 matrices.  From each of  ::
* six random 32-bit integers from the generator under test, a   ::
* specified byte is chosen, and the resulting six bytes form a  ::
* 6x8 binary matrix whose rank is determined.  That rank can be ::
* from 0 to 6, but ranks 0,1,2,3 are rare; their counts are     ::
* pooled with those for rank 4. Ranks are found for 100,000     ::
* random matrices, and a chi-square test is performed on        ::
* counts for ranks 6,5 and <=4.                                 ::
*/

#include "libdieharder.hpp"
#include "vtest.hpp"

gsl_rng *rng;                  /* global gsl random number generator */

double diehard_rank_6x8(QVector<double> const &sample)
{
	rng = gsl_rng_alloc(gsl_rng_taus);
	int i = 0;
	int t = 0;
	int rank = 0;
	uint bitstring;
	Vtest vtest;

	uint **mtx;
	mtx = new uint * [6];
	for (i = 0; i < 6; i++){
		mtx[i] = new uint [8];
	}

	Vtest_create(&vtest, 7);
	vtest.cutoff = 5.0;
	for (i = 0; i < 2; i++){
		vtest.x[i] = 0.0;
		vtest.y[i] = 0.0;
	}

	vtest.x[2] = 0.0;
	vtest.y[2] = sample[1];
	vtest.x[3] = 0.0;
	vtest.y[3] = sample[2];
	vtest.x[4] = 0.0;
	vtest.y[4] = sample[3];
	vtest.x[5] = 0.0;
	vtest.y[5] = sample[4];
	vtest.x[6] = 0.0;
	vtest.y[6] = sample[5];
	
	double r = 0;
	for (t = 0; t < 6; t++) {

		/*
		 * We generate 6 random rmax_bits-bit integers and put a
		 * randomly chosen byte into the LEFTMOST byte position
		 * of the row/slot of mtx.
		 */
		for (i = 0; i < 6; i++){
			bitstring = get_rand_bits_uint(32, 0xffffffff, rng);
			mtx[i][0] = bitstring;
		}

		rank = binary_rank(mtx, 6, 8);
		r += rank;
		//MYDEBUG(D_DIEHARD_RANK_6x8){
		// printf("binary rank = %d\n", rank);
		//}

		if (rank <= 2) {
			vtest.x[2]++;
		}
		else {
			vtest.x[rank]++;
		}
	}

	Vtest_eval(&vtest);
	int result = vtest.pvalue;

	Vtest_destroy(&vtest);

	for (i = 0; i < 6; i++) {
		delete [] mtx[i];
	}
	delete [] mtx;
	gsl_rng_free(rng);

	return r / 6.0 ;
}