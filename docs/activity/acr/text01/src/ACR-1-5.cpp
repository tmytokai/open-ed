#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// DFT
void DFT( const double* f, double* A, double* B, const int N )
{
    ?
}

// IDFT
void IDFT( const double* A, const double* B, double* f, const int N )
{
    ?
}

// ���ȑ��� R[n]
double ACR( const int n, const double* f, const int N )
{
    // ���K 1-1 �̓��e���R�s�[����
}

int main()
{
    const int N = 45;
    double f[N];
    double A[N];
    double B[N];
    double P[N];
    double R[N];

    for(int i=0;i < N; ++i ){
        // ���K 1-4 �œ��͂��������R�s�[����
        f[i] = ? ;
    }

    // �M����DFT
    DFT(f,A,B,N);

    // �p���[�X�y�N�g�������߂�
    for( int k = 0; k < N; ++k ){
        P[k] = ? ;
    }

    // �p���[�X�y�N�g����IDFT
    memset( B, 0, sizeof(double)*N ); // �������� B[k] ���[���N���A���čė��p����
    IDFT(P,B,R,N);

    FILE* file = fopen( "ACR-1-5-P.csv", "wb");
    if( file == NULL ){
        printf( "�t�@�C�����J���܂���");
        exit(1);
    }
    for( int i = 0; i <N ; ++i ){
        fprintf( file, "%d,%lf\n", i,P[i] );
    }
    fclose(file);

    file = fopen( "ACR-1-5-R.csv", "wb");
    if( file == NULL ){
        printf( "�t�@�C�����J���܂���");
        exit(1);
    }
    for( int i = 0; i <N ; ++i ){
        fprintf( file, "%d,%lf\n", i,R[i] );
    }
    fclose(file);

    return 0;
}
    
