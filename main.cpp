#include <systemc.h>
#include "systolic_array.h"

int A[3][3] = {
    {1,2,3},
    {4,5,6},
    {7,8,9}
};

int B[3][3] = {
    {1,0,0},
    {0,1,0},
    {0,0,1}
};

int sc_main(int argc, char* argv[])
{
    sc_clock clk("clk",10,SC_NS);
    sc_signal<bool> rst;

    SystolicArray3x3 sa("SA");

    sa.clk(clk);
    sa.rst(rst);

    // Reset array
    rst.write(true);
    sc_start(20, SC_NS);

    rst.write(false);

    int cycles = 7;

    for(int t=0; t<cycles; t++)
    {
        // feed A with skew
        for(int i=0;i<3;i++)
        {
            if(t-i >= 0 && t-i < 3)
                sa.a_sig[i][0].write(A[i][t-i]);
            else
                sa.a_sig[i][0].write(0);
        }

        // feed B with skew
        for(int j=0;j<3;j++)
        {
            if(t-j >= 0 && t-j < 3)
                sa.b_sig[0][j].write(B[t-j][j]);
            else
                sa.b_sig[0][j].write(0);
        }

        sc_start(10,SC_NS);
    }

    cout << "Result Matrix C:" << endl;

    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            cout << sa.c_sig[i][j].read() << " ";
        }
        cout << endl;
    }

    return 0;
}
