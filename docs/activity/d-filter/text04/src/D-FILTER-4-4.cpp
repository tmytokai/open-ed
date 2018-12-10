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

// ���ȑ��� R[n]
double ACR( const int n, const double* f, const int N )
{
    // ���ȑ��ւ̉��K�ō쐬���� ACR �֐��̒��g���R�s�[����
}

int main()
{
    FILE * fin = fopen( "D-FILTER-4-4.wav", "rb" );
    if( !fin ){
        fprintf( stderr, "�t�@�C���I�[�v���Ɏ��s���܂���\n" );
        exit(EXIT_FAILURE);
    }

    // �t�H�[�}�b�g�擾
    WAVEFORMAT wavefmt;
    size_t ret = fread( &wavefmt, 1, sizeof( WAVEFORMAT ) - 8, fin );

    if( ret != sizeof( WAVEFORMAT ) -8 ){
       fprintf( stderr, "�w�b�_�����Ă��܂�\n" );
       exit(EXIT_FAILURE);
    }
    if( wavefmt.riff[ 0 ] != 'R' || wavefmt.riff[ 1 ] != 'I' ){
        fprintf( stderr, "Wave �t�@�C���ł͂���܂���\n" );
        exit(EXIT_FAILURE);
    }
    if( wavefmt.channel != 1 ){
        fprintf( stderr, "�X�e���I�����͎g�p�ł��܂���\n" );
        exit(EXIT_FAILURE);
    }
    if( wavefmt.rate < MAXHZ*2 ){
        fprintf( stderr, "�T���v�����O���g�����Ⴂ�ł�\n" );
        exit(EXIT_FAILURE);
    }
    if( wavefmt.bit != 16 ){
        fprintf( stderr, "8bit�����͎g�p�ł��܂���\n" );
        exit(EXIT_FAILURE);
    }

    // data �܂ŃX�L�b�v
    size_t pos = sizeof( WAVEFORMAT ) - 8;
    while( pos < 200 && ( wavefmt.data[0] != 'd' || wavefmt.data[1] != 'a' ) ){
        fseek( fin, pos++, SEEK_SET );
        ret = fread( wavefmt.data, 1, 4, fin );
    }

    if( wavefmt.data[ 0 ] != 'd' || wavefmt.data[ 1 ] != 'a' ){
        fprintf( stderr, "�f�[�^������܂���\n" );
        exit(EXIT_FAILURE);
    }

    // �f�[�^�T�C�Y���擾
    ret = fread( &wavefmt.data_size, 1, sizeof( unsigned int ), fin );

    if( (double)wavefmt.data_size / wavefmt.avgbyte < STARTPOS + DURATION ){
        fprintf( stderr, "�^�����Ԃ��Z���ł�\n" );
        exit(EXIT_FAILURE);
    }

    // �t�H�[�}�b�g�Đݒ�
    wavefmt.fmt_size = 16;
    wavefmt.data_size = (unsigned int)( DURATION * wavefmt.avgbyte );
    wavefmt.total_size = sizeof( WAVEFORMAT ) + wavefmt.data_size - 8;

    // �f�[�^�ǂݍ���
    short* buf = ( short* )malloc( wavefmt.data_size );
    fseek( fin, (unsigned int)(STARTPOS * wavefmt.avgbyte), SEEK_CUR );
    ret = fread( buf, 1, wavefmt.data_size, fin );
    if( ret != wavefmt.data_size ){
       fprintf( stderr, "�f�[�^�̓ǂݍ��݂Ɏ��s���܂���\n" );
       exit(EXIT_FAILURE);
    }

    fclose( fin );

    // ���K�Ŏg���f�[�^��z����쐬
    const int f_s = wavefmt.rate;
    fprintf( stderr,"f_s = %d\n", wavefmt.rate );

    const int N = wavefmt.data_size / wavefmt.block;
    fprintf( stderr,"N = %d\n", N);

    double* X = ( double* )calloc( 1, (N+MAXL) * sizeof(double) );
    double* x = X+MAXL;
    for( int i = 0; i < N; ++i ) x[i] = (double)buf[i];

    double* hatx = ( double* )malloc( N * sizeof(double) );

    //----------------------------------------------
    // �������牉�K�J�n

    // D-FILTER-4-4.wav �� 1.0 �b���_���� 0.5 �b�Ԃ��������M����؂�o����
    // ���� N �̃f�B�W�^���M�� x[0] �` x[N-1] ���쐬��

    const int L = 10; // ���`�\������
    double R[L+1]; // ���ȑ��֊֐�
    double P[L+1]; // PARCOR(�p�[�R�[��)�W��
    double a[L+1]; // LPC �W��
    double a2[L+1];

    // ���K 4-1 �̃��r���\���E�_�[�r��(Levinson-Durbin)�E�A���S���Y�����R�s�[����


    // ���`�\�����f��
    // hatx �͒�`��


    // �����܂�
    //----------------------------------------------

    printf("LPC�W��\n");
    for( int n = 1; n <= L; ++n ){
        printf( "a[%d] = %lf\n", n, a[n] );
    }

    FILE* fout = fopen( "D-FILTER-4-4-out.wav", "wb" );
    if( !fout ){
        fprintf( stderr, "�t�@�C���I�[�v���Ɏ��s���܂���\n" );
        exit(EXIT_FAILURE);
    }
    fwrite( &wavefmt, 1, sizeof( WAVEFORMAT ), fout );
    fwrite( buf, 1, wavefmt.data_size , fout );
    fclose( fout );

    for( int i = 0; i < N; ++i ) buf[i] = (short)hatx[i];
    fout = fopen( "D-FILTER-4-4-hatx.wav", "wb" );
    if( !fout ){
        fprintf( stderr, "�t�@�C���I�[�v���Ɏ��s���܂���\n" );
        exit(EXIT_FAILURE);
    }
    fwrite( &wavefmt, 1, sizeof( WAVEFORMAT ), fout );
    fwrite( buf, 1, wavefmt.data_size , fout );
    fclose( fout );

    free(buf);
    free(X);

    return 0;
}
