#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


// 正規乱数 N( mu, sigma^2)の出力
// mu : 平均
// sigma2 : 分散
double nrand( double mu, double sigma2 )
{
    // Box-Muller 法を使用
    double sigma = sqrt(sigma2);
    double x = sqrt( -2*log( (double)rand()/RAND_MAX ) ) * cos( 2*M_PI*rand()/RAND_MAX ) ;
    return mu + sigma*x;
}

///////////////////////////
// ここから

const int L = 100; // 線形予測次数
const int OCTAVE = 3; // オクターブ
const double GAIN = 1.0; // 出力全体の音量
const double VOICEGAIN[] = {
    1.0, // "ア"の音量
    1.0, // "イ"の音量
    1.0, // "ウ"の音量
    1.0, // "エ"の音量
    1.0  // "オ"の音量
};

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

// AR モデル
void AR( double *x, // AR モデル出力
         const double *a, // LPC 係数
         const double *err, // 入力 (線形予測誤差)
         const int N )
{
    for(int i=0;i < N; ++i ){
        x[i] = ? ;
        for( int n = 1; n <= L; ++n ){
            x[i] += ? ;
        }
        x[i] *= ? ;
        x[i] += ? ;
    }
}

// ここまで
///////////////////////////

enum
{
    VOICE_A = 0,
    VOICE_I,
    VOICE_U,
    VOICE_E,
    VOICE_O,
    
    VOICE_R
};

enum
{
    SCALE_C = 0,
    SCALE_D,
    SCALE_E,
    SCALE_F,
    SCALE_G,
    SCALE_A,
    SCALE_B,
    
    SCALE_R
};

struct NOTE
{
    int voice;
    int scale;
};

// 出力音声の内容を変えたい時は以下を修正する
const NOTE notes[] =
{
    {VOICE_A, SCALE_C},
    {VOICE_A, SCALE_C},
    {VOICE_R, SCALE_R},

    {VOICE_I, SCALE_C},
    {VOICE_I, SCALE_C},
    {VOICE_R, SCALE_R},

    {VOICE_U, SCALE_C},
    {VOICE_U, SCALE_C},
    {VOICE_R, SCALE_R},

    {VOICE_E, SCALE_C},
    {VOICE_E, SCALE_C},
    {VOICE_R, SCALE_R},

    {VOICE_O, SCALE_C},
    {VOICE_O, SCALE_C},
    {VOICE_R, SCALE_R},

    {VOICE_A, SCALE_C},
    {VOICE_I, SCALE_D},
    {VOICE_A, SCALE_E},
    {VOICE_A, SCALE_E},

    {VOICE_A, SCALE_C},
    {VOICE_I, SCALE_D},
    {VOICE_A, SCALE_E},
    {VOICE_A, SCALE_E},

    {VOICE_U, SCALE_G},
    {VOICE_I, SCALE_E},
    {VOICE_U, SCALE_D},
    {VOICE_O, SCALE_C},

    {VOICE_A, SCALE_D},
    {VOICE_A, SCALE_E},
    {VOICE_A, SCALE_D},
};

const double STARTPOS = 1.0;  // wave ファイルの読み込み開始位置 (秒)
const double DURATION = 0.5;  // wave ファイルの読み込みサイズ (秒)
const int MAXHZ = 8000; // wave ファイルに含まれる最大周波数 (Hz)

const int MAXL = 256; // 線形予測次数の最大値
const double NOTELNG = 0.5; // 1 音の長さ(秒)
const double PULSEAMP = 10.0; // 線形予測誤差のパルス信号の大きさ
const double PULSEWIDTH = 100.0; // 線形予測誤差のハルス信号の幅
const double ERRSIGMA2 = PULSEAMP/2.0; // 線形予測誤差のホワイトノイズの分散
const double scale_freq[]={ 261.6, 293.7, 329.6, 349.2, 392.0, 440.0, 493.9 };

