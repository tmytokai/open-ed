#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


///////////////////////////
// ここから

const int L = 100; // 線形予測次数

// 自己相関 R[n]
double ACR( const int n, const double* f, const int N )
{
    // 自己相関の演習で作成した ACR 関数の中身をコピーする

}

// レビンソン・ダービン・アルゴリズム
void LevinsonDurbin(
    double *a,// LPC 係数
    double *P, // PARCOR(パーコール)係数
    const double* x, // 入力
    const int N )
{
    double R[L+1]; // 自己相関関数
    double a2[L+1];

    // 演習 4-1 のレビンソン・ダービン・アルゴリズムをコピーする

}

// 線形予測値
void HATX( double *hatx, // 線形予測値
           const double *a, // LPC 係数
           const double *x, // 入力
           const int N )
{
    // 演習 4-2 で予測値を求めている部分をコピーする

}

// 線形予測誤差
void ERR( double *err, // 線形予測誤差
           const double *a, // LPC 係数
           const double *x, // 入力
           const int N )
{
    // 演習 4-3 で予測誤差を求めている部分をコピーする

}

// ここまで
///////////////////////////

const double STARTPOS = 1.0;  // wave ファイルの読み込み開始位置 (秒)
const double DURATION = 0.5;  // wave ファイルの読み込みサイズ (秒)
const int MAXHZ = 8000; // wave ファイルに含まれる最大周波数 (Hz)

const int MAXL = 256; // 線形予測次数の最大値
const double ERRGAIN = 100.0; // 線形予測誤差のゲイン

// 標準 WAVE ヘッダ ( 44 byte )
struct WAVEFORMAT
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
};

short* read_wav( const char* file, WAVEFORMAT *wavefmt )
{
    FILE * fin = fopen( file, "rb" );
    if( !fin ){
        fprintf( stderr, "ファイルオープンに失敗しました\n" );
        exit(EXIT_FAILURE);
    }

    // フォーマット取得
    size_t ret = fread( wavefmt, 1, sizeof( WAVEFORMAT ) - 8, fin );

    if( ret != sizeof( WAVEFORMAT ) -8 ){
       fprintf( stderr, "ヘッダが壊れています\n" );
       exit(EXIT_FAILURE);
    }
    if( wavefmt->riff[ 0 ] != 'R' || wavefmt->riff[ 1 ] != 'I' ){
        fprintf( stderr, "Wave ファイルではありません\n" );
        exit(EXIT_FAILURE);
    }
    if( wavefmt->channel != 1 ){
        fprintf( stderr, "ステレオ音声は使用できません\n" );
        exit(EXIT_FAILURE);
    }
    if( wavefmt->rate < MAXHZ*2 ){
        fprintf( stderr, "サンプリング周波数が低いです\n" );
        exit(EXIT_FAILURE);
    }
    if( wavefmt->bit != 16 ){
        fprintf( stderr, "8bit音声は使用できません\n" );
        exit(EXIT_FAILURE);
    }

    // data までスキップ
    size_t pos = sizeof( WAVEFORMAT ) - 8;
    while( pos < 200 && ( wavefmt->data[0] != 'd' || wavefmt->data[1] != 'a' ) ){
        fseek( fin, pos++, SEEK_SET );
        ret = fread( wavefmt->data, 1, 4, fin );
    }

    if( wavefmt->data[ 0 ] != 'd' || wavefmt->data[ 1 ] != 'a' ){
        fprintf( stderr, "データがありません\n" );
        exit(EXIT_FAILURE);
    }

    // データサイズを取得
    ret = fread( &wavefmt->data_size, 1, sizeof( unsigned int ), fin );

    const double duration = (double)wavefmt->data_size / wavefmt->avgbyte;
    if( duration < STARTPOS + DURATION ){
        fprintf( stderr, "録音時間が短いです\n" );
        exit(EXIT_FAILURE);
    }

    // フォーマット再設定
    wavefmt->fmt_size = 16;
    wavefmt->data_size = (unsigned int)( DURATION * wavefmt->avgbyte );
    wavefmt->total_size = sizeof( WAVEFORMAT ) + wavefmt->data_size - 8;

    // STARTPOS 秒から DURATION 秒間のデータ読み込み
    short* buf = ( short* )calloc( 1, wavefmt->data_size );
    fseek( fin, (unsigned int)(STARTPOS * wavefmt->avgbyte), SEEK_CUR );
    ret = fread( buf, 1, wavefmt->data_size, fin );
    if( ret != wavefmt->data_size ){
       fprintf( stderr, "データの読み込みに失敗しました\n" );
       exit(EXIT_FAILURE);
    }

    fclose( fin );

    return buf;
}

void save_wav( const char* file, const WAVEFORMAT* wavefmt, const short* buf )
{
    FILE* fout = fopen( file, "wb" );
    if( !fout ){
        fprintf( stderr, "%s のオープンに失敗しました\n", file );
        exit(EXIT_FAILURE);
    }
    fwrite( wavefmt, 1, sizeof( WAVEFORMAT ), fout );
    fwrite( buf, 1, wavefmt->data_size , fout );
    fclose( fout );
    fprintf( stderr, "save to %s\n", file);
}

int main()
{
    WAVEFORMAT wavefmt;
    short* buf = read_wav( "a.wav", &wavefmt );

    fprintf( stderr,"L = %d\n", L);

    const int f_s = wavefmt.rate;
    fprintf( stderr,"f_s = %d\n", wavefmt.rate );

    const int N = wavefmt.data_size / wavefmt.block;
    fprintf( stderr,"N = %d\n", N);

    double* x = ( double* )calloc( 1, (N+MAXL) * sizeof(double) ) + MAXL;
    double* a = (double*)calloc( 1, (L+1)*sizeof(double) );
    double* P = (double*)calloc( 1, (L+1)*sizeof(double) );
    for( int i = 0; i < N; ++i ) x[i] = (double)buf[i];

    double* hatx = ( double* )calloc( 1, N * sizeof(double) );
    double* err  = ( double* )calloc( 1, N * sizeof(double) );

    LevinsonDurbin( a, P, x, N );
    HATX( hatx, a, x, N );
    ERR( err, a, x, N );

    save_wav( "D-FILTER-4-4-out.wav", &wavefmt, buf );

    for( int i = 0; i < N; ++i ) buf[i] = (short)hatx[i];
    save_wav( "D-FILTER-4-4-hat.wav", &wavefmt, buf );

    for( int i = 0; i < N; ++i ) buf[i] = (short)(err[i]*ERRGAIN);
    save_wav( "D-FILTER-4-4-err.wav", &wavefmt, buf );

    free( buf );
    free( x-MAXL );
    free( a );
    free( P );
    free( hatx );
    free( err );

    return 0;
}
