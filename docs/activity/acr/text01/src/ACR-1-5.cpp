#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// DFT
void DFT( const double* f, double* A, double* B, const int N )
{
    ?
}

// IDFT
void IDFT( const double* A, const double* B, double* f, const int N )
{
    ?
}

// 自己相関 R[n]
double ACR( const int n, const double* f, const int N )
{
    // 演習 1-1 の内容をコピーする
}

int main()
{
    const int N = 45;
    double f[N];
    double A[N];
    double B[N];
    double P[N];
    double R[N];

    for(int i=0;i < N; ++i ){
        // 演習 1-4 で入力した式をコピーする
        f[i] = ? ;
    }

    // 信号をDFT
    DFT(f,A,B,N);

    // パワースペクトルを求める
    for( int k = 0; k < N; ++k ){
        P[k] = ? ;
    }

    // パワースペクトルをIDFT
    memset( B, 0, sizeof(double)*N ); // 虚数成分 B[k] をゼロクリアして再利用する
    IDFT(P,B,R,N);

    FILE* file = fopen( "ACR-1-5-P.csv", "wb");
    if( file == NULL ){
        printf( "ファイルを開けません");
        exit(1);
    }
    for( int i = 0; i <N ; ++i ){
        fprintf( file, "%d,%lf\n", i,P[i] );
    }
    fclose(file);

    file = fopen( "ACR-1-5-R.csv", "wb");
    if( file == NULL ){
        printf( "ファイルを開けません");
        exit(1);
    }
    for( int i = 0; i <N ; ++i ){
        fprintf( file, "%d,%lf\n", i,R[i] );
    }
    fclose(file);

    return 0;
}
    
