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

    // �����̏�ɉ��K 2-1 �ŏ������C���p���X�����̌v�Z�������̂܂܃R�s�[����

    const int N = 200;
    const double wmax = M_PI*fs;
    FILE* f = fopen( "D-FILTER-2-2.csv", "wb");
    for( int i = 0; i <N ; ++i ){
        double w = wmax*i/N;
        fprintf( f, "%lf, %lf\n", w/(2*M_PI), H(w,h,L,C,fs) );
    }
    fclose(f);

    return 0;
}
