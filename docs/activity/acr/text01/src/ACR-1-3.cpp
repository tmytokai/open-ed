#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ��l���� U(a,b)�̏o��
double urand( double a, double b )
{
    return a + (b-a)*(double)rand()/RAND_MAX;
}

// ���ȑ��� R[n]
double ACR( const int n, const double* f, const int N )
{
    // ���K 1-1 �̓��e���R�s�[����
}

int main()
{
    const int N = 10000;
    const int Nout = 20;
    double f[N];
    double R[Nout];

    for(int i=0;i < N; ++i ){
        f[i] = ? ;
    }

    for(int n=0; n < Nout; ++n ){
        R[n] = ACR( n, f, N );
    }

    FILE* file = fopen( "ACR-1-3-f.csv", "wb");
    if( file == NULL ){
        printf( "�t�@�C�����J���܂���");
        exit(1);
    }
    for( int i = 0; i <Nout ; ++i ){
        fprintf( file, "%d,%lf\n", i,f[i] );
    }
    fclose(file);

    file = fopen( "ACR-1-3-R.csv", "wb");
    if( file == NULL ){
        printf( "�t�@�C�����J���܂���");
        exit(1);
    }
    for( int i = 0; i <Nout ; ++i ){
        fprintf( file, "%d,%lf\n", i,R[i] );
    }
    fclose(file);

    return 0;
}
    
