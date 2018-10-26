#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    // サンプリング周波数 [Hz]
    const double fs = ?;  

    // FIR フィルタ次数(タップ数)
    const int L = ? ;

    // フィルタ係数 = インパルス応答
    double h[L];

    // カットオフ周波数 [Hz]
    const double fc = ? ;

    // FIR ローパスフィルタ係数を計算
    // 円周率は M_PI を使用する
    const int C = (L-1)/2;
    const double Alpha = ? ;
    h[C] = ? ;
    for( int i = 1; i <= ? ; ++i ){
        h[C-i] = h[C+i] = ? ;
    }

    FILE* f = fopen( "D-FILTER-2-1.csv", "wb");
    for( int i = 0; i < L ; ++i ){
        fprintf( f, "%d, %lf\n", i, h[i] );
    }
    fclose(f);

    return 0;
}
