//-----------------------------------------------------------------------------
// ass1.c
//
// This program reads in some possible triangular side lengths from the user
// and then checks this data and prints out whether or not it is an
// triangle and if yes, what kind of triangle it is (equilateral, isosceles,
// rectangular).
//
// Group: Group 10, study assistant David Bidner
//
// Authors: Fabian Obermayer 01131905
// Daniel Krems <Matriculum Number>
//-----------------------------------------------------------------------------
//

// all needed includes
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

// necessary defines
#define TRUE 1
#define FALSE 0
#define SIDES 3 // nr of sides of a triangle
#define EXIT_SUCCESS 0


// Function Prototypes
int getNumberOfTriplets();
float getTripletSideLength(char *);
void getTripletData(float (*)[SIDES], int);
//void printTripletData(float (*)[SIDES], int); // for DEBUG purposes
void sort(float (*)[SIDES], int, int);
void checkTriplets(float (*)[SIDES], int);
void checkIfTriangle(float *);
int checkIfRectangular(float *);
int checkIfEquilateral(float *);
int checkIfIsosceles(float *);
int isEqual(float, float);

//-----------------------------------------------------------------------------
///
/// Goes through all the triplets found at the triplet_data array and checks
/// if they are triangles and if yes which type of triangle they are.
/// @param triplet_data pointer to the triplet array where the side lengths
/// are stored
/// @return void
//
void checkTriplets(float (*triplet_data)[SIDES], int nr_of_triplets)
{
  int i;
  for(i=0; i<nr_of_triplets; i++)
  {
    printf("Triplet %d ", i+1);
    checkIfTriangle(triplet_data[i]);
  }
}
//-----------------------------------------------------------------------------
///
/// Checks if the data found in the triplet_data array is an rectangular
/// triangle and returns TRUE if yes and FALSE if not.
/// @param triplet_data pointer to the triplet array where the side lengths
/// are stored
/// @return int TRUE or FALSE
//
int checkIfRectangular(float* triplet_data)
{
  float a = triplet_data[0];
  float b = triplet_data[1];
  float c = triplet_data[2];
  if(isEqual(a * a + b * b, c * c))
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

//-----------------------------------------------------------------------------
///
/// Checks if the data found in the triplet_data array is an isosceles
/// triangle and returns TRUE if yes and FALSE if not.
/// @param triplet_data pointer to the triplet array where the side lengths
/// are stored
/// @return int TRUE or FALSE
//
int checkIfIsosceles(float *triplet_data)
{
  float a = triplet_data[0];
  float b = triplet_data[1];
  if(isEqual(a, b))
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}
//-----------------------------------------------------------------------------
///
/// Checks if the data found in the triplet_data array is an equilateral
/// triangle and returns TRUE if yes and FALSE if not.
/// @param triplet_data pointer to the triplet array where the side lengths
/// are stored
/// @return int TRUE or FALSE
//
int checkIfEquilateral(float *triplet_data)
{
  float a = triplet_data[0];
  float b = triplet_data[1];
  float c = triplet_data[2];
  if(isEqual(a, b) && isEqual(b, c))
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}
//-----------------------------------------------------------------------------
///
/// Compares two float variables and returns TRUE if they are equal or FALSE
/// if they are unequal
/// @param a First float variable
/// @param b Second float variable
/// @return int TRUE or FALSE
//
int isEqual(float a, float b)
{
  if(fabs(a-b) >= FLT_EPSILON)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

//-----------------------------------------------------------------------------
///
/// Checks if the triplet is indeed an triangle by evaluating the triangle
/// inequality. If it is a triangle it also evaluates what kind of triangle
/// it is by calling other functions.
/// @param triplet_data pointer to the triplet array where the side lengths
/// are stored
/// @return void
//
void checkIfTriangle(float *triplet_data)
{
  float a = triplet_data[0];
  float b = triplet_data[1];
  float c = triplet_data[2];

  if(isEqual(a + b, c) || fabs(a+b-c)<FLT_EPSILON)
  {
    printf("(a=%.6f, b=%.6f, c=%.6f) is NO triangle.\n", a, b, c);
  }
  else
  {
    printf("(a=%.6f, b=%.6f, c=%.6f) is a triangle.\n", a, b, c);
    if(checkIfEquilateral(triplet_data))
    {
      printf(" It is an equilateral triangle.\n");
      printf(" It is an isosceles triangle.\n");
    }
    else if(checkIfIsosceles(triplet_data))
    {
      printf(" It is an isosceles triangle.\n");
      if(checkIfRectangular(triplet_data))
      {
        printf(" It is a right triangle.\n");
      }
    }
    else if(checkIfRectangular(triplet_data))
    {
      printf(" It is a right triangle.\n");
    }

  }
}


//-----------------------------------------------------------------------------
///
/// Bubble sorts an 2-d float array in increasing order
/// @param triplet_data pointer to the triplet array that needs to be sorted
/// @param  nr_of_triplets number of triplets (= rows) in the 2-d array
/// @param length length of the array to be sorted
/// @return void
//
void sort(float (*triplet_data)[SIDES], int nr_of_triplets, int length)
{
  int k;
  int i;
  int j;
  for(k=0; k<nr_of_triplets; k++)
  {
    float* data_row = triplet_data[k];
    for(i=0; i < length-1; i++)
    {
      for(j=0; j < length-1; j++)
      {
        if (data_row[j] > data_row[j+1])
        {
          float tmp = data_row[j];
          data_row[j] = data_row[j+1];
          data_row[j+1] = tmp;
        }
      }
    }
  }
}


//-----------------------------------------------------------------------------
///
/// Prints the currently stored triplet data for DEBUG purposes
/// @param triplet_data pointer to the triplet array
/// @param nr_of_triplets number of triangles in array
/// @return void
//
void printTripletData(float (*triplet_data)[SIDES], int nr_of_triplets)
{
  int i;
  int j;
  for(i=0; i < nr_of_triplets; i++)
  {
    printf("Triplet %d: ", i+1);
    for(j=0; j < SIDES; j++)
    {
      printf("%f ", triplet_data[i][j]);
    }
    printf("\n");
  }
}


//-----------------------------------------------------------------------------
///
/// Asks the user to input all side length data for the number of triangles he
/// specified
/// @param triplet_data float pointer to the triangle data array
/// @param nr_of_triplets number of elements in the data array
///
//
void getTripletData(float (*triplet_data)[SIDES], int nr_of_elements)
{
  char* sides_array[]= {"first", "second", "third"};

  int i;
  int j;
  for (i=0; i < nr_of_elements; i++)
  {
    for(j=0; j<SIDES; j++)
    {
      triplet_data[i][j] = getTripletSideLength(sides_array[j]);
    }
  }
}


//-----------------------------------------------------------------------------
///
/// Asks for the one side length of the triangle and checks if the input is
/// correct.
/// @param name char pointer of the name of the side
///
/// @return float triplet side length
//
float getTripletSideLength(char *name)
{

  while(TRUE)
  {
    printf("Please enter the %s number of the triplet: ", name);
    char input[] = "";
    scanf("%s", input);
    float triangle_side_length = atof(input);
    if (triangle_side_length == 0 || triangle_side_length < 0.0 ||
        triangle_side_length > FLT_MAX)
    {
      printf("[ERR] Invalid number for the triplet.\n");
      continue;
    }
    else
    {
      return triangle_side_length;
    }
  }
}


//-----------------------------------------------------------------------------
///
/// This function asks for the number of triplets to check and also checks
/// if the input is correct.
///
/// @return int number of triplets
//
int getNumberOfTriplets()
{
  while(TRUE)
  {
    char input[] = ""; // input char pointer initialized to null
    printf("Please enter the number of triangles to check: ");
    scanf("%s", input);
    int nr_of_triplets = atoi(input);
    if (nr_of_triplets == 0 || nr_of_triplets > UCHAR_MAX )
    {
      printf("[ERR] Invalid number of triangles.\n");
      continue;
    }
    else
    {
      return nr_of_triplets;
    }
  }
}


//------------------------------------------------------------------------------
///
/// The main program.
/// Reads in the number of triangles to check and then ask to insert the
/// side lengths of the triangles. It then checks if the given data describes
/// an equilateral, isosceles or right triangle and returns the answer on the
/// console output.
///
/// @param argc not used
/// @param argv not used
///
/// @return int always zero
//
int main()
{
  int nr_of_triplets = getNumberOfTriplets();
  float triplet_data[nr_of_triplets][SIDES];
  getTripletData(triplet_data, nr_of_triplets);

  sort(triplet_data, nr_of_triplets, SIDES);

  //printTripletData(triplet_data, nr_of_triplets);
  checkTriplets(triplet_data, nr_of_triplets);

  return EXIT_SUCCESS;
}



