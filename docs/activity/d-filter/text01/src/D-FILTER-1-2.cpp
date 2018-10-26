#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.1415926535
#endif

// �W���I�� WAVE �w�b�_ ( 44 byte )
typedef struct
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
} WAVEFORMAT;

int main()
{
    FILE * fin = fopen( "D-FILTER-1-1.wav", "rb" );
    if( !fin ){
        fprintf( stderr, "�t�@�C���I�[�v���Ɏ��s���܂���\n" );
        exit(EXIT_FAILURE);
    }

    WAVEFORMAT wavefmt;
    size_t ret = fread( &wavefmt, 1, sizeof( WAVEFORMAT ) - 8, fin );
    if( ret != sizeof( WAVEFORMAT ) -8 ){
       fprintf( stderr, "�w�b�_�����Ă��܂�\n" );
       exit(EXIT_FAILURE);
    }

    // data �܂ŃX�L�b�v
    size_t pos = sizeof( WAVEFORMAT ) - 8;
    while( pos < 200 && ( wavefmt.data[0] != 'd' || wavefmt.data[1] != 'a' ) ){
        fseek( fin, pos++, SEEK_SET );
        ret = fread( wavefmt.data, 1, 4, fin );
    }
    ret = fread( &wavefmt.data_size, 1, sizeof( unsigned int ), fin );
    wavefmt.fmt_size = 16;

    if( wavefmt.data[ 0 ] != 'd' || wavefmt.data[ 1 ] != 'a' ){
        fprintf( stderr, "�w�b�_�����Ă��܂�\n" );
        exit(EXIT_FAILURE);
    }
    if( wavefmt.channel != 1 ){
        fprintf( stderr, "�X�e���I�����͎g�p�ł��܂���\n" );
        exit(EXIT_FAILURE);
    }
    if( wavefmt.bit != 16 ){
        fprintf( stderr, "8bit�����͎g�p�ł��܂���\n" );
        exit(EXIT_FAILURE);
    }
    if( wavefmt.rate != 22050 ){
        fprintf( stderr, "�T���v�����O���g���� 22050 Hz�ł���܂���\n" );
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

    //----------------------------------------------
    // �������猊���ߊJ�n

    // �T���v�����O���g�� [Hz]
    const double fs = 22050;  

    // x[i] �� fs = 22050 [Hz] �� 5 �b�ԃT���v�����O���������̃f�B�W�^���M���Ƃ���
    // i �͈̔͂� 0 <= i < N �ƂȂ�
    const int N = 5 * fs; // 10 [�b] * fs [Hz]

    // FIR �t�B���^����(�^�b�v��)
    const int L = ? ;

    // �t�B���^�W�� = �C���p���X����
    double h[L];

    // �J�b�g�I�t���g�� [Hz]
    const double fc = ? ;

    // FIR ���[�p�X�t�B���^�W�����v�Z
    // �~������ M_PI ���g�p����
    const int C = (L-1)/2;
    const double Alpha = ? ;
    h[C] = ? ;
    for( int i = 1; i <= ? ; ++i ){
        h[C-i] = h[C+i] = ? ;
    }

    // FIR �t�B���^
    // �o�͐M���� y[i]
    // i-j �����̏ꍇ�� x[i-j] = 0 �Ɗ��ɂȂ��Ă���̂ŁA�ꍇ���������ɂ��̂܂܎g���� OK
    for( int i = 0; i < N; ++i ){
        y[i] = ?;
        for( int j = 0; j < ? ; ++j ) y[i] += ? ;
    }

    // �����܂�
    //----------------------------------------------

    FILE* fout = fopen( "D-FILTER-1-2-out.wav", "wb" );
    if( !fout ){
        fprintf( stderr, "�t�@�C���I�[�v���Ɏ��s���܂���\n" );
        exit(EXIT_FAILURE);
    }
    for( int i = 0; i < lng; ++i ) buf[i] = (short)(y[i]*0.8);

    fwrite( &wavefmt, 1, sizeof( WAVEFORMAT ), fout );
    fwrite( buf, 1, wavefmt.data_size , fout );
    fclose( fout );
    
    return 0;
}
