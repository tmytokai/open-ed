#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ���g������(�U������)�̌v�Z
double H( const double w, const double* h, const int L, const int C, const double fs )
{
    // �T���v�����O�Ԋu(�b)
    double tau = ?;

    // out �͊֐��̏o��
    double out = ?;
    for( int i = 1; i <=C; ++i ){
        out += ?;
    }

    return out;
}

int main()
{
    // �T���v�����O���g�� [Hz]
    const double fs = 22050;  

    // �J�b�g�I�t���g�� [Hz]
    const double fc = ? ;

    // ���K���J�b�g�I�t���g��
    const double Alpha = ? ;

    // FIR �t�B���^��
    const int L = ? ;

    // �C���p���X����
    double h[L];

    // FIR ���[�p�X�t�B���^�̃C���p���X�����̌v�Z
    // �~������ M_PI ���g�p����
    const int C = (L-1)/2;
    h[C] = ? ;
    for( int i = 1; i <= ? ; ++i ){
        h[C-i] = h[C+i] = ? ;
    }

    const int N = 200;
    const double wmax = M_PI*fs;
    FILE* f = fopen( "D-FILTER-2-7.csv", "wb");
    for( int i = 0; i <N ; ++i ){
        double w = wmax*i/N;
        fprintf( f, "%lf, %lf\n", w/(2*M_PI), H(w,h,L,C,fs) );
    }
    fclose(f);

    return 0;
}
