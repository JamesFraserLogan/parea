#include "parea.h"
#define MAX 10
size_t inside_unit_circle_count(Us U);
int main(void)
{
    int i=100000000;
    Us U = NewUs(i);
    printf("%lf\n",4.0*(double)inside_unit_circle_count(U)/(double)i);
    return 0;
}
size_t inside_unit_circle_count(Us U)
{
    size_t count=0;
    size_t n = GetUsn(U);
    printf("n is %zu.\n",n);
    for(size_t i=0;i<n;i++)
    {
        double x=GetPointx(U,i);
        double y=GetPointy(U,i);
        if(((x*x)+(y*y)) <= 1.0)
        {
            count++;
        }
    }
    return count;
}