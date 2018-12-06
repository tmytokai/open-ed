#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int main()
{
    const int N = 8;
    double *f;
    double *A;
    double *B;
    clock_t clock_start, clock_end;

    f = (double*)malloc(sizeof(double)*N);
    A = (double*)malloc(sizeof(double)*N);
    B = (double*)malloc(sizeof(double)*N);
    
    for( int i = 0; i < N; ++i ){
        f[i] = (double)rand()/RAND_MAX;
    }

    clock_start = clock();

    // A[k] �� B[k] �̌v�Z�����R�s�[����


    // FFT �̃��C�u�������l�b�g�ŒT���ĈڐA����

    clock_end = clock();

    // ����m�F�p�Ȃ̂ōŏ��� 8 �����\��
    for( int k = 0; k < 8; ++k ) printf("A[%d] =  %lf, B[%d] = %lf\n", k, A[k], k, B[k]);
    printf( "N = %d, CPU time = %lu\n", N, clock_end - clock_start );

    free(f);
    free(A);
    free(B);

    return 0;
}
