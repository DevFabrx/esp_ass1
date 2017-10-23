#include <stdio.h>

#define True 1
#define False 0
#define Hansi "Hansi ist cool"
#define TRIANGSIDES 3

int main() {

    int numer_of_triangles;
    printf("Please enter the number of triangles to check: ");
    scanf("%d", &numer_of_triangles);
    float triangle_data[numer_of_triangles][TRIANGSIDES];


    int i;
    char *sides_array[]= {"first", "second", "third"};
    for (i=0; i < numer_of_triangles; i++)
    {
        int j;
        for (j=0; j < 3; j++)
        {
            printf("Please enter the %s number of the triplet: ",
                   sides_array[j]);
            scanf("%f", &triangle_data[i][j]);

        }
    }


    return 0;
}