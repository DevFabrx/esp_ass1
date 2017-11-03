//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
//


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
#define INVALID_INPUT -1
#define BUFFERSIZE 20
// Text defines for multiple text usages
#define RECTANGULAR "  It is a right triangle.\n"
#define EQUILATERAL "  It is an equilateral triangle.\n"
#define ISOSCELES "  It is an isosceles triangle.\n"
#define ERROR_NUMBER_OF_TRIANGLES "[ERR] Invalid number of triangles.\n"
#define ERROR_TRIPLET_NUMBER "[ERR] Invalid number for the triplet.\n"


// Function Prototypes
int getNumberOfTriplets();
float getTripletSideLength(char *);
int getTripletData(float (*)[SIDES], int);
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
    printf("Triplet %d ", triplet_counter + 1);
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
  // triangle inequality formula: c <= a+b and make sure that
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
  int sort_count;
  int sort_count2;

  // This is the first for loop that goes through all the triplets stored in
  // the array
  for(triplet_counter = 0; triplet_counter < number_of_triplets;
      triplet_counter++)
  {
    float* data = triplet_data[triplet_counter];

    // The main for loop for the bubble sorting algorithm
    for(sort_count = 0; sort_count < length - 1; sort_count++)
    {
      for(sort_count2 = 0; sort_count2 < length - sort_count - 1; sort_count2++)
      {
        if (data[sort_count2] > data[sort_count2 + 1])
        {
          float temporary_clone = data[sort_count2];
          data[sort_count2] = data[sort_count2 + 1];
          data[sort_count2+1] = temporary_clone;
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
/// @return int INVALID_INPUT if invalid input or 1 if successful
//
int getTripletData(float (*triplet_data)[SIDES], int number_of_triplets)
{
  char* side_text[]= {"first", "second", "third"};

  int triplet_counter;
  int length_counter;
  for (triplet_counter = 0; triplet_counter < number_of_triplets;
       triplet_counter++)
  {
    for(length_counter = 0; length_counter < SIDES; length_counter++)
    {
      float side_length = getTripletSideLength(side_text[length_counter]);
      if((int)side_length == -1)
      {
        return INVALID_INPUT;
      }
      triplet_data[triplet_counter][length_counter] = side_length;
    }
  }
  return 1;
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
  // Input loop
  while(TRUE)
  {
    printf("Please enter the %s number of the triplet: ", side_text);
    char input_buffer[BUFFERSIZE];
    char* line;
    line = fgets(input_buffer, BUFFERSIZE, stdin);
    // if fgets returns NULL, EOF or error occurred and so we need to end the
    // program
    if(line == NULL)
    {
      return INVALID_INPUT;
    }
    // If the input exceeds the buffer size of the input, we need to read the
    // overflowing data so that it is not inserted in the next input
    if((strchr(line, '\n') == NULL))
    {
      char clear_stdin;
      while((clear_stdin = fgetc(stdin) != '\n' && clear_stdin != EOF));
      printf(ERROR_TRIPLET_NUMBER);
      continue;
    }
    // If input is just \n the promp will show again
    if(!strcmp(line, "\n"))
    {
      continue;
    }

    float triplet_side_length = atof(line);
    // Check if input data is valid
    if ( compareFloats(triplet_side_length, 0.0) || triplet_side_length < 0.0 ||
        triplet_side_length > FLT_MAX)
    {
      printf(ERROR_TRIPLET_NUMBER);
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
    char input[BUFFERSIZE];
    printf("Please enter the number of triangles to check: ");
    char* line = fgets(input, BUFFERSIZE, stdin);
    if(line == NULL)
    {
      return INVALID_INPUT;
    }
    // If the input exceeds the buffer size of the input, we need to read the
    // overflowing data so that it is not inserted in the next input
    if((strchr(line, '\n') == NULL))
    {
      char clear_stdin;
      while((clear_stdin = fgetc(stdin) != '\n' && clear_stdin != EOF));
      printf(ERROR_NUMBER_OF_TRIANGLES);
      continue;
    }

    if(!strcmp(line, "\n"))
    {
      continue;
    }

    int number_of_triplets = atoi(line);

    if (number_of_triplets <= 0 || number_of_triplets > UCHAR_MAX )
    {
      printf(ERROR_NUMBER_OF_TRIANGLES);
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
  if(number_of_triplets == INVALID_INPUT)
  {
    return EXIT_SUCCESS;
  }
  float triplet_data[number_of_triplets][SIDES];
  int get_triplet_response = getTripletData(triplet_data, number_of_triplets);
  if(get_triplet_response == INVALID_INPUT)
  {
    return EXIT_SUCCESS;
  }
  sort(triplet_data, number_of_triplets, SIDES);
  analyzeAllTriplets(triplet_data, number_of_triplets);

  return EXIT_SUCCESS;
}