struct VOICE
{
    char file[64];
    short* buf;
    double* x;
    double *a;
    double *P;
};

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
    // テンプレート音声読み込み
    VOICE voice[] ={
        { "a.wav", NULL, NULL, NULL, NULL },
        { "i.wav", NULL, NULL, NULL, NULL },
        { "u.wav", NULL, NULL, NULL, NULL },
        { "e.wav", NULL, NULL, NULL, NULL },
        { "o.wav", NULL, NULL, NULL, NULL },
    };
    const unsigned int voice_size = sizeof(voice)/sizeof(VOICE);

    WAVEFORMAT wavefmt;
    for( int i = 0; i < voice_size; ++i ){
        voice[i].buf = read_wav( voice[i].file, &wavefmt );
    }

    fprintf( stderr,"L = %d\n", L);

    const int f_s = wavefmt.rate;
    fprintf( stderr,"f_s = %d\n", wavefmt.rate );

    const int N = wavefmt.data_size / wavefmt.block;
    fprintf( stderr,"N = %d\n", N);

    for( int i = 0; i < voice_size; ++i ){
        voice[i].x = ( double* )calloc( 1, (N+MAXL) * sizeof(double) ) + MAXL;
        voice[i].a = (double*)calloc( 1, (L+1)*sizeof(double) );
        voice[i].P = (double*)calloc( 1, (L+1)*sizeof(double) );

        for( int i2 = 0; i2 < N; ++i2 ) voice[i].x[i2] = (double)voice[i].buf[i2];
    }

    const unsigned int note_size = sizeof(notes)/sizeof(NOTE);

    WAVEFORMAT wavefmt2 = wavefmt;
    wavefmt2.data_size = (unsigned int)( note_size * NOTELNG * wavefmt2.avgbyte );
    wavefmt2.total_size = sizeof( WAVEFORMAT ) + wavefmt2.data_size - 8;

    const int N2 = wavefmt2.data_size / wavefmt2.block;
    fprintf( stderr,"N2 = %d\n", N2);

    double* err  = ( double* )calloc( 1, N2 * sizeof(double) );
    double* x2 = ( double* )calloc( 1, (N2+MAXL)*sizeof(double) ) + MAXL;
    short* buf2 = ( short* )calloc( 1, wavefmt2.data_size );

    // LPC 係数
    for( int i = 0; i < voice_size; ++i ){
        LevinsonDurbin( voice[i].a, voice[i].P, voice[i].x, N );
    }

    int i = 0;
    const int duration = (int)(f_s*NOTELNG);
    int pre_v = VOICE_R;
    int pre_s = SCALE_R;
    for( int n = 0; n < note_size ; ++n ){
        const int v = notes[ n ].voice;
        const int s = notes[ n ].scale;
        if( v != pre_v || s != pre_s ) i = 0;
        pre_v = v;
        pre_s = s;
        if( s != SCALE_R ){

            // 予測誤差 err[i] の作成
            // 周期 T のパルス音(三角波)とする
            const double f = scale_freq[ notes[ n ].scale ] / pow(2,(4-OCTAVE)); // 周波数
            const int T = (int)( f_s/ f ); // 周期
            fprintf( stderr, "%02d: v = %c, f = %5.1lf Hz, T = %d\n", n, *voice[v].file, f, T );
            for( int i2 = 0 ; i2 < duration; ++i, ++i2 ){
                if( i % T == 0 ){
                    // 三角波作成
                    for( int i3 = 0 ; i3 < PULSEWIDTH; ++i3 ) err[ duration*n + i2 + i3 ] = (double)PULSEAMP*i3/PULSEWIDTH;
                }
                err[ duration*n + i2 ] += nrand(0,ERRSIGMA2);
            }

            // 自己回帰
            AR( x2 + duration*n, voice[v].a, err + duration*n, duration );

            // ゲイン調整
            for( int i2 = 0 ; i2 < duration; ++i2 ){
                x2[ duration*n + i2 ] *= VOICEGAIN[v];
            }
        }
        else{
            fprintf( stderr, "%02d: R\n", n );
        }
    }

    for( int i = 0; i < N2; ++i ) buf2[i] = (short)(x2[i]*GAIN);
    save_wav( "D-FILTER-4-5-ar.wav", &wavefmt2, buf2 );

    for( int i = 0; i < N2; ++i ) buf2[i] = (short)(err[i]*GAIN);
    save_wav( "D-FILTER-4-5-err.wav", &wavefmt2, buf2 );

    for( int i = 0; i < voice_size; ++i ){
        free( voice[i].buf );
        free( voice[i].x-MAXL );
        free( voice[i].a );
        free( voice[i].P );
    }
    free( err );
    free( x2-MAXL );
    free( buf2 );

    return 0;
}
