#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ���ȑ��� R[n]
double ACR( const int n, const double* f, const int N )
{
    // ���K 1-1 �̓��e���R�s�[����
}

int main()
{
    const int N = 45;
    double f[N];
    double R[N];

    for(int i=0;i < N; ++i ){
        f[i] = ? ;
    }

    for(int n=0; n < N; ++n ){
        R[n] = ACR( n, f, N );
    }

    FILE* file = fopen( "ACR-1-4-f.csv", "wb");
    if( file == NULL ){
        printf( "�t�@�C�����J���܂���");
        exit(1);
    }
    for( int i = 0; i <N ; ++i ){
        fprintf( file, "%d,%lf\n", i,f[i] );
    }
    fclose(file);

    file = fopen( "ACR-1-4-R.csv", "wb");
    if( file == NULL ){
        printf( "�t�@�C�����J���܂���");
        exit(1);
    }
    for( int i = 0; i <N ; ++i ){
        fprintf( file, "%d,%lf\n", i,R[i] );
    }
    fclose(file);

    return 0;
}
    
