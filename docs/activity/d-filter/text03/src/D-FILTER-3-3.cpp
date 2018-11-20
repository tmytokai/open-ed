#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double z[256] = {0};

    // �T���v�����O���g�� [Hz]
    const double fs = ? ;

    // �C���p���X���� h[i] �� h(t) �� fs [Hz] �� 0.01 �b�ԃT���v�����O������Ƀт��|�����l�Ƃقڈ�v����
    // i �͈̔͂� 0 <= i < N �ƂȂ�
    const int N = (int)(0.01 * fs); // 0.01 [�b] * fs [Hz]
    double h[ N ];

    // �J�b�g�I�t���g�� [Hz]
    const double fc = ? ;

    // �T���v�����O�Ԋu [�b]
    const double tau = ? ;

    // IIR �t�B���^���� (����� 1 ��)
    const int L = 1;

    // 1�� IIR ���[�p�X�t�B���^�W�����v�Z
    // �~������ M_PI ���g�p����
    double a[2] = {0};
    double b[2] = {0};
    a[1] = ? ;
    b[0] = ? ;
    b[1] = ? ;

    // L �� IIR �t�B���^�̃C���p���X����
    // ���͐M�����f�W�^���C���p���X�M�� ��[i] = {1,0,0,0,0,....} �ɂ����
    // �o�͐M���� h[i] �ƂȂ�
    // z[k] �� k �����O�́��̒l
    for( int i = 0; i < N; ++i ){

        // �O�i�t�B�[�h�o�b�N��
        if( i == 0 ) z[0] = 1;
        else z[0] = 0;
        for( int k = 1; k <= L; ++k ) z[0] += ? ;

        // ��i�t�B�[�h�t�H���[�h��
        h[i] = 0;
        for( int k = 0; k <= L; ++k ) h[i] += ? ;

        // �o�b�t�@�V�t�g
        for( int k = 1; k <= L; ++k ) z[k] = ? ;
    }

    // �C���p���X������csv�t�@�C���ɏo��
    FILE* f = fopen( "D-FILTER-3-3.csv", "wb");
    for( int i = 0; i < N ; ++i ){
        fprintf( f, "%d, %lf\n", i, h[i] );
    }
    fclose(f);

    return 0;
}
