#ifndef SYSTOLIC_ARRAY_H
#define SYSTOLIC_ARRAY_H

#include <systemc.h>
#include "pe.h"

SC_MODULE(SystolicArray3x3)
{
    sc_in<bool> clk;
    sc_in<bool> rst;

    sc_signal<int> a_sig[3][4];
    sc_signal<int> b_sig[4][3];
    sc_signal<int> c_sig[3][3];

    PE* pe[3][3];

    SC_CTOR(SystolicArray3x3)
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                char name[20];
                sprintf(name,"PE_%d_%d",i,j);

                pe[i][j] = new PE(name);

                pe[i][j]->clk(clk);
                pe[i][j]->rst(rst);

                pe[i][j]->a_in(a_sig[i][j]);
                pe[i][j]->a_out(a_sig[i][j+1]);

                pe[i][j]->b_in(b_sig[i][j]);
                pe[i][j]->b_out(b_sig[i+1][j]);

                pe[i][j]->c_out(c_sig[i][j]);
            }
        }
    }
};

#endif
