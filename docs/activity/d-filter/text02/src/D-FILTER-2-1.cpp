#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    // FIR�t�B���^����(�^�b�v��)
    const int L = ? ;

    // �C���p���X����
    double h[L];

    // �J�b�g�I�t���g�� [Hz]
    const double fc = ?;

    // �T���v�����O���g�� [Hz]
    const double fs = ?;  

    // �C���p���X�������v�Z
    // �~������ M_PI ���g�p����
    const double Alpha = ?;
    const int C = ?;
    h[C] = ?;
    for( int i = 1; i <= C ; ++i ){
        h[C-i] = h[C+i] = ?;
    }

    FILE* f = fopen( "D-FILTER-2-1.csv", "wb");
    for( int i = 0; i < L ; ++i ){
        fprintf( f, "%d, %lf\n", i, h[i] );
    }
    fclose(f);

    return 0;
}
