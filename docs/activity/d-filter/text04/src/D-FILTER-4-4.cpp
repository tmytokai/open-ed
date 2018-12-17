#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


///////////////////////////
// ��������

const int L = 100; // ���`�\������

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

// ���`�\���l
void HATX( double *hatx, // ���`�\���l
           const double *a, // LPC �W��
           const double *x, // ����
           const int N )
{
    // ���K 4-2 �ŗ\���l�����߂Ă��镔�����R�s�[����

}

// ���`�\���덷
void ERR( double *err, // ���`�\���덷
           const double *a, // LPC �W��
           const double *x, // ����
           const int N )
{
    // ���K 4-3 �ŗ\���덷�����߂Ă��镔�����R�s�[����

}

// �����܂�
///////////////////////////

const double STARTPOS = 1.0;  // wave �t�@�C���̓ǂݍ��݊J�n�ʒu (�b)
const double DURATION = 0.5;  // wave �t�@�C���̓ǂݍ��݃T�C�Y (�b)
const int MAXHZ = 8000; // wave �t�@�C���Ɋ܂܂��ő���g�� (Hz)

const int MAXL = 256; // ���`�\�������̍ő�l
const double ERRGAIN = 100.0; // ���`�\���덷�̃Q�C��

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
