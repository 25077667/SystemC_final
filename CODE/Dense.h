#include <iostream>
#include "define.h"
#include "systemc.h"

using namespace std;

// vvvvv put your code here vvvvv
SC_MODULE(Dense)
{
    sc_in_clk clk;
    sc_in<bool> rst;

    sc_in<bool> dense_valid;
    sc_in<MUL_DATA_TYPE> dense_data;

    sc_out<DATA_TYPE> result;
    sc_out<bool> output_valid;

    void run();

    // vvvvv my code vvvvv
    int state = 0;
    DATA_TYPE data[41854];

    int m = 0, index = 0, count = 0;
    MUL_DATA_TYPE MaxP2[16][4 * 4];
    MUL_DATA_TYPE Flatten[16 * 4 * 4];
    MUL_DATA_TYPE Dense1[120];
    MUL_DATA_TYPE Dense2[84];
    MUL_DATA_TYPE Dense3[10];
    // ^^^^^ my code ^^^^^

    SC_CTOR(Dense)
    {
        // vvvvv my code vvvvv
        SC_METHOD(run);
        sensitive << clk.pos();
        // ^^^^^ my code ^^^^^
    }
};
// ^^^^^ put your code here ^^^^^
