#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 周波数特性(振幅特性)の計算
double H( const double w, const double* h, const int L, const int C, const double fs )
{
    // サンプリング間隔(秒)
    double tau = ?;

    // out は関数の出力
    double out = ?;
    for( int i = 1; i <=C; ++i ){
        out += ?;
    }

    return out;
}

int main()
{

    // ↑この上に演習 2-1 で書いたインパルス応答の計算部をそのままコピーする

    const int N = 200;
    const double wmax = M_PI*fs;
    FILE* f = fopen( "D-FILTER-2-2.csv", "wb");
    for( int i = 0; i <N ; ++i ){
        double w = wmax*i/N;
        fprintf( f, "%lf, %lf\n", w/(2*M_PI), H(w,h,L,C,fs) );
    }
    fclose(f);

    return 0;
}
