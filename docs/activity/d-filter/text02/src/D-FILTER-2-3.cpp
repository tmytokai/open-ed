#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ���g������(�U������)�̌v�Z
double H( const double w )
{
    // �T���v�����O���g�� [Hz]
    const double fs = 22050;  

    // FIR �t�B���^��
    const int L = ? ;

    const int C = ? ;

    // �T���v�����O�Ԋu(�b)
    const double tau = ?;

    // out �͊֐��̏o��
    double out = ?;
    for( int i = 1; i <=C; ++i ){
        out += ?;
    }

    return out;
}

int main()
{
    const double fs = 22050;

    const int N = 200;
    const double wmax = M_PI*fs;
    FILE* f = fopen( "D-FILTER-2-3.csv", "wb");
    for( int i = 0; i <N ; ++i ){
        double w = wmax*i/N;
        fprintf( f, "%lf, %lf\n", w/(2*M_PI), H(w) );
    }
    fclose(f);

    return 0;
}
