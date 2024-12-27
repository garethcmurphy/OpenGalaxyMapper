#include <headers.h>
/*
how to determine the Extinction from the output files from the star counting
*/
#define DEPTH 71
#define HEIGHT 180
#define WIDTH 180
#define LARGE_ARRAY_SIZE 540
#define PLANE_P 55
#define ARR_SIZE 200
int
main (int argc, char *argv[])
{
  float        ***OriginalBox;
  float         **Extinction;
  float        ***smooth;
  float        ***OriginalSmallBox;
  int             ii, jj, kk, aa, bb, plane;
  float           Extinction_float;
  float           minimum;
  float           dx;
  float           dy;
  float           dx1;
  float           dy1;
  float           average;
  float           sum;
  float           diff;
  float           longtitude = 0;
  float           latitude = 0;
  float           temp = 0;
  ifstream        fin;
  ofstream        fout;
  ifstream        inFile;
  ifstream        examplefile;
  ofstream        outFile ("output/output.dat");
  int             rc = 0;
  int             myrank = 0;
  int             numprocs = 0;
  char            inputdir[50] = "input/";
  char            outputdir[50] = "output/";
  char            filename[50] = "psc_K_";
  stringstream    s;
  stringstream    stream_filename;
  stringstream    stream_temp_b;
  string          str_file_tag;
  string          str_output_filename;
  string          str_input_filename;

  rc = MPI_Init (&argc, &argv);
  rc |= MPI_Comm_rank (MPI_COMM_WORLD,	/* always use this */
		       &myrank);	/* process rank, 0 thru N-1 */
  rc |= MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
  if (rc != 0)
    printf ("\nFailed to begin MPI\n");

/* at first we have to read in the output file that we are interested in and also the surrounding eight fields, in order to ensure we can properly determine the running average. We are interested in the field (x,y).  */
/* create an array able to store the nine fields OriginalBox = ARRAY (LARGE_ARRAY_SIZE, LARGE_ARRAY_SIZE, DEPTH); */
/* loop over all 9000 output files and read in their first line to check if this file is one of the nine we need.                                   */


  OriginalBox = ThreeDim (LARGE_ARRAY_SIZE, LARGE_ARRAY_SIZE, DEPTH);



  for (ii = 1; ii < 10; ii++)
     {

       s.clear ();
       s.width (5);
       s.fill ('0');
       s << ii;
       cout << ii << endl;
       s >> str_file_tag;
       stream_filename.clear ();
       stream_filename << inputdir << filename << str_file_tag;
       stream_filename >> str_input_filename;
       cout << str_input_filename << "\n";
       inFile.clear ();
       inFile.open (str_input_filename.c_str ());
       if (!inFile)
	  {
	    cerr << "Unable to open file" << endl;
	  }
       inFile >> longtitude >> latitude;
       outFile << longtitude << "\t" << latitude << endl;
       for (kk = 0; kk < HEIGHT; kk++)
	  {
	    for (jj = 0; jj < HEIGHT; jj++)
	       {
		 for (plane = 0; plane < DEPTH; plane++)
		    {
		      switch (ii)
			 {
			 case 1:
			   inFile >> OriginalBox[kk][jj][plane];
			   outFile << OriginalBox[kk][jj][plane] << " ";
			   break;
			 case 2:
			   inFile >> OriginalBox[kk + HEIGHT][jj][plane];
			   outFile << OriginalBox[kk + HEIGHT][jj][plane] << " ";
			   break;
			 case 3:
			   inFile >> OriginalBox[kk + 2 * HEIGHT][jj][plane];
			   outFile << OriginalBox[kk +
					       2 * HEIGHT][jj][plane] << " ";
			   break;
			 case 4:
			   inFile >> OriginalBox[kk][jj + HEIGHT][plane];
			   outFile << OriginalBox[kk][jj + HEIGHT][plane] << " ";
			   break;
			 case 5:
			   inFile >> OriginalBox[kk + HEIGHT][jj +
							   HEIGHT][plane];
			   outFile << OriginalBox[kk + HEIGHT][jj +
							    HEIGHT][plane] <<
			     " ";
			   break;
			 case 6:
			   inFile >> OriginalBox[kk + 2 * HEIGHT][jj +
							       HEIGHT][plane];
			   outFile << OriginalBox[kk + 2 * HEIGHT][jj +
								HEIGHT][plane]
			     << " ";
			   break;
			 case 7:
			   inFile >> OriginalBox[kk][jj + 2 * HEIGHT][plane];
			   outFile << OriginalBox[kk][jj +
						   2 * HEIGHT][plane] << " ";
			   break;
			 case 8:
			   inFile >> OriginalBox[kk + HEIGHT][jj +
							   2 * HEIGHT][plane];
			   outFile << OriginalBox[kk + HEIGHT][jj +
							    2 *
							    HEIGHT][plane] <<
			     " ";
			   break;
			 case 9:
			   inFile >> OriginalBox[kk + 2 * HEIGHT][jj +
							       2 *
							       HEIGHT][plane];
			   outFile << OriginalBox[kk + 2 * HEIGHT][jj +
								2 *
								HEIGHT][plane]
			     << " ";
			   break;

			 }
		    }
		 outFile << "\n";
	       }
	    outFile << "\n\n";
	  }
/* 
Need to replace this with file close
*/
       //      inFile.clear ();
       inFile.close ();
     }
/* create an array that contains the smoothed inner field and one containing
the OriginalBox field.
*/
  OriginalSmallBox = ThreeDim (HEIGHT, HEIGHT, DEPTH);

  for (plane = 0; plane < DEPTH; plane++)
     {
       for (jj = 0; jj < HEIGHT; jj++)
	  {
	    for (kk = 0; kk < HEIGHT; kk++)
	       {
		 OriginalSmallBox[jj][kk][plane] =
		   OriginalBox[jj + HEIGHT][kk + HEIGHT][plane];
	       }
	  }
     }

/* Now we determine the running average for the star counts for all DEPTH planes
in the central field. the average is determined in fields with size dx and
dy.
*/

  smooth = ThreeDim (HEIGHT, HEIGHT, DEPTH);
  for (plane = 0; plane < DEPTH; plane++)
     {
       for (jj = 0; jj < HEIGHT; jj++)
	  {
	    for (kk = 0; jj < HEIGHT; jj++)
	       {
		 /* dx has to be corrected for the declination
		  */
		 /* if we make the loop with k the outer loop we save time since we have
		    to determine dx1 only after a change in k
		  */
		 dx1 = dx / (cos (jj + (kk - HEIGHT + 1) / HEIGHT));	/* Degrees!!! */
		 /* We need to sum up the values in the box +-dx1/2 and +-dy/2 arround the
		    pixel (j,k)
		  */
		 sum = 0.0;
		 for (aa = (jj - dx1 / 2); aa < (jj + dx1 / 2); aa++)
		    {
		      for (bb = (kk - dy / 2); bb < (kk + dy / 2); bb++)
			 {
			   sum = sum + OriginalBox[aa][bb][plane];
			 }
		    }
		 /* and determine the average
		  */
		 average = sum / (dx1 * dy);
		 /* and write the the average for the pixel (j,k) into the array smooth
		  */
		 smooth[jj][kk][plane] = average;
	       }
	  }
     }

  free (OriginalBox);
/* now we determine the Extinction. The Extinction is determined actually just
for one plane (p) but in principle we could do this for all planes by a for
*/
/* create an array containing the the Extinction values
*/
/* determine the Extinction
*/
  Extinction = TwoDim (HEIGHT, HEIGHT);

  for (jj = 0; jj < HEIGHT; jj++)
     {
       for (kk = 0; kk < HEIGHT; kk++)
	  {
	    minimum = 999999.9;
	    Extinction_float = 0.0;
	    for (plane = DEPTH; plane > 1; plane--)
	       {
		 diff =
		   fabs (OriginalSmallBox[jj][kk][PLANE_P] - smooth[jj][kk][plane]);
		 if (diff < minimum)
		    {
		      minimum = diff;
		      Extinction_float = (PLANE_P - plane) / 10.;
		    }
	       }

	    /* write the Extinction value into the array
	     */
	    Extinction[jj][kk] = Extinction_float;
//        cout << jj << kk << Extinction;
	  }
     }

/* and now justwrite out the Extinction array into a file. as first line again
the coordinates (x,y)
*/
  free (Extinction);
  free (OriginalSmallBox);
  free (smooth);
  MPI_Finalize ();

  return 0;
}
