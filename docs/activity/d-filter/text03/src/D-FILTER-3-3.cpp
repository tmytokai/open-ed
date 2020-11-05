#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double z[256] = {0};

    // サンプリング周波数 [Hz]
    const double fs = ? ;

    const int N = (int)(0.01 * fs); // 0.01 [秒] * fs [Hz]

    // デジタルインパルス信号 {1,0,0,0,0,....}
    double x[ N ] = {0};
    x[0] = 1;

    // 入力信号をデジタルインパルス信号とすると出力信号 y[i] はインパルス応答 h[i] になる
    // なおインパルス応答 h[i] はアナログインパルス応答 h(t) を fs [Hz] でサンプリングした後にτを掛けた値とほぼ一致する
    double y[ N ] = {0};

    // カットオフ周波数 [Hz]
    const double fc = ? ;

    // カットオフ角周波数 [rad/秒]
    // 円周率は M_PI を使用する
    const double wc = ? ;

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
    // z[n] は n 時刻前の☆の値
    for( int i = 0; i < N; ++i ){
        ?
    }

    // インパルス応答をcsvファイルに出力
    FILE* f = fopen( "D-FILTER-3-3.csv", "wb");
    for( int i = 0; i < N ; ++i ){
        fprintf( f, "%d, %lf\n", i, y[i] );
    }
    fclose(f);

    return 0;
}
