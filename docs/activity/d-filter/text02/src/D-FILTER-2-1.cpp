#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    // �T���v�����O���g�� [Hz]
    const double fs = ?;  

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

    FILE* f = fopen( "D-FILTER-2-1.csv", "wb");
    for( int i = 0; i < L ; ++i ){
        fprintf( f, "%d, %lf\n", i, h[i] );
    }
    fclose(f);

    return 0;
}
