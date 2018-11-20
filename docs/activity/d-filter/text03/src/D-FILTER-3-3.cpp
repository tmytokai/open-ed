#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double z[256] = {0};

    // サンプリング周波数 [Hz]
    const double fs = ? ;

    // インパルス応答 h[i] は h(t) を fs [Hz] で 0.01 秒間サンプリングした後にτを掛けた値とほぼ一致する
    // i の範囲は 0 <= i < N となる
    const int N = (int)(0.01 * fs); // 0.01 [秒] * fs [Hz]
    double h[ N ];

    // カットオフ周波数 [Hz]
    const double fc = ? ;

    // サンプリング間隔 [秒]
    const double tau = ? ;

    // IIR フィルタ次数 (今回は 1 次)
    const int L = 1;

    // 1次 IIR ローパスフィルタ係数を計算
    // 円周率は M_PI を使用する
    double a[2] = {0};
    double b[2] = {0};
    a[1] = ? ;
    b[0] = ? ;
    b[1] = ? ;

    // L 次 IIR フィルタのインパルス応答
    // 入力信号をデジタルインパルス信号 δ[i] = {1,0,0,0,0,....} にすると
    // 出力信号は h[i] となる
    // z[k] は k 時刻前の☆の値
    for( int i = 0; i < N; ++i ){

        // 前段フィードバック部
        if( i == 0 ) z[0] = 1;
        else z[0] = 0;
        for( int k = 1; k <= L; ++k ) z[0] += ? ;

        // 後段フィードフォワード部
        h[i] = 0;
        for( int k = 0; k <= L; ++k ) h[i] += ? ;

        // バッファシフト
        for( int k = 1; k <= L; ++k ) z[k] = ? ;
    }

    // インパルス応答をcsvファイルに出力
    FILE* f = fopen( "D-FILTER-3-3.csv", "wb");
    for( int i = 0; i < N ; ++i ){
        fprintf( f, "%d, %lf\n", i, h[i] );
    }
    fclose(f);

    return 0;
}
