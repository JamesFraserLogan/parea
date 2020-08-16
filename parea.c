#include "parea.h"
typedef struct point
{
    double x;
    double y;
}point;
typedef struct points
{
    size_t n;
    point **a;
}points;
static void del_point(point *p);
static void del_points(points *p);
static point *get_point(points *p,size_t n);
static size_t get_n(points *p);
static double get_x(point *p);
static double get_y(point *p);
static point *new_point(void);
static points *new_points(size_t n);
// Only works for positive integers right now
static double *normalize(int *a,size_t n);
static void print_point(point *p);
static void set_point(point *p,double x,double y);
static void set_points(points *p,size_t n,double x,double y);

size_t GetUsn(Us U)
{
    return get_n(U);
}
Point GetPoint(Us U,size_t n)
{
    return get_point(U,n);
}
double GetPointx(Us U,size_t n)
{
    return get_x(get_point(U,n));
}
double GetPointy(Us U,size_t n)
{
    return get_y(get_point(U,n));
}
Us NewUs(size_t n)
{
    points *ret = new_points(n);
    srand(time(NULL));
    int max, min;
    int *x=calloc(n,sizeof(int));
    if(x==NULL)
    {
        fprintf(stderr,"Error: calloc returned NULL for x in NewUs.\n");
        exit(EXIT_FAILURE);
    }
    int *y=calloc(n,sizeof(int));
    if(y==NULL)
    {
        fprintf(stderr,"Error: calloc returned NULL for y in NewUs.\n");
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));
    for(size_t i=0;i<n;i++)
    {
        x[i]=rand();
        y[i]=rand();
    }
    double *v=normalize(x,n);
    double *w=normalize(y,n);
    for(size_t i=0;i<n;i++)
    {
        set_points(ret,i,v[i],w[i]);
    }
    for(size_t i=0;i<n;i++)
    {
        v[i]=0;
        w[i]=0;
        x[i]=0;
        y[i]=0;
    }
    free(v);
    free(w);
    free(x);
    free(y);
    return ret;
}
void PrintUs(Us U)
{
    for(size_t i=0;i<U->n;i++)
    {
        print_point(U->a[i]);
    }
}



static void del_point(point *p)
{
    if(p==NULL)
    {
        fprintf(stderr,"Error: input is NULL for del_point.\n");
        exit(EXIT_FAILURE);
    }
    p->x=0;
    p->y=0;
    free(p);
}
static void del_points(points *p)
{
    if(p==NULL)
    {
        fprintf(stderr,"Error: input is NULL for del_points.\n");
        exit(EXIT_FAILURE);
    }
    for(size_t i=0;i<p->n;i++)
    {
        p->a[i]->x=0;
        p->a[i]->y=0;
        free(p->a[i]);
    }
    free(p);
}
static point *get_point(points *p,size_t n)
{
    if(p==NULL)
    {
        fprintf(stderr,"Error: input points is NULL for get_point.\n");
        exit(EXIT_FAILURE);
    }
    if(n>SIZE_MAX||n<0)
    {
        fprintf(stderr,"Error: input size out of range in get_point.\n");
        exit(EXIT_FAILURE);
    }
    if(n>=p->n)
    {
        fprintf(stderr,"Error: n out of valid range in get_point.\n");
        exit(EXIT_FAILURE);
    }
    return p->a[n];
}
static size_t get_n(points *p)
{
    if(p==NULL)
    {
        fprintf(stderr,"Error: input is NULL for get_n.\n");
        exit(EXIT_FAILURE);
    }
    return p->n;
}
static double get_x(point *p)
{
    if(p==NULL)
    {
        fprintf(stderr,"Error: input is NULL for get_x.\n");
        exit(EXIT_FAILURE);
    }
    return p->x;
}
static double get_y(point *p)
{
    if(p==NULL)
    {
        fprintf(stderr,"Error: input is NULL for get_y.\n");
        exit(EXIT_FAILURE);
    }
    return p->y;
}
static point *new_point(void)
{
    point *ret=calloc(1,sizeof(point));
    if(ret==NULL)
    {
        fprintf(stderr,"Error: calloc retunred NULL in new_point.\n");
        exit(EXIT_FAILURE);
    }
    return ret;
}
static points *new_points(size_t n)
{
    if(n>SIZE_MAX||n<=0)
    {
        fprintf(stderr,"Error: input size out of range in new_points.\n");
        exit(EXIT_FAILURE);
    }
    points *ret=calloc(1,sizeof(points));
    if(ret==NULL)
    {
        fprintf(stderr,"Error: calloc returns NULL for ret in new_points.\n");
        exit(EXIT_FAILURE);
    }
    ret->a=calloc(n,sizeof(point *));
    if(ret->a==NULL)
    {
        fprintf(stderr,"Error: calloc returns null for a in new_points.\n");
        exit(EXIT_FAILURE);
    }
    for(size_t i=0;i<n;i++)
    {
        ret->a[i]=calloc(1,sizeof(point));
        if(ret->a[i]==NULL)
        {
            fprintf(stderr,"Error: calloc returns NULL for *(a+i) in new_points.\n");
            exit(EXIT_FAILURE);
        }
    }
    ret->n=n;
    return ret;
}
static double *normalize(int *a,size_t n)
{
    if(a==NULL)
    {
        fprintf(stderr,"Error: input a is NULL for normalize.\n");
        exit(EXIT_FAILURE);
    }
    if(n>SIZE_MAX||n<=0)
    {
        fprintf(stderr,"Error: input size out of range in normalize.\n");
        exit(EXIT_FAILURE);
    }
    int max=0,min=0,d=0;
    max=min=a[0];
    for(size_t i=1;i<n;i++)
    {
        if(a[i]>max)
        {
            max=a[i];
        }
        else if(a[i]<min)
        {
            min=a[i];
        }
    }
    printf("max: %d, min: %d\n",max,min);
    d=max-min;
    if(d==0)
    {
        fprintf(stderr,"Error: delta equals zero; div/0\n");
        exit(EXIT_FAILURE);
    }
    double *ret=calloc(n,sizeof(double));
    if(ret==NULL)
    {
        fprintf(stderr,"Error: calloc returned NULL for ret in normalize.\n");
        exit(EXIT_FAILURE);
    }
    for(size_t i=0;i<n;i++)
    {
        ret[i]=a[i]-min;
        ret[i]/=(double)d;
    }
    return ret;
}
static void print_point(point *p)
{
    if(p==NULL)
    {
        fprintf(stderr,"Error: input is NULL for print_point.\n");
        exit(EXIT_FAILURE);
    }
    printf("point(%lf, %lf)\n",p->x,p->y);
}
static void set_point(point *p,double x,double y)
{
    if(p==NULL)
    {
        fprintf(stderr,"Error: input is NULL for set_point.\n");
        exit(EXIT_FAILURE);
    }
    p->x=x;
    p->y=y;
}
static void set_points(points *p,size_t n,double x,double y)
{
    if(p==NULL)
    {
        fprintf(stderr,"Error: input points is NULL for set_points.\n");
        exit(EXIT_FAILURE);
    }
    if(n>SIZE_MAX||n<0)
    {
        fprintf(stderr,"Error: input size out of range in set_points.\n");
        exit(EXIT_FAILURE);
    }
    if(n>=p->n)
    {
        fprintf(stderr,"Error: n out of valid range in set_points.\n");
        exit(EXIT_FAILURE);
    }
    p->a[n]->x=x;
    p->a[n]->y=y;
}