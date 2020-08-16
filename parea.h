#include <stdbool.h> 
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct points *Us;
typedef struct point *Point;
Us NewUs(size_t n);
size_t GetUsn(Us u);
void PrintUs(Us U);
Point GetPoint(Us U,size_t n);
double GetPointx(Us U,size_t n);
double GetPointy(Us U,size_t n);