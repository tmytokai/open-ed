#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


///////////////////////////
// ��������

const int L = 100; // ���`�\������
const int OCTAVE = 4; // �I�N�^�[�u
const double VOICEGAIN[] = {
    1.0, // "�A"�̉���
    1.0, // "�C"�̉���
    1.0, // "�E"�̉���
    1.0, // "�G"�̉���
    1.0  // "�I"�̉���
};

// ���ȑ��� R[n]
double ACR( const int n, const double* f, const int N )
{
    // ���ȑ��ւ̉��K�ō쐬���� ACR �֐��̒��g���R�s�[����

}

// ���r���\���E�_�[�r���E�A���S���Y��
void LevinsonDurbin(
    double *a,// LPC �W��
    double *P, // PARCOR(�p�[�R�[��)�W��
    const double* x, // ����
    const int N )
{
    double R[L+1]; // ���ȑ��֊֐�
    double a2[L+1];

    // ���K 4-1 �̃��r���\���E�_�[�r���E�A���S���Y�����R�s�[����

}

// AR ���f��
void AR( double *x, // AR ���f���o��
         const double *a, // LPC �W��
         const double *err, // ���� (���`�\���덷)
         const int N )
{
    for(int i=0;i < N; ++i ){
        x[i] = ? ;
        for( int n = 1; n <= L; ++n ){
            x[i] += ? ;
        }
        x[i] += ? ;
    }
}

// �����܂�
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

// �o�͉����̓��e��ς��������͈ȉ����C������
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

const double STARTPOS = 1.0;  // wave �t�@�C���̓ǂݍ��݊J�n�ʒu (�b)
const double DURATION = 0.5;  // wave �t�@�C���̓ǂݍ��݃T�C�Y (�b)
const int MAXHZ = 8000; // wave �t�@�C���Ɋ܂܂��ő���g�� (Hz)

const int MAXL = 256; // ���`�\�������̍ő�l
const double NOTELNG = 0.5; // 1 ���̒���(�b)
const double ERRAMP = 100.0; // ����(���`�\���덷)�̃C���p���M���̑傫��
const double GAIN = 1.0; // �o�͂̃Q�C��
const double ERRGAIN = 50.0; // ���`�\���덷�̃Q�C��
const double scale_freq[]={ 261.6, 293.7, 329.6, 349.2, 392.0, 440.0, 493.9 };

struct VOICE
{
    char file[64];
    short* buf;
    double* x;
    double *a;
    double *P;
};

// �W�� WAVE �w�b�_ ( 44 byte )
struct WAVEFORMAT
{
    char riff[ 4 ];             // = "RIFF"
    unsigned int total_size;    // �S�̃T�C�Y
    char fmt[ 8 ];              // "WAVEfmt "
    unsigned int fmt_size;      // fmt �`�����N�T�C�Y
    unsigned short  format;     // �t�H�[�}�b�g�̎��
    unsigned short  channel;    // �`�����l��
    unsigned int   rate;        // �T���v�����O���[�g
    unsigned int   avgbyte;     // rate * block
    unsigned short  block;      // channels * bit / 8
    unsigned short  bit;        // �r�b�g��
    char data[ 4 ];             // = "data"
    unsigned int data_size;     // data �`�����N�T�C�Y
};

