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
    const int Nout = 20;
    double f[N];
    double R[Nout];

    for(int i=0;i < N; ++i ){
        f[i] = ? ;
    }

    for(int n=0; n < Nout; ++n ){
        R[n] = ACR( n, f, N );
    }

    FILE* file = fopen( "ACR-1-2-f.csv", "wb");
    if( file == NULL ){
        printf( "ファイルを開けません");
        exit(1);
    }
    for( int i = 0; i <Nout ; ++i ){
        fprintf( file, "%lf\n", f[i] );
    }
    fclose(file);

    file = fopen( "ACR-1-2-R.csv", "wb");
    if( file == NULL ){
        printf( "ファイルを開けません");
        exit(1);
    }
    for( int i = 0; i <Nout ; ++i ){
        fprintf( file, "%lf\n", R[i] );
    }
    fclose(file);

    return 0;
}
    
