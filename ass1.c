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
void sort_data(float*);


//-----------------------------------------------------------------------------
///
/// Asks for the one side length of the triangle and checks if the input is
/// correct.
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
  printf("You chose to calculate %d Triangles\n", nr_of_triangles);
  float triangle_data[nr_of_triangles][SIDES];

  char* sides_array[]= {"first", "second", "third"};

  int i, j;
  for (i=0; i < nr_of_triangles; i++)
  {
    for (j=0; j < SIDES; j++)
    {
      triangle_data[i][j] = get_triangle_side_length(sides_array[j]);
    }

  }

  return EXIT_SUCCESS;
}



