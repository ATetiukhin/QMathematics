 /*
  * This is the struct used in vtest.cpp, a standard Pearson's chisq
  * test on a vector of measurements and corresponding expected
  * mean values.
  */
 typedef struct {
   unsigned int nvec;  /* Length of x,y vectors */
   unsigned int ndof;  /* Number of degrees of freedom, default nvec-1 */
   double cutoff;      /* y has to be greater than this to be included */
   double *x;          /* Vector of measurements */
   double *y;          /* Vector of expected values */
   double chisq;       /* Resulting Pearson's chisq */
   double pvalue;      /* Resulting p-value */
 } Vtest;

 void Vtest_create(Vtest *vtest, unsigned int nvec);
 void Vtest_destroy(Vtest *vtest);
 void Vtest_eval(Vtest *vtest);