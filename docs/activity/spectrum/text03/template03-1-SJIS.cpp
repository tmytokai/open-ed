#include <stdio.h>
#include <stdlib.h>
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
    if( wavefmt.rate != 8000 ){
        fprintf( stderr, "�T���v�����O���g���� 8000 Hz�ł���܂���\n" );
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

    double* f = ( double* )malloc( lng * sizeof(double) );
    for( int i = 0; i < lng; ++i ) f[i] = (double)buf[i];

    //----------------------------------------------
    // �������猊���ߊJ�n

    // f[N] �� f_s = 8000 [Hz] �� 2 �b�ԃT���v�����O���������̃f�B�W�^���M���Ƃ���

    // �{���Ȃ�ΐl�Ԃ̐��͎������M���ł͂Ȃ������� N �̎������M���Ƃ݂Ȃ��� DFT ����
    const int N = 2 * 8000; // 2 [�b] * 8000 [Hz]

    // DFT �W���̎��������̌v�Z
    double A[N];
    ? ;

    // DFT �W���̋��������̌v�Z
    double B[N];
    ? ;

    // �U���X�y�N�g���v�Z
    double abs_C[N];
    ? ;

    // �ʑ��X�y�N�g���v�Z
    double arg_C[N];
    ? ;

    // k -> f_k [Hz] �ɕϊ�
    int f_k[N];
    for( int k = 0; k < N; ++k ) f_k[k] = ? ;

    // �����܂�
    //----------------------------------------------

    FILE *csv = fopen( "out.csv", "w" );
    for( int k = 0; k < N/2; ++k ){
        fprintf( csv, "%d, %lf, %lf\n", f_k[k], abs_C[k], arg_C[k] );
    }
    fclose(csv);
    
    return 0;
}
