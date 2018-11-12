#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.1415926535
#endif

// 標準的な WAVE ヘッダ ( 44 byte )
typedef struct
{
    char riff[ 4 ];             // = "RIFF"
    unsigned int total_size;    // 全体サイズ
    char fmt[ 8 ];              // "WAVEfmt "
    unsigned int fmt_size;      // fmt チャンクサイズ
    unsigned short  format;     // フォーマットの種類
    unsigned short  channel;    // チャンネル
    unsigned int   rate;        // サンプリングレート
    unsigned int   avgbyte;     // rate * block
    unsigned short  block;      // channels * bit / 8
    unsigned short  bit;        // ビット数
    char data[ 4 ];             // = "data"
    unsigned int data_size;     // data チャンクサイズ
} WAVEFORMAT;

int main()
{
    FILE * fin = fopen( "trumpet_22k_mono.wav", "rb" );
    if( !fin ){
        fprintf( stderr, "ファイルオープンに失敗しました\n" );
        exit(EXIT_FAILURE);
    }

    WAVEFORMAT wavefmt;
    size_t ret = fread( &wavefmt, 1, sizeof( WAVEFORMAT ) - 8, fin );
    if( ret != sizeof( WAVEFORMAT ) -8 ){
       fprintf( stderr, "ヘッダが壊れています\n" );
       exit(EXIT_FAILURE);
    }

    // data までスキップ
    size_t pos = sizeof( WAVEFORMAT ) - 8;
    while( pos < 200 && ( wavefmt.data[0] != 'd' || wavefmt.data[1] != 'a' ) ){
        fseek( fin, pos++, SEEK_SET );
        ret = fread( wavefmt.data, 1, 4, fin );
    }
    ret = fread( &wavefmt.data_size, 1, sizeof( unsigned int ), fin );
    wavefmt.fmt_size = 16;

    if( wavefmt.data[ 0 ] != 'd' || wavefmt.data[ 1 ] != 'a' ){
        fprintf( stderr, "ヘッダが壊れています\n" );
        exit(EXIT_FAILURE);
    }
    if( wavefmt.channel != 1 ){
        fprintf( stderr, "ステレオ音声は使用できません\n" );
        exit(EXIT_FAILURE);
    }
    if( wavefmt.bit != 16 ){
        fprintf( stderr, "8bit音声は使用できません\n" );
        exit(EXIT_FAILURE);
    }
    if( wavefmt.rate != 22050 ){
        fprintf( stderr, "サンプリング周波数が 22050 Hzでありません\n" );
        exit(EXIT_FAILURE);
    }

    fprintf( stderr,"fmt_size = %d\n", wavefmt.fmt_size );
    fprintf( stderr,"channel = %d\n", wavefmt.channel );
    fprintf( stderr,"rate = %d\n", wavefmt.rate );
    fprintf( stderr,"avgbyte = %d\n", wavefmt.avgbyte );
    fprintf( stderr,"block = %d\n", wavefmt.block );
    fprintf( stderr,"bit = %d\n", wavefmt.bit );   
    fprintf( stderr,"data_size = %d\n", wavefmt.data_size );

    short* buf = ( short* )malloc( 2 * 1024 * 1024 );
    ret = fread( buf , 1, wavefmt.data_size, fin );
    fclose( fin );

    size_t lng = wavefmt.data_size / wavefmt.block;
    fprintf( stderr,"length = %d\n", (int)lng);

    double* x_tmp = ( double* )malloc( lng * 2 * sizeof(double) );
    memset( x_tmp, 0, lng * 2 * sizeof(double) );
    double *x = x_tmp + lng;
    for( int i = 0; i < lng; ++i ) x[i] = (double)buf[i];

    double* y = ( double* )malloc( lng * sizeof(double) );
    memset( y, 0, lng * sizeof(double) );

    double z[256] = {0};

    //----------------------------------------------
    // ここから穴埋め開始

    // サンプリング周波数 [Hz]
    const double fs = ?;  

    // x[i] を fs [Hz] で 5 秒間サンプリングした音声のディジタル信号とする
    // i の範囲は 0 <= i < N となる
    const int N = 5 * fs; // 5 [秒] * fs [Hz]

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

    // L 次 IIR フィルタ
    // 出力信号は y[i]
    // z[k] は k 時刻前の☆の値

    for( int i = 0; i < N; ++i ){

        // 前段フィードバック部
        z[0] = ? ;
        for( int k = 1; k <= L; ++k ) z[0] += ? ;

        // 後段フィードフォワード部
        y[i] = ? ;
        for( int k = 0; k <= L; ++k ) y[i] += ? ;

        // バッファシフト
        for( int k = 1; k <= L; ++k ) z[k] = ? ;
    }

    // ここまで
    //----------------------------------------------

    FILE* fout = fopen( "D-FILTER-3-1-out.wav", "wb" );
    if( !fout ){
        fprintf( stderr, "ファイルオープンに失敗しました\n" );
        exit(EXIT_FAILURE);
    }
    for( int i = 0; i < lng; ++i ) buf[i] = (short)(y[i]*0.8);

    fwrite( &wavefmt, 1, sizeof( WAVEFORMAT ), fout );
    fwrite( buf, 1, wavefmt.data_size , fout );
    fclose( fout );
    
    return 0;
}
