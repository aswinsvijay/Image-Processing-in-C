#include "ppm.h"
#include "transformations.h"
#include "matrix.h"
#include<stdlib.h>

void invert(PPMimg *img)
{
    matrix A,B,C;
    int i,j;

    A=(matrix_t*)malloc(sizeof(matrix_t));
    B=(matrix_t*)malloc(sizeof(matrix_t));

    A->m=1;
    A->n=4;
    B->m=4;
    B->n=4;

    A->data=(float**)malloc(A->m*sizeof(float*));
    for(i=0;i<A->m;i++)
        *(A->data+i)=(float*)malloc(sizeof(int)*A->n);
    B->data=(float**)malloc(B->m*sizeof(float*));
    for(i=0;i<B->m;i++)
        *(B->data+i)=(float*)malloc(sizeof(int)*B->n);

    B->data[0][0]=-1;
    B->data[0][1]=0;
    B->data[0][2]=0;
    B->data[0][3]=0;
    B->data[1][0]=0;
    B->data[1][1]=-1;
    B->data[1][2]=0;
    B->data[1][3]=0;
    B->data[2][0]=0;
    B->data[2][1]=0;
    B->data[2][2]=-1;
    B->data[2][3]=0;
    B->data[3][0]=255;
    B->data[3][1]=255;
    B->data[3][2]=255;
    B->data[3][3]=1;

    C=(matrix_t*)malloc(sizeof(matrix_t));
    C->m=1;
    C->n=4;
    C->data=(float**)malloc(C->m*sizeof(float*));
    for(i=0;i<C->m;i++)
    *(C->data+i)=(float*)malloc(sizeof(int)*C->n);

    for(i=0;i<img->x;i++)
    {
        for (j=0;j<img->y;j++)
        {
            A->data[0][0]=img->data[i*(img->y)+j].rgb[0];
            A->data[0][1]=img->data[i*(img->y)+j].rgb[1];
            A->data[0][2]=img->data[i*(img->y)+j].rgb[2];
            A->data[0][3]=1;
            multiply(C,A,B);
            img->data[i*(img->y)+j].rgb[0]=C->data[0][0];
            img->data[i*(img->y)+j].rgb[1]=C->data[0][1];
            img->data[i*(img->y)+j].rgb[2]=C->data[0][2];
        }
    }
}

void greyscale(PPMimg *img)
{
    matrix A,B,C;
    int i,j;

    A=(matrix_t*)malloc(sizeof(matrix_t));
    B=(matrix_t*)malloc(sizeof(matrix_t));

    A->m=1;
    A->n=3;
    B->m=3;
    B->n=3;

    A->data=(float**)malloc(A->m*sizeof(float*));
    for(i=0;i<A->m;i++)
        *(A->data+i)=(float*)malloc(sizeof(int)*A->n);
    B->data=(float**)malloc(B->m*sizeof(float*));
    for(i=0;i<B->m;i++)
        *(B->data+i)=(float*)malloc(sizeof(int)*B->n);

    B->data[0][0]=0.3;
    B->data[0][1]=0.3;
    B->data[0][2]=0.3;
    B->data[1][0]=0.59;
    B->data[1][1]=0.59;
    B->data[1][2]=0.59;
    B->data[2][0]=0.11;
    B->data[2][1]=0.11;
    B->data[2][2]=0.11;

    C=(matrix_t*)malloc(sizeof(matrix_t));
    C->m=1;
    C->n=3;
    C->data=(float**)malloc(C->m*sizeof(float*));
    for(i=0;i<C->m;i++)
        *(C->data+i)=(float*)malloc(sizeof(int)*C->n);

    for(i=0;i<img->x;i++)
    {
        for (j=0;j<img->y;j++)
        {
            A->data[0][0]=img->data[i*(img->y)+j].rgb[0];
            A->data[0][1]=img->data[i*(img->y)+j].rgb[1];
            A->data[0][2]=img->data[i*(img->y)+j].rgb[2];
            multiply(C,A,B);
            img->data[i*(img->y)+j].rgb[0]=C->data[0][0];
            img->data[i*(img->y)+j].rgb[1]=C->data[0][1];
            img->data[i*(img->y)+j].rgb[2]=C->data[0][2];
        }
    }	
}
