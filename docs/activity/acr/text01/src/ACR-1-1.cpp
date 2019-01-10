#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ���K���� N( mu, sigma^2)�̏o��
// mu : ����
// sigma : �W���΍� = �㕪�U
double nrand( double mu, double sigma )
{
    // Box-Muller �@���g�p
    double x = sqrt( -2*log( (double)rand()/RAND_MAX ) ) * cos( 2*M_PI*rand()/RAND_MAX ) ;
    return mu + sigma*x;
}

// ���ȑ��� R[n]
double ACR( const int n, const double* f, const int N )
{
    double out = 0;
    for( int i = 0; i < N; ++i ){
        out += ?;
    };
    out /= ? ;

    return out;
}

int main()
{
    const int N = 10000;
    const int Nout = 20;
    double f[N];
    double R[Nout];

    for(int i=0;i < N; ++i ){
        f[i] = ?;
    }

    for(int n=0; n < Nout; ++n ){
        R[n] = ACR( n, f, N );
    }

    FILE* file = fopen( "ACR-1-1-f.csv", "wb");
    if( file == NULL ){
        printf( "�t�@�C�����J���܂���");
        exit(1);
    }
    for( int i = 0; i <Nout ; ++i ){
        fprintf( file, "%d,%lf\n", i,f[i] );
    }
    fclose(file);

    file = fopen( "ACR-1-1-R.csv", "wb");
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
    
