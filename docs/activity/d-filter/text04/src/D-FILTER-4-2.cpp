#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 正規乱数 N( mu, sigma^2)の出力
// mu : 平均
// sigma2 : 分散
double nrand( double mu, double sigma2 )
{
    // Box-Muller 法を使用
    double sigma = sqrt(sigma2);
    double x = sqrt( -2*log( (double)rand()/RAND_MAX ) ) * cos( 2*M_PI*rand()/RAND_MAX ) ;
    return mu + sigma*x;
}

// 自己相関 R[n]
double ACR( const int n, const double* f, const int N )
{
    // 自己相関の演習で作成した ACR 関数の中身をコピーする
}

int main()
{
    const int L = 4; // 線形予測次数
    const int N = 50000;
    const int Nout = 100;
    double X[N+L]={0};
    double *x = X+L; // 信号値
    double R[L+1]; // 自己相関関数
    double P[L+1]; // PARCOR(パーコール)係数
    double a[L+1]; // LPC 係数
    double a2[L+1];

    // 演習 4-1 の x[i] をコピーする
    for(int i=0;i < N; ++i ){
        x[i] = ? ;
    }

    // 演習 4-1 のレビンソン・ダービン(Levinson-Durbin)・アルゴリズムをコピーする


    // 線形予測モデル
    double hatx[Nout];
    for( int i = 0; i < Nout; ++i ){
        hatx[i] = 0;
        for( int n = 1; n <= L; ++n ){
            hatx[i] += ? ;
        }
        hatx[i] *= ? ;
    }

    printf("LPC係数の推定値\n");
    for( int n = 1; n <= L; ++n ){
        printf( "a[%d] = %lf\n", n, a[n] );
    }

    FILE* file = fopen( "D-FILTER-4-2-hatx.csv", "wb");
    if( file == NULL ){
        printf( "ファイルを開けません");
        exit(1);
    }
    for( int i = 0; i <Nout ; ++i ){
        fprintf( file, "%d, %lf\n", i, hatx[i] );
    }
    fclose(file);

    return 0;
}
    
