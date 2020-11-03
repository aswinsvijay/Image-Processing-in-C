typedef struct
{
    int m,n;
    float **data;
}matrix_t;

typedef matrix_t* matrix;

int multiply(matrix P,matrix A,matrix B);
