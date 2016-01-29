#include "ThreeDim.h"

float ***
ThreeDim (int nrow, int ncol, int ndep)
{
  int i;
  float ***m;
  int j;

  if ((m = (float ***) malloc ((size_t) (nrow * sizeof (float **)))) == NULL)
    {
      cout << "Could not allocate Memory";
      exit (EXIT_FAILURE);
    }
  if ((m[0] =
       (float **) malloc ((size_t) ((nrow * ncol) * sizeof (float *)))) ==
      NULL)
    {
      cout << "Could not allocate Memory";
      exit (EXIT_FAILURE);
    }
  if ((m[0][0] =
       (float *) malloc ((size_t) ((nrow * ncol * ndep) * sizeof (float)))) ==
      NULL)
    {
      cout << "Could not allocate Memory";
      exit (EXIT_FAILURE);
    }
  for (j = 1; j < ncol; j++)
    m[0][j] = m[0][j - 1] + ndep;
  for (i = 1; i < nrow; i++)
    {
      m[i] = m[i - 1] + ncol;
      m[i][0] = m[i - 1][0] + ncol * ndep;
      for (j = 1; j < ncol; j++)
	m[i][j] = m[i][j - 1] + ndep;
    }
  return m;
}
