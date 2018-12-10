#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ���K���� N( mu, sigma^2)�̏o��
// mu : ����
// sigma : �W���΍� = �㕪�U
double nrand( double mu, double sigma )
{
    // Box-Muller �@���g�p
    double x = sqrt( -2*log( (double)rand()/RAND_MAX ) ) * cos( 2*M_PI*rand()/RAND_MAX ) ;
    return mu + sigma*x;
}

// ���ȑ��� R[n]
double ACR( const int n, const double* f, const int N )
{
    // ���ȑ��ւ̉��K�ō쐬���� ACR �֐��̒��g���R�s�[����
}

int main()
{
    const int L = 4; // ���`�\������
    const int N = 50000;
    const int Nout = 100;
    double X[N+L]={0};
    double *x = X+L; // �M���l
    double R[L+1]; // ���ȑ��֊֐�
    double P[L+1]; // PARCOR(�p�[�R�[��)�W��
    double a[L+1]; // LPC �W��
    double a2[L+1];

    // ���K 4-1 �� x[i] ���R�s�[����
    for(int i=0;i < N; ++i ){
        x[i] = ? ;
    }

    // ���K 4-1 �̃��r���\���E�_�[�r��(Levinson-Durbin)�E�A���S���Y�����R�s�[����


    // ���`�\�����f��
    double hatx[Nout];
    for( int i = 0; i < Nout; ++i ){
        hatx[i] = 0;
        for( int n = 1; n <= L; ++n ){
            hatx[i] += ? ;
        }
        hatx[i] *= ? ;
    }

    printf("LPC�W��\n");
    for( int n = 1; n <= L; ++n ){
        printf( "a[%d] = %lf\n", n, a[n] );
    }

    FILE* file = fopen( "DFILTER-4-2-hatx.csv", "wb");
    if( file == NULL ){
        printf( "�t�@�C�����J���܂���");
        exit(1);
    }
    for( int i = 0; i <Nout ; ++i ){
        fprintf( file, "%d, %lf\n", i, hatx[i] );
    }
    fclose(file);

    return 0;
}
    
