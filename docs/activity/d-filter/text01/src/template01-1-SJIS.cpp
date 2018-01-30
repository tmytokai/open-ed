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
    FILE * fin = fopen( "test.wav", "rb" );
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
    if( wavefmt.rate != 11025 ){
        fprintf( stderr, "�T���v�����O���g���� 11025 Hz�ł���܂���\n" );
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

    // x[i] �� fs = 11025 [Hz] �� 10 �b�ԃT���v�����O���������̃f�B�W�^���M���Ƃ���
    // i �͈̔͂� 0 <= i < N �ƂȂ�
    const int fs = 11025;  // �T���v�����O���g�� [Hz]
    const int N = 10 * fs; // 10 [�b] * fs [Hz]

    // ��Z��̏搔 a �� b ���Z�b�g
    // a �� b �͕����ł������A|a| + |b| �� 1.0 �𒴂��Ȃ��悤�ɂ���
    const double a = ?;
    const double b = ?;

    // �x���f�q�̒x������ k �̌v�Z
    const double delay = ?; // �x��b��
    const int k = (int)( delay * fs ); // k = �x��b�� * fs

    // �f�B�W�^�����`�t�B���^ H(z) = a + b�Ez^{-k}
    // �o�͐M���� y[i]
    // i-k �����̏ꍇ�� x[i-k] = 0 �Ɗ��ɂȂ��Ă���̂ŁA�ꍇ���������ɂ��̂܂܎g���� OK
    for( int i = 0; i < N; ++i ){
        y[i] = ?
    }

    // �����܂�
    //----------------------------------------------

    FILE* fout = fopen( "out1.wav", "wb" );
    if( !fout ){
        fprintf( stderr, "�t�@�C���I�[�v���Ɏ��s���܂���\n" );
        exit(EXIT_FAILURE);
    }
    for( int i = 0; i < lng; ++i ) buf[i] = (short)y[i];

    fwrite( &wavefmt, 1, sizeof( WAVEFORMAT ), fout );
    fwrite( buf, 1, wavefmt.data_size , fout );
    fclose( fout );
    
    return 0;
}
