#include "matrix.h"

int multiply(matrix P,matrix A,matrix B)
{
    if(A->n!=B->m)            //number of columns of A and rows of B
        return(1);

    int i=0,j=0,k=0;

    for(i=0;i<A->m;i++)
        for(j=0;j<B->n;j++)
        {
            *(*(P->data+i)+j)=0;
            for(k=0;k<A->n;k++)
            {
                *(*(P->data+i)+j)+=*(*(A->data+i)+k) * *(*(B->data+k)+j);  //ith row jth column
            }
        }
    return(0);
}