short* read_wav( const char* file, WAVEFORMAT *wavefmt )
{
    FILE * fin = fopen( file, "rb" );
    if( !fin ){
        fprintf( stderr, "�t�@�C���I�[�v���Ɏ��s���܂���\n" );
        exit(EXIT_FAILURE);
    }

    // �t�H�[�}�b�g�擾
    size_t ret = fread( wavefmt, 1, sizeof( WAVEFORMAT ) - 8, fin );

    if( ret != sizeof( WAVEFORMAT ) -8 ){
       fprintf( stderr, "�w�b�_�����Ă��܂�\n" );
       exit(EXIT_FAILURE);
    }
    if( wavefmt->riff[ 0 ] != 'R' || wavefmt->riff[ 1 ] != 'I' ){
        fprintf( stderr, "Wave �t�@�C���ł͂���܂���\n" );
        exit(EXIT_FAILURE);
    }
    if( wavefmt->channel != 1 ){
        fprintf( stderr, "�X�e���I�����͎g�p�ł��܂���\n" );
        exit(EXIT_FAILURE);
    }
    if( wavefmt->rate < MAXHZ*2 ){
        fprintf( stderr, "�T���v�����O���g�����Ⴂ�ł�\n" );
        exit(EXIT_FAILURE);
    }
    if( wavefmt->bit != 16 ){
        fprintf( stderr, "8bit�����͎g�p�ł��܂���\n" );
        exit(EXIT_FAILURE);
    }

    // data �܂ŃX�L�b�v
    size_t pos = sizeof( WAVEFORMAT ) - 8;
    while( pos < 200 && ( wavefmt->data[0] != 'd' || wavefmt->data[1] != 'a' ) ){
        fseek( fin, pos++, SEEK_SET );
        ret = fread( wavefmt->data, 1, 4, fin );
    }

    if( wavefmt->data[ 0 ] != 'd' || wavefmt->data[ 1 ] != 'a' ){
        fprintf( stderr, "�f�[�^������܂���\n" );
        exit(EXIT_FAILURE);
    }

    // �f�[�^�T�C�Y���擾
    ret = fread( &wavefmt->data_size, 1, sizeof( unsigned int ), fin );

    const double duration = (double)wavefmt->data_size / wavefmt->avgbyte;
    if( duration < STARTPOS + DURATION ){
        fprintf( stderr, "�^�����Ԃ��Z���ł�\n" );
        exit(EXIT_FAILURE);
    }

    // �t�H�[�}�b�g�Đݒ�
    wavefmt->fmt_size = 16;
    wavefmt->data_size = (unsigned int)( DURATION * wavefmt->avgbyte );
    wavefmt->total_size = sizeof( WAVEFORMAT ) + wavefmt->data_size - 8;

    // STARTPOS �b���� DURATION �b�Ԃ̃f�[�^�ǂݍ���
    short* buf = ( short* )calloc( 1, wavefmt->data_size );
    fseek( fin, (unsigned int)(STARTPOS * wavefmt->avgbyte), SEEK_CUR );
    ret = fread( buf, 1, wavefmt->data_size, fin );
    if( ret != wavefmt->data_size ){
       fprintf( stderr, "�f�[�^�̓ǂݍ��݂Ɏ��s���܂���\n" );
       exit(EXIT_FAILURE);
    }

    fclose( fin );

    return buf;
}

void save_wav( const char* file, const WAVEFORMAT* wavefmt, const short* buf )
{
    FILE* fout = fopen( file, "wb" );
    if( !fout ){
        fprintf( stderr, "%s �̃I�[�v���Ɏ��s���܂���\n", file );
        exit(EXIT_FAILURE);
    }
    fwrite( wavefmt, 1, sizeof( WAVEFORMAT ), fout );
    fwrite( buf, 1, wavefmt->data_size , fout );
    fclose( fout );
    fprintf( stderr, "save to %s\n", file);
}

int main()
{
    // �e���v���[�g�����ǂݍ���
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

    // LPC �W��
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

            // �\���덷
            const double f = scale_freq[ notes[ n ].scale ] / pow(2,(4-OCTAVE));
            const int T = (int)( f_s/ f );
            fprintf( stderr, "%02d: v = %c, f = %5.1lf Hz, T = %d\n", n, *voice[v].file, f, T );
            for( int i2 = 0 ; i2 < duration; ++i, ++i2 ){
                if( i % T == 0 ) err[ duration*n + i2 ] = ERRAMP;
            }

            // ���ȉ�A
            AR( x2 + duration*n, voice[v].a, err + duration*n, duration );

            // �Q�C������
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

    for( int i = 0; i < N2; ++i ) buf2[i] = (short)(err[i]*ERRGAIN);
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
