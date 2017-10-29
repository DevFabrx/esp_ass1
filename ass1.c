#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <float.h>

#define TRUE 1
#define FALSE 0
#define SIDES 3
#define EXIT_SUCCESS 0
#define EXIT_ERROR 1

// Function Prototypes
int get_number_of_triangles();
float get_triangle_side_length(char*);
void get_triangle_data(float*, int);
void print_triangles(float*, int);
void sort(float [], int);
void sort_array(float* [][SIDES], int);

void sort_array(float* triangle_data[][SIDES], int
nr_of_triangles)
{
  int i;
  for(i=0; i<nr_of_triangles; i++)
  {
    printf("DEBUG: Entering sort_array.\n");
    sort(triangle_data[i], SIDES);
  }
}


//-----------------------------------------------------------------------------
///
/// Sorts an float array in increasing order
/// @param array float pointer to an float array
/// @param len length of the array
/// return void
//
void sort(float array[], int length)
{
  printf("DEBUG: Entering sort.\n");
  int i;
  int j;

  for(i=0; i < length-1; i++)
  {
    for(j=0; j < length-1; j++)
    {
      if (array[j] > array[j+1])
      {
        float tmp = array[j];
        array[j] = array[j+1];
        array[j+1] = tmp;
      }
    }
  }
}

//-----------------------------------------------------------------------------
///
/// Prints the currently stored data of the triangles
/// @param triangle_data pointer to the triangle array
/// @param size number of triangles in array
/// return void
//
void print_triangles(float* triangle_data, int size)
{
  int i;
  int j=0;
  for(i=0; i < size; i++)
  {
    if(j == 3)
    {
      printf("\n");
      j = 0;
    }
    printf("%f ",*(triangle_data+i));
    j += 1;
  }
}

//-----------------------------------------------------------------------------
///
/// Asks the user to input all data for the triangles he specified
/// @param triangle_data float pointer to the triangle data array
/// @param nr_of_triangles number of lines of the data array
///
//
void get_triangle_data(float* triangle_data, int nr_of_triangles)
{
  char* sides_array[]= {"first", "second", "third"};

  int i;
  int j;
  for (i=0; i < nr_of_triangles*SIDES; i++)
  {
    j = i%3;
    *(triangle_data+i) = get_triangle_side_length(sides_array[j]);
  }
}


//-----------------------------------------------------------------------------
///
/// Asks for the one side length of the triangle and checks if the input is
/// correct.
/// @param name char pointer of the name of the side
///
/// @return float triangle side length
//
float get_triangle_side_length(char* name)
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
/// This function asks for the number of triangles to check and also checks
/// if the input is correct.
///
/// @return int number of triangles to check
//
int get_number_of_triangles()
{
  printf("DEBUG: Entering get_number_of_triangles.\n");
  while(TRUE)
  {
    char input[] = ""; // input char pointer initialized to null
    printf("Please enter the number of triangles to check: ");
    scanf("%s", input);
    int nr_of_triangles = atoi(input);
    if (nr_of_triangles == 0 || nr_of_triangles > UCHAR_MAX )
    {
      printf("[ERR] Invalid number of triangles.\n");
      continue;
    }
    else
    {
      return nr_of_triangles;
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
/// @return always zero
//
int main()
{
  int nr_of_triangles = get_number_of_triangles();
  printf("You want to check %d triplets\n", nr_of_triangles);
  float triangle_data[nr_of_triangles][SIDES];
  int nr_of_elements = sizeof(triangle_data)/ sizeof(triangle_data[0][0]);
  get_triangle_data(triangle_data, nr_of_triangles);

  print_triangles(triangle_data, nr_of_elements);
  printf("\n________________________________\n\n");
  sort_array(triangle_data, nr_of_triangles);

  print_triangles(triangle_data, nr_of_elements);


  return EXIT_SUCCESS;
}



