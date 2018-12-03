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

    for(int i=0;i < N; ++i ){
        x[i] = ? ;
    }

    // ���r���\���E�_�[�r��(Levinson-Durbin)�E�A���S���Y��
    for(int n=0; n <= L; ++n ){
        R[n] = ACR( n, x, N );
    }
    double e = ? ;
    double W = ? ;
    for( int n = 1; n <= L; ++n ){

        for(int i = 1; i<=n; ++i ) a2[i] = ? ;
        P[n] = ? ;
        a[n] = ? ;
        for(int i = 1; i<=n-1; ++i ){
            a[i] = ? ;
        }
        e = ? ;
        W = R[n+1];
        for(int i = 1; i<=n; ++i ){
            W += ? ;
        }
    }

    printf("LPC�W��\n");
    for( int n = 1; n <= L; ++n ){
        printf( "a[%d] = %lf\n", n, a[n] );
    }

    printf("PARCOR�W��\n");
    for( int n = 1; n <= L; ++n ){
        printf( "P[%d] = %lf\n", n, P[n] );
    }

    FILE* file = fopen( "DFILTER-4-1-x.csv", "wb");
    if( file == NULL ){
        printf( "�t�@�C�����J���܂���");
        exit(1);
    }
    for( int i = 0; i <Nout ; ++i ){
        fprintf( file, "%lf\n", x[i] );
    }
    fclose(file);

    return 0;
}
    
