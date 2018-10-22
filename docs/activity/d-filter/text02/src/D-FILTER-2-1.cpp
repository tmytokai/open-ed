#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    // FIRフィルタ次数(タップ数)
    const int L = ? ;

    // インパルス応答
    double h[L];

    // カットオフ周波数 [Hz]
    const double fc = ?;

    // サンプリング周波数 [Hz]
    const double fs = ?;  

    // インパルス応答を計算
    // 円周率は M_PI を使用する
    const double Alpha = ?;
    const int C = ?;
    h[C] = ?;
    for( int i = 1; i <= C ; ++i ){
        h[C-i] = h[C+i] = ?;
    }

    FILE* f = fopen( "D-FILTER-2-1.csv", "wb");
    for( int i = 0; i < L ; ++i ){
        fprintf( f, "%d, %lf\n", i, h[i] );
    }
    fclose(f);

    return 0;
}
