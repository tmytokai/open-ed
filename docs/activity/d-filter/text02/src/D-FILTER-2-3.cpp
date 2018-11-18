#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 周波数特性(振幅特性)の計算
double H( const double w )
{
    // サンプリング周波数 [Hz]
    const double fs = 22050;  

    // FIR フィルタ長
    const int L = ? ;

    const int C = ? ;

    // サンプリング間隔(秒)
    const double tau = ?;

    // out は関数の出力
    double out = ?;
    for( int i = 1; i <=C; ++i ){
        out += ?;
    }

    return out;
}

int main()
{
    const double fs = 22050;

    const int N = 200;
    const double wmax = M_PI*fs;
    FILE* f = fopen( "D-FILTER-2-3.csv", "wb");
    for( int i = 0; i <N ; ++i ){
        double w = wmax*i/N;
        fprintf( f, "%lf, %lf\n", w/(2*M_PI), H(w) );
    }
    fclose(f);

    return 0;
}
