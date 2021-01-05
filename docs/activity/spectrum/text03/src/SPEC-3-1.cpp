#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
const double M_PI = 3.1415926535;
#endif

const double STARTPOS = 1.0;
const double DURATION = 0.5;
const int MAXHZ = 8000;

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
    FILE * fin = fopen( "SPEC-3-1.wav", "rb" );
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

    double* f = ( double* )malloc( N * sizeof(double) );
    for( int i = 0; i < N; ++i ) f[i] = (double)buf[i];

    double *A = (double*)calloc( 1, N * sizeof(double) );
    double *B = (double*)calloc( 1, N * sizeof(double) );
    double *absC = (double*)calloc( 1, N * sizeof(double) );
    double *argC = (double*)calloc( 1, N * sizeof(double) );

    //----------------------------------------------
    // ここから演習開始

    // SPEC-3-1.wav の 1.0 秒時点から 0.5 秒間だけ音声信号を切り出して
    // 長さ N のディジタル信号 f[0] 〜 f[N-1] を作成済

    // 本来ならば人間の声は周期性信号ではないが、今回は周期 N の周期性信号とみなして DFT する
    // DFT-1-3.cpp を開き、A、B、absC、argC の計算部をコピーする
    // なお A[N]、B[N]、absC[N]、argC[N] は上の方で定義済なので定義部を消す


    // ここまで
    //----------------------------------------------

    FILE *csv = fopen( "SPEC-3-1.csv", "w" );
    if( !csv ){
        fprintf( stderr, "ファイルオープンに失敗しました\n" );
        exit(EXIT_FAILURE);
    }
    for( int k = 0; k < MAXHZ * N / f_s; ++k ){
        fprintf( csv, "%d, %lf, %lf\n", k * f_s / N, absC[k], argC[k] );
    }
    fclose(csv);

    FILE* fout = fopen( "SPEC-3-1-out.wav", "wb" );
    if( !fout ){
        fprintf( stderr, "ファイルオープンに失敗しました\n" );
        exit(EXIT_FAILURE);
    }
    fwrite( &wavefmt, 1, sizeof( WAVEFORMAT ), fout );
    fwrite( buf, 1, wavefmt.data_size , fout );
    fclose( fout );

    free(buf);
    free(f);
    free(A);
    free(B);
    free(absC);
    free(argC);

    return 0;
}
