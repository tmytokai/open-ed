#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 正規乱数 N( mu, sigma^2)の出力
// mu : 平均
// sigma : 標準偏差 = √分散
double nrand( double mu, double sigma )
{
    // Box-Muller 法を使用
    double x = sqrt( -2*log( (double)rand()/RAND_MAX ) ) * cos( 2*M_PI*rand()/RAND_MAX ) ;
    return mu + sigma*x;
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

    FILE* file = fopen( "ACR-1-2-f.csv", "wb");
    for( int i = 0; i <100 ; ++i ){
        fprintf( file, "%lf\n", f[i] );
    }
    fclose(file);

    file = fopen( "ACR-1-2-R.csv", "wb");
    for( int i = 0; i <100 ; ++i ){
        fprintf( file, "%lf\n", R[i] );
    }
    fclose(file);

    return 0;
}
    
