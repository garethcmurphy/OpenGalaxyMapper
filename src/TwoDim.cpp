#include "TwoDim.h"
float **
TwoDim (int nrow, int ncol)
{
  float **m;
  int i;

  m = (float **) malloc ((size_t) (nrow * sizeof (float *)));
  m[0] = (float *) malloc ((size_t) ((nrow * ncol) * sizeof (float)));

  for (i = 1; i < nrow; i++)
    m[i] = m[i - 1] + ncol;

  return m;
}
