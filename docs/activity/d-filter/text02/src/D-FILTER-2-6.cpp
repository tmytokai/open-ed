#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

    FILE* f = fopen( "D-FILTER-2-6.csv", "wb");
    for( int i = 0; i < L ; ++i ){
        fprintf( f, "%d, %lf\n", i, h[i] );
    }
    fclose(f);

    return 0;
}
