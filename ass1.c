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
// Daniel Krems 00930736
//-----------------------------------------------------------------------------
//

// all needed includes
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <string.h>

// necessary defines
#define TRUE 1
#define FALSE 0
#define SIDES 3 // nr of sides of a triangle
#define EXIT_SUCCESS 0
#define RECTANGULAR " It is a right triangle.\n"
#define EQUILATERAL " It is an equilateral triangle.\n"
#define ISOSCELES " It is an isosceles triangle.\n"


// Function Prototypes
int getNumberOfTriplets();
float getTripletSideLength(char *);
void getTripletData(float (*)[SIDES], int);
void sort(float (*)[SIDES], int, int);
void analyzeAllTriplets(float (*)[SIDES], int);
void analyzeTriplet(float *);
int isRectangular(float *);
int isEquilateral(float *);
int isIsosceles(float *);
int compareFloats(float, float);

//-----------------------------------------------------------------------------
///
/// Goes through all the triplets found at the triplet_data array and checks
/// if they are triangles and if yes which type of triangle they are.
///
/// @param triplet_data pointer to the triplet array where the side lengths
/// are stored
///
/// @return void
//
void analyzeAllTriplets(float (*triplet_data)[SIDES], int nr_of_triplets)
{
  int triplet_counter;
  for(triplet_counter = 0; triplet_counter < nr_of_triplets; triplet_counter++)
  {
    printf("Triplet %d ", triplet_counter+1);
    analyzeTriplet(triplet_data[triplet_counter]);
  }
}
//-----------------------------------------------------------------------------
///
/// Checks if the data found in the triplet_data array is an rectangular
/// triangle and returns TRUE if yes and FALSE if not.
///
/// @param triplet_data pointer to the triplet array where the side lengths
/// are stored
///
/// @return int TRUE or FALSE
//
int isRectangular(float *triplet_data)
{
  float side_a = triplet_data[0];
  float side_b = triplet_data[1];
  float side_c = triplet_data[2];
  if(compareFloats(side_a * side_a + side_b * side_b, side_c * side_c))
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
int isIsosceles(float *triplet_data)
{
  float side_a = triplet_data[0];
  float side_b = triplet_data[1];
  if(compareFloats(side_a, side_b))
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
int isEquilateral(float *triplet_data)
{
  float side_a = triplet_data[0];
  float side_b = triplet_data[1];
  float side_c = triplet_data[2];
  if(compareFloats(side_a, side_b) && compareFloats(side_b, side_c))
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
/// @param first_float First float variable
/// @param second_float Second float variable
///
/// @return int TRUE or FALSE
//
int compareFloats(float first_float, float second_float)
{
  if(fabs(first_float - second_float) >= FLT_EPSILON)
  {
    return FALSE;
  }
  else
  {
    return TRUE;
  }
}

//-----------------------------------------------------------------------------
///
/// Checks if the triplet is indeed a triangle by evaluating the triangle
/// inequality. If it is a triangle it also evaluates what kind of triangle
/// it is by calling the corresponding other functions.
///
/// @param triplet_data pointer to the triplet array where the side lengths
/// are stored
///
/// @return void
//
void analyzeTriplet(float *triplet_data)
{
  float side_a = triplet_data[0];
  float side_b = triplet_data[1];
  float side_c = triplet_data[2];

  // First we need to check if the triplet is a triangle by evaluating the
  // triangle inequality formula: c <= a+b
  if(compareFloats(side_a + side_b, side_c) || fabs(side_a + side_b - side_c)
                                               < FLT_EPSILON)
  {
    printf("(a=%.6f, b=%.6f, c=%.6f) is NO triangle.\n", side_a, side_b,
           side_c);
  }
  else
  {
    // Now we evaluate the type of the triangle (equilateral, isosceles or
    // rectangular)
    printf("(a=%.6f, b=%.6f, c=%.6f) is a triangle.\n", side_a, side_b, side_c);
    if(isEquilateral(triplet_data))
    {
      printf(EQUILATERAL);
      printf(ISOSCELES);
    }
    else if(isIsosceles(triplet_data))
    {
      printf(ISOSCELES);
      if(isRectangular(triplet_data))
      {
        printf(RECTANGULAR);
      }
    }
    else if(isRectangular(triplet_data))
    {
      printf(RECTANGULAR);
    }
  }
}


//-----------------------------------------------------------------------------
///
/// Bubble sorts an 2-d float array in increasing order
/// @param triplet_data pointer to the triplet array that needs to be sorted
/// @param  number_of_triplets number of triplets (= rows) in the 2-d array
/// @param length length of the array to be sorted
/// @return void
//
void sort(float (*triplet_data)[SIDES], int number_of_triplets, int length)
{
  int triplet_counter;
  int sort_counter1;
  int sort_counter2;

  // This is the first for loop that goes through all the triplets stored in
  // the array
  for(triplet_counter = 0; triplet_counter < number_of_triplets;
      triplet_counter++)
  {
    float* data = triplet_data[triplet_counter];

    // This is the main for loop for the bubble sorting
    for(sort_counter1 = 0; sort_counter1 < length - 1; sort_counter1++)
    {
      for(sort_counter2 = 0; sort_counter2 < length - 1; sort_counter2++)
      {
        if (data[sort_counter2] > data[sort_counter2 + 1])
        {
          float temporary_clone = data[sort_counter2];
          data[sort_counter2] = data[sort_counter2 + 1];
          data[sort_counter2+1] = temporary_clone;
        }
      }
    }
  }
}


//-----------------------------------------------------------------------------
///
/// Asks the user to input all side length data for the number of triangles he
/// specified
///
/// @param triplet_data float pointer to the triplet data array
/// @param number_of_triplets number of triplets in the data array
///
/// @return void
//
void getTripletData(float (*triplet_data)[SIDES], int number_of_triplets)
{
  char* side_text[]= {"first", "second", "third"};

  int triplet_counter;
  int length_counter;
  for (triplet_counter = 0; triplet_counter < number_of_triplets;
       triplet_counter++)
  {
    for(length_counter = 0; length_counter < SIDES; length_counter++)
    {
      triplet_data[triplet_counter][length_counter] =
          getTripletSideLength(side_text[length_counter]);
    }
  }
}


//-----------------------------------------------------------------------------
///
/// Asks for the one side length of the triangle and checks if the input is
/// correct.
///
/// @param side_text Text of the triplet data( "first", "second", "third")
///
/// @return float triplet side length
//
float getTripletSideLength(char *side_text)
{

  while(TRUE)
  {
    printf("Please enter the %s number of the triplet: ", side_text);
    // Input buffer
    char input_buffer[80];
    char* line;
    line = fgets(input_buffer, 80, stdin);
    if(line == NULL)
    {
      exit(EXIT_SUCCESS);
    }
    if(!strcmp(line, "\n"))
    {
      continue;
    }

    float triplet_side_length = atof(line);

    if (triplet_side_length == 0 || triplet_side_length < 0.0 ||
        triplet_side_length > FLT_MAX)
    {
      printf("[ERR] Invalid number for the triplet.\n");
      continue;
    }
    else
    {
      return triplet_side_length;
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
    char input[80]; // input char pointer initialized to null
    printf("Please enter the number of triangles to check: ");
    char* line = fgets(input, 80, stdin);
    if(line == NULL)
    {
      exit(EXIT_SUCCESS);
    }
    if(!strcmp(line, "\n"))
    {
      continue;
    }

    int number_of_triplets = atoi(line);

    if (number_of_triplets <= 0 || number_of_triplets > UCHAR_MAX )
    {
      printf("[ERR] Invalid number of triangles.\n");
      continue;
    }
    else
    {
      return number_of_triplets;
    }
  }
}


//------------------------------------------------------------------------------
///
/// The main program.
/// Reads in the number of triangles to check and then ask to insert the
/// side lengths of the triangles and sorts them in increasing order. It then
/// checks if the given data describes an equilateral, isosceles or right
/// triangle and returns the answer on the console.
///
/// @param argc not used
/// @param argv not used
///
/// @return int always zero
//
int main()
{
  int number_of_triplets = getNumberOfTriplets();
  float triplet_data[number_of_triplets][SIDES];
  getTripletData(triplet_data, number_of_triplets);
  sort(triplet_data, number_of_triplets, SIDES);
  analyzeAllTriplets(triplet_data, number_of_triplets);

  return EXIT_SUCCESS;
}



