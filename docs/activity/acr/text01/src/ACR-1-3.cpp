#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 一様乱数 U(a,b)の出力
double urand( double a, double b )
{
    return a + (b-a)*(double)rand()/RAND_MAX;
}

// 自己相関 R[n]
double ACR( const int n, const double* f, const int N )
{
    // 演習 1-1 の内容をコピーする
}

int main()
{
    const int N = 10000;
    double f[N];
    double R[N];

    for(int i=0;i < N; ++i ){
        f[i] = ? ;
    }

    for(int n=0; n < N; ++n ){
        R[n] = ACR( n, f, N );
    }

    FILE* file = fopen( "ACR-1-3-f.csv", "wb");
    for( int i = 0; i <100 ; ++i ){
        fprintf( file, "%lf\n", f[i] );
    }
    fclose(file);

    file = fopen( "ACR-1-3-R.csv", "wb");
    for( int i = 0; i <100 ; ++i ){
        fprintf( file, "%lf\n", R[i] );
    }
    fclose(file);

    return 0;
}
    
