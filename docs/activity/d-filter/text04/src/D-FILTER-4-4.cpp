#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
const double M_PI = 3.1415926535;
#endif

const double STARTPOS = 1.0;
const double DURATION = 0.5;
const int MAXHZ = 8000;
const int MAXL = 100;

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

// 自己相関 R[n]
double ACR( const int n, const double* f, const int N )
{
    // 自己相関の演習で作成した ACR 関数の中身をコピーする
}

int main()
{
    FILE * fin = fopen( "D-FILTER-4-4.wav", "rb" );
    if( !fin ){
        fprintf( stderr, "ファイルオープンに失敗しました\n" );
        exit(EXIT_FAILURE);
    }

    // フォーマット取得
    WAVEFORMAT wavefmt;
    size_t ret = fread( &wavefmt, 1, sizeof( WAVEFORMAT ) - 8, fin );

    if( ret != sizeof( WAVEFORMAT ) -8 ){
       fprintf( stderr, "ヘッダが壊れています\n" );
       exit(EXIT_FAILURE);
    }
    if( wavefmt.riff[ 0 ] != 'R' || wavefmt.riff[ 1 ] != 'I' ){
        fprintf( stderr, "Wave ファイルではありません\n" );
        exit(EXIT_FAILURE);
    }
    if( wavefmt.channel != 1 ){
        fprintf( stderr, "ステレオ音声は使用できません\n" );
        exit(EXIT_FAILURE);
    }
    if( wavefmt.rate < MAXHZ*2 ){
        fprintf( stderr, "サンプリング周波数が低いです\n" );
        exit(EXIT_FAILURE);
    }
    if( wavefmt.bit != 16 ){
        fprintf( stderr, "8bit音声は使用できません\n" );
        exit(EXIT_FAILURE);
    }

    // data までスキップ
    size_t pos = sizeof( WAVEFORMAT ) - 8;
    while( pos < 200 && ( wavefmt.data[0] != 'd' || wavefmt.data[1] != 'a' ) ){
        fseek( fin, pos++, SEEK_SET );
        ret = fread( wavefmt.data, 1, 4, fin );
    }

    if( wavefmt.data[ 0 ] != 'd' || wavefmt.data[ 1 ] != 'a' ){
        fprintf( stderr, "データがありません\n" );
        exit(EXIT_FAILURE);
    }

    // データサイズを取得
    ret = fread( &wavefmt.data_size, 1, sizeof( unsigned int ), fin );

    if( (double)wavefmt.data_size / wavefmt.avgbyte < STARTPOS + DURATION ){
        fprintf( stderr, "録音時間が短いです\n" );
        exit(EXIT_FAILURE);
    }

    // フォーマット再設定
    wavefmt.fmt_size = 16;
    wavefmt.data_size = (unsigned int)( DURATION * wavefmt.avgbyte );
    wavefmt.total_size = sizeof( WAVEFORMAT ) + wavefmt.data_size - 8;

    // データ読み込み
    short* buf = ( short* )malloc( wavefmt.data_size );
    fseek( fin, (unsigned int)(STARTPOS * wavefmt.avgbyte), SEEK_CUR );
    ret = fread( buf, 1, wavefmt.data_size, fin );
    if( ret != wavefmt.data_size ){
       fprintf( stderr, "データの読み込みに失敗しました\n" );
       exit(EXIT_FAILURE);
    }

    fclose( fin );

    // 演習で使うデータや配列を作成
    const int f_s = wavefmt.rate;
    fprintf( stderr,"f_s = %d\n", wavefmt.rate );

    const int N = wavefmt.data_size / wavefmt.block;
    fprintf( stderr,"N = %d\n", N);

    double* X = ( double* )calloc( 1, (N+MAXL) * sizeof(double) );
    double* x = X+MAXL;
    for( int i = 0; i < N; ++i ) x[i] = (double)buf[i];

    double* hatx = ( double* )malloc( N * sizeof(double) );

    //----------------------------------------------
    // ここから演習開始

    // D-FILTER-4-4.wav の 1.0 秒時点から 0.5 秒間だけ音声信号を切り出して
    // 長さ N のディジタル信号 x[0] ～ x[N-1] を作成済

    const int L = 10; // 線形予測次数
    double R[L+1]; // 自己相関関数
    double P[L+1]; // PARCOR(パーコール)係数
    double a[L+1]; // LPC 係数
    double a2[L+1];

    // 演習 4-1 のレビンソン・ダービン(Levinson-Durbin)・アルゴリズムをコピーする


    // 線形予測モデル
    // hatx は定義済


    // ここまで
    //----------------------------------------------

    printf("LPC係数\n");
    for( int n = 1; n <= L; ++n ){
        printf( "a[%d] = %lf\n", n, a[n] );
    }

    FILE* fout = fopen( "D-FILTER-4-4-out.wav", "wb" );
    if( !fout ){
        fprintf( stderr, "ファイルオープンに失敗しました\n" );
        exit(EXIT_FAILURE);
    }
    fwrite( &wavefmt, 1, sizeof( WAVEFORMAT ), fout );
    fwrite( buf, 1, wavefmt.data_size , fout );
    fclose( fout );

    for( int i = 0; i < N; ++i ) buf[i] = (short)hatx[i];
    fout = fopen( "D-FILTER-4-4-hatx.wav", "wb" );
    if( !fout ){
        fprintf( stderr, "ファイルオープンに失敗しました\n" );
        exit(EXIT_FAILURE);
    }
    fwrite( &wavefmt, 1, sizeof( WAVEFORMAT ), fout );
    fwrite( buf, 1, wavefmt.data_size , fout );
    fclose( fout );

    free(buf);
    free(X);

    return 0;
}
