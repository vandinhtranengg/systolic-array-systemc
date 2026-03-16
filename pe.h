#ifndef PE_H
#define PE_H

#include <systemc.h>

SC_MODULE(PE)
{
    sc_in<int> a_in;
    sc_in<int> b_in;
    sc_in<bool> clk;
    sc_in<bool> rst;

    sc_out<int> a_out;
    sc_out<int> b_out;
    sc_out<int> c_out;

    int sum;

    void compute()
    {
        if (rst.read())
        {
            sum = 0;
            a_out.write(0);
            b_out.write(0);
            c_out.write(0);
        }
        else
        {
            int a = a_in.read();
            int b = b_in.read();

            sum += a * b;

            a_out.write(a);
            b_out.write(b);
            c_out.write(sum);
        }
    }

    SC_CTOR(PE)
    {
        sum = 0;
        SC_METHOD(compute);
        sensitive << clk.pos();
    }
};

#endif
