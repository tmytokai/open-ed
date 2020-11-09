#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    // サンプリング周波数 [Hz]
    const double fs = ? ;

    // カットオフ周波数 [Hz]
    const double fc = ? ;

    // 正規化カットオフ周波数
    const double Alpha = ? ;

    // FIR フィルタ長
    const int L = ? ;

    // インパルス応答
    double h[L];

    // FIR ローパスフィルタのインパルス応答の計算
    // 円周率は M_PI を使用する
    const int C = (L-1)/2;
    h[C] = ? ;
    for( int i = 1; i <= ? ; ++i ){
        h[C-i] = h[C+i] = ? ;
    }

    FILE* f = fopen( "D-FILTER-2-6.csv", "wb");
    for( int i = 0; i < L ; ++i ){
        fprintf( f, "%d, %lf\n", i, h[i] );
    }
    fclose(f);

    return 0;
}
